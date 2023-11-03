// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTack.h"

void UTankTack::SetThrottle(float Throttle)
{
	// auto Time = GetWorld()->GetTimeSeconds();
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Throttle: %f"), *Name, Throttle);

	// TODO clamp actual Throttle value so player can't over-drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
