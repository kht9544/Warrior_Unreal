// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    UE_LOG(LogTemp, Error, TEXT("Your message"));
}