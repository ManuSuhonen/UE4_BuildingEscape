// Fill out your copyright notice in the Description page of Project Settings.



//#include "Engine/World.h"
//#include "GameFramework/PlayerController.h"
#include "DoorOpen.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DefaultPawn.h"
#include "Kismet/GameplayStatics.h"

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

	initialYaw = GetOwner()->GetActorRotation().Yaw;
	currentYaw = initialYaw;
	targetYaw += initialYaw;

	//player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	player = GetWorld()->GetFirstPlayerController()->GetPawn();

	//UE_LOG(LogTemp,Display, TEXT("%s"),*player->GetName());

	if(TriggerVolume == nullptr)
	{
		UE_LOG(LogTemp,Display, TEXT("ATriggerVolume not set in editor"),);
	}

	if(TriggerVolume != nullptr)
	{		
		TriggerVolume->OnActorBeginOverlap.AddDynamic(this,&UDoorOpen::BeginOverlap);
		TriggerVolume->OnActorEndOverlap.AddDynamic(this,&UDoorOpen::EndOverlap);
	}

}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DoorHandling(DeltaTime);
	
}


void UDoorOpen::BeginOverlap(AActor* Actor, AActor* OtherActor)
{
	//UE_LOG(LogTemp,Display, TEXT("overlap detected between %s and %s"),*Actor->GetName(),*OtherActor->GetName());

	if(EventDriven == true)
	{	
		auto doorRotation = GetOwner()->GetActorRotation();
		doorRotation.Yaw = currentYaw+90;
		GetOwner()->SetActorRotation(doorRotation);
	}

}

void UDoorOpen::EndOverlap(AActor* Actor, AActor* OtherActor)
{
	//TimeAfterOverlapEnd = FDateTime::Now();

	//UE_LOG(LogTemp,Display, TEXT("overlap between %s and %s ended at %s"),*Actor->GetName(),*OtherActor->GetName(),*TimeAfterOverlapEnd.ToString());


	if(EventDriven == true)
	{
		auto doorRotation = GetOwner()->GetActorRotation();
		doorRotation.Yaw = currentYaw;
		GetOwner()->SetActorRotation(doorRotation);
	}
}


void UDoorOpen::DoorHandling(float DeltaTime)
{
	if(EventDriven == false)
	{
		if(TriggerVolume->IsOverlappingActor(player))
		{
			currentYaw = FMath::FInterpTo(currentYaw,targetYaw,DeltaTime,speed);
			auto rotate = GetOwner()->GetActorRotation();
			rotate.Yaw = currentYaw;
			GetOwner()->SetActorRotation(rotate);
			time = GetWorld()->GetTimeSeconds();
		}
		else
		{
			if(time+closeDoorAfterSeconds < GetWorld()->GetTimeSeconds())
			{
				currentYaw = FMath::FInterpTo(currentYaw,initialYaw,DeltaTime,speed);
				auto rotate = GetOwner()->GetActorRotation();
				rotate.Yaw = currentYaw;
				GetOwner()->SetActorRotation(rotate);
				//UE_LOG(LogTemp,Display, TEXT("%s"),*FDateTime::Now().ToString());
			}
		}
	}
}