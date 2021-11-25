// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultMaterial = CreateDefaultSubobject<UMaterial>(TEXT("DefaultMaterial"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetMaterial(0, DefaultMaterial);
	RootComponent = MeshComp;


	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForceComp"));
	ForceComp->SetupAttachment(MeshComp);
	ForceComp->Radius = 750;
	ForceComp->ImpulseStrength = 2500;
	ForceComp->bImpulseVelChange = true;
	ForceComp->SetAutoActivate(false);

	DestroyedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("DestroyedMaterial"));


}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->SetMaterial(0, DefaultMaterial);
	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::MyMeshComponentHit);


		
}

void ASExplosiveBarrel::MyMeshComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{



	AActor* MyOwner = GetOwner();
	
	MeshComp->SetMaterial(0, DestroyedMaterial);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EffectComp, GetActorLocation(), GetActorRotation());

	ForceComp->FireImpulse();

	SetLifeSpan(3);



}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

