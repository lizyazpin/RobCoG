// Copyright 2017, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "GameModeTimePub.h"
#include "rosgraph_msgs/Clock.h"

AGameModeTimePub::AGameModeTimePub()
	: Super()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AGameModeTimePub::BeginPlay()
{
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(TEXT("127.0.0.1"), 9090));
    TimePublisher = MakeShareable<FROSBridgePublisher>(
		new FROSBridgePublisher(TEXT("rosgraph_msgs/Clock"), TEXT("clock")));
    Handler->AddPublisher(TimePublisher);
    Handler->Connect();
    UE_LOG(LogTemp, Log, TEXT("[%s] Websocket server connected."), *FString(__FUNCTION__));
}

void AGameModeTimePub::Tick(float DeltaSeconds)
{
    float GameTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
    uint64 GameSeconds = (int)GameTime;
    uint64 GameUseconds = (GameTime - GameSeconds) * 1000000000;
    TSharedPtr<rosgraph_msgs::Clock> Clock = MakeShareable
            (new rosgraph_msgs::Clock(FROSTime(GameSeconds, GameUseconds)));
    Handler->PublishMsg("clock", Clock);
	Handler->Process();
}

void AGameModeTimePub::Logout(AController *Exiting)
{
    Handler->Disconnect();
    AGameModeBase::Logout(Exiting);
}
