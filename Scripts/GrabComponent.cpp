// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GrabComponent.h"

#define OUTPARAMETER

// Sets default values for this component's properties
UGrabComponent::UGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeGame();
}

// Called every frame
void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	physicsHandler->SetTargetLocation(GetEndLineCalculator());
}
void UGrabComponent::InitializeGame()
{
	physicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(physicsHandler == nullptr || inputComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s object has a nullptr in initialization"), *GetOwner()->GetName())
	}

	inputComponent->BindAction("Interact", IE_Pressed, this, &UGrabComponent::Interact);
	inputComponent->BindAction("Release", IE_Released, this, &UGrabComponent::Release);
}
void UGrabComponent::Interact()
{
	RaycastInteract();
}

void UGrabComponent::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("De-Bruh"));
	physicsHandler->ReleaseComponent();
}

FVector UGrabComponent::GetEndLineCalculator() const
{
	FVector playerViewLocation;
	FRotator playerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUTPARAMETER playerViewLocation, OUTPARAMETER playerViewRotation);
	FVector endOfLine = playerViewLocation + playerViewRotation.Vector() * reach;
	//DrawDebugLine(GetWorld(), playerViewLocation, endOfLine, FColor(0, 0, 255), false, 0.f, 0, 5.f);
	return endOfLine;
}

AActor* UGrabComponent::RaycastInteract() const
{
	FVector playerViewLocation;
	FRotator playerViewRotation;
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUTPARAMETER playerViewLocation, OUTPARAMETER playerViewRotation);
	FHitResult hit;
	GetWorld()->LineTraceSingleByChannel(OUTPARAMETER hit, playerViewLocation, GetEndLineCalculator(), ECollisionChannel::ECC_PhysicsBody, traceParameters);

	if (hit.GetActor() != nullptr)
	{
		UPrimitiveComponent* primitiveComponent = hit.GetComponent();
		UE_LOG(LogTemp, Warning, TEXT("%s has been hit"), *hit.GetActor()->GetName())
		physicsHandler->GrabComponentAtLocation(primitiveComponent,NAME_None,GetEndLineCalculator());
	}
	
	return hit.GetActor();
}
