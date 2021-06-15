#include <algorithm>

#include "BasicCameraSensor.h"


// Sets default values
ABasicCameraSensor::ABasicCameraSensor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USphereComponent>( TEXT( "Root" ) );
	Camera = CreateDefaultSubobject<USceneCaptureComponent2D>( TEXT( "Camera" ) );
	ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> RenderTargetAsset( TEXT( "/Game/Rooms/Blueprints/Camera_renderTarget2D" ) );
	
	// here you need to have prepared the target asset, type RenderTarget2D. 
	// You can have one for many actors, it is duplicated. 
	// What is not resolved by me: i don't know if it is stable solution or it will crash after many calls
	
	 GLog->Logf(TEXT("BasicCameraSensor -- GetSurfaceHeight(): %f, %f"), RenderTargetAsset.Object->GetSurfaceHeight(), RenderTargetAsset.Object->GetSurfaceWidth());

	RenderTarget = DuplicateObject( RenderTargetAsset.Object, NULL );
	RenderTarget->InitAutoFormat( 1024, 1024 );
	Camera->TextureTarget = RenderTarget;
}

// Called when the game starts or when spawned
void ABasicCameraSensor::BeginPlay()
{
	Super::BeginPlay();

	int X = RenderTarget->GetSurfaceHeight();
	int Y = RenderTarget->GetSurfaceWidth();
	GLog->Logf( TEXT( "BasicCameraSensor -- Size: %d %d" ), X, Y );
	Texture2D = RenderTarget->ConstructTexture2D( this, FString( "Tex2D" ), EObjectFlags::RF_NoFlags );
	//FTextureRenderTargetResource *Resource = RenderTarget->GetRenderTargetResource();
	int xx = Texture2D->GetSizeX();
	int yy = Texture2D->GetSizeY();
	GLog->Logf( TEXT( "BasicCameraSensor -- Texture size: %d %d" ), xx, yy );

	Data = Texture2D->PlatformData;
	EPixelFormat Format = Data->PixelFormat;
	GLog->Logf( TEXT( "BasicCameraSensor -- Pixel format: %d" ), (uint8)(Format) );
	// format of pixel is PFloatRGBA
	
	elementSize = Data->Mips[0].BulkData.GetElementSize();
	elementCount = Data->Mips[0].BulkData.GetElementCount();
	GLog->Logf( TEXT( "BasicCameraSensor -- Number of elements: %d, size of one element: %d" ), elementCount, elementSize);
	// 1 byte per element ??

	cameraImage.Reserve( elementCount * elementSize * 4 );
	cameraImage.SetNum( elementCount * elementSize * 4 );

	GetCameraImage();
}

// Called every frame
void ABasicCameraSensor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicCameraSensor::GetCameraImage()
{
	//elementSize = Data->Mips[0].BulkData.GetElementSize();
	//elementCount = Data->Mips[0].BulkData.GetElementCount();
	//GLog->Logf(TEXT("Number of elements: %d, size of one element: %d"), elementCount, elementSize);

	const void* Table = Data->Mips[0].BulkData.LockReadOnly();
	Data->Mips[0].BulkData.Unlock();

	const uint16* camImg = StaticCast<const uint16*>(Table);
	
	for( long i = 0; i < elementCount * elementSize * 4; i+=4 ) {
		// R G B A
		cameraImage[i] = camImg[i];
		cameraImage[i+1] = camImg[i+1];
		cameraImage[i+2] = camImg[i+2];
		cameraImage[i+3] = camImg[i+3];
	}
	
}