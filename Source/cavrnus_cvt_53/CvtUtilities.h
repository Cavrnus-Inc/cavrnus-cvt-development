// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CvtUtilities.generated.h"

USTRUCT(BlueprintType)
struct FCvtSaveGameData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString SlotName;

	UPROPERTY(BlueprintReadWrite, Category = "Transform Command")
	TArray<FString> ActorNames;
	UPROPERTY(BlueprintReadWrite, Category = "Transform Command")
	TArray<FTransform> ActorTransforms;

	UPROPERTY(BlueprintReadWrite, Category = "XRay Command")
	TArray<FString> XRayNames;

	UPROPERTY(BlueprintReadWrite, Category = "Dimension Command")
	TArray<FVector> DimensionControlLocations;

	UPROPERTY(BlueprintReadWrite, Category = "Annotaion Command")
	TArray<FTransform> AnnotationPointTransforms;
	UPROPERTY(BlueprintReadWrite, Category = "Annotaion Command")
	TArray<int32> AnnotationLastIndices;
	UPROPERTY(BlueprintReadWrite, Category = "Annotaion Command")
	TArray<FLinearColor> AnnotationColors;
	UPROPERTY(BlueprintReadWrite, Category = "Annotaion Command")
	TArray<FText> AnnotationTexts;
	UPROPERTY(BlueprintReadWrite, Category = "Annotaion Command")
	TArray<FVector> AnnotationTextLocations;
	UPROPERTY(BlueprintReadWrite, Category = "Annotaion Command")
	TArray<FVector> AnnotationTargetLocations;
};

UCLASS(Abstract)
class UCvtUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FTransform JsonObjectToFTransform(TSharedPtr<FJsonObject> JsonObject, bool& Success);
	static FVector JsonObjectToFVector(TSharedPtr<FJsonObject> JsonObject, bool& Success);
	static FQuat JsonObjectToFQuat(TSharedPtr<FJsonObject> JsonObject, bool& Success);

	UFUNCTION(BlueprintCallable, CallInEditor, Exec, Category = "Cavrnus",
		meta = (ToolTip = "Convert SaveData to Json", ShortToolTip = "Serialize CVT SaveGameData"))
	static FString SerializeSaveGameData(const FCvtSaveGameData& InData, bool& Success);

	UFUNCTION(BlueprintCallable, CallInEditor, Exec, Category = "Cavrnus",
		meta = (ToolTip = "Convert Json to SaveGameData", ShortToolTip = "Dsserialize SaveGameData"))
	static FCvtSaveGameData DeserializeSaveGameData(const FString& InData, bool& Success);

	UFUNCTION(BlueprintCallable, CallInEditor, Exec, Category = "Cavrnus",
		meta = (ToolTip = "Convert JSON string to an array of FTransforms", ShortToolTip = "Convert JSON string to an array of FTransforms"))
	static TArray<FTransform> JsonStringToFTransformArray(const FString& JsonStr, const FString& FieldName, bool& Success);

	UFUNCTION(BlueprintCallable, CallInEditor, Exec, Category = "Cavrnus",
	meta = (ToolTip = "Convert JSON string to an array of FStrings", ShortToolTip = "Convert JSON string to an array of FStrings"))
	static TArray<FString> JsonStringToFStringArray(const FString& JsonStr, const FString& FieldName, bool& Success);
};