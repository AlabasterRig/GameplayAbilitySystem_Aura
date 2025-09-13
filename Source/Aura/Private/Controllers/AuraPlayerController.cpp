 // Copyright Utkrist Jaiswal


#include "Controllers/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

 AAuraPlayerController::AAuraPlayerController()
 {
 	bReplicates = true;
 }

 void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
 {
 	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

 	const FRotator Rotation = GetControlRotation();
 	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

 	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
 	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

 	if (APawn* ControlledPawn = GetPawn())
 	{
 		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
 		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
 	}
 }

 void AAuraPlayerController::CursorTrace()
 {
 	FHitResult CursorHitResult;
 	GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);
 	if (!CursorHitResult.bBlockingHit)
 	{
 		return;
 	}

 	LastActor = ThisActor;
 	ThisActor = CursorHitResult.GetActor();

 	/**
 	 * Line Trace from Cursor.
 	 * 1. Last Actor is nul and this actor is null
 	 *		- Do Nothing
 	 * 2. Last Actor is Null and this Actor is Valid
 	 *		- Hightlight this actor.
 	 * 3. Last actor is valid and this actor is null
 	 *		- UnHighlight Last Actor
 	 * 4. Both Actor is Valid, But LastActor != ThisActor
 	 *		- UnHighlight last actor and highlight this actor
 	 * 5. Both Actors are valid, and are the same actor
 	 *		- Do Nothing
 	 */

 	if (LastActor == nullptr)
 	{
 		if (ThisActor != nullptr)
 		{
 			// Case 2.
 			ThisActor->HightlightActor();
 		}
	    else
	    {
		    // Case 1. - Both are null do nothing
	    }
 	}
    else // Last Actor is valid
    {
	    if (ThisActor == nullptr)
	    {
		    // Case 3.
		    LastActor->UnhightlightActor();
	    }
	    else // Both are valid
	    {
		    if (LastActor != ThisActor)
		    {
			    // Case 4.
		    	LastActor->UnhightlightActor();
		    	ThisActor->HightlightActor();
		    }
		    else
		    {
			    // Case 5. - Do Nothing
		    }
	    }
    }
 }

 void AAuraPlayerController::BeginPlay()
 {
 	Super::BeginPlay();

 	check(AuraInputContext);
 	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
 	check(InputSubsystem);
 	InputSubsystem->AddMappingContext(AuraInputContext, 0);

 	bShowMouseCursor = true;
 	DefaultMouseCursor = EMouseCursor::Default;

 	FInputModeGameAndUI InputModeData;
 	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
 	InputModeData.SetHideCursorDuringCapture(false);
 	SetInputMode(InputModeData);
 }

 void AAuraPlayerController::SetupInputComponent()
 {
	 Super::SetupInputComponent();

 	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
 	{
 		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
 	}
 }

 void AAuraPlayerController::Tick(float DeltaSeconds)
 {
	 Super::Tick(DeltaSeconds);

 	CursorTrace();
 }
