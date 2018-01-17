// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RRobot.h"
#include "ROSBridgeHandler.h"
#include "ROSBridgeSubscriber.h"
#include "sensor_msgs/JointState.h"

class FRobotForceSubscriberCallback : public FROSBridgeSubscriber 
{

public:
    ARRobot* Robot;

    FRobotForceSubscriberCallback(FString InTopic, ARRobot* InRobot) :
        FROSBridgeSubscriber(TEXT("sensor_msgs/JointState"), InTopic)
    {
        Robot = InRobot;
    }

    ~FRobotForceSubscriberCallback() override {};

    TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override
    {
        TSharedPtr<FROSBridgeMsgSensormsgsJointState> JointStateMessage =
            MakeShareable<FROSBridgeMsgSensormsgsJointState>(new FROSBridgeMsgSensormsgsJointState());
        JointStateMessage->FromJson(JsonObject);

        return StaticCastSharedPtr<FROSBridgeMsg>(JointStateMessage);
    }

    void Callback(TSharedPtr<FROSBridgeMsg> msg) override
    {
        TSharedPtr<FROSBridgeMsgSensormsgsJointState> JointStateMessage = StaticCastSharedPtr<FROSBridgeMsgSensormsgsJointState>(msg);

        TArray<FString> ListJointName = JointStateMessage->GetName();
        TArray<double> ListJointForce = JointStateMessage->GetEffort();
        UE_LOG(LogTemp, Warning, TEXT("ListJointName.Num() = %d"), ListJointName.Num());

        checkf(ListJointName.Num() == ListJointForce.Num(), TEXT("Error: Length of JointName and JointForce aren't equal."));

        for (int i = 0; i < ListJointName.Num(); i++)
        {
            FString JointName = ListJointName[i];
            double JointEffort = ListJointForce[i];
            Robot->AddForceToJoint(JointName, JointEffort * 10000);
        }
        return;
    }

};
