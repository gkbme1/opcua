#include "myappnodemanager.h"
#include "uavariant.h"
#include <iostream>

//#define DemoId_Demo_Events "Demo.Events"
#define DemoId_Demo_Events "Group1"
#include "nodeaccessinfobase.h"
#include "roletypeoperations.h"

#define AccessId_Demo_AccessRights_RoleBased "Demo.AccessRights.RoleBased"
#define AccessId_Demo_AccessRights_RoleBased_Browse_Anonymous "Demo.AccessRights.RoleBased.Browse_Anonymous"
#define AccessId_Demo_AccessRights_RoleBased_Browse_AuthenticatedUser "Demo.AccessRights.RoleBased.Browse_AuthenticatedUser"
#define AccessId_Demo_AccessRights_RoleBased_Browse_ConfigureAdmin "Demo.AccessRights.RoleBased.Browse_ConfigureAdmin"
#define AccessId_Demo_AccessRights_RoleBased_Browse_Engineer "Demo.AccessRights.RoleBased.Browse_Engineer"
#define AccessId_Demo_AccessRights_RoleBased_Browse_Observer "Demo.AccessRights.RoleBased.Browse_Observer"
#define AccessId_Demo_AccessRights_RoleBased_Browse_Operator "Demo.AccessRights.RoleBased.Browse_Operator"
#define AccessId_Demo_AccessRights_RoleBased_Browse_SecurityAdmin "Demo.AccessRights.RoleBased.Browse_SecurityAdmin"
#define AccessId_Demo_AccessRights_RoleBased_Browse_Supervisor "Demo.AccessRights.RoleBased.Browse_Supervisor"
#define AccessId_Demo_AccessRights_RoleBased_Object_Anonymous "Demo.AccessRights.RoleBased.Object_Anonymous"
#define AccessId_Demo_AccessRights_RoleBased_Object_AuthenticatedUser "Demo.AccessRights.RoleBased.Object_AuthenticatedUser"
#define AccessId_Demo_AccessRights_RoleBased_Object_Observer "Demo.AccessRights.RoleBased.Object_Observer"
#define AccessId_Demo_AccessRights_RoleBased_Object_Operator "Demo.AccessRights.RoleBased.Object_Operator"
#define AccessId_Demo_AccessRights_Simple "Demo.AccessRights.Simple"


#define AccessId_Demo_AccessRights_RoleBased_Authenticated_BRW "Demo.AccessRights.RoleBased.Authenticated_BRW"
#define AccessId_Demo_AccessRights_RoleBased_Operator_BRW "Demo.AccessRights.RoleBased.Operator_BRW"
#define AccessId_Demo_AccessRights_RoleBased_Anon_B_Auth_BR_OperBRW "Demo.AccessRights.RoleBased.Anon_B_Auth_BR_OperBRW"
#define AccessId_Demo_AccessRights_RoleBased_Anon_BR_Oper_BRW "Demo.AccessRights.RoleBased.Anon_BR_Oper_BRW"
#define AccessId_Demo_AccessRights_RoleBased_Anon_BRW "Demo.AccessRights.RoleBased.Anon_BRW"


#include "OPCUAMaster.h";
#include "OPCUASlave.h";
#include "OPCUATag.h";
#include "Tag.h";

class COPCUAMaster;
class COPCUASlave;
class COPCUATag;

UaVariant FormatUaVariant(double value, int type)
{
	UaVariant uaVariant;
	switch (type)
	{
		case DT_BOOL:case DT_1BIT:case DT_2BITS:case DT_4BITS:case DT_DSM6:
		{
			OpcUa_Boolean boolValue = value == 0 ? OpcUa_False : OpcUa_True;
			uaVariant = UaVariant(boolValue);
		}
		break;

		case DT_SINGLE:case DT_AS_REAL:
		{
			OpcUa_Float floatValue = float(value);
			uaVariant = UaVariant(floatValue);
		}
		break;

		case DT_DOUBLE:
		{
			OpcUa_Double doubleValue = double(value);
			uaVariant = UaVariant(doubleValue);
		}
		break;

		case DT_BYTE:
		{
			OpcUa_Byte byteValue = byte(value);
			//uaVariant = UaVariant(byteValue);
			uaVariant.setByte(byteValue);
		}
		break;

		case DT_SBYTE:
		{
			OpcUa_SByte sbyteValue = char(value);
			uaVariant = UaVariant(sbyteValue);
		}
		break;

		case DT_WORD:
		{
			OpcUa_UInt16 uint16Value = WORD(value);
			uaVariant = UaVariant(uint16Value);
		}
		break;

		case DT_SWORD:
		{
			OpcUa_Int16 int16Value = short(value);
			uaVariant = UaVariant(int16Value);
		}
		break;

		case DT_DWORD:
		{
			OpcUa_UInt32 uint32Value = DWORD(value);
			uaVariant = UaVariant(uint32Value);
		}
		break;

		case DT_SDWORD:
		{
			OpcUa_Int32 int32Value = int(value);
			uaVariant = UaVariant(int32Value);
		}
		break;

		default:
		{
			{
				OpcUa_Float floatValue = float(value);
				uaVariant = UaVariant(floatValue);
			}
			break;
		}

	}
	return uaVariant;
}

