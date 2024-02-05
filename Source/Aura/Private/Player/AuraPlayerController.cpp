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
	*	���������� ��� �÷��̾� ��Ʈ���� ������ ������
	*	Ŭ���̾�Ʈ������ ������ �÷��̾� ��Ʈ�Ѹ��� ������ �ִ�.
	*	���� �÷��̾� ��Ʈ���� ������ �ִ��� Ȯ���ϰ� �����ϴ� ������ �ʿ�
	*	��Ƽ�÷��� ȯ�濡�� �����ؾ��� ����
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

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)		//�ݹ��Լ�
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
	* Ŀ���� ���� ����Ʈ���̼�. �������� ��찡 �ֽ��ϴ�
	* 1. LastActor == null && ThisActor == null
	*	-> �ƹ��͵� ���� �ʴ´�.
	* 2. LastActor == null && ThisAcotr is valid
	*	-> LastActor�� ���̶���Ʈ ����
	* 3. LastActor is valid && ThisActor == null
	*	-> LastActor�� ���̶���Ʈ ����
	* 4. �� Actor valid, But LastActor != ThisActor
	*	-> LastActor ���̶���Ʈ ����, ThisActor ���̶���Ʈ ����
	* 5. �� Acotr valid, LastActor == ThisActor
	*	-> �ƹ��͵� �����ʴ´�.
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
