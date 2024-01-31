// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TCharacterBase.generated.h"

UCLASS(ABSTRACT)
class AURA_API ATCharacterBase : public ACharacter
{ 
	GENERATED_BODY()

public:
	ATCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, Category = "Combat");
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
