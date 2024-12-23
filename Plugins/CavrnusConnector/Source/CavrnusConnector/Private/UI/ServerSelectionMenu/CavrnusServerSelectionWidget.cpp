// Copyright (c) 2024 Cavrnus. All rights reserved.

#include "CavrnusFunctionLibrary.h"
#include "CavrnusSpatialConnector.h"
#include "CavrnusSpatialConnectorSubSystem.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "UI/ServerSelectionMenu/CavrnusServerSelectWidget.h"

void UCavrnusServerSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ProceedButton->OnClicked.AddDynamic(this, &UCavrnusServerSelectionWidget::ProceedButtonClicked);
	ServerTextBox->OnTextChanged.AddDynamic(this, &UCavrnusServerSelectionWidget::ServerTextBoxUpdated);
	
	ProceedButton->SetIsEnabled(false);
}

void UCavrnusServerSelectionWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
	ProceedButton->OnClicked.RemoveDynamic(this, &UCavrnusServerSelectionWidget::ProceedButtonClicked);
	ServerTextBox->OnTextChanged.RemoveDynamic(this, &UCavrnusServerSelectionWidget::ServerTextBoxUpdated);
}

void UCavrnusServerSelectionWidget::ProceedButtonClicked()
{
	if (ACavrnusSpatialConnector* Csc = UCavrnusFunctionLibrary::GetCavrnusSpatialConnector())
		Csc->MyServer = ServerTextBox->GetText().ToString();
	
	if (UCavrnusSpatialConnectorSubSystemProxy* Csp = UCavrnusFunctionLibrary::GetCavrnusSpatialConnectorSubSystemProxy())
		Csp->BeginAuthenticationProcess();

	RemoveFromParent();
}

void UCavrnusServerSelectionWidget::ServerTextBoxUpdated(const FText& Text)
{
	ProceedButton->SetIsEnabled(!Text.IsEmptyOrWhitespace());
}