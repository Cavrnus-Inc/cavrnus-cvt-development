// // Copyright (c), Cavrnus. All rights reserved.

#include "UI/MessageMenus/ChatMenu/CavrnusChatWindow.h"

#include "CavrnusFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "TimerManager.h"

void UCavrnusChatWindow::NativeConstruct()
{
	Super::NativeConstruct();

	SubmitButton->SetIsEnabled(false);
	DefaultButtonIconColor = SubmitButtonIcon->ColorAndOpacity;
}

void UCavrnusChatWindow::SubmitButtonClicked()
{
	if (!InputTextBox->Text.IsEmptyOrWhitespace())
		SubmitChat();
}

void UCavrnusChatWindow::TextInputChanged(const FText& InputValue)
{
	const bool ValidInput = !InputValue.IsEmptyOrWhitespace();
	SubmitButton->SetIsEnabled(ValidInput);
	SubmitButtonIcon->SetBrushTintColor(ValidInput ? ButtonEnabledColor : DefaultButtonIconColor);
}

void UCavrnusChatWindow::TextInputFieldSubmit(const FText&, ETextCommit::Type CommitValue)
{
	if (CommitValue == ETextCommit::OnEnter)
		SubmitChat();
}

void UCavrnusChatWindow::SubmitChat()
{
	UCavrnusFunctionLibrary::PostChatMessage(SpaceConnection, InputTextBox->Text.ToString());

	InputTextBox->SetText(FText::FromString(""));
	InputTextBox->SetKeyboardFocus();
	
	ScrollToEnd();
}

void UCavrnusChatWindow::HandleChatAdded(FChatEntry ChatAdded)
{
	if (ChatAdded.IsTranscription)
		return;
	
	Super::HandleChatAdded(ChatAdded);
}

void UCavrnusChatWindow::HandleChatUpdated(FChatEntry ChatUpdated)
{
	if (ChatUpdated.IsTranscription)
		return;

	Super::HandleChatUpdated(ChatUpdated);
}

void UCavrnusChatWindow::HandleChatRemoved(FString ChatRemoved)
{
	if (AllWidgetsMap.Contains(ChatRemoved))
	{
		Super::HandleChatRemoved(ChatRemoved);
	}
}

void UCavrnusChatWindow::LocalUserArrived()
{
	Super::LocalUserArrived();

	SubmitButton->OnClicked.AddDynamic(this, &UCavrnusChatWindow::SubmitButtonClicked);
	InputTextBox->OnTextChanged.AddDynamic(this, &UCavrnusChatWindow::TextInputChanged);
	InputTextBox->OnTextCommitted.AddDynamic(this, &UCavrnusChatWindow::TextInputFieldSubmit);
}