// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyCpp.h"
#include "TestActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStudyCpp::AStudyCpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStudyCpp::BeginPlay()
{
	Super::BeginPlay();


	ATestActor* actor1= Cast<ATestActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass
	(this,ATestActor::StaticClass(),this->GetActorTransform()));

	if (actor1)
	{
		actor1->testFloat = 9.9f;
	}

	UGameplayStatics::FinishSpawningActor(actor1,this->GetActorTransform());

	GetWorldTimerManager().SetTimer(TimerHandle,this,&AStudyCpp::AdvanceTimer,1.0f,true);

	

}

// Called every frame
void AStudyCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStudyCpp::AdvanceTimer()
{
	UE_LOG(LogTemp,Log,TEXT("测试"));
}

