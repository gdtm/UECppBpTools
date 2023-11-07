// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character_Data.h"
#include "Character_Ability.generated.h"

/**
 *
 */
UCLASS()
class ACharacter_Ability : public ACharacter_Data
{
	GENERATED_BODY()

public:
	ACharacter_Ability();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
		FVector forwardMoveSpeed;

	UFUNCTION(BlueprintCallable)
		bool InitAIData();

	UFUNCTION(BlueprintCallable)
		bool SetMoveType();

	UFUNCTION(BlueprintCallable)
		bool BeginAiMove();

	UFUNCTION()
		bool BeginAiForwardMove();

	UFUNCTION()
		bool BeginAipatrolMove();

	UFUNCTION()
		bool BeginAIAndSplineMove();

	UFUNCTION()
		bool BeginAiFollowSplineMove();


};
