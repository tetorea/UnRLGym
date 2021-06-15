// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctionUtils.h"

TArray<uint8> UBPFunctionUtils::getCameraImage(AActor *actor, UTextureRenderTarget2D* RenderTarget)
{
	UTexture2D* Texture2D = RenderTarget->ConstructTexture2D(actor, FString("Tex2D"), EObjectFlags::RF_NoFlags);
	//FTextureRenderTargetResource *Resource = RenderTarget->GetRenderTargetResource();
	int xx = Texture2D->GetSizeX();
	int yy = Texture2D->GetSizeY();
	GLog->Logf(TEXT("getCameraImage -- Texture size: %d %d"), xx, yy);

	FTexturePlatformData* Data = Texture2D->PlatformData;
	EPixelFormat Format = Data->PixelFormat;
	GLog->Logf(TEXT("getCameraImage -- Pixel format: %d"), (uint8)(Format));	// PF_FloatRGBA = 10

	int32 elementSize = Data->Mips[0].BulkData.GetElementSize();
	int32 elementCount = Data->Mips[0].BulkData.GetElementCount();	// count the number of total bytes!!  = DimX x DimY x Channel x ElementSize
	GLog->Logf(TEXT("getCameraImage -- Number of elements: %d, size of one element: %d"), elementCount, elementSize);
	// 1 byte per element returned BUT I set 16f so it should be 2 bytes

	TArray<uint8> cameraImage;
	cameraImage.Reserve( elementCount ); // number of element in array is = DimX x DimY x NbChannel
	cameraImage.SetNum( elementCount );

	const void* Table = Data->Mips[0].BulkData.LockReadOnly();
	const uint8* camImg = StaticCast<const uint8*>(Table);
	for( long i = 0; i < elementCount; i++ ) cameraImage[i] = camImg[i];
	Data->Mips[0].BulkData.Unlock();

	return cameraImage;
}