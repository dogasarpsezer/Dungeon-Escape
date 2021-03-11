// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEDUNGEON_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	bool NameChecker() const;
private:
	UPROPERTY(EditAnywhere)
	float targetYaw;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* doorPlate = nullptr;
	UPROPERTY(EditAnywhere)
	float doorDelay = 3.f;
	UPROPERTY(EditAnywhere)
	float doorOpenSpeed = 4.f;
	UPROPERTY(EditAnywhere)
	float doorCloseSpeed = 2.f;
	UPROPERTY(EditAnywhere)
	AActor* theKeyObject = nullptr;
	UPROPERTY(EditAnywhere)
	bool puzzleDoor = false;	

	UPROPERTY()
	UAudioComponent* audioComponent = nullptr;


	float doorOpenedTime = 0.f;
	float initialYaw;
	float currentYaw;
	bool openDoorSound = false;
	bool closeDoorSound = true;
	FRotator currentRotator;
};
