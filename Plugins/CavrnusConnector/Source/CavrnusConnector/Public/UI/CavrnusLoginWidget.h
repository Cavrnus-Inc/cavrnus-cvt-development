// Copyright (c) 2024 Cavrnus. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "CavrnusBaseUserWidget.h"
#include "CavrnusLoginWidget.generated.h"

class UButton;
class UEditableTextBox;
class UTexture2D;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLoginClicked, FString, FString);

/**
 * @brief Base class for widget for obtaining login credentials.
 *
 * This widget provides a user interface for inputting email and password credentials,
 * and handles the login process within the Cavrnus platform.
 */

UCLASS(Abstract)
class CAVRNUSCONNECTOR_API UCavrnusLoginWidget : public UCavrnusBaseUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief Sets up the login widget.
	 *
	 * This function initializes the widget and prepares it for user interaction.
	 */
	UFUNCTION(BlueprintCallable, Category = "Cavrnus|Login")
	void Setup();

	virtual void NativeDestruct() override;
	
	/**
	 * @brief Handles the login button click event.
	 *
	 * This function is called when the login button is clicked, triggering the login process.
	 */
	UFUNCTION()
	void OnLoginClicked();

	/** The text box for entering the email address. */
	UPROPERTY(BlueprintReadOnly, Category = "Cavrnus|Login", meta = (BindWidget))
	UEditableTextBox* EmailInput = nullptr;

	/** The text box for entering the password. */
	UPROPERTY(BlueprintReadOnly, Category = "Cavrnus|Login", meta = (BindWidget))
	UEditableTextBox* PasswordInput = nullptr;

	/** The button for initiating the login process. */
	UPROPERTY(BlueprintReadOnly, Category = "Cavrnus|Login", meta = (BindWidget))
	UButton* LoginButton = nullptr;

	/** Delegate for handling the login click event. */
	FOnLoginClicked OnLogin;
};
