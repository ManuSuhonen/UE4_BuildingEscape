// Fill out your copyright notice in the Description page of Project Settings.



//#include "Engine/World.h"
//#include "GameFramework/PlayerController.h"
#include "DoorOpen.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DefaultPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Misc/App.h"

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
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	UE_LOG(LogTemp,Display, TEXT("Owner Name %s"),*GetOwner()->GetName());

	if(AudioComponent == nullptr)
	{
		UE_LOG(LogTemp,Error, TEXT("AudioComponent not set in editor"),);
	}


	if(TriggerVolume == nullptr)
	{
		UE_LOG(LogTemp,Error, TEXT("ATriggerVolume not set in editor"),);
	}

	if(TriggerVolume != nullptr)
	{		
		TriggerVolume->OnActorBeginOverlap.AddDynamic(this,&UDoorOpen::BeginOverlap);
		TriggerVolume->OnActorEndOverlap.AddDynamic(this,&UDoorOpen::EndOverlap);
	}

	IsOpen = false;

}

// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DoorHandling(DeltaTime);
	//UE_LOG(LogTemp,Display, TEXT("count is %i"),*Actor->GetName(),*OtherActor);
	
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
	if(EventDriven == true)
	{
		auto doorRotation = GetOwner()->GetActorRotation();
		doorRotation.Yaw = currentYaw;
		GetOwner()->SetActorRotation(doorRotation);
	}
}

void UDoorOpen::DoorHandling(float DeltaTime)
{
	//UE_LOG(LogTemp,Display, TEXT("%i"),IsOpen);
	if(EventDriven == false)
	{
		if(TotalMass() > RequiredMass)
		{
			OpenSound();
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
				CloseSound();
			}
		}
	}
}

float UDoorOpen::TotalMass()
{
	float totalmass = 0;
	TArray<AActor*> overlappingactors;
	TriggerVolume->GetOverlappingActors(overlappingactors);

	for (const auto ref:overlappingactors)
	{
		totalmass += ref->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	//UE_LOG(LogTemp,Display, TEXT("total mass: %f"),totalmass);
	
	return totalmass;
}



void UDoorOpen::OpenSound()
{
	if(IsOpen == false)
	{
		UE_LOG(LogTemp,Display, TEXT("open sound playing"));
		AudioComponent->Activate();
		AudioComponent->Play();
		IsOpen = true;
	}
}


void UDoorOpen::CloseSound()
{
	if(IsOpen == true)
	{
		UE_LOG(LogTemp,Display, TEXT("close sound playing"));
		AudioComponent->Activate();
		AudioComponent->Play();
		IsOpen = false;
	}
}



