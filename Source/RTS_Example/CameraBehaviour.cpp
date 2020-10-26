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

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Test"));
	}

	inputComponent = cameraPawn->FindComponentByClass<UInputComponent>();
	if (inputComponent) 
	{
		inputComponent->BindAxis("MoveForward", this, &UCameraBehaviour::MoveForward);
		inputComponent->BindAction("ZoomReset", IE_Pressed, this, &UCameraBehaviour::ZoomReset);
		inputComponent->BindAxis("ZoomIn", this, &UCameraBehaviour::ZoomIn);
		inputComponent->BindAction("Pan", IE_Pressed, this, &UCameraBehaviour::EnableCameraMovement);
		inputComponent->BindAction("Pan", IE_Released, this, &UCameraBehaviour::DisableCameraMovement);
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have an InputController!"), *GetOwner()->GetName());
	}

	playerController = UGameplayStatics::GetPlayerController(GetOwner()->GetWorld(), 0);
	if (!playerController) {
		UE_LOG(LogTemp, Error, TEXT("No playerController found!"));
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
	if (!disableCameraMovement) {
		CameraPan();
	}

}

void UCameraBehaviour::InputTest() 
{
	UE_LOG(LogTemp, Warning, TEXT("Input found!"));
}

void UCameraBehaviour::ZoomReset()
{
	springarm->TargetArmLength = StartZoom;
}

void UCameraBehaviour::ZoomIn(float AxisValue) 
{
	if (AxisValue != .0f) {
		float length = AxisValue * zoomSpeed + springarm->TargetArmLength;
		length = FMath::Clamp(length, minZoomLimit, maxZoomLimit);
		springarm->TargetArmLength = length;
	}
}

void UCameraBehaviour::CameraPan() 
{
	float newMouseX, newMouseY;

	playerController->GetMousePosition(newMouseX, newMouseY);
	float moveX = newMouseX - mouseX;
	float moveY = newMouseY - mouseY;
	UE_LOG(LogTemp, Log, TEXT("Mouse X : %f  Mouse Y : %f"), moveX, moveY);

	FRotator cameraRot = cameraPawn->GetActorRotation();

	cameraRot.Yaw += (moveX * panSpeed);

	float pitch = cameraRot.Pitch + (moveY * panSpeed);
	cameraRot.Pitch = FMath::Clamp(pitch, -25.0f, 50.0f);

	cameraPawn->SetActorRotation(cameraRot);
}

void UCameraBehaviour::MoveForward(float Value) 
{
	if (Value != .0f) {
		UE_LOG(LogTemp, Log, TEXT("MOVIN"));
	}
}

void UCameraBehaviour::EnableCameraMovement() 
{
	disableCameraMovement = false;
	playerController->GetMousePosition(mouseX, mouseY);
}
void UCameraBehaviour::DisableCameraMovement() 
{
	disableCameraMovement = true;
}
