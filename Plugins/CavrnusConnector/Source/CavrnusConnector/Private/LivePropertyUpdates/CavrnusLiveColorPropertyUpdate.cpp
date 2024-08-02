// Copyright(c) Cavrnus. All rights reserved.
#include "LivePropertyUpdates/CavrnusLiveColorPropertyUpdate.h"
#include "RelayModel/CavrnusVirtualPropertyUpdate.h"
#include "Translation/CavrnusProtoTranslation.h"

UCavrnusLiveColorPropertyUpdate::UCavrnusLiveColorPropertyUpdate()
{
}

UCavrnusLiveColorPropertyUpdate::~UCavrnusLiveColorPropertyUpdate()
{
}

void UCavrnusLiveColorPropertyUpdate::Initialize(Cavrnus::CavrnusRelayModel* relayModel, FCavrnusSpaceConnection spaceConn, const FAbsolutePropertyId& propertyId, FLinearColor value)
{
	livePropertyUpdate = new Cavrnus::CavrnusVirtualPropertyUpdate(relayModel, spaceConn, propertyId, Cavrnus::FPropertyValue::ColorPropValue(value));
}

void UCavrnusLiveColorPropertyUpdate::UpdateWithNewData(FLinearColor value)
{
	TrySendUpdateData(Cavrnus::FPropertyValue::ColorPropValue(value));
}

void UCavrnusLiveColorPropertyUpdate::Finalize(FLinearColor value)
{
	if (livePropertyUpdate)
		livePropertyUpdate->Finalize(Cavrnus::FPropertyValue::ColorPropValue(value));
}
