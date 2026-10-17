#include "uagatewaynodemanager.h"
#include "opcua_foldertype.h"
#include "nodemanagerroot.h"

static void UaGatewayNodeManager_GetDefaultValue(
	OpcUa_Byte type, 
	OpcUa_Byte arrayType, 
	UaVariant& val)
{
	if (OpcUa_VariantArrayType_Scalar == arrayType)
	{
		if (OpcUaType_Boolean <= type && OpcUaType_Double >= type)
		{
			OpcUa_Variant tmpVariant;
			OpcUa_Variant_Initialize(&tmpVariant);
			tmpVariant.Datatype = type;
			tmpVariant.ArrayType = OpcUa_VariantArrayType_Scalar;
			val = UaVariant(tmpVariant);
			OpcUa_Variant_Clear(&tmpVariant);
		}
		else {
			switch (type)
			{
			case OpcUaType_String:
			{
				val.setString(UaString());
				return;
			}
			case OpcUaType_DateTime:
			{
				val.setDateTime(UaDateTime());
				return;
			}
			case OpcUaType_Guid:
			{
				val.setGuid(UaGuid());
				return;
			}
			case OpcUaType_ByteString:
			{
				UaByteString tmpByteString;
				val.setByteString(tmpByteString, OpcUa_False);
				return;
			}
			case OpcUaType_XmlElement:
			{
				val.setXmlElement(UaString());
				return;
			}
			case OpcUaType_NodeId:
			{
				val.setNodeId(UaNodeId());
				return;
			}
			case OpcUaType_ExpandedNodeId:
			{
				val.setExpandedNodeId(UaExpandedNodeId());
				return;
			}
			case OpcUaType_StatusCode:
			{
				val.setStatusCode(OpcUa_Good);
				return;
			}
			case OpcUaType_QualifiedName:
			{
				val.setQualifiedName(UaQualifiedName());
				return;
			}
			case OpcUaType_LocalizedText:
			{
				val.setLocalizedText(UaLocalizedText());
				return;
			}
			case OpcUaType_ExtensionObject:
			{
				UaExtensionObject tmpExtensionObject;
				val.setExtensionObject(tmpExtensionObject, OpcUa_False);
				return;
			}
			case OpcUaType_DataValue:
			{
				UaDataValue tmpDataValue;
				val.setDataValue(&tmpDataValue, OpcUa_False);
				return;
			}
			default:
			{
				return;
			}
			}
		}
	}
	else if (OpcUa_VariantArrayType_Array == arrayType) {
		if (OpcUaType_Boolean <= type && OpcUaType_DataValue >= type)
		{
			OpcUa_Variant tmpVariant;
			OpcUa_Variant_Initialize(&tmpVariant);
			tmpVariant.Datatype = type;
			tmpVariant.ArrayType = OpcUa_VariantArrayType_Array;
			val = UaVariant(tmpVariant);
			OpcUa_Variant_Clear(&tmpVariant);
		}
	}
	else if (OpcUa_VariantArrayType_Matrix == arrayType) {
		if (OpcUaType_Boolean <= type && OpcUaType_DataValue >= type)
		{
			OpcUa_Variant tmpVariant;
			OpcUa_Variant_Initialize(&tmpVariant);
			tmpVariant.Datatype = type;
			tmpVariant.ArrayType = OpcUa_VariantArrayType_Matrix;
			val = UaVariant(tmpVariant);
			OpcUa_Variant_Clear(&tmpVariant);
		}
	}
}

