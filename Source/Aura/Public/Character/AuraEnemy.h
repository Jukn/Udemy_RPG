#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
		
public:
	AAuraEnemy();

	/**  Enemy Interface **/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	/**  End Enemy Interface **/

	/** Combat Interface **/
	virtual int32 GetPlayerLevel() override;

	/** End Combat Interface **/


protected:
	virtual void BeginPlay();
	virtual void InitAbilityActorInfo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults");
	int32 Level = 1;
private:


};
