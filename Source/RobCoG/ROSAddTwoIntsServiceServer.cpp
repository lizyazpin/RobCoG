// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

#include "ROSAddTwoIntsServiceServer.h"
#include "ROSAddTwoIntsServer.h"


// Sets default values
AROSAddTwoIntsServiceServer::AROSAddTwoIntsServiceServer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Default IP localhost
	IPAddress = TEXT("127.0.0.1");

	// Set Port to 9090
	Port = 9090;

	// Set ROS topic name which publish strings
	Name = TEXT("add_two_ints");
}

// Called when the game starts or when spawned
void AROSAddTwoIntsServiceServer::BeginPlay()
{
	Super::BeginPlay();
	
	// Set websocket server address to default
	ROSHandler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(IPAddress, Port));

	// Connect to rosbridge
	ROSHandler->Connect();

	// Add service clients and servers
	TSharedPtr<FROSAddTwoIntsServer> ServiceServer = 
		MakeShareable<FROSAddTwoIntsServer>(new FROSAddTwoIntsServer(this, Name, TEXT("rospy_tutorials/AddTwoInts")));
	ROSHandler->AddServiceServer(ServiceServer);
}

// Called when game ends or actor deleted
void AROSAddTwoIntsServiceServer::EndPlay(const EEndPlayReason::Type Reason)
{
	// Disconnect the handler before parent ends
	ROSHandler->Disconnect();
	Super::EndPlay(Reason);
}

// Called every frame
void AROSAddTwoIntsServiceServer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

