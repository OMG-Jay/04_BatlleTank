// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "BattleTank.h"

void UTankMovementComponent::Initilize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call Super; replacing functionality
	auto TankFoward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIFowardIntention = MoveVelocity.GetSafeNormal();
	auto FowardThrow = FVector::DotProduct(TankFoward, AIFowardIntention);
	auto RightThrow = FVector::CrossProduct(AIFowardIntention, TankFoward).Z;
	IntendMoveForward(FowardThrow);
	IntendTurnRight(RightThrow);
	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s "), *TankName, *MoveVelocityString);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveBackward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(-Throw);
}