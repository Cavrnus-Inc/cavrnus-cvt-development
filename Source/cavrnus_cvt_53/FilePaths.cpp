// Fill out your copyright notice in the Description page of Project Settings.

#include "FilePaths.h"

bool UFilePaths::DeleteLocalFile(FString FilePath)
{
	return IFileManager::Get().Delete(*FilePath);
}

bool UFilePaths::DeleteLocalFolder(FString FolderPath)
{
	IFileManager& FileManager = IFileManager::Get();

	const FString AbsoluteFolderPath = FPaths::ConvertRelativePathToFull(FolderPath);

	// Delete the directory and its contents
	return FileManager.DeleteDirectory(*AbsoluteFolderPath, false, true);
}

FString UFilePaths::GetSavedFolder(const FString SubDirectory)
{
	const FString CacheDirectory = FPaths::ProjectSavedDir() / SubDirectory;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.DirectoryExists(*CacheDirectory))
	{
		PlatformFile.CreateDirectory(*CacheDirectory);
	}

	return CacheDirectory;
}

TArray<FString> UFilePaths::GetFilesOfType(const FString& FolderPath, const FString& Extension)
{
	TArray<FString> FoundFiles;

	const FString AbsoluteFolderPath = FPaths::ConvertRelativePathToFull(FolderPath);
	const FString SearchPattern = FString::Printf(TEXT("%s/*%s"), *AbsoluteFolderPath, *Extension);

	IFileManager& FileManager = IFileManager::Get();
	FileManager.FindFiles(FoundFiles, *SearchPattern, true, false);

	for (FString& FileName : FoundFiles)
	{
		FileName = FPaths::Combine(AbsoluteFolderPath, FileName);
	}

	return FoundFiles;
}
