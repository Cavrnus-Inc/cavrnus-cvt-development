// // Copyright (c), Cavrnus. All rights reserved.

#pragma once

#include <Types/ChatEntry.h>

#include "CoreMinimal.h"
#include "Components/VerticalBox.h"
#include "UI/CavrnusBaseUserWidget.h"
#include "CavrnusChatEntry.generated.h"

struct FCavrnusUser;
class UBorder;
class UImage;
class UTextBlock;
struct FCavrnusSpaceConnection;

UCLASS(Abstract)
class CAVRNUSCONNECTOR_API UCavrnusChatEntry : public UCavrnusBaseUserWidget
{
	GENERATED_BODY()

public:
	void Setup(const FChatEntry& InChatEntry);

	UPROPERTY(BlueprintReadWrite, Category = "Cavrnus|ChatEntry", meta = (BindWidget))
	UTextBlock* CreatorName = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Cavrnus|ChatEntry", meta = (BindWidget))
	UTextBlock* CreationTime = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Cavrnus|ChatEntry", meta = (BindWidget))
	UTextBlock* Message = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Cavrnus|ChatEntry", meta = (BindWidget))
	UImage* ProfilePicImage = nullptr;

	// Chat Visuals
	UPROPERTY(EditAnywhere, Category = "Cavrnus|ChatEntry")
	FLinearColor LocalUserColor = FLinearColor();
	
	UPROPERTY(BlueprintReadWrite, Category = "Cavrnus|ChatEntry", meta = (BindWidget))
	UBorder* ChatBubbleBackground = nullptr;

	UFUNCTION(BlueprintImplementableEvent, Category = "Cavrnus|ChatEntry")
	void SetupComplete(FChatEntry InChatEntry);

	FChatEntry ChatData = FChatEntry();

private:
	void HandleLocalUserChat();

	FString FormatTime(const FChatEntry& ChatEntry);
};