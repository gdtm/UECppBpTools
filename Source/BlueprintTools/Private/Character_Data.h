// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintTools/MyActor.h"
#include "GameFramework/Character.h"
#include "Character_Data.generated.h"

UCLASS()
class ACharacter_Data : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Data();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, DisplayName = "移动方式")
		EAI_Move EMoveType = EAI_Move::EAM_Stop;

	UPROPERTY(BlueprintReadWrite, DisplayName = "是否在移动")
		bool bIsMove;

	UPROPERTY(BlueprintReadWrite, DisplayName = "是否有武器")
		bool bHaveWeapons;

	UPROPERTY(BlueprintReadWrite, DisplayName = "阵营归属")
		EAscription EClique = EAscription::E_Blue;

	UPROPERTY(BlueprintReadWrite, DisplayName = "模型消失时间")
		FVector2D ModelDisappearancetime = FVector2D(1.0F, 2.0F);

	UPROPERTY(BlueprintReadWrite, DisplayName = "HP")
		float healthValue = 5.0f;

	UPROPERTY(BlueprintReadWrite, DisplayName = "ai寻路速度",
		meta = (EditCondition = "(EMoveWay == EAI_Move::EAM_AIMove)||(EMoveWay == EAI_Move::EAM_patrol)||(EMoveWay == EAI_Move::EAM_AIAndSpline)", EditConditionHides))
		float AiMoveSpeed = 500.0f;

	UPROPERTY(BlueprintReadWrite, DisplayName = "直线移动速度",
		meta = (EditCondition = "EMoveWay == EAI_Move::EAM_Forward", EditConditionHides))
		float MoveSpeed = 5.0f;

	UPROPERTY(BlueprintReadWrite, DisplayName = "样条线移动速度",
		meta = (EditCondition = "EMoveWay == EAI_Move::EAM_FollowSpline", EditConditionHides))
		float SplineMoveSpeed = 0.1f;

	UPROPERTY(BlueprintReadWrite, DisplayName = "模型")
		USkeletalMesh* AIMesh;

	UPROPERTY(BlueprintReadWrite, DisplayName = "动画蓝图")
		UAnimInstance* AnimationBP;

	UPROPERTY(BlueprintReadWrite, DisplayName = "AI目标")
		AActor* AIMoveTarget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "AI数据")
		FCppAiData FAiData;
};
