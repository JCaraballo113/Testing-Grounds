// Fill out your copyright notice in the Description page of Project Settings.

#include "FocusAtActor.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

EBTNodeResult::Type UFocusAtActor::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get Blackboard Component from Behavior Tree
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	// Get the AI Controller from Behavior Tree
	auto AIControl = OwnerComp.GetAIOwner();

	// Get Value of Enemy Key from Blackboard Component
	auto FocusEnemy = Cast<AActor>(BlackboardComp->GetValueAsObject(EnemyKey.SelectedKeyName));

	// Set it as Focus on the AI Controller
	AIControl->SetFocus(FocusEnemy);

	return EBTNodeResult::Succeeded;
}
