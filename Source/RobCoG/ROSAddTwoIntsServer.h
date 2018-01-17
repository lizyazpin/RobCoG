// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "ROSBridgeSrvServer.h"
#include "beginner_tutorials/AddTwoInts.h"

class FROSAddTwoIntsServer final : public FROSBridgeSrvServer
{
public:
    FROSAddTwoIntsServer(FString Name):
        FROSBridgeSrvServer(Name, TEXT("beginner_tutorials/AddTwoInts"))
    {

    }

    TSharedPtr<FROSBridgeSrv::SrvRequest> FromJson(TSharedPtr<FJsonObject> JsonObject) const override
    {
        TSharedPtr<beginner_tutorials::AddTwoInts::Request> Request_ =
            MakeShareable(new beginner_tutorials::AddTwoInts::Request());
        Request_->FromJson(JsonObject);
        return TSharedPtr<FROSBridgeSrv::SrvRequest>(Request_);
    }

    TSharedPtr<FROSBridgeSrv::SrvResponse> Callback(TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest) override
    {
        TSharedPtr<beginner_tutorials::AddTwoInts::Request> Request =
            StaticCastSharedPtr<beginner_tutorials::AddTwoInts::Request>(InRequest);

        int64 Sum = Request->GetA() + Request->GetB();
        UE_LOG(LogTemp, Log, TEXT("Service [%s] Server: Add Two Ints: %d + %d = %d"),
			*Name, Request->GetA(), Request->GetB(), Sum);

        return MakeShareable<FROSBridgeSrv::SrvResponse>
                (new beginner_tutorials::AddTwoInts::Response(Sum));
    }
};
