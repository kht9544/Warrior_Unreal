// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WarriorWeaponBase.h"
#include "Components/BoxComponent.h"
#include "WarriorFunctionLibrary.h"

#include "WarriorDebugHelper.h"

// Sets default values
AWarriorWeaponBase::AWarriorWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaeponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaeponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWarriorWeaponBase::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddDynamic(this, &AWarriorWeaponBase::OnCollisionBoxEndOverlap);

}

void AWarriorWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn,TEXT("Weapon has no owning pawn"));

	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if(UWarriorFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}
	}

}

void AWarriorWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn,TEXT("Weapon has no owning pawn"));

	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if(UWarriorFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}


