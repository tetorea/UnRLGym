// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "BPFunctionUtils.generated.h"

/**
 * 
 */
UCLASS()
class UNRLGYM_API UBPFunctionUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Camera Sensor")
		static TArray<uint8> getCameraImage(AActor* actor, UTextureRenderTarget2D* RenderTarget );
};
