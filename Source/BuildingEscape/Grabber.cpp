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
	PhysicsHandle =  GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if(PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp,Error, TEXT("%s has no Physics Handle Component"),*GetOuter()->GetName());
	}

	if(InputComponent == nullptr)
	{
		UE_LOG(LogTemp,Error, TEXT("%s has no Input Component"),*GetOuter()->GetName());
	}

	if(InputComponent != nullptr)
	{
		InputComponent->BindAction("Grab",IE_Pressed,this,&UGrabber::Grab);
		InputComponent->BindAction("Grab",IE_Released,this,&UGrabber::Release);
	}

	TraceParam = FCollisionQueryParams(FName(TEXT("")),false,GetOwner());
	ObjectParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playervector,OUT playerrotator);

	lineEnd = playervector + playerrotator.Vector() * RayLength;

	if(PhysicsHandle->GrabbedComponent != nullptr)
	{
		PhysicsHandle->SetTargetLocation(lineEnd);
	}
}


void UGrabber::Grab(void)
{
	UE_LOG(LogTemp,Display, TEXT("Grab event triggered."));

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playervector,OUT playerrotator);

	lineEnd = playervector + playerrotator.Vector() * RayLength;

	DrawDebugLine(GetWorld(),playervector,lineEnd,FColor::Red,false,1,0,5);

	hits = GetWorld()->LineTraceSingleByObjectType(OUT OutHit,playervector,lineEnd,ObjectParams,TraceParam);

	if(hits)
	{
		UE_LOG(LogTemp,Display, TEXT("RayCast hit: %s"),*OutHit.GetActor()->GetName());
		PhysicsHandle->GrabComponentAtLocation(OutHit.GetComponent(),NAME_None,lineEnd);
	}	

}

void UGrabber::Release(void)
{
	UE_LOG(LogTemp,Display, TEXT("Release event triggered."));
	PhysicsHandle->ReleaseComponent();
}
