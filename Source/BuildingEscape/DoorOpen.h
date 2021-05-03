// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Misc/DateTime.h"
#include "DoorOpen.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

	UFUNCTION()
    void BeginOverlap(AActor* Actor, AActor* OtherActor);

	UFUNCTION()
	void EndOverlap(AActor* Actor, AActor* OtherActor);

	void DoorHandling(float DeltaTime);

	float TotalMass();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door param")
	float speed;

	float initialYaw;
	float currentYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door param")
	float targetYaw;
		
	UPROPERTY(EditAnywhere)
	ATriggerVolume* TriggerVolume;

	AActor* player;

	//True = Event Driven. False = Poll Driven.
	UPROPERTY(EditAnywhere)
	bool EventDriven;

	FDateTime TimeAfterOverlapEnd;

	//closes door X seconds from Overlap end
	UPROPERTY(EditAnywhere)
	float closeDoorAfterSeconds = 1.1f;

	float time = 0;


	//Mass required to open door.
	UPROPERTY(EditAnywhere)
	float RequiredMass;
};
