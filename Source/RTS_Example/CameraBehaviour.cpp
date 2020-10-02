// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraBehaviour.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCameraBehaviour::UCameraBehaviour()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraBehaviour::BeginPlay()
{
	Super::BeginPlay();

	// ...
	cameraPawn = UGameplayStatics::GetPlayerPawn(GetOwner()->GetWorld(), 0);
	UE_LOG(LogTemp, Error, TEXT("TEST!!!"));


	inputComponent = cameraPawn->FindComponentByClass<UInputComponent>();
	if (!inputComponent) {
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have an InputController!"), *GetOwner()->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s found an InputController!"), *GetOwner()->GetName());
	}
	springarm = cameraPawn->FindComponentByClass<USpringArmComponent>();
	if (!springarm) {
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have an springarm!"), *GetOwner()->GetName());
	}


}


// Called every frame
void UCameraBehaviour::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	inputComponent->BindAxis("ZoomIn", this, &UCameraBehaviour::ZoomIn);
}

void UCameraBehaviour::ZoomIn(float AxisValue) 
{
	float length = AxisValue * zoomSpeed + springarm->TargetArmLength;
	FMath::Clamp(length, minZoomLimit, maxZoomLimit);
	springarm->TargetArmLength = length;
}
