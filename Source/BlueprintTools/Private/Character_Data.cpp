// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Data.h"

// Sets default values
ACharacter_Data::ACharacter_Data()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AIMesh = FAiData.AIMesh.;


}

// Called when the game starts or when spawned
void ACharacter_Data::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("222%d"),FAiData.AIMesh.Num());
}

// Called every frame
void ACharacter_Data::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Data::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

