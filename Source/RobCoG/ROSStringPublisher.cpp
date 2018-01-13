// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "ROSStringPublisher.h"
#include "std_msgs/String.h"


// Sets default values
AROSStringPublisher::AROSStringPublisher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set websocket server address to the ros IP address
	IPAddress = TEXT("127.0.0.1");

	// Set Port to 9090
	Port = 9090;
	
	// Set rostopic name which publish strings
	Topic = TEXT("UnrealString");
}

// Called when the game starts or when spawned
void AROSStringPublisher::BeginPlay()
{
	Super::BeginPlay();

	// Set websocket server address to default
	Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(IPAddress, Port));

	// **** Create publishers here ****
	Publisher = MakeShareable<FROSBridgePublisher>(
		new FROSBridgePublisher(TEXT("std_msgs/String"), Topic));
	Handler->AddPublisher(Publisher);	

	//Connect to ROSBridge Websocket server.
	Handler->Connect();	
}

// Called when game ends or actor deleted
void AROSStringPublisher::EndPlay(const EEndPlayReason::Type Reason)
{
	// Disconnect the handler before parent ends
	Handler->Disconnect();
	Super::EndPlay(Reason);
}


// Called every frame
void AROSStringPublisher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Create and set string msg
	TSharedPtr<std_msgs::String> UnrealString = MakeShareable(
		new std_msgs::String());
	UnrealString->SetData("Hello World");

	// Send msg to ROS
	Handler->PublishMsg(Topic, UnrealString);
	UE_LOG(LogTemp, Log, TEXT("Sending string msg to ROS: %s"), *UnrealString->ToString());

	// Process messages
	Handler->Process();
}


