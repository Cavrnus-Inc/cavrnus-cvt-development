// Fill out your copyright notice in the Description page of Project Settings.


#include "CvtUtilities.h"

TArray<FTransform> UCvtUtilities::JsonStringToFTransformArray(const FString& JsonStr, const FString& FieldName,
                                                              bool& Success)
{
	TArray<FTransform> Transforms;
	TSharedPtr<FJsonObject> JsonObject;
	TArray<TSharedPtr<FJsonValue>> JsonTransforms;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonStr);
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		JsonTransforms = JsonObject->GetArrayField(FieldName);
		for (const TSharedPtr<FJsonValue>& TransformValue : JsonTransforms)
		{
			bool bSuccess = false;
			FTransform Transform = JsonObjectToFTransform(TransformValue->AsObject(), bSuccess);
			if (bSuccess)
			{
				Transforms.Add(Transform);
			}
		}
	}

	Success = JsonTransforms.Num() > 0 && Transforms.Num() == JsonTransforms.Num();
	return Transforms;
}

TArray<FString> UCvtUtilities::JsonStringToFStringArray(const FString& JsonStr, const FString& FieldName, bool& Success)
{
	TArray<FString> ReturnValue;
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonStr);
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		const TArray<TSharedPtr<FJsonValue>>* JsonArray;
		if (JsonObject->TryGetArrayField(FieldName, JsonArray))
		{
			for (const TSharedPtr<FJsonValue>& StringValue : *JsonArray)
			{
				FString FoundString = StringValue.Get()->AsString();
				ReturnValue.Add(FoundString);
			}
		}
	}

	Success = ReturnValue.Num() > 0;

	return ReturnValue;
}

FTransform UCvtUtilities::JsonObjectToFTransform(TSharedPtr<FJsonObject> JsonObject, bool& Success)
{
	FJsonObject* Data = JsonObject.Get();
	if (Data->Values.Num() == 3)
	{
		bool bTranslationSuccess = false;
		TSharedPtr<FJsonObject> TranslationObject = Data->Values["translation"]->AsObject();
		const FVector3d Translation = JsonObjectToFVector(TranslationObject, bTranslationSuccess);

		bool bRotationSuccess = false;
		TSharedPtr<FJsonObject> RotationObject = Data->Values["rotation"]->AsObject();
		const FQuat Rotation = JsonObjectToFQuat(RotationObject, bRotationSuccess);

		bool bScaleSuccess = false;
		TSharedPtr<FJsonObject> ScaleObject = Data->Values["scale3D"]->AsObject();
		const FVector3d Scale = JsonObjectToFVector(ScaleObject, bScaleSuccess);

		Success = bTranslationSuccess && bRotationSuccess && bScaleSuccess;
		return FTransform(Rotation, Translation, Scale);
	}

	return FTransform();
}

FVector UCvtUtilities::JsonObjectToFVector(TSharedPtr<FJsonObject> JsonObject, bool& Success)
{
	FJsonObject* Data = JsonObject.Get();
	if (Data->Values.Num() == 3)
	{
		double LocationX = Data->Values["x"]->AsNumber();
		double LocationY = Data->Values["y"]->AsNumber();
		double LocationZ = Data->Values["z"]->AsNumber();
		FVector3d Vector(LocationX, LocationY, LocationZ);

		Success = true;
		return Vector;
	}

	return FVector();
}

FQuat UCvtUtilities::JsonObjectToFQuat(TSharedPtr<FJsonObject> JsonObject, bool& Success)
{
	FJsonObject* Data = JsonObject.Get();
	if (Data->Values.Num() == 4)
	{
		double X = Data->Values["x"]->AsNumber();
		double Y = Data->Values["y"]->AsNumber();
		double Z = Data->Values["z"]->AsNumber();
		double W = Data->Values["w"]->AsNumber();
		FQuat Quaternion(X, Y, Z, W);

		Success = true;
		return Quaternion;
	}

	return FQuat();
}

