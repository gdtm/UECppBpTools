// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Ability.h"

#include "AIController.h"

#include "Components/CapsuleComponent.h"


ACharacter_Ability::ACharacter_Ability()
{


}

void ACharacter_Ability::BeginPlay()
{
	Super::BeginPlay();

	this->SetMoveType();

}

void ACharacter_Ability::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((EMoveType==EAI_Move::EAM_Forward)&&(bIsMove==true))
	{
		this->AddActorWorldOffset(forwardMoveSpeed);
	}
}

void ACharacter_Ability::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ACharacter_Ability::InitAIData()
{
	/*
	 * 读取模型数据，加载模型
	 */
	bool bSetMsehOk = false;
	int32 number = FMath::RandRange(0, FAiData.AIMesh.Num() - 1);
	if (FAiData.AIMesh.Num() > 0)
	{
		//UE_LOG(LogTemp, Log, TEXT("随机数%d"), number);
		AIMesh = FAiData.AIMesh[number];
		if (AIMesh)
		{
			this->GetMesh()->SetSkeletalMesh(AIMesh);
			bSetMsehOk = true;
		}
	}
	/*
	 * 设置动画蓝图
	 */
	bool bSetAnimaBpOk = false;
	if (FAiData.AnimationBPs.Num() != 0)
	{
		if (FAiData.AnimationBPs.Num() == 1)
		{
			this->GetMesh()->SetAnimInstanceClass(FAiData.AnimationBPs[0]);
			bSetAnimaBpOk = true;
		}
		else if (FAiData.AnimationBPs.Num() == FAiData.AIMesh.Num())
		{
			this->GetMesh()->SetAnimInstanceClass(FAiData.AnimationBPs[number]);
			bSetAnimaBpOk = true;
		}
	}
	/*
	 * 设置模型大小
	 */
	float fNumber = FMath::RandRange(FAiData.MeshMinSize, FAiData.MeshMaxSize);
	if (FAiData.MeshMaxSize != FAiData.MeshMinSize)
	{
		this->GetCapsuleComponent()->SetWorldScale3D(FVector(fNumber));
		this->GetMesh()->SetWorldScale3D(FVector(fNumber));
		this->GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}
	else if (FAiData.MeshMaxSize == FAiData.MeshMinSize)
	{
		this->GetCapsuleComponent()->SetWorldScale3D(FVector(FAiData.MeshMaxSize));
		this->GetMesh()->SetWorldScale3D(FVector(FAiData.MeshMaxSize));
		this->GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}
	else
	{
		this->GetMesh()->SetWorldScale3D(FVector(1.0f));
		this->GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}
/*
 * 设置目标蓝图
 */
	bool bIsTarget = false;
	if (FAiData.AIMoveTarget)
	{
		AIMoveTarget = FAiData.AIMoveTarget;

		bIsTarget =true;

	}




	return bSetAnimaBpOk && bSetMsehOk;
}

bool ACharacter_Ability::SetMoveType()
{
	this->EMoveType = FAiData.AiMoveType;

	switch (EMoveType)
	{
	case EAI_Move::EAM_Stop:
		this->bIsMove = false;
		UE_LOG(LogTemp,Log,TEXT("EAM_Stop"));
		break;
	case EAI_Move::EAM_AIMove:
		this->BeginAiMove();
		UE_LOG(LogTemp, Log, TEXT("EAM_AIMove"));
		break;
	case EAI_Move::EAM_Forward:
		this->BeginAiForwardMove();
		UE_LOG(LogTemp, Log, TEXT("EAM_Forward"));
		break;
	case EAI_Move::EAM_patrol:
		this->BeginAipatrolMove();
		UE_LOG(LogTemp, Log, TEXT("EAM_patrol"));
		break;
	case EAI_Move::EAM_AIAndSpline:
		this->BeginAIAndSplineMove();
		UE_LOG(LogTemp, Log, TEXT("EAM_AIAndSpline"));
		break;
	case EAI_Move::EAM_FollowSpline:
		this->BeginAiFollowSplineMove();
		UE_LOG(LogTemp, Log, TEXT("EAM_FollowSpline"));
		break;
	default:
		return false;
	}


	return true;
}

bool ACharacter_Ability::BeginAiMove()
{
	this->bIsMove = true;
	UE_LOG(LogTemp, Log, TEXT("aimoveisok1"));
	if (AIMoveTarget)
	{
		UE_LOG(LogTemp, Log, TEXT("aimoveisok2"));

		if (EMoveType == EAI_Move::EAM_AIMove)
		{
			if (this->GetController())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToActor(this->GetController(), AIMoveTarget);
				//EPathFollowingRequestResult reTagt = Cast<AAIController>(this->GetController())->MoveToActor(AIMoveTarget);
				//return true;

			}
		}

	}



	return false;
}

bool ACharacter_Ability::BeginAiForwardMove()
{
	this->bIsMove = true;
	FVector Speed= this->GetActorForwardVector();
	Speed.Normalize();
	forwardMoveSpeed = FVector(Speed.X* MoveSpeed,Speed.Y* MoveSpeed,Speed.Z* MoveSpeed);
	UE_LOG(LogTemp, Log, TEXT("1111111") );
	return false;
}

bool ACharacter_Ability::BeginAipatrolMove()
{
	this->bIsMove = true;
	return false;
}

bool ACharacter_Ability::BeginAIAndSplineMove()
{
	this->bIsMove = true;
	return false;
}

bool ACharacter_Ability::BeginAiFollowSplineMove()
{
	this->bIsMove = true;
	return false;
}
