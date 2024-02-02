// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "TCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(ABSTRACT)
class AURA_API ATCharacterBase : public ACharacter, public IAbilitySystemInterface
{ 
	GENERATED_BODY()

public:
	ATCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, Category = "Combat");
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
