// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicCameraSensor.h"


// Sets default values
ABasicCameraSensor::ABasicCameraSensor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USphereComponent>( TEXT( "Root" ) );
	Camera = CreateDefaultSubobject<USceneCaptureComponent2D>( TEXT( "Camera" ) );
	ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> RenderTargetAsset( TEXT( "/Game/Rooms/Blueprints/CamSensor_RenderTarget2D" ) );
	//here you need to have prepared MyLittleRenderTarget asset, type RenderTarget2D. You can have one for many actors, it is duplicated. What is not resolved by me: i don't know if it is stable solution or it will make crash after many calls

	
	RenderTarget = DuplicateObject( RenderTargetAsset.Object, NULL );
	RenderTarget->InitAutoFormat( 1024, 1024 );
	Camera->TextureTarget = RenderTarget;
	
}

// Called when the game starts or when spawned
void ABasicCameraSensor::BeginPlay()
{
	Super::BeginPlay();
	
	Camera->TextureTarget = RenderTarget;

	int X = RenderTarget->GetSurfaceHeight();
	int Y = RenderTarget->GetSurfaceWidth();
	GLog->Logf( TEXT( "Size: %d %d" ), X, Y );
	Texture2D = RenderTarget->ConstructTexture2D( this, FString( "Tex2D" ), EObjectFlags::RF_NoFlags );
	//FTextureRenderTargetResource *Resource = RenderTarget->GetRenderTargetResource();
	int xx = Texture2D->GetSizeX();
	int yy = Texture2D->GetSizeY();
	GLog->Logf( TEXT( "Texture size: %d %d" ), xx, yy );

	FTexturePlatformData *Data = Texture2D->PlatformData;
	EPixelFormat Format = Data->PixelFormat;
	GLog->Logf( TEXT( "Pixel format: %d" ), (uint8)(Format) );
	//format of pixel is PFloatRGBA

	int size = Data->Mips[0].BulkData.GetElementSize();
	int N = Data->Mips[0].BulkData.GetElementCount();
	GLog->Logf( TEXT( "Number of elements: %d, size of one element: %d" ), N, size );
	//i've got 1 byte size of element

	const void *Table = Data->Mips[0].BulkData.LockReadOnly();
	Data->Mips[0].BulkData.Unlock();

	const uint16 *Tab2 = StaticCast<const uint16*>( Table );
	//ok, quick calculation. I get 8*1024*1024 bytes from 1024*1024 pixels, so one pixel got 8 bytes of data. Format is RGBA, so you can figure it yourself :)
	for( int i = 0; i < xx; i++ ) {
		for( int j = 0; j < yy; j++ ) {
			int k = 4 * (i*yy + j);
			int R = Tab2[k];
			int G = Tab2[k + 1];
			int B = Tab2[k + 2];
			int A = Tab2[k + 3];
		}
	}
	
}

// Called every frame
void ABasicCameraSensor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

