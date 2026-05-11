// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
#include "WarriorFunctionLibrary.h"
#include "Characters/WarriorEnemyCharacter.h"
#include "Components/BoxComponent.h"

#include "WarriorDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if(OverlappedActors.Contains(HitActor))
    {
        return;
    }
    
    OverlappedActors.Add(HitActor);

    bool bIsValidBlock = false;

    const bool bIsPlayerBlocking = UWarriorFunctionLibrary::NativeDoesActorHaveTag(HitActor, WarriorGameplayTags::Player_Status_Blocking);
    const bool bIsMyAttackUnBlockable = UWarriorFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), WarriorGameplayTags::Enemy_Status_Unblockable);

    if(bIsPlayerBlocking && !bIsMyAttackUnBlockable)
    {
       bIsValidBlock = UWarriorFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);

    }

    FGameplayEventData EventData;
    EventData.Instigator = GetOwningPawn();
    EventData.Target = HitActor;

    if(bIsValidBlock)
    {
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
            HitActor,
            WarriorGameplayTags::Player_Event_SuccessfulBlock, 
            EventData);
    }
    else
    {
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
            GetOwningPawn(), 
            WarriorGameplayTags::Shared_Event_MeleeHit, 
            EventData);
    }

}


void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AWarriorEnemyCharacter* OwningEnemyCharacter = GetOwningPawn<AWarriorEnemyCharacter>();

    check(OwningEnemyCharacter);

    UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
    UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();
    
    check(LeftHandCollisionBox && RightHandCollisionBox);

    auto PrepareCollisionBox = [](UBoxComponent* CollisionBox)
    {
        CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
        CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
        CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
        CollisionBox->SetGenerateOverlapEvents(true);
    };

    switch (ToggleDamageType)
    {
        case EToggleDamageType::LeftHand:
            PrepareCollisionBox(LeftHandCollisionBox);
            LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
            break;
        case EToggleDamageType::RightHand:
            PrepareCollisionBox(RightHandCollisionBox);
            RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
            break;
        default:
            break;

    }
    
    if(!bShouldEnable)
    {
        OverlappedActors.Empty();
    }
}
