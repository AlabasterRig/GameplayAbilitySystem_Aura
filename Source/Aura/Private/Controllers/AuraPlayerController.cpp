 // Copyright Utkrist Jaiswal


#include "Controllers/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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