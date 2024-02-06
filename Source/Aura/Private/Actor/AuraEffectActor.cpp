// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include  "Components/SphereComponent.h"

/*
* GPE�� ����ϱ� ��
*/
//AAuraEffectActor::AAuraEffectActor()
//{
//	PrimaryActorTick.bCanEverTick = false;
//
//	//�޽� �߰��� �� �߰��� c++���� û�������� �ű��.
//	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
//	SetRootComponent(Mesh);
//
//	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
//	Sphere->SetupAttachment(GetRootComponent());
//
//}
//
//void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, 
//	AActor* OtherActor, 
//	UPrimitiveComponent* OtherComp, 
//	int32 OtherBodyIndex, 
//	bool bFromSweep, 
//	const FHitResult& SweepResult)
//{
//
//}
//
//void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, 
//	AActor* OtherActor, 
//	UPrimitiveComponent* OtherComp, 
//	int32 OtherBodyIndex)
//{
//	//TODO: change this to apply a Gameplay Effect. For now, using const_cast as a hack
//	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
//	{
//		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
//		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
//		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
//		MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana() - 25.f);
//		Destroy();
//	}
//}
//
//void AAuraEffectActor::BeginPlay()
//{
//	Super::BeginPlay();
//
//	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
//	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
//
//}

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));

}
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

//��� ȿ���� �����ϴ� �Լ�
void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	/*IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(Target);

	if (ASCInterface)
	{
		ASCInterface->GetAbilitySystemComponent();
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	}*/

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr)
	{
		return;
	}

	check(GameplayEffectClass);
	//1. �����÷��� ȿ���� �����ϴ� ��� 1
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
}



