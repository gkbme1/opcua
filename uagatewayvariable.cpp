#include "uagatewayvariable.h"

UaGatewayVariable::UaGatewayVariable(
	const UaNodeId& nodeId,
	const UaString& name,
	OpcUa_UInt16       browseNameNameSpaceIndex,
	const UaVariant& initialValue,
	OpcUa_Byte         accessLevel,
	NodeManagerConfig* pNodeConfig,
	UaMutexRefCounted* pSharedMutex) : OpcUa::BaseDataVariableType(
		nodeId, 
		name, 
		browseNameNameSpaceIndex,
		initialValue,
		accessLevel,
		pNodeConfig, 
		pSharedMutex)
{
	m_handle_COPCTag = NULL;
}

UaGatewayVariable::~UaGatewayVariable()
{}

void UaGatewayVariable::setValue(
	UaVariant&        value,
	const UaDateTime& timestamp,
	OpcUa_StatusCode  quality)
{
	UaDataValue dataValue;

	if (value.isEmpty())
	{
		value = *OpcUa::BaseDataVariableType::value(OpcUa_Null).value();
	}
	
	dataValue.setDataValue(value, OpcUa_True, quality, timestamp, timestamp);
	OpcUa::BaseDataVariableType::setValue(OpcUa_Null, dataValue, OpcUa_False);	
}

void UaGatewayVariable::getValue(UaVariant& value)
{
	value = *OpcUa::BaseDataVariableType::value(OpcUa_Null).value();
}

UaDataValue UaGatewayVariable::getValue()
{
	return OpcUa::BaseDataVariableType::value(OpcUa_Null);
}

UaStatus UaGatewayVariable::setAttributeValue(
	Session* pSession,
	OpcUa_Int32 attributeId,
	const UaDataValue& dataValue,
	NodeAccessInfo* pDefaultPermissions,
	OpcUa_Boolean checkWriteMask)
{
	if (OpcUa_Attributes_Value == attributeId) return OpcUa_Good;
	return OpcUa::BaseDataVariableType::setAttributeValue(pSession, attributeId, dataValue, pDefaultPermissions, checkWriteMask);
}