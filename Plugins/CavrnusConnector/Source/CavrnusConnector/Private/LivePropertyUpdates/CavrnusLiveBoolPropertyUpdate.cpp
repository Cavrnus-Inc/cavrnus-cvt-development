// Copyright(c) Cavrnus. All rights reserved.
#include "LivePropertyUpdates/CavrnusLiveBoolPropertyUpdate.h"
#include "RelayModel/CavrnusVirtualPropertyUpdate.h"
#include "Translation/CavrnusProtoTranslation.h"

UCavrnusLiveBoolPropertyUpdate::UCavrnusLiveBoolPropertyUpdate()
{
}

UCavrnusLiveBoolPropertyUpdate::~UCavrnusLiveBoolPropertyUpdate()
{
}

void UCavrnusLiveBoolPropertyUpdate::Initialize(Cavrnus::CavrnusRelayModel* relayModel, FCavrnusSpaceConnection spaceConn, const FAbsolutePropertyId& propertyId, bool value)
{
	livePropertyUpdate = new Cavrnus::CavrnusVirtualPropertyUpdate(relayModel, spaceConn, propertyId, Cavrnus::FPropertyValue::BoolPropValue(value));
}

void UCavrnusLiveBoolPropertyUpdate::UpdateWithNewData(bool value)
{
	TrySendUpdateData(Cavrnus::FPropertyValue::BoolPropValue(value));
}

void UCavrnusLiveBoolPropertyUpdate::Finalize(bool value)
{
	if (livePropertyUpdate)
		livePropertyUpdate->Finalize(Cavrnus::FPropertyValue::BoolPropValue(value));
}