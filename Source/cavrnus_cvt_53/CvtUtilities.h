// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CvtUtilities.generated.h"

UCLASS(Abstract)
class UCvtUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FTransform JsonObjectToFTransform(TSharedPtr<FJsonObject> JsonObject, bool& Success);
	static FVector JsonObjectToFVector(TSharedPtr<FJsonObject> JsonObject, bool& Success);
	static FQuat JsonObjectToFQuat(TSharedPtr<FJsonObject> JsonObject, bool& Success);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Exec, Category = "Cavrnus",
		meta = (ToolTip = "Convert JSON string to an array of FTransforms", ShortToolTip = "Convert JSON string to an array of FTransforms"))
	static TArray<FTransform> JsonStringToFTransformArray(const FString& JsonStr, const FString& FieldName, bool& Success);

	UFUNCTION(BlueprintCallable, CallInEditor, Exec, Category = "Cavrnus",
	meta = (ToolTip = "Convert JSON string to an array of FStrings", ShortToolTip = "Convert JSON string to an array of FStrings"))
	static TArray<FString> JsonStringToFStringArray(const FString& JsonStr, const FString& FieldName, bool& Success);
};