// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "PatrolRoute.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get the Blackboard Component
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	// Get the current index
	auto CurrentIndex = BlackboardComp->GetValueAsInt(Index.SelectedKeyName);

	// Get the AI Pawn
	auto AIPawn = OwnerComp.GetAIOwner()->GetPawn();

	// Get it's patrol route component
	auto PatrolRoute = AIPawn->FindComponentByClass<UPatrolRoute>();

	if (!PatrolRoute) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Patrol Route Component is missing"));
		return EBTNodeResult::Failed;
	}

	// Get the PatrolPoints
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();

	if (PatrolPoints.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set some on %s patrol points first."), *AIPawn->GetName());
	}

	// Set the next waypoint on the blackboard
	BlackboardComp->SetValueAsObject(Waypoint.SelectedKeyName, PatrolPoints[CurrentIndex]);

	// Cycle to the next waypoint index
	auto NextWaypointIndex = (CurrentIndex + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(Index.SelectedKeyName, NextWaypointIndex);

	return EBTNodeResult::Succeeded;
}
