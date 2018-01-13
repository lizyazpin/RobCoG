// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROSBridgeHandler.h"
#include "ROSStringSubscriber.generated.h"

UCLASS()
class ROBCOG_API AROSStringSubscriber : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AROSStringSubscriber();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when game ends or actor deleted
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "ROS Subscriber")
	FString IPAddress;

	UPROPERTY(EditAnywhere, Category = "ROS Subscriber")
	uint32 Port;

	UPROPERTY(EditAnywhere, Category = "ROS Subscriber")
	FString Topic;

private:
	// Add a smart pointer to ROSBridgeHandler
	TSharedPtr<FROSBridgeHandler> Handler;

	// Add a ROSBridgePublisher smart pointer
	TSharedPtr<FROSBridgeSubscriber> Subscriber;	
};
