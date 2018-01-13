// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "ROSStringSubscriberCallback.h"

FROSStringSubscriberCallback::FROSStringSubscriberCallback(FString InTopic) :
	FROSBridgeSubscriber(TEXT("std_msgs/String"), InTopic) 
{
}

FROSStringSubscriberCallback::~FROSStringSubscriberCallback()
{
}

TSharedPtr<FROSBridgeMsg> FROSStringSubscriberCallback::ParseMessage
(TSharedPtr<FJsonObject> JsonObject) const
{
	TSharedPtr<std_msgs::String> StringMessage =
		MakeShareable<std_msgs::String>(new std_msgs::String());
	StringMessage->FromJson(JsonObject);
	return StaticCastSharedPtr<FROSBridgeMsg>(StringMessage);
}

void FROSStringSubscriberCallback::CallBack(TSharedPtr<FROSBridgeMsg> Msg)
{
	TSharedPtr<std_msgs::String> StringMessage = StaticCastSharedPtr<std_msgs::String>(Msg);
	// downcast to subclass using StaticCastSharedPtr function

	UE_LOG(LogTemp, Log, TEXT("Message received! Content: %s"), *StringMessage->GetData());
	// do something with the message

	return;
}