MyAppNodeManager::MyAppNodeManager() : UaGatewayNodeManager("hollysys.com/myapp")
{
	//m_counter = 0;
	//m_pDouble = OpcUa_Null;
}

MyAppNodeManager::~MyAppNodeManager()
{}

bool MyAppNodeManager::onInitialize()
{
	return true;
}

void MyAppNodeManager::onFinalize()
{
}

bool MyAppNodeManager::onConfigure()
{	
	//// set default permissions for this namespace - we want everyone to have read, write, call permissions
	//NodeAccessInfoBase* pDefaultAccessPermissions = new NodeAccessInfoBase();
	//pDefaultAccessPermissions->setRolePermissions(
	//	m_pServerManager->getIdForWellKnownRole(OpcUaId_WellKnownRole_Anonymous),
	//	NodeAccessInfo::PERMISSION_OPERATION);

	//setDefaultPermissions(pDefaultAccessPermissions);
	//pDefaultAccessPermissions->releaseReference();

	//// Any user identity shall get the Anonymous Role in addition to other Roles
	//// Like that it's enough to just specify a default permission for Anonymous
	//UaIdentityMappingRuleType rule;
	//rule.setCriteriaType(OpcUa_IdentityCriteriaType_AuthenticatedUser);
	//RoleTypeOperations* pRoleTypeOperations = NULL;
	//m_pServerManager->getRoleByNodeId(OpcUaId_WellKnownRole_Anonymous, &pRoleTypeOperations);
	//if (pRoleTypeOperations)
	//{
	//	pRoleTypeOperations->addIdentity(rule);
	//}



	//UaStatus ret;
	////ret = m_pServerManager->addRole(OpcUaId_WellKnownRole_Observer, "", &m_pRoleTypeOperations1);
	////UA_ASSERT(ret.isGood());


	//// ***** create a Role in ServerNamespace *****
	////*
	//ret = m_pServerManager->addRole("MyDemoRole1", "", &m_pRoleTypeOperations1);
	//UA_ASSERT(ret.isGood());
	////*/

	//// ***** create a Role in this Namespace *****
	////*
	//ret = addRole("MyDemoRole2", &m_pRoleTypeOperations2);
	//UA_ASSERT(ret.isGood());

	UaMutexRefCounted* pSharedMutex = new UaMutexRefCounted;
	COPCUAMaster *pCOPCUAMaster = (COPCUAMaster*)m_OPCUAMasterHandele;
#if OPCUA_DIAG_LOG
	int diagVarCount = 0;
#endif
	for (int i = 0;i<pCOPCUAMaster->m_OPCSlaveArray.GetSize();i++)
	{

		COPCUASlave *pCOPCUASlave = (COPCUASlave*)pCOPCUAMaster->m_OPCSlaveArray.GetAt(i);
		if (OPC_GROUP_S2C == pCOPCUASlave->m_OPCGroupType && pCOPCUASlave->m_bWirteAndRead)
		{
			for (int j = 0; j < pCOPCUASlave->m_tagNumer; j++)
			{
				COPCUATag* pCOPCUATag = pCOPCUASlave->m_OPCTagO[j];
				COPCUATag* pCOPCUATagR = pCOPCUAMaster->m_OPCTagI[pCOPCUATag->m_pOpcSlave->m_pGroupSlave->m_MasterTagFristIndexI + pCOPCUATag->m_TagIndexOfSlave];
				pCOPCUATag->m_handle_UaVariable = pCOPCUATagR->m_handle_UaVariable;
			}
			continue;
		}
		UaString ustrNodeName = UaString::fromLocal8Bit(pCOPCUASlave->m_grpName);
		//UaNodeId groupId(ustrNodeName, getNameSpaceIndex());
		UaNodeId groupId(ustrNodeName, getNameSpaceIndex());
		if (!this->addFolder(groupId, ustrNodeName))
		{
#if OPCUA_DIAG_LOG
			char szDiag[512];
			sprintf(szDiag, "[DIAG onConfigure] addFolder failed: group=%s -> onConfigure returns false, scan thread will NOT start", pCOPCUASlave->m_grpName);
			pCOPCUAMaster->m_pSetLogInfo(pCOPCUAMaster->m_handle, INFOTYPE_ERR, pCOPCUAMaster->m_log_Source, szDiag, szDiag, true, true);
#endif
			return false;
		}

		//AE组
		if (AEFromDriver == pCOPCUASlave->m_OPCGroupType)
		{
			UaString ustrAESourceDriverName = UaString::fromLocal8Bit(pCOPCUASlave->m_AESourceDriverName);
			//************************************************************************
			// Event notifier
			//************************************************************************
			OpcUa::BaseObjectType* pAlarmsNoNodes = new OpcUa::BaseObjectType(
				UaNodeId(ustrAESourceDriverName, getNameSpaceIndex()),
				ustrAESourceDriverName,
				getNameSpaceIndex(),
				this,
				pSharedMutex);
			addNodeAndReference(groupId, pAlarmsNoNodes, OpcUaId_Organizes);
			//pAlarmsNoNodes->setEventNotifier(OpcUa_EventNotifiers_SubscribeToEvents); //OpcUa_EventNotifiers_None
			pAlarmsNoNodes->setEventNotifier(OpcUa_EventNotifiers_None); //

			registerEventNotifier(OpcUaId_Server, pAlarmsNoNodes->nodeId());
			addUaReference(OpcUaId_Server, pAlarmsNoNodes->nodeId(), OpcUaId_HasNotifier);


			m_pUaOffNormalAlarmData = new OpcUa::OffNormalAlarmTypeData;
			m_pUaOffNormalAlarmData->setSource(pAlarmsNoNodes);
			m_pUaOffNormalAlarmData->setConditionNodeId(UaNodeId("AlarmsNoNodes.OffNormalAlarm", getNameSpaceIndex()));
			m_pUaOffNormalAlarmData->setConditionName("NoNodesOffNormalAlarm");
			m_pUaOffNormalAlarmData->setConditionClassId(OpcUaId_ProcessConditionClassType);
			m_pUaOffNormalAlarmData->setConditionClassName(UaLocalizedText("", "ProcessConditionClassType"));
			m_pUaOffNormalAlarmData->setClientUserId("");
			m_pUaOffNormalAlarmData->setInputNode(pAlarmsNoNodes->nodeId());
			m_pUaOffNormalAlarmData->setComment(UaLocalizedText("", ""));
			m_pUaOffNormalAlarmData->setBranchId(UaNodeId());
			m_pUaOffNormalAlarmData->setSeverity(500);
			m_pUaOffNormalAlarmData->setAckedState(OpcUa_True);
			m_pUaOffNormalAlarmData->setActiveState(OpcUa_False);
			m_pUaOffNormalAlarmData->setEnabledState(OpcUa_True);

			continue;
		}


		for (int j = 0; j < pCOPCUASlave->m_tagNumer; j++)
		{
			COPCUATag* pCOPCUATag;
			if (OPC_GROUP_S2C == pCOPCUASlave->m_OPCGroupType)
			{
				pCOPCUATag = pCOPCUASlave->m_OPCTagO[j];
			}
			else
			{
				pCOPCUATag = pCOPCUASlave->m_OPCTagI[j];
			}
			CTag* pTag = pCOPCUATag->m_pTag;
			UaNodeId tagId;
			if (NODE_ID_TYPE_S == pCOPCUASlave->m_nNodeIDType)
			{
				if (NULL != pTag->m_rev1)
				{
					tagId = UaNodeId(pTag->m_rev1, getNameSpaceIndex());
				}
				else
				{
					tagId = UaNodeId(pTag->name, getNameSpaceIndex());
				}

			}
			else if (NODE_ID_TYPE_I == pCOPCUASlave->m_nNodeIDType)
			{
				if (NULL != pTag->m_rev1)
				{
					OpcUa_UInt32 opcUa_UInt32 = atoi(pTag->m_rev1);
					tagId = UaNodeId(opcUa_UInt32, getNameSpaceIndex());
					//if (0 == opcUa_UInt32)
					//{
					//	tagId = UaNodeId(opcUa_UInt32, pCOPCUAMaster->m_nSpaceNameIndex);
					//}
					//else 
					//{
					//	tagId = UaNodeId(pTag->name, pCOPCUAMaster->m_nSpaceNameIndex);
					//}
				}
				else
				{
					tagId = UaNodeId(pTag->name, getNameSpaceIndex());
				}
			}

			
			OpcUa_BuiltInType dataType;
			if (pCOPCUATag->m_type == DT_BOOL || pCOPCUATag->m_type == DT_1BIT)
				dataType = OpcUaType_Boolean;
			else if (pCOPCUATag->m_type == DT_BYTE)
				dataType = OpcUaType_Byte;
			else if (pCOPCUATag->m_type == DT_SBYTE)
				dataType = OpcUaType_SByte;
			else if (pCOPCUATag->m_type == DT_WORD)
				dataType = OpcUaType_UInt16;
			else if (pCOPCUATag->m_type == DT_SWORD)
				dataType = OpcUaType_Int16;
			else if (pCOPCUATag->m_type == DT_DWORD)
				dataType = OpcUaType_UInt32;
			else if (pCOPCUATag->m_type == DT_SDWORD)
				dataType = OpcUaType_Int32;
			else if (pCOPCUATag->m_type == DT_SINGLE)
				dataType = OpcUaType_Float;
			else if (pCOPCUATag->m_type == DT_DOUBLE)
				dataType = OpcUaType_Double;
			else if (pCOPCUATag->m_type == DT_STRING)
				dataType = OpcUaType_String;
			else
				dataType = OpcUaType_Float;

			OpcUa_Byte accessLevel;
			if (OPC_GROUP_S2C == pCOPCUASlave->m_OPCGroupType)
			{
				accessLevel = OpcUa_AccessLevels_CurrentRead;	
			}
			else if (OPC_GROUP_C2S == pCOPCUASlave->m_OPCGroupType && pCOPCUASlave->m_bWirteAndRead)
			{
				accessLevel = OpcUa_AccessLevels_CurrentReadOrWrite;
			}
			else if(OPC_GROUP_C2S == pCOPCUASlave->m_OPCGroupType)
			{
				//accessLevel = OpcUa_AccessLevels_CurrentWrite;
				accessLevel = OpcUa_AccessLevels_CurrentReadOrWrite;
			}

			UaString uastrDisplayName;
			if (DISPLAYNAME_TAGNAME == pCOPCUAMaster->m_nDisplayNameType)
			{
				uastrDisplayName = UaString(pTag->name);
			}
			else if (DISPLAYNAME_DS == pCOPCUAMaster->m_nDisplayNameType)
			{
				if (NULL != pTag->m_rev3)
				{
					uastrDisplayName = UaString::fromLocal8Bit(pTag->m_rev3);
				}
				else
				{
					uastrDisplayName = UaString(pTag->name);
				}
			}
			else if (DISPLAYNAME_ADDRESS == pCOPCUAMaster->m_nDisplayNameType)
			{
				if (NULL != pTag->m_rev1 &&  NODE_ID_TYPE_S == pCOPCUASlave->m_nNodeIDType)
				{
					uastrDisplayName = UaString(pTag->m_rev1);
				}
				else
				{
					uastrDisplayName = UaString(pTag->name);
				}
			}

			UaGatewayVariable* uaVariable = this->addVariable(
				tagId,
				uastrDisplayName,
				groupId,
				dataType,
				false,
				accessLevel);

			if (OpcUa_Null == uaVariable)
			{
				char szTempCH[1024] = { 0 };
				char szTempEN[1024] = { 0 };
				sprintf(szTempCH, "标签 %s添加失败", pTag->name);
				sprintf(szTempEN, "Fail to add tag %s,", pTag->name);
				pCOPCUAMaster->m_pSetLogInfo(pCOPCUAMaster->m_handle, INFOTYPE_ERR, pCOPCUAMaster->m_log_Source, szTempCH, szTempEN, true, true);
				return false;
			}


			pCOPCUATag->m_handle_UaVariable = uaVariable;
			uaVariable->m_handle_COPCTag = pCOPCUATag;
#if OPCUA_DIAG_LOG
			diagVarCount++;
#endif

		}
	}

	pSharedMutex->releaseReference();

#if OPCUA_DIAG_LOG
	{
		char szDiag[512];
		sprintf(szDiag, "[DIAG onConfigure] OK: groups=%d, variables=%d, tagNumerI=%u, tagNumerO=%u, scanRate(m_cc)=%d ms",
			pCOPCUAMaster->m_OPCSlaveArray.GetSize(), diagVarCount,
			pCOPCUAMaster->m_tagNumerI, pCOPCUAMaster->m_tagNumerO, pCOPCUAMaster->m_cc);
		pCOPCUAMaster->m_pSetLogInfo(pCOPCUAMaster->m_handle, INFOTYPE_RUN, pCOPCUAMaster->m_log_Source, szDiag, szDiag, true, true);
	}
#endif

	//pNode = findNode(UaNodeId(3, getNameSpaceIndex()));
	//if (pNode)
	//{
	//	NodeAccessInfoBase* pAccessInfo = new NodeAccessInfoBase();
	//	pAccessInfo->setRolePermissions(
	//		m_pServerManager->getIdForWellKnownRole(OpcUaId_WellKnownRole_Anonymous),
	//		NodeAccessInfo::PERMISSION_BROWSE);
	//	pAccessInfo->setRolePermissions(
	//		m_pServerManager->getIdForWellKnownRole(OpcUaId_WellKnownRole_AuthenticatedUser),
	//		//NodeAccessInfo::PERMISSION_BROWSE | NodeAccessInfo::PERMISSION_READ);
	//		NodeAccessInfo::PERMISSION_BROWSE);
	//	pAccessInfo->setRolePermissions(
	//		m_pServerManager->getIdForWellKnownRole(OpcUaId_WellKnownRole_Observer),
	//		//NodeAccessInfo::PERMISSION_BROWSE | NodeAccessInfo::PERMISSION_READ);
	//		NodeAccessInfo::PERMISSION_BROWSE);
	//	pAccessInfo->setRolePermissions(
	//		m_pServerManager->getIdForWellKnownRole(OpcUaId_WellKnownRole_Operator),
	//		NodeAccessInfo::PERMISSION_BROWSE | NodeAccessInfo::PERMISSION_READ | NodeAccessInfo::PERMISSION_WRITE);
	//		//NodeAccessInfo::PERMISSION_BROWSE);
	//	pAccessInfo->setRolePermissions(
	//		m_pServerManager->getIdForWellKnownRole(OpcUaId_WellKnownRole_ConfigureAdmin),
	//		//NodeAccessInfo::PERMISSION_BROWSE | NodeAccessInfo::PERMISSION_READROLEPERMISSIONS | NodeAccessInfo::PERMISSION_READ);
	//		NodeAccessInfo::PERMISSION_BROWSE);
	//	pAccessInfo->setRolePermissions(
	//		m_pServerManager->getIdForWellKnownRole(OpcUaId_WellKnownRole_SecurityAdmin),
	//		//NodeAccessInfo::PERMISSION_BROWSE | NodeAccessInfo::PERMISSION_READROLEPERMISSIONS | NodeAccessInfo::PERMISSION_READ | NodeAccessInfo::PERMISSION_WRITE);
	//		NodeAccessInfo::PERMISSION_BROWSE);
	//	pNode->setAccessInfo(pAccessInfo);
	//	pAccessInfo->releaseReference();

	return true;
}

