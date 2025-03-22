// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilites/WarriorHeroGameplayAbility.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"
#include "Components/Combat/HeroCombatComponent.h"

AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacteFromActorInfo()
{
    if(!CachedWarriorHeroCharacter.IsValid())
    {
        CachedWarriorHeroCharacter = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);
    }
	return CachedWarriorHeroCharacter.IsValid() ? CachedWarriorHeroCharacter.Get() : nullptr;
}

AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroComtrollerFromActorInfo()
{
    if(!CachedWarriorHeroController.IsValid())
    {
        CachedWarriorHeroController = Cast<AWarriorHeroController>(CurrentActorInfo->AvatarActor);
    }
	return CachedWarriorHeroController.IsValid() ? CachedWarriorHeroController.Get() : nullptr;	
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombotComponentFromActorInfo()
{
	return GetHeroCharacteFromActorInfo()->GetHeroCombatComponent();
}
