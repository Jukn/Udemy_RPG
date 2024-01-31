// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnyWhere, Category = "Input");
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnyWhere, Category = "Input");
	TObjectPtr<UInputAction> MoveAction;						//입력 작업을 위한 변수

	void Move(const FInputActionValue& InputActionValue);		//데이터를 제공하는 입력 작업에 대한 이동을 바인딩하기 위한 함수
};
