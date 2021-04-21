// Fill out your copyright notice in the Description page of Project Settings.
// torea - got the basic code here : https://answers.unrealengine.com/questions/486630/accessing-camera-images.html

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SphereComponent.h"
#include "Engine/TextureRenderTarget2D.h"

#include "BasicCameraSensor.generated.h"


UCLASS()
class UNRLGYM_API ABasicCameraSensor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicCameraSensor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	USceneCaptureComponent2D *Camera;
	UTextureRenderTarget2D *RenderTarget;
	UTexture2D *Texture2D;
};
