#pragma once

#include "CoreMinimal.h"
#include "TCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public ATCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
		
public:
	AAuraEnemy();

	/**  Enemy Interface **/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/**  End Interface **/

protected:
	virtual void BeginPlay();
};
