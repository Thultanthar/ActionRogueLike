// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"
//#include "Kismet/GameplayStatics.h"


// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	
	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::BeginJump()
{
	Jump();
}

void ASCharacter::EndJump()
{
	StopJumping();
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector() * Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	//x = forward (red)
	//y = right (Green)
	//z = up(Blue
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);


}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	//FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	//GetControlRotation()

	FMinimalViewInfo CameraViewInfo;
	CameraComp->GetCameraView(1.0f, CameraViewInfo);
	FVector CameraLocation = CameraViewInfo.Location;
	FRotator CameraRotation = CameraViewInfo.Rotation;

	FTransform CameraTM = FTransform(CameraRotation, CameraLocation);
	//FTransform SpawnTM = FTransform(GetControlRotation(),HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	//SpawnTM
	GetWorld()->SpawnActor<AActor>(PrimaryAttackClass, CameraTM, SpawnParams);
}

void ASCharacter::Attack1()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_Attack1, this, &ASCharacter::Attack1_TimeElapsed, 0.2f);
}

void ASCharacter::Attack1_TimeElapsed()
{
	//FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FMinimalViewInfo CameraViewInfo;
	CameraComp->GetCameraView(1.0f, CameraViewInfo);
	FVector CameraLocation = CameraViewInfo.Location;
	FRotator CameraRotation = CameraViewInfo.Rotation;

	FTransform CameraTM = FTransform(CameraRotation, CameraLocation);

	//FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	//CameraTM
	GetWorld()->SpawnActor<AActor>(Attack1Class, CameraTM, SpawnParams);
}

void ASCharacter::Ability1()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_Ability1, this, &ASCharacter::Ability1_TimeElapsed, 0.2f);
}

void ASCharacter::Ability1_TimeElapsed()
{
	FMinimalViewInfo CameraViewInfo;
	CameraComp->GetCameraView(1.0f, CameraViewInfo);
	FVector CameraLocation = CameraViewInfo.Location;
	FRotator CameraRotation = CameraViewInfo.Rotation;

	FTransform CameraTM = FTransform(CameraRotation, CameraLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(Ability1Class, CameraTM, SpawnParams);
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp) 
	{
		InteractionComp->PrimaryInteract();
	}
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ASCharacter::BeginJump);
	PlayerInputComponent->BindAction("Jump",IE_Released, this, &ASCharacter::EndJump);

	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);

	//Attack
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &ASCharacter::Attack1);

	//Abilities
	PlayerInputComponent->BindAction("Ability1", IE_Pressed, this, &ASCharacter::Ability1);

	//Interact with Objects
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

}

