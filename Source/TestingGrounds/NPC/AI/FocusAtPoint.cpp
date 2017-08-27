// Fill out your copyright notice in the Description page of Project Settings.

#include "FocusAtPoint.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

EBTNodeResult::Type UFocusAtPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get Blackboard Component from Behavior Tree
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	// Get the AI Controller from Behavior Tree
	auto AIControl = OwnerComp.GetAIOwner();

	// Get Value of Focus Point from Blackboard Component
	auto FocusPoint = BlackboardComp->GetValueAsVector(FocusLocation.SelectedKeyName);

	// Set it as Focus point on the AI Controller
	AIControl->SetFocalPoint(FocusPoint);

	return EBTNodeResult::Succeeded;
}
