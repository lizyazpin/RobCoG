// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROSBridgeHandler.h"
#include "ROSBridgePublisher.h"
#include "ROSStringPublisher.generated.h"

UCLASS()
class ROBCOG_API AROSStringPublisher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AROSStringPublisher();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when game ends or actor deleted
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	FString IPAddress;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	uint32 Port;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	FString Topic;

private:
	// Add a smart pointer to ROSBridgeHandler
	TSharedPtr<FROSBridgeHandler> Handler;

	// Add a ROSBridgePublisher smart pointer
	TSharedPtr<FROSBridgePublisher> Publisher;	
};
