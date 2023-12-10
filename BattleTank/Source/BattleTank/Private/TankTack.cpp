// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTack.h"

UTankTack::UTankTack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTack::OnHit);
}

void UTankTack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, +1);
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTack::ApplySidewaysForce()
{
	// Work-out the required acceleration this frame to correct
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}

