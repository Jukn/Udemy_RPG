// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	/**
	*	서버에서는 모든 플레이어 컨트롤을 가지고 있지만
	*	클라이언트에서는 각각의 플레이어 컨트롤만을 가지고 있다.
	*	따라서 플레이어 컨트롤을 가지고 있는지 확인하고 맵핑하는 과정이 필요
	*	멀티플레이 환경에서 주의해야할 사항
	**/
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0); 
	}

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

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)		//콜백함수
{
	const FVector2D InputAxtixVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForworadDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RigthDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForworadDirection, InputAxtixVector.Y);
		ControlledPawn->AddMovementInput(RigthDirection, InputAxtixVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	* 커서를 통한 라인트레이서. 여러가지 경우가 있습니다
	* 1. LastActor == null && ThisActor == null
	*	-> 아무것도 하지 않는다.
	* 2. LastActor == null && ThisAcotr is valid
	*	-> LastActor에 하이라이트 적용
	* 3. LastActor is valid && ThisActor == null
	*	-> LastActor에 하이라이트 해제
	* 4. 두 Actor valid, But LastActor != ThisActor
	*	-> LastActor 하이라이트 해제, ThisActor 하이라이트 적용
	* 5. 두 Acotr valid, LastActor == ThisActor
	*	-> 아무것도 하지않는다.
	**/
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case 2
			ThisActor->HighlightActor();
		}
		else
		{
			// Case 1
		}
	}
	else  //LastAcotr is valid
	{
		if (ThisActor == nullptr)
		{
			// Case 3
			LastActor->UnHighlightActor();
		}
		else  //Both actor are valid
		{
			if (LastActor != ThisActor)
			{
				// Case 4
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case 5
			}
		}
	}
	
}
