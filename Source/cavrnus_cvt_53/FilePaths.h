// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FilePaths.generated.h"

/**
 * 
 */
UCLASS()
class UFilePaths : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Cavrnus|Files")
	static bool DeleteLocalFile(FString FilePath);

	UFUNCTION(BlueprintCallable, Category = "Cavrnus|Files")
	static bool DeleteLocalFolder(FString FolderPath);
	
	UFUNCTION(BlueprintPure, Category = "Cavrnus|Files")
	static FString GetSavedFolder(const FString SubDirectory = "CavrnusDownloads");

	UFUNCTION(BlueprintPure, Category = "Cavrnus|Files")
	static TArray<FString> GetFilesOfType(const FString& FolderPath, const FString& Extension);
};