FString UCvtUtilities::SerializeSaveGameData(const FCvtSaveGameData& InData, bool& Success)
{
	TArray<TSharedPtr<FJsonValue>> ActorNames;
	for (const FString& Element : InData.ActorNames)
		ActorNames.Add(MakeShareable(new FJsonValueString(Element)));

	TArray<TSharedPtr<FJsonValue>> ActorTransforms;
	for (const FTransform& Element : InData.ActorTransforms)
		ActorTransforms.Add(MakeShareable(new FJsonValueString(Element.ToString())));

	TArray<TSharedPtr<FJsonValue>> XRayNames;
	for (const FString& Element : InData.XRayNames)
		XRayNames.Add(MakeShareable(new FJsonValueString(Element)));

	TArray<TSharedPtr<FJsonValue>> DimensionControlLocations;
	for (const FVector& Element : InData.DimensionControlLocations)
		DimensionControlLocations.Add(MakeShareable(new FJsonValueString(Element.ToString())));

	TArray<TSharedPtr<FJsonValue>> AnnotationPointTransforms;
	for (const FTransform& Element : InData.AnnotationPointTransforms)
		AnnotationPointTransforms.Add(MakeShareable(new FJsonValueString(Element.ToString())));

	TArray<TSharedPtr<FJsonValue>> AnnotationLastIndices;
	for (const int32& Element : InData.AnnotationLastIndices)
		AnnotationLastIndices.Add(MakeShareable(new FJsonValueString(FString::FromInt(Element))));

	TArray<TSharedPtr<FJsonValue>> AnnotationColors;
	for (const FLinearColor& Element : InData.AnnotationColors)
		AnnotationColors.Add(MakeShareable(new FJsonValueString(Element.ToString())));

	TArray<TSharedPtr<FJsonValue>> AnnotationTexts;
	for (const FText& Element : InData.AnnotationTexts)
		AnnotationTexts.Add(MakeShareable(new FJsonValueString(Element.ToString())));

	TArray<TSharedPtr<FJsonValue>> AnnotationTextLocations;
	for (const FVector& Element : InData.AnnotationTextLocations)
		AnnotationTextLocations.Add(MakeShareable(new FJsonValueString(Element.ToString())));

	TArray<TSharedPtr<FJsonValue>> AnnotationTargetLocations;
	for (const FVector& Element : InData.AnnotationTargetLocations)
		AnnotationTargetLocations.Add(MakeShareable(new FJsonValueString(Element.ToString())));

	const TSharedRef<FJsonObject> JsonObject(new FJsonObject());
	JsonObject->SetArrayField("ActorNames", ActorNames);
	JsonObject->SetArrayField("ActorTransforms", ActorTransforms);
	JsonObject->SetArrayField("XRayNames", XRayNames);
	JsonObject->SetArrayField("DimensionControlLocations", DimensionControlLocations);
	JsonObject->SetArrayField("AnnotationPointTransforms", AnnotationPointTransforms);
	JsonObject->SetArrayField("AnnotationLastIndices", AnnotationLastIndices);
	JsonObject->SetArrayField("AnnotationColors", AnnotationColors);
	JsonObject->SetArrayField("AnnotationTexts", AnnotationTexts);
	JsonObject->SetArrayField("AnnotationTextLocations", AnnotationTextLocations);
	JsonObject->SetArrayField("AnnotationTargetLocations", AnnotationTargetLocations);

	FString Result;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Result);
	FJsonSerializer::Serialize(JsonObject, JsonWriter);

	Success = !Result.IsEmpty();

	return Result;
}

FCvtSaveGameData UCvtUtilities::DeserializeSaveGameData(const FString& InData, bool& Success)
{
	TSharedPtr<FJsonObject> json(new FJsonObject());
	TSharedRef<TJsonReader<FString::ElementType>> Reader = TJsonReaderFactory<FString::ElementType>::Create(InData);
	FJsonSerializer::Deserialize(Reader, json);

	FCvtSaveGameData ReturnData;

	TArray<TSharedPtr<FJsonValue>> ActorNames = json->GetArrayField("ActorNames");
	for (const TSharedPtr<FJsonValue>& Element : ActorNames)
	{
		ReturnData.ActorNames.Add(Element->AsString());
	}

	TArray<TSharedPtr<FJsonValue>> ActorTransforms = json->GetArrayField("ActorTransforms");
	for (const TSharedPtr<FJsonValue>& Element : ActorTransforms)
	{
		FTransform Value;
		Value.InitFromString(Element->AsString());
		ReturnData.ActorTransforms.Add(Value);
	}

	TArray<TSharedPtr<FJsonValue>> XRayNames = json->GetArrayField("XRayNames");
	for (const TSharedPtr<FJsonValue>& Element : XRayNames)
	{
		ReturnData.XRayNames.Add(Element->AsString());
	}

	TArray<TSharedPtr<FJsonValue>> DimensionControlLocations = json->GetArrayField("DimensionControlLocations");
	for (const TSharedPtr<FJsonValue>& Element : DimensionControlLocations)
	{
		FVector Value;
		Value.InitFromString(Element->AsString());
		ReturnData.DimensionControlLocations.Add(Value);
	}

	TArray<TSharedPtr<FJsonValue>> AnnotaionPointTransforms = json->GetArrayField("AnnotaionPointTransforms");
	for (const TSharedPtr<FJsonValue>& Element : AnnotaionPointTransforms)
	{
		FTransform Value;
		Value.InitFromString(Element->AsString());
		ReturnData.AnnotationPointTransforms.Add(Value);
	}

	TArray<TSharedPtr<FJsonValue>> AnnotationLastIndices = json->GetArrayField("AnnotationLastIndices");
	for (const TSharedPtr<FJsonValue>& Element : AnnotationLastIndices)
	{
		ReturnData.AnnotationLastIndices.Add(FCString::Atoi(*Element->AsString()));
	}

	TArray<TSharedPtr<FJsonValue>> AnnotationColors = json->GetArrayField("AnnotationColors");
	for (const TSharedPtr<FJsonValue>& Element : AnnotationColors)
	{
		FLinearColor Value;
		Value.InitFromString(Element->AsString());
		ReturnData.AnnotationColors.Add(Value);
	}

	TArray<TSharedPtr<FJsonValue>> AnnotationTexts = json->GetArrayField("AnnotationTexts");
	for (const TSharedPtr<FJsonValue>& Element : AnnotationTexts)
	{
		FText Value;
		Value.FromString(Element->AsString());
		ReturnData.AnnotationTexts.Add(Value);
	}

	TArray<TSharedPtr<FJsonValue>> AnnotationTextLocations = json->GetArrayField("AnnotationTextLocations");
	for (const TSharedPtr<FJsonValue>& Element : AnnotationTextLocations)
	{
		FVector Value;
		Value.InitFromString(Element->AsString());
		ReturnData.AnnotationTextLocations.Add(Value);
	}

	TArray<TSharedPtr<FJsonValue>> AnnotationTargetLocations = json->GetArrayField("AnnotationTargetLocations");
	for (const TSharedPtr<FJsonValue>& Element : AnnotationTargetLocations)
	{
		FVector Value;
		Value.InitFromString(Element->AsString());
		ReturnData.AnnotationTargetLocations.Add(Value);
	}

	return ReturnData;
}