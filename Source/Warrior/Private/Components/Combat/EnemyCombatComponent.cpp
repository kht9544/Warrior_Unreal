// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"

#include "WarriorDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if(OverlappedActors.Contains(HitActor))
    {
        return;
    }
    
    OverlappedActors.Add(HitActor);

    bool bIsValidBlock = false;

    const bool bIsPlayerBlocking = false;
    const bool bIsMyttackUnBlockable = false;

    if(bIsPlayerBlocking && !bIsMyttackUnBlockable)
    {
       //TODO bIsValidBlock = true;
    }

    FGameplayEventData EventData;
    EventData.Instigator = GetOwningPawn();
    EventData.Target = HitActor;

    if(bIsValidBlock)
    {
        //TODO Play Blocked Hit Reaction
    }
    else
    {
        //TODO Play Normal Hit Reaction
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
            GetOwner(), 
            WarriorGameplayTags::Shared_Event_MeleeHit, 
            EventData);
    }

}