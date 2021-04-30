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

	FVector lineEnd = playervector + playerrotator.Vector() * 100;

	DrawDebugLine(GetWorld(),playervector,lineEnd,FColor::Red,false,0,0,5);

	FHitResult OutHit;
	FCollisionQueryParams TraceParam(FName(TEXT("")),false,GetOwner());
	FCollisionObjectQueryParams ObjectParams(ECollisionChannel::ECC_PhysicsBody);

	bool hits = GetWorld()->LineTraceSingleByObjectType(OUT OutHit,playervector,lineEnd,ObjectParams,TraceParam);

	if(hits)
	{
		UE_LOG(LogTemp,Display, TEXT("Raycast hit: %s"),*OutHit.GetActor()->GetName());
	}	


}