void MyAppNodeManager::onScan(const UaDateTime& time)
{
	COPCUAMaster *pCOPCUAMaster = (COPCUAMaster*)m_OPCUAMasterHandele;
#if OPCUA_DIAG_LOG
	static DWORD s_diagTick = 0;
	static bool s_diagFirst = true;
	static unsigned int s_scanCount = 0;
	s_scanCount++;
	bool bDiag = OpcUaDiagDue(s_diagTick, s_diagFirst);
	int diagInOk = 0, diagAuthFail = 0, diagNullVar = 0, diagDetail = 0;
	char diagLines[OPCUA_DIAG_TAG_DETAIL][512];
#endif
	// The IOServer host may never call IODriverOutput for this driver (observed: it keeps the
	// tag memory fresh but skips Output()), so m_dataO / m_dataQualityO would never be filled.
	// If Output() has not been called within the last 10s, pull the values from tag memory here.
	DWORD dwLastOutput = pCOPCUAMaster->m_dwLastOutputTick;
	bool bPullFromMem = (0 == dwLastOutput) || (GetTickCount() - dwLastOutput > 10000);
	static int s_lastPullMode = -1;
	if (s_lastPullMode != (bPullFromMem ? 1 : 0))
	{
		s_lastPullMode = bPullFromMem ? 1 : 0;
		char szInfo[256];
		sprintf(szInfo, bPullFromMem ?
			"IODriverOutput not called by host, OPC UA values are read from tag memory." :
			"IODriverOutput called by host, OPC UA values come from Output().");
		pCOPCUAMaster->m_pSetLogInfo(pCOPCUAMaster->m_handle, INFOTYPE_RUN, pCOPCUAMaster->m_log_Source, szInfo, szInfo, true, true);
	}

	EnterCriticalSection(&pCOPCUAMaster->m_criticalIOMemAccess);
	
	OpcUa_StatusCode opcUa_StatusCode = OpcUa_Good;
	for (int i = 0; i < (int)pCOPCUAMaster->m_tagNumerO; i++)
	{
#if OPCUA_DIAG_LOG
		if (bDiag)
		{
			COPCUATag *pDiagTag = pCOPCUAMaster->m_OPCTagO[i];
			if (pCOPCUAMaster->m_dataQualityO[i] & TAG_IO_TAGQUALITY_IN_OK) diagInOk++;
			if (!pDiagTag->m_pTag->m_bAuthorizationFlag) diagAuthFail++;
			if (NULL == pDiagTag->m_handle_UaVariable) diagNullVar++;
		}
#endif
		if (bPullFromMem)
		{
			COPCUATag *pPullTag = pCOPCUAMaster->m_OPCTagO[i];
			CTag *pPull = pPullTag->m_pTag;
			double pullValue = 0;
			unsigned int pullQuality = 0;
			char pullStr[MAX_TAGSTRINGVALUE_LEN] = { 0 };
			if (DT_STRING == pPull->type)
				pPull->ReadTagFromMem(pullStr, pullQuality, pPull->type);
			else
				pPull->ReadTagFromMem(pullValue, pullQuality, pPull->type);

			if ((pullQuality & WRITEONETAG_TAGQUALITY_OK) && pPull->m_bAuthorizationFlag)
			{
				pCOPCUAMaster->m_dataQualityO[i] |= TAG_IO_TAGQUALITY_IN_OK;
				if (DT_STRING == pPull->type)
					pPull->WriteTagHex(pCOPCUAMaster->m_dataO + pPullTag->m_offset / 8, pullStr);
				else
					pPull->WriteTagHex(pCOPCUAMaster->m_dataO + pPullTag->m_offset / 8, pullValue, pPullTag->m_offset % 8);
			}
			else
			{
				pCOPCUAMaster->m_dataQualityO[i] &= ~TAG_IO_TAGQUALITY_IN_OK;
			}
		}

		if (pCOPCUAMaster->m_dataQualityO[i] & TAG_IO_TAGQUALITY_IN_OK)
		{
			opcUa_StatusCode = OpcUa_Good;
			COPCUATag *pOPCUATag = pCOPCUAMaster->m_OPCTagO[i];
			CTag *pTag = pOPCUATag->m_pTag;
			double dbValue;
			char strTmep[MAX_TAGSTRINGVALUE_LEN] = { 0 };
			UaGatewayVariable* pUaGatewayVariable = (UaGatewayVariable*)pOPCUATag->m_handle_UaVariable;
			if (DT_STRING != pTag->type)
			{
				pTag->ReadTagHex(pCOPCUAMaster->m_dataO + pOPCUATag->m_offset / 8, dbValue, pOPCUATag->m_offset % 8);
				if (pOPCUATag->m_pOpcSlave->m_bWirteAndRead)
				{
					if (pOPCUATag->m_dbValue != dbValue)
					{
						UaVariant uaVariant = FormatUaVariant(dbValue, pOPCUATag->m_type);
						pUaGatewayVariable->setValue(uaVariant, time, opcUa_StatusCode);
						pOPCUATag->m_dbValue = dbValue;
					}
				}
				else
				{
					UaVariant uaVariant = FormatUaVariant(dbValue, pOPCUATag->m_type);
					pUaGatewayVariable->setValue(uaVariant, time, opcUa_StatusCode);
				}
			

			}
			else
			{
				pTag->ReadTagHex(pCOPCUAMaster->m_dataO  + pOPCUATag->m_offset / 8, strTmep);
				if (pOPCUATag->m_pOpcSlave->m_bWirteAndRead)
				{
					if (0 != pOPCUATag->m_strValue.compare(strTmep))
					{
						UaString  UaStringValue = UaString::fromLocal8Bit(strTmep);
						UaVariant uaVariant(UaStringValue);
						pUaGatewayVariable->setValue(uaVariant, time, opcUa_StatusCode);
						pTag->WriteTagHex(pCOPCUAMaster->m_dataO + pOPCUATag->m_offset / 8, strTmep);
					}
				}
				else
				{
					UaString  UaStringValue = UaString::fromLocal8Bit(strTmep);
					UaVariant uaVariant(UaStringValue);
					pUaGatewayVariable->setValue(uaVariant, time, opcUa_StatusCode);
					pTag->WriteTagHex(pCOPCUAMaster->m_dataO + pOPCUATag->m_offset / 8, strTmep);
				}
			}
			
		}
		else
		{
			opcUa_StatusCode = OpcUa_Bad;
			COPCUATag *pBadTag = pCOPCUAMaster->m_OPCTagO[i];
			UaGatewayVariable* pBadVar = (UaGatewayVariable*)pBadTag->m_handle_UaVariable;
			if (NULL != pBadVar && OpcUa_IsGood(pBadVar->getValue().statusCode()))
			{
				UaVariant lastValue;
				pBadVar->getValue(lastValue);
				pBadVar->setValue(lastValue, time, OpcUa_BadNoCommunication);
				pBadTag->m_dbValue = 0xFFFFFFFF;// force the change-only path to republish Good when quality recovers
			}
		}
	}

#if OPCUA_DIAG_LOG
	if (bDiag)
	{
		for (int i = 0; i < (int)pCOPCUAMaster->m_tagNumerO && diagDetail < OPCUA_DIAG_TAG_DETAIL; i++)
		{
			COPCUATag *pDiagTag = pCOPCUAMaster->m_OPCTagO[i];
			UaGatewayVariable* pDiagVar = (UaGatewayVariable*)pDiagTag->m_handle_UaVariable;
			OpcUa_StatusCode varStatus = OpcUa_BadInternalError;
			UaString varValue("<null variable>");
			if (NULL != pDiagVar)
			{
				UaDataValue dv = pDiagVar->getValue();
				varStatus = dv.statusCode();
				varValue = UaVariant(*dv.value()).toString();
			}
			// read the tag memory directly, the same call Output() uses, to see whether the
			// host keeps it fresh even though it never calls IODriverOutput
			double memValue = 0;
			unsigned int memQuality = 0;
			char memStr[MAX_TAGSTRINGVALUE_LEN] = { 0 };
			if (DT_STRING == pDiagTag->m_pTag->type)
				pDiagTag->m_pTag->ReadTagFromMem(memStr, memQuality, pDiagTag->m_pTag->type);
			else
				pDiagTag->m_pTag->ReadTagFromMem(memValue, memQuality, pDiagTag->m_pTag->type);
			_snprintf(diagLines[diagDetail], sizeof(diagLines[0]) - 1,
				"[DIAG onScan] tag[%d] %s: memQuality=0x%X (OK=%d), mem=%f/%s, qualityO=0x%02X (IN_OK=%d), uaStatus=0x%08X, uaValue=%s, auth=%d, uaVar=%p",
				i, pDiagTag->m_pTag->name,
				memQuality, (memQuality & WRITEONETAG_TAGQUALITY_OK) ? 1 : 0,
				memValue, memStr,
				(unsigned char)pCOPCUAMaster->m_dataQualityO[i],
				(pCOPCUAMaster->m_dataQualityO[i] & TAG_IO_TAGQUALITY_IN_OK) ? 1 : 0,
				varStatus, varValue.toUtf8(),
				pDiagTag->m_pTag->m_bAuthorizationFlag ? 1 : 0, pDiagVar);
			diagLines[diagDetail][sizeof(diagLines[0]) - 1] = 0;
			diagDetail++;
		}
	}
#endif

	LeaveCriticalSection(&pCOPCUAMaster->m_criticalIOMemAccess);

#if OPCUA_DIAG_LOG
	if (bDiag)
	{
		char szDiag[512];
		sprintf(szDiag, "[DIAG onScan] scanCount=%u, scanRate=%u ms, tagNumerO=%u, IN_OK=%d, authFail=%d, nullUaVar=%d",
			s_scanCount, scanRate(), pCOPCUAMaster->m_tagNumerO, diagInOk, diagAuthFail, diagNullVar);
		pCOPCUAMaster->m_pSetLogInfo(pCOPCUAMaster->m_handle, INFOTYPE_RUN, pCOPCUAMaster->m_log_Source, szDiag, szDiag, true, true);
		for (int d = 0; d < diagDetail; d++)
			pCOPCUAMaster->m_pSetLogInfo(pCOPCUAMaster->m_handle, INFOTYPE_RUN, pCOPCUAMaster->m_log_Source, diagLines[d], diagLines[d], true, true);
	}
#endif
	
	//OpcUa_Boolean bActive = OpcUa_True;
	//EventManagerBase* pEventManager = getEventManagerUaNode();
	//m_pUaOffNormalAlarmData->lockEventData();
	//m_pUaOffNormalAlarmData->setActiveState(bActive);
	//m_pUaOffNormalAlarmData->setActiveState_TransitionTime(UaDateTime::now());
	//if (OpcUa_False == bActive)
	//{
	//	m_pUaOffNormalAlarmData->setMessage(UaLocalizedText("en", "No nodes off normal alarm inactive"));
	//}
	//else
	//{
	//	m_pUaOffNormalAlarmData->setMessage(UaLocalizedText("en", "No nodes off normal alarm active"));
	//}
	//m_pUaOffNormalAlarmData->prepareNewEvent(UaDateTime::now(), UaDateTime::now(), UaByteString());
	//// Unlock event data before fire event
	//m_pUaOffNormalAlarmData->unlockEventData();
	//if (bActive)
	//{

	//	//pEventManager->fireEvent(m_pOffNormalAlarmData);
	//	pEventManager->fireEvent(m_pUaOffNormalAlarmData);
	//}
}

