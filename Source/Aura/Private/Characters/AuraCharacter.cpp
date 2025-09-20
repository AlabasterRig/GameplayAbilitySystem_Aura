// Copyright Utkrist Jaiswal


#include "Characters/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerState/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Ability Actor Info for the server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Ability Actor Info for the client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	if (AAuraPlayerState* CharacterPlayerState = GetPlayerState<AAuraPlayerState>())
	{
		CharacterPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(CharacterPlayerState, this);
		AbilitySystemComponent = CharacterPlayerState->GetAbilitySystemComponent();
		AttributeSet = CharacterPlayerState->GetAttributeSet();
	}
}
