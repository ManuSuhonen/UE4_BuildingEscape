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

	FVector playervector;
	FRotator playerrotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playervector,OUT playerrotator);

	//UE_LOG(LogTemp,Display, TEXT("vector: %s	rotator: %s"),*vector.ToString(),*rotator.ToString());


	auto lineEnd = playervector + playerrotator.Vector() * 100;
	playervector = playervector + playerrotator.Vector() * 40;


	//UE_LOG(LogTemp,Display, TEXT("vector: %s	endvector: %s"),*vector.ToString(),*lineEnd.ToString());

	DrawDebugLine(GetWorld(),playervector,lineEnd,FColor::Red,false,0,0,5);

	TArray<FHitResult> OutHits;

	bool hits = GetWorld()->LineTraceMultiByObjectType(OutHits,playervector,lineEnd,FCollisionObjectQueryParams::AllDynamicObjects,FCollisionQueryParams::DefaultQueryParam);

	if(hits)
	{
		for (const FHitResult& ref: OutHits)
		{
			if(ref.GetActor() != nullptr) 
			{
				UE_LOG(LogTemp,Display, TEXT("object hit name: %s"),*ref.GetActor()->GetName());
				
				if(GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton))
				{
						ref.GetActor()->SetActorLocation(lineEnd);
				}

			}
		}
	}	


}

