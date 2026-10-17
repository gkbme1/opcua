#ifndef MYAPPNODEMANAGER_H
#define MYAPPNODEMANAGER_H

#include "uagatewaynodemanager.h"

#if SUPPORT_Event_Subscription_Server_Facet
#include "eventmanageruanode.h"
#include "opcua_offnormalalarmtype.h"
#include "opcua_nonexclusivelevelalarmtype.h"
#include "opcua_exclusivelevelalarmtype.h"
#endif // SUPPORT_Event_Subscription_Server_Facet
#include "opcua_foldertype.h"

#include <uagenericoptionsetvalue.h>
#include <uaoptionsetdefinition.h>


#if SUPPORT_Historical_Access
class HistoryManagerCache;
#endif // SUPPORT_Historical_Access

struct  UaNodeIdHandle
{
	HANDLE Handle_COPCTag = NULL;
	HANDLE Handle_UaVariable = NULL;
};

#if SUPPORT_Historical_Access
class HistoryManagerCache;
#endif // SUPPORT_Historical_Access

class MyAppNodeManager : public UaGatewayNodeManager
{
public:
	MyAppNodeManager();
	virtual ~MyAppNodeManager();
	
public:
	virtual bool onInitialize();
	virtual void onFinalize();

	virtual bool onConfigure();

	virtual void onScan(const UaDateTime& time);

	virtual void onWrite(
		UaVariant& value,
		UaGatewayVariable* pVariable);
		
	virtual OpcUa_UInt32 scanRate() const;

//
//#if SUPPORT_Historical_Access
//	HistoryManagerCache*                   m_pHistoryManagerCache;
//#endif // SUPPORT_Historical_Access

#if SUPPORT_Event_Subscription_Server_Facet && SUPPORT_Method_Server_Facet
	OpcUa::OffNormalAlarmType*             m_pUaOffNormalAlarm;
	OpcUa::OffNormalAlarmTypeData*         m_pUaOffNormalAlarmData;

	RoleTypeOperations* m_pRoleTypeOperations1;
	RoleTypeOperations* m_pRoleTypeOperations2;
	HANDLE  m_OPCUAMasterHandele;
#endif // SUPPORT_Event_Subscription_Server_Facet && SUPPORT_Method_Server_Facet
	
};	

#endif