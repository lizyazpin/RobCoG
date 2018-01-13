// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "ROSStringSubscriber.h"
#include "ROSStringSubscriberCallback.h"
#include "std_msgs/String.h"


// Sets default values
AROSStringSubscriber::AROSStringSubscriber()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IPAddress = TEXT("127.0.0.1");

	// Set Port to 9090
	Port = 9090;

	// Set rostopic name which publish strings
	Topic = TEXT("ROSString");
}

// Called when the game starts or when spawned
void AROSStringSubscriber::BeginPlay()
{
	Super::BeginPlay();

	// Set websocket server address to default
	Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(IPAddress, Port));

	// Create subscriber with callback class
	Subscriber = MakeShareable<FROSStringSubscriberCallback>(new FROSStringSubscriberCallback(Topic));
	
	// Add subscriber to ros handler
	Handler->AddSubscriber(Subscriber);

	//Connect to rosbridge
	Handler->Connect();	
}

// Called when the game starts or when spawned
void AROSStringSubscriber::EndPlay(const EEndPlayReason::Type Reason)
{
	// Disconnect the handler
	Handler->Disconnect();
	Super::EndPlay(Reason);
}

// Called every frame
void AROSStringSubscriber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Tick handler
	Handler->Process();
}


