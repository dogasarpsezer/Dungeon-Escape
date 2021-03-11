// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEnd.h"

#define OUTPARAMETER

// Sets default values for this component's properties
UGameEnd::UGameEnd()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGameEnd::BeginPlay()
{
	Super::BeginPlay();

	if(!endPlate)
	{
		UE_LOG(LogTemp, Error,TEXT("There is a nullptr!"));
	}
	
}


// Called every frame
void UGameEnd::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckThePawn();
}

void UGameEnd::CheckThePawn() const
{
	TArray<AActor*> actorsOnPlate;
	endPlate->GetOverlappingActors(OUTPARAMETER actorsOnPlate);

	for(AActor* actor: actorsOnPlate)
	{
		if(actor->GetName() == "DefaultPawn_BP_C_0")
		{
			UE_LOG(LogTemp,Warning,TEXT("BRUH"));
			keyActor->Destroy();
		}
	}

}

