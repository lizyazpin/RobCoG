// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROSBridgeHandler.h"
#include "ROSAddTwoIntsServiceClient.generated.h"

UCLASS()
class ROBCOG_API AROSAddTwoIntsServiceClient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AROSAddTwoIntsServiceClient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when game ends or actor deleted
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "ROS Service Server")
	FString IPAddress;

	UPROPERTY(EditAnywhere, Category = "ROS Service Server")
	uint32 Port;

	UPROPERTY(EditAnywhere, Category = "ROS Service Server")
	FString Name;

private:
	// ROS Bridge handler
	TSharedPtr<FROSBridgeHandler> ROSHandler;	
};
