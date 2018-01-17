// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "ROSBridgeSrvClient.h"
#include "beginner_tutorials/AddTwoInts.h"

class FROSAddTwoIntsClient final : public FROSBridgeSrvClient
{
public:
    FROSAddTwoIntsClient(FString Name):
        FROSBridgeSrvClient(Name, TEXT("beginner_tutorials/AddTwoInts"))
    {

    }

    void Callback(TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest, TSharedPtr<FROSBridgeSrv::SrvResponse> InResponse) const override
    {
        TSharedPtr<beginner_tutorials::AddTwoInts::Request> Request =
            StaticCastSharedPtr<beginner_tutorials::AddTwoInts::Request>(InRequest);
        TSharedPtr<beginner_tutorials::AddTwoInts::Response> InResponse=
            StaticCastSharedPtr<beginner_tutorials::AddTwoInts::Response>(InResponse);
        UE_LOG(LogTemp, Log, TEXT("Add Two Ints: %d + %d = %d"),
			Request->GetA(), Request->GetB(), InResponse->GetSum());
    }
};
