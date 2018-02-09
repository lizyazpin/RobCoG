// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "ROSBridgeSrvServer.h"
#include "rospy_tutorials/AddTwoInts.h"

class FROSAddTwoIntsServer final : public FROSBridgeSrvServer
{
public:
    FROSAddTwoIntsServer(AActor* InOwner, const FString& InName, const FString& InType):
        FROSBridgeSrvServer(InName, InType)
    {
		Owner = InOwner;
    }

    TSharedPtr<FROSBridgeSrv::SrvRequest> FromJson(TSharedPtr<FJsonObject> JsonObject) const override
    {
        TSharedPtr<rospy_tutorials::AddTwoInts::Request> Request =
            MakeShareable(new rospy_tutorials::AddTwoInts::Request());
        Request->FromJson(JsonObject);
        return TSharedPtr<FROSBridgeSrv::SrvRequest>(Request);
    }

    TSharedPtr<FROSBridgeSrv::SrvResponse> Callback(TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest) override
    {
        TSharedPtr<rospy_tutorials::AddTwoInts::Request> Request =
            StaticCastSharedPtr<rospy_tutorials::AddTwoInts::Request>(InRequest);

        int64 Sum = Request->GetA() + Request->GetB();

        UE_LOG(LogTemp, Log, TEXT("[%s] In actor %s: Service [%s] Server: Add Two Ints: %d + %d = %d"),
			*FString(__FUNCTION__), *Owner->GetName(), *Name, Request->GetA(), Request->GetB(), Sum);

        return MakeShareable<FROSBridgeSrv::SrvResponse>
                (new rospy_tutorials::AddTwoInts::Response(Sum));
    }

private:
	AActor* Owner;
};
