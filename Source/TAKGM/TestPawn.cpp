// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ATestPawn::ATestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector(-300.0f, 0.0f, 300.0f));
	Camera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CurrentVelocity = FVector(0.f);
	MaxSpeed = 100.f;

}

// Called when the game starts or when spawned
void ATestPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATestPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATestPawn::MoveRight);

}

void ATestPawn::MoveForward(float value)
{
	CurrentVelocity.X = FMath::Clamp(value, -1.f, 1.f) * MaxSpeed;
}
void ATestPawn::MoveRight(float value)
{
	CurrentVelocity.Y = FMath::Clamp(value, -1.f, 1.f) * MaxSpeed;
}

