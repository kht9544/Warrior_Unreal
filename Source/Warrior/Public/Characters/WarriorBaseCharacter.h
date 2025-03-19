// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "WarriorBaseCharacter.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorAttributeSet;
class UDataAsset_StartUpDataBase;

UCLASS()
class WARRIOR_API AWarriorBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarriorBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AbilitySystem")
	UWarriorAbilitySystemComponent* WarriorAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AbilitySystem")
	UWarriorAttributeSet* WarriorAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;


	// Synchronous Load(동기): 스레드를 차단(로딩 될 때까지 정지) / 로딩 중인 객체를 바로 검색 가능
	// 장점: 로딩이 완료될 때까지 기다리므로, 로딩된 객체를 즉시 사용할 수 있다.
	// 단점: 로딩이 완료될 때까지 게임이 멈추므로, 로딩 시간이 길어질 경우 사용자 경험이 저하될 수 있다.

	// Asynchronous Load(비동기): 백그라운드에서 로드(정지x) / 로딩 중인 객체를 바로 검색 불가
	// 장점: 로딩 중에도 게임이 계속 진행되므로, 사용자 경험이 저하되지 않는다.
	// 단점: 로딩이 완료되기 전까지 객체를 사용할 수 없으므로, 로딩 완료를 확인하는 추가 로직이 필요하다.



public:
	FORCEINLINE UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponent() const {return WarriorAbilitySystemComponent;}
	
	FORCEINLINE UWarriorAttributeSet* GetWarriorAttributeSet()const { return WarriorAttributeSet;}

	

	/*EINLINE은 함수를 강제적으로 inline화 시킨다. 
	inline화란 컴파일 단계에서 컴파일러가 함수 호출 지점에 함수 내용을 갖다 붙이는 것을 말한다. 
	왜냐하면, 간단한 함수의 경우(한 줄짜리 getter, setter 등) 함수를 호출하는 데 발생하는 오버헤드가 함수 자리에 함수 내용이 
	작성되어 있는 것보다 효율성이 좋지 않을 수 있기 때문이다
	*/
};
