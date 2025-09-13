// Copyright Utkrist Jaiswal

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	bool bIsHightlighted = false;

	virtual void HightlightActor() override;
	virtual void UnhightlightActor() override;
};
