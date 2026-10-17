#ifndef UAGATEWAYVARIABLE_H
#define UAGATEWAYVARIABLE_H

#include "opcua_basedatavariabletype.h"

class UaGatewayVariable : public OpcUa::BaseDataVariableType
{
public:
	UaGatewayVariable(
		const UaNodeId&    nodeId,
		const UaString&    name,
		OpcUa_UInt16       browseNameNameSpaceIndex,
		const UaVariant&   initialValue,
		OpcUa_Byte         accessLevel,
		NodeManagerConfig* pNodeConfig,
		UaMutexRefCounted* pSharedMutex);

	virtual ~UaGatewayVariable();

	void setValue(
		UaVariant&          value, 
		const UaDateTime&   timestamp,
		OpcUa_StatusCode    quality = OpcUa_Good);

	void getValue(UaVariant& value);
	UaDataValue getValue();
	HANDLE m_handle_COPCTag;
private:
	UaStatus setAttributeValue(
		Session* pSession, 
		OpcUa_Int32 attributeId, 
		const UaDataValue& dataValue, 
		NodeAccessInfo* pDefaultPermissions, 
		OpcUa_Boolean checkWriteMask);
};	

#endif