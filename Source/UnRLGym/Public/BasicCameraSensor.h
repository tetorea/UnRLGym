// Fill out your copyright notice in the Description page of Project Settings.
// torea - got the basic code here : https://answers.unrealengine.com/questions/486630/accessing-camera-images.html

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SphereComponent.h"
#include <array>
#include "Engine/TextureRenderTarget2D.h"
#include "BasicCameraSensor.generated.h"


UCLASS()
class UNRLGYM_API ABasicCameraSensor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasicCameraSensor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GetCameraImage();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Sensor")
	TArray<int> cameraImage;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Sensor")
	int elementSize;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Sensor")
	int elementCount;


	USceneCaptureComponent2D *Camera;
	UTextureRenderTarget2D *RenderTarget;
	UTexture2D *Texture2D;
	FTexturePlatformData *Data;
};
