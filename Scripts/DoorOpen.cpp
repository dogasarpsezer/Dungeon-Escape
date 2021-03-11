// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "DoorOpen.h"

#define OUTPARAMETER

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();
	//Initializing variables
	currentRotator = GetOwner()->GetActorRotation();
	initialYaw = currentRotator.Yaw;
	currentYaw = initialYaw;
	audioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!doorPlate || !audioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has a null pointer assigned on its' components"), *GetOwner()->GetName());
	}

}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(doorPlate && NameChecker())
	{
		OpenDoor(DeltaTime);
		doorOpenedTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() >= doorOpenedTime + doorDelay)
		{
			CloseDoor(DeltaTime);
		}
	}

	//Print results
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *currentRotator.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%f"), currentRotator.Yaw);

	/*UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("%f"), GetOwner()->GetActorRotation().Yaw);*/
}
void UDoorOpen::OpenDoor(float DeltaTime)
{
	//Change the value yaw towards the target
	currentYaw = FMath::FInterpTo(currentYaw, initialYaw + targetYaw, DeltaTime, doorOpenSpeed);
	currentRotator.Yaw = currentYaw;
	GetOwner()->SetActorRotation(currentRotator);
	if (!openDoorSound)
	{
		audioComponent->Play();
		openDoorSound = true;
		closeDoorSound = false;
	}
}

void UDoorOpen::CloseDoor(float DeltaTime)
{
	//Change the value yaw towards the target
	currentYaw = FMath::FInterpTo(currentYaw, initialYaw, DeltaTime, doorCloseSpeed);
	currentRotator.Yaw = currentYaw;
	GetOwner()->SetActorRotation(currentRotator);
	if(!closeDoorSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sound is played"));
		audioComponent->Play();
		closeDoorSound = true;
		openDoorSound = false;
	}
}

bool UDoorOpen::NameChecker() const
{
	bool nameCheck = false;
	FString objectName = theKeyObject->GetName();
	TArray<AActor*> objectsOnThePlate;
	doorPlate->GetOverlappingActors(OUTPARAMETER objectsOnThePlate);

	for(AActor* actor:objectsOnThePlate)
	{
		if(actor->GetName() == objectName && puzzleDoor)
		{
			nameCheck = true;
		}
		else if(actor->GetName() == "DefaultPawn_BP_C_0" && !puzzleDoor)
		{
			nameCheck = true;
		}

		UE_LOG(LogTemp, Warning, TEXT("%s is on the plate"), *actor->GetName());
	}

	return nameCheck;
}

