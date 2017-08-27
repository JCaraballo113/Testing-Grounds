// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FocusAtActor.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API UFocusAtActor : public UBTTaskNode
{
	GENERATED_BODY()
	

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector EnemyKey;
	
	
};
