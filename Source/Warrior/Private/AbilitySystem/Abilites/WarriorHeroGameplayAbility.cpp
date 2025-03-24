// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilites/WarriorHeroGameplayAbility.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"
#include "Components/Combat/HeroCombatComponent.h"

AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacteFromActorInfo()
{
    if (!CachedWarriorHeroCharacter.IsValid())
	{
		CachedWarriorHeroCharacter = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
   
    return CachedWarriorHeroCharacter.IsValid()? CachedWarriorHeroCharacter.Get() : nullptr;
}

AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (!CachedWarriorHeroController.IsValid())
	{
        UE_LOG(LogTemp,Warning,TEXT("Controller not valid"));
		CachedWarriorHeroController = Cast<AWarriorHeroController>(CurrentActorInfo->PlayerController);
	}
    
    if(CachedWarriorHeroController.IsValid())
    {
        UE_LOG(LogTemp,Warning,TEXT("Controller valid"));
        return CachedWarriorHeroController.Get();

    }
    else
    {
        UE_LOG(LogTemp,Warning,TEXT("Controller nullptr"));
        return nullptr;
    }

}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacteFromActorInfo()->GetHeroCombatComponent();
}
