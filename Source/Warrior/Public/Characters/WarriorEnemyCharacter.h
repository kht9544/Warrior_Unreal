// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/WarriorBaseCharacter.h"
#include "CoreMinimal.h"
#include "WarriorEnemyCharacter.generated.h"

class UEnemyCombatComponent;
class UEnemyUIComponent;
class UWidgetComponent;
class UBoxComponent;

/**
 *
 */
UCLASS()
class WARRIOR_API AWarriorEnemyCharacter : public AWarriorBaseCharacter {
  GENERATED_BODY()

public:
  AWarriorEnemyCharacter();

  virtual UPawnCombatComponent *GetPawnCombatComponent() const override;

  virtual UPawnUIComponent *GetPawnUIComponent() const override;
  virtual UEnemyUIComponent *GetEnemyUIComponent() const override;

protected:
  virtual void BeginPlay() override;

  virtual void PossessedBy(AController *NewController) override;

#if WITH_EDITOR
  virtual void
  PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
#endif
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
  UEnemyCombatComponent *EnemyCombatComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
  UBoxComponent *LeftHandCollisionBox;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
  FName LeftHandCollisionBoxAttachBoneName;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
  UBoxComponent *RightHandCollisionBox;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
  FName RightHandCollisionBoxAttachBoneName;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
  UEnemyUIComponent *EnemyUIComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
  UWidgetComponent *EnemyHealthWidgetComponent;

  UFUNCTION()
  virtual void OnBodyCollisionBoxBeginOverlap(
      UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
      UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
      const FHitResult &SweepResult);

private:
  void InitEnemyStartUpData();

public:
  FORCEINLINE UEnemyCombatComponent *GetEnemyCombatComponent() const {
    return EnemyCombatComponent;
  }
  FORCEINLINE UBoxComponent *GetLeftHandCollisionBox() const {
    return LeftHandCollisionBox;
  }
  FORCEINLINE UBoxComponent *GetRightHandCollisionBox() const {
    return RightHandCollisionBox;
  }
};
