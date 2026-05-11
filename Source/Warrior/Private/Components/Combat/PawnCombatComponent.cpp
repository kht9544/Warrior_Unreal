// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/Combat/PawnCombatComponent.h"
#include "Weapons/WarriorWeaponBase.h"
#include "Components/BoxComponent.h"

#include "WarriorDebugHelper.h"


void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,AWarriorWeaponBase* InWeaponToRegister,bool bRegisterAsEquippedWeapon)
{
    checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister),TEXT("A named %s has already carried weapon"),*InWeaponTagToRegister.ToString());
    check(InWeaponToRegister);

    CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister,InWeaponToRegister);

    InWeaponToRegister->SetOwner(GetOwningPawn());
    InWeaponToRegister->SetInstigator(GetOwningPawn<APawn>());

    InWeaponToRegister->OnWeaponHitTarget.BindUObject(this,&UPawnCombatComponent::OnHitTargetActor);
    InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this,&UPawnCombatComponent::OnWeaponPulledFromTargetActor);

    if(bRegisterAsEquippedWeapon)
    {
        CurrentEquippedWeaponTag = InWeaponTagToRegister;
    }

}


AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
    if(CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
    {
        if(AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
        {
            return *FoundWeapon;
        }
    }

    return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if(!CurrentEquippedWeaponTag.IsValid())
    {
        return nullptr;
    }

    return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable,EToggleDamageType ToggleDamageType)
{
	if(ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
    {
        ToggleCurrentEquippedWeaponCollision(bShouldEnable);
    }
    else
    {
        ToggleBodyCollisionBoxCollision(bShouldEnable, ToggleDamageType);
    }

    //TODO: Handle body collision 
}

void UPawnCombatComponent::ToggleCurrentEquippedWeaponCollision(bool bShouldEnable)
{
	AWarriorWeaponBase* WeaponToToggle =  GetCharacterCurrentEquippedWeapon();

       check(WeaponToToggle);
        if(bShouldEnable)
        {
            WeaponToToggle->GetWeaponCollisionBox()->SetCollisionObjectType(ECC_WorldDynamic);
            WeaponToToggle->GetWeaponCollisionBox()->SetCollisionResponseToAllChannels(ECR_Ignore);
            WeaponToToggle->GetWeaponCollisionBox()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
            WeaponToToggle->GetWeaponCollisionBox()->SetGenerateOverlapEvents(true);
            WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
            
        }   
        else
        {
            WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            OverlappedActors.Empty();
        }
}

void UPawnCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	
}


void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	
}
