// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform();
}

void AMovingPlatform::MovePlatform(const float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += PlatformVelocity * DeltaTime;
	SetActorLocation(CurrentLocation);
}

void AMovingPlatform::RotatePlatform()
{
	const float DistanceMoved = FVector::Dist(StartLocation, GetActorLocation());
	if (DistanceMoved < MoveDistance)
	{
		return;
	}

	float OverShoot = DistanceMoved - MoveDistance;
	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("%s Platform Overshoot %f"), *Name, OverShoot);
	FVector MoveDirection = PlatformVelocity.GetSafeNormal();
	StartLocation = StartLocation + MoveDirection * MoveDistance;
	SetActorLocation(StartLocation);

	PlatformVelocity *= -1;
}

