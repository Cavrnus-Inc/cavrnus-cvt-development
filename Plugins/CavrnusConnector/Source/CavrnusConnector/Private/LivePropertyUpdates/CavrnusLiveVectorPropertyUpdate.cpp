// Copyright(c) Cavrnus. All rights reserved.
#include "LivePropertyUpdates/CavrnusLiveVectorPropertyUpdate.h"
#include "RelayModel/CavrnusVirtualPropertyUpdate.h"
#include "Translation/CavrnusProtoTranslation.h"

UCavrnusLiveVectorPropertyUpdate::UCavrnusLiveVectorPropertyUpdate()
{
}

UCavrnusLiveVectorPropertyUpdate::~UCavrnusLiveVectorPropertyUpdate()
{
}

void UCavrnusLiveVectorPropertyUpdate::Initialize(Cavrnus::CavrnusRelayModel* relayModel, FCavrnusSpaceConnection spaceConn, const FAbsolutePropertyId& propertyId, FVector value)
{
	livePropertyUpdate = new Cavrnus::CavrnusVirtualPropertyUpdate(relayModel, spaceConn, propertyId, Cavrnus::FPropertyValue::VectorPropValue(value));
}

void UCavrnusLiveVectorPropertyUpdate::UpdateWithNewData(FVector value)
{
	TrySendUpdateData(Cavrnus::FPropertyValue::VectorPropValue(value));
}

void UCavrnusLiveVectorPropertyUpdate::Finalize(FVector value)
{
	if (livePropertyUpdate)
		livePropertyUpdate->Finalize(Cavrnus::FPropertyValue::VectorPropValue(value));
}