static bool UaGatewayNodeManager_GetValueByType(
	const UaDataValue& value,
	OpcUa_Byte         dataType,
	UaVariant& val)
{
	val.clear();

	const OpcUa_Variant* pVariant = value.value();
	OpcUa_StatusCode statusCode = OpcUa_Good;

	if (pVariant->Datatype == dataType)
	{
		val = *pVariant;
		return true;
	}

	if (OpcUa_VariantArrayType_Scalar == pVariant->ArrayType)
	{
		UaVariant inputValue(*pVariant);

		if (OpcUaType_Null == dataType)
		{
			val = *pVariant;
			return true;
		}

		if (OpcUaType_Boolean == dataType)
		{
			OpcUa_Boolean value = OpcUa_False;
			statusCode = inputValue.toBool(value);
			if (OpcUa_IsNotGood(statusCode)) return false;
			val.setBool(value);
		}
		else if (OpcUaType_Double == dataType)
		{
			OpcUa_Double value = 0;
			statusCode = inputValue.toDouble(value);
			if (OpcUa_IsNotGood(statusCode)) return false;
			val.setDouble(value);
		}
		else if (OpcUaType_UInt32 == dataType)
		{
			OpcUa_UInt32 value = 0;
			statusCode = inputValue.toUInt32(value);
			if (OpcUa_IsNotGood(statusCode)) return false;
			val.setUInt32(value);
		}
		else if (OpcUaType_Int32 == dataType)
		{
			OpcUa_Int32 value = 0;
			statusCode = inputValue.toInt32(value);
			if (OpcUa_IsNotGood(statusCode)) return false;
			val.setInt32(value);
		}
		else if (OpcUaType_String == dataType)
		{
			val.setString(inputValue.toString());
		}
		else if (OpcUaType_SByte == dataType)
		{
			OpcUa_SByte value = 0;
			statusCode = inputValue.toSByte(value);
			if (OpcUa_IsNotGood(statusCode)) return false;
			val.setSByte(value);
		}
		else if (OpcUaType_Byte == dataType)
		{
			OpcUa_Byte value = 0;
			statusCode = inputValue.toByte(value);
			if (OpcUa_IsNotGood(statusCode)) return false;
			val.setByte(value);
		}
		else if (OpcUaType_Int16 == dataType)
		{
			OpcUa_Int16 value = 0;
			statusCode = inputValue.toInt16(value);
			if (OpcUa_IsNotGood(statusCode)) return false;
			val.setInt16(value);
		}
		else if (OpcUaType_UInt16 == dataType)
		{
			OpcUa_UInt16 value = 0;
			statusCode = inputValue.toUInt16(value);
			if (OpcUa_IsNotGood(statusCode)) return false;
			val.setUInt16(value);
		}
		else if (OpcUaType_Int64 == dataType)
		{
			OpcUa_Int64 value = 0;
			statusCode = inputValue.toInt64(value);
			if (OpcUa_IsNotGood(statusCode)) return false;
			val.setInt64(value);
		}
		else if (OpcUaType_UInt64 == dataType)
		{
			OpcUa_UInt64 value = 0;
			statusCode = inputValue.toUInt64(value);
			if (OpcUa_IsNotGood(statusCode)) return false;
			val.setUInt64(value);
		}
		else if (OpcUaType_Float == dataType)
		{
			OpcUa_Float value = 0;
			statusCode = inputValue.toFloat(value);
			if (OpcUa_IsNotGood(statusCode)) return false;
			val.setFloat(value);
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

	return true;
}

UaGatewayNodeManager::UaGatewayNodeManager(const UaString& uri) : 
	NodeManagerBase(UaString(uri), OpcUa_True, 3000007)
{	
	m_continueFlag = true;
	m_mutexIndex = 0;

	for (OpcUa_UInt32 i = 0; i < 50; ++i)
	{
		m_mutexes.push_back(new UaMutexRefCounted);
	}
}

UaGatewayNodeManager::~UaGatewayNodeManager()
{
	for (auto mutex : m_mutexes)
	{
		mutex->releaseReference();
	}
}

UaStatus UaGatewayNodeManager::afterStartUp()
{
	if (!onInitialize() || !onConfigure())
	{
		NodeManagerRoot::CreateRootNodeManager()->changeServerState(OpcUa_ServerState_NoConfiguration);
		NodeManagerRoot::CreateRootNodeManager()->changeServiceLevel(1, 255);
		return OpcUa_BadConfigurationError;
	}	

	UaThread::start();
	return OpcUa_Good;
}

UaStatus UaGatewayNodeManager::beforeShutDown()
{
	m_continueFlag = false;
	UaThread::wait();
	onFinalize();
	return OpcUa_Good;
}

OpcUa_UInt32 UaGatewayNodeManager::scanRate() const
{
	return 2000;
}

void UaGatewayNodeManager::run()
{	
	while (m_continueFlag)
	{
		onScan(UaDateTime::now());
		UaThread::msleep(scanRate());
	}
}

OpcUa_Boolean UaGatewayNodeManager::beforeSetAttributeValue(
	Session* pSession,
	UaNode* pNode,
	OpcUa_Int32 attributeId,
	const UaDataValue& dataValue,
	OpcUa_Boolean& checkWriteMask)
{
	if (OpcUa_Attributes_Value != attributeId ||
		OpcUa_NodeClass_Variable != pNode->nodeClass()) return OpcUa_False;

	return OpcUa_True;
}

void UaGatewayNodeManager::afterSetAttributeValue(
	Session* pSession,
	UaNode* pNode,
	OpcUa_Int32 attributeId,
	const UaDataValue& dataValue)
{
	if (OpcUa_NodeClass_Variable != pNode->nodeClass()) return;
	UaGatewayVariable* pVariable = static_cast<UaGatewayVariable*>(pNode);

	UaVariant val;
	UaDataValue currentDataValue = pVariable->getValue();

	if (!UaGatewayNodeManager_GetValueByType(
		dataValue,
		currentDataValue.value()->Datatype,
		val)) return;
		
	onWrite(val, pVariable);
}

bool UaGatewayNodeManager::addFolder(
	const UaNodeId& nodeId,
	const UaString& name,
	const UaNodeId& parentId)
{	
	OpcUa_UInt16 nsIndex = this->getNameSpaceIndex();

	if (nodeId.namespaceIndex() != nsIndex) return false;
		
	OpcUa::FolderType* pFolder = new OpcUa::FolderType(
		nodeId,
		name, 
		nsIndex,
		this, 
		getSharedMutex());

	//pFolder->useAccessInfoFromType();

	UaStatus ret = this->addNodeAndReference(parentId, pFolder, OpcUaId_Organizes);

	if (ret.isNotGood())
	{
		pFolder->releaseReference();
		return false;
	}

	return true;
}

UaGatewayVariable* UaGatewayNodeManager::addVariable(
	const UaNodeId& nodeId,
	const UaString& name,
	const UaNodeId& parentId,
	OpcUa_BuiltInType dataType,
	bool isArray,
	OpcUa_Byte accessLevel,
	UserDataBase* pUserData)
{
	if (OpcUaType_StatusCode <= dataType) return false;

	OpcUa_UInt16 nsIndex = this->getNameSpaceIndex();

	if (nodeId.namespaceIndex() != nsIndex) return false;
		
	OpcUa_Byte arrayType = OpcUa_VariantArrayType_Scalar;
	OpcUa_Int32 valueRank = OpcUa_ValueRanks_Scalar;
	
	if (isArray)
	{
		arrayType = OpcUa_VariantArrayType_Array;
		valueRank = OpcUa_ValueRanks_OneDimension;
	}


	UaVariant initialValue;
	UaGatewayNodeManager_GetDefaultValue(dataType, arrayType, initialValue);

	UaGatewayVariable* pVariable = new UaGatewayVariable(
		nodeId,
		name,
		nsIndex,
		UaVariant(),
		accessLevel,
		this,
		getSharedMutex());

	pVariable->setDataType(UaNodeId(dataType));
	pVariable->setValueRank(valueRank);
	pVariable->setValue(initialValue, UaDateTime::fromTime_t(0), OpcUa_BadWaitingForInitialData);
	pVariable->setUserData(pUserData);

	UaStatus ret = this->addNodeAndReference(parentId, pVariable, OpcUaId_HasComponent);

	if (ret.isNotGood())
	{
		pVariable->releaseReference();
		return OpcUa_Null;
	}

	return pVariable;
}

UaMutexRefCounted* UaGatewayNodeManager::getSharedMutex()
{
	if (m_mutexIndex >= m_mutexes.size()) m_mutexIndex = 0;
	OpcUa_UInt32 index = m_mutexIndex;
	m_mutexIndex++;
	return m_mutexes[index];
}