void MyAppNodeManager::onWrite(
	UaVariant& value,
	UaGatewayVariable* pVariable)
{
	//UaNodeId uaNodeId = pVariable->nodeId();
	if (NULL != pVariable->m_handle_COPCTag)
	{
		COPCUATag* pCOPCUATag = (COPCUATag*)pVariable->m_handle_COPCTag;
		CTag*pTag = pCOPCUATag->m_pTag;
		COPCUAMaster *pCOPCUAMaster = (COPCUAMaster*)m_OPCUAMasterHandele;
		EnterCriticalSection(&pCOPCUAMaster->m_criticalIOMemAccess);

		OpcUa_BuiltInType dataType;
		//if (pCOPCUATag->m_type == DT_BOOL)
		//	dataType = OpcUaType_Boolean;
		//else if (pCOPCUATag->m_type == DT_BYTE)
		//	dataType = OpcUaType_Byte;
		//else if (pCOPCUATag->m_type == DT_SBYTE)
		//	dataType = OpcUaType_SByte;
		//else if (pCOPCUATag->m_type == DT_WORD)
		//	dataType = OpcUaType_UInt16;
		//else if (pCOPCUATag->m_type == DT_SWORD)
		//	dataType = OpcUaType_Int16;
		//else if (pCOPCUATag->m_type == DT_DWORD)
		//	dataType = OpcUaType_UInt32;
		//else if (pCOPCUATag->m_type == DT_SDWORD)
		//	dataType = OpcUaType_Int32;
		//else if (pCOPCUATag->m_type == DT_SINGLE)
		//	dataType = OpcUaType_Float;
		//else if (pCOPCUATag->m_type == DT_DOUBLE)
		//	dataType = OpcUaType_Double;
		//else if (pCOPCUATag->m_type == DT_STRING)
		//	dataType = OpcUaType_String;
		//else
		//	dataType = OpcUaType_Float;

		if (pCOPCUATag->m_type != DT_STRING)
		{
			OpcUa_Double opcUa_Double;
			if (OpcUa_IsNotGood(value.toDouble(opcUa_Double)))
			{
				LeaveCriticalSection(&pCOPCUAMaster->m_criticalIOMemAccess);
				return;
			}

			pVariable->setValue(value, UaDateTime::now());
			pTag->WriteTagHex(pCOPCUAMaster->m_dataI + pCOPCUATag->m_offset / 8, opcUa_Double, pCOPCUATag->m_offset % 8);
			//确保能写如实时库
			if (opcUa_Double !=0 )
			{
				pCOPCUATag->m_dbValue = 0;
			}
			pCOPCUAMaster->m_dataQualityI[pCOPCUATag->m_iTagIndex] |= TAG_IO_TAGQUALITY_IN_OK;
		}
		else
		{
			UaString opcUaString;
		
			opcUaString = value.toString();
			pVariable->setValue(value, UaDateTime::now());
			char strTmep[MAX_TAGSTRINGVALUE_LEN] = { 0 };
			memcpy(strTmep, opcUaString.toLocal8Bit(), min(opcUaString.toLocal8Bit().size(), MAX_TAGSTRINGVALUE_LEN));
			pTag->WriteTagHex(pCOPCUAMaster->m_dataI + pCOPCUATag->m_offset / 8, strTmep);
			//确保能写如实时库
			if (opcUaString != "")
			{
				pCOPCUATag->m_strValue = "";
			}
			pCOPCUAMaster->m_dataQualityI[pCOPCUATag->m_iTagIndex] |= TAG_IO_TAGQUALITY_IN_OK;
		}

		LeaveCriticalSection(&pCOPCUAMaster->m_criticalIOMemAccess);
	}

	
	//if (UaNodeId(5, getNameSpaceIndex()) == pVariable->nodeId())
	//{
	//	if (OpcUa_IsNotGood(value.toUInt32(m_counter))) return;
	//	m_pCounterWrite->setValue(value, UaDateTime::now());
	//}
	//
	//else if (UaNodeId("AlarmsNoNodes.OffNormalAlarmTrigger", getNameSpaceIndex()) == pVariable->nodeId())
	//{
	//	OpcUa_Boolean isActive = OpcUa_False;
	//	value.toBool(isActive);
	//	OpcUa_Boolean bActive = isActive;
	//	EventManagerBase* pEventManager = getEventManagerUaNode();
	//	OpcUa_ReferenceParameter(pEventManager);
	//	if (bActive == OpcUa_False && m_pUaOffNormalAlarmData->getAckedState() != OpcUa_False)
	//	{
	//		m_pUaOffNormalAlarmData->setRetain(OpcUa_False);
	//	}
	//	else
	//	{
	//		m_pUaOffNormalAlarmData->setRetain(OpcUa_True);
	//	}
	//	// if the alarm gets active we require acknowledging
	//	if (bActive)
	//	{
	//		m_pUaOffNormalAlarmData->setAckedState(OpcUa_False);
	//	}

	//	// Lock the event data for change since a refresh may access the data in parallel
	//	m_pUaOffNormalAlarmData->lockEventData();
	//	m_pUaOffNormalAlarmData->setActiveState(bActive);
	//	m_pUaOffNormalAlarmData->setActiveState_TransitionTime(UaDateTime::now());
	//	if (OpcUa_False == bActive)
	//	{
	//		m_pUaOffNormalAlarmData->setMessage(UaLocalizedText("en", "No nodes off normal alarm inactive"));
	//	}
	//	else
	//	{
	//		m_pUaOffNormalAlarmData->setMessage(UaLocalizedText("en", "No nodes off normal alarm active"));
	//	}
	//	m_pUaOffNormalAlarmData->prepareNewEvent(UaDateTime::now(), UaDateTime::now(), UaByteString());
	//	// Unlock event data before fire event
	//	m_pUaOffNormalAlarmData->unlockEventData();
	//	if (bActive)
	//	{

	//		//pEventManager->fireEvent(m_pOffNormalAlarmData);
	//		pEventManager->fireEvent(m_pUaOffNormalAlarmData);
	//	}
	//	
	//}

}

OpcUa_UInt32 MyAppNodeManager::scanRate() const
{
	COPCUAMaster *pCOPCUAMaster = (COPCUAMaster*)m_OPCUAMasterHandele;
	return pCOPCUAMaster->m_cc;
	//return 2000;
}


