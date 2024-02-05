// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

/*
* GPE를 사용하기 전
*/
//class AURA_API AAuraEffectActor : public AActor
//{
//	GENERATED_BODY()
//	
//public:	
//	AAuraEffectActor();
//
//	UFUNCTION()
//	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, 
//		AActor* OtherActor,
//		UPrimitiveComponent* OtherComp,
//		int32 OtherBodyIndex,
//		bool bFromSweep,
//		const FHitResult& SweepResult);		//구성 요소가 겹쳤을 때 바인딩되는 함수
//
//	UFUNCTION()
//	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent,
//		AActor* OtherActor,
//		UPrimitiveComponent* OtherComp,
//		int32 OtherBodyIndex);
//
//protected:
//	virtual void BeginPlay() override;
//
//private:
//	UPROPERTY(VisibleAnyWhere)
//	TObjectPtr<USphereComponent> Sphere;
//
//	UPROPERTY(VisibleAnyWhere)
//	TObjectPtr<UStaticMeshComponent> Mesh;
//};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();


protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

private:

};