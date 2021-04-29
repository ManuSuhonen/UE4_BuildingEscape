// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp,Display, TEXT("Grabber Initialized"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	FVector vector;
	FRotator rotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT vector,OUT rotator);

	//UE_LOG(LogTemp,Display, TEXT("vector: %s	rotator: %s"),*vector.ToString(),*rotator.ToString());


	auto lineEnd = vector + rotator.Vector() * 100;


	//UE_LOG(LogTemp,Display, TEXT("vector: %s	endvector: %s"),*vector.ToString(),*lineEnd.ToString());

	DrawDebugLine(GetWorld(),vector,lineEnd,FColor::Red,false,0,0,5);

	TArray<FHitResult> OutHits;
	FVector Start;
	FVector End;
	FCollisionObjectQueryParams ObjectQueryParams;
	FCollisionQueryParams Params;

	bool hits = GetWorld()->LineTraceMultiByObjectType(OutHits,vector,lineEnd,FCollisionObjectQueryParams::AllObjects,FCollisionQueryParams::DefaultQueryParam);

	
	if(hits)
	{
		for (const auto& ref: OutHits)
		{
			UE_LOG(LogTemp,Display, TEXT("object hit name: %s"),*ref.GetActor()->GetName());
		}
	}	
}

