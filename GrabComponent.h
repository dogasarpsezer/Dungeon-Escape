// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEDUNGEON_API UGrabComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Interact();
	void Release();
	void InitializeGame();
	AActor* RaycastInteract() const;
	FVector GetEndLineCalculator() const;
private:
	UPROPERTY(EditAnywhere)
	float reach = 100.f;
	
	UPROPERTY()
	UPhysicsHandleComponent* physicsHandler = nullptr;
	UPROPERTY()
	UInputComponent* inputComponent = nullptr;

};
