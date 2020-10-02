// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CameraBehaviour.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS_EXAMPLE_API UCameraBehaviour : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraBehaviour();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float zoomSpeed = 80.0f;

private:

	UInputComponent* inputComponent = nullptr;
	USpringArmComponent* springarm = nullptr;
	APawn* cameraPawn;

	void ZoomIn(float AxisValue);


	float minZoomLimit = 300.0f;
	float maxZoomLimit = 4000.0f;
};
