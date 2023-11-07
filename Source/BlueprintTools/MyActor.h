// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"



/**
 *  This enum lists the various motion methods of AI.
 */
UENUM(BlueprintType, DisplayName = "移动方式")
enum class EAI_Move :uint8
{
	EAM_Stop=0			UMETA(DisplayName = "不移动"),
	EAM_FollowSpline    UMETA(DisplayName = "沿着线走"),
	EAM_Forward			UMETA(DisplayName = "向前移动"),
	EAM_AIMove			UMETA(DisplayName = "追踪目标"),
	EAM_AIAndSpline		UMETA(DisplayName = "样条线ai混合"),
	EAM_patrol			UMETA(DisplayName = "巡逻")
};
/**
 *  This enum lists the various capabilities of the function box.
 */
UENUM(BlueprintType, DisplayName = "盒子工能")
enum class EBox_Ability :uint8
{
	EBA_Destroy			UMETA(DisplayName = "销毁"),
	EBA_Harm			UMETA(DisplayName = "伤害"),
	EBA_SetSpeed		UMETA(DisplayName = "修改速度"),
	EBA_SetRotation		UMETA(DisplayName = "修改角度"),
	EBA_SetVisible		UMETA(DisplayName = "设置显示"),
	EBA_SetMoveMode		UMETA(DisplayName = "设置移动方式"),
	EBA_HitFly			UMETA(DisplayName = "击飞")
};

UENUM(BlueprintType, DisplayName = "AI阵营")
enum class EAscription :uint8
{
	E_Red     UMETA(DisplayName = "红色"),
	E_Blue	  UMETA(DisplayName = "蓝色")
};

USTRUCT(BlueprintType, DisplayName = "击飞设置")
struct FHitFlyData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "是否击飞")
		bool bFly = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "击飞力度",
		meta = (EditCondition = "bFly", EditConditionHides))
		float fHitFlyStrength = 1.0f;

};


USTRUCT(BlueprintType, DisplayName = "特效设置")
struct FParticleData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "是否播放特效")
		bool bPlay = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "特效大小",
		meta = (EditCondition = "bPlay", EditConditionHides))
		FVector FX_Size;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "特效",
		meta = (EditCondition = "bPlay", EditConditionHides))
		UParticleSystem* Particle;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "Niagara",
		meta = (EditCondition = "bPlay", EditConditionHides))
		UNiagaraSystem* BulletNia;

	
};


USTRUCT(BlueprintType, DisplayName = "AI数据")
struct FCppAiData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "模型最大系数")
		float MeshMaxSize = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "模型最小系数")
		float MeshMinSize = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "模型消失时间")
		FVector2D ModelDisappearancetime=FVector2D(1.0F,2.0F);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "生命值")
		int32 HP = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "移动方式")
		EAI_Move AiMoveType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "ai寻路速度",
	meta=(EditCondition = "(AiMoveType == EAI_Move::EAM_AIMove)||(AiMoveType == EAI_Move::EAM_patrol)||(AiMoveType == EAI_Move::EAM_AIAndSpline)", EditConditionHides))
		float AiMoveSpeed = 500.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "直线移动速度",
		meta = (EditCondition = "AiMoveType == EAI_Move::EAM_Forward", EditConditionHides))
		float MoveSpeed = 5.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "样条线移动速度",
		meta = (EditCondition = "AiMoveType == EAI_Move::EAM_FollowSpline", EditConditionHides))
		float SplineMoveSpeed = 0.1f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "是否有武器")
		bool bWeapon = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "寻敌视野",
		meta = (EditCondition = "bWeapon", EditConditionHides))
		float VisualField = 300.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "模型")
		TArray<USkeletalMesh*> AIMesh;

	UPROPERTY(BlueprintReadWrite, Category = UAnimInstance, EditAnywhere, DisplayName = "动画蓝图组")
		TArray<TSubclassOf<UAnimInstance>> AnimationBPs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "阵营")
		EAscription Ascription;

	UPROPERTY(BlueprintReadWrite, Category = AActor, EditAnywhere, DisplayName = "蓝图")
		TSubclassOf<AActor> BpClass;

	UPROPERTY(BlueprintReadWrite, Category = AActor, EditAnywhere, DisplayName = "AI目标")
		AActor* AIMoveTarget;

};


UCLASS()
class BLUEPRINTTOOLS_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
