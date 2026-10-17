// OPCMaster.h: interface for the COPCMaster class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCUAMASTER_H__FB801AC6_89CB_41AB_BC2F_D72E62FD2CA5__INCLUDED_)
#define AFX_OPCUAMASTER_H__FB801AC6_89CB_41AB_BC2F_D72E62FD2CA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LightThread.h"
#include "LightMutex.h"
class COPCUASlave;
class COPCUATag;
class COPCUAFrame;
#define MAX_TAG 100000 
#include "GTIODriverOPCUASERVER.h"
#include "LuaRuntime.h"
#include "taghash.h"
#include "MyArray.h"
#include "uagatewayserver.h"
#include "shutdownsignal.h"
#include "myappnodemanager.h"
#include "myappcallback.h"
#pragma comment(lib, "comsuppw.lib")

// Diagnostic logging for the "BadWaitingForInitialData / no refresh" issue.
// Set OPCUA_DIAG_LOG to 0 to disable all diag output.
#define OPCUA_DIAG_LOG 1
#define OPCUA_DIAG_INTERVAL_MS 10000   // at most one diag batch per 10s per call site
#define OPCUA_DIAG_TAG_DETAIL 5        // number of tags printed in detail

// Returns true on the first call and then at most once per OPCUA_DIAG_INTERVAL_MS.
inline bool OpcUaDiagDue(DWORD& lastTick, bool& first)
{
	DWORD now = GetTickCount();
	if (first || now - lastTick >= OPCUA_DIAG_INTERVAL_MS)
	{
		first = false;
		lastTick = now;
		return true;
	}
	return false;
}
class COPCUAMaster //: public CLightThread
{
public:
	//bool WriteTagCallback(COPCSDKTag*pOPCSDKTag);
	//bool ReadTagCallback(COPCSDKTag*pOPCSDKTag);
	//读下一个协议报文格式，pLine是当前一行，pMem是后面内容
	BOOL m_autosimulatequalitybad;
	BOOL m_autosimulatequalityok;
	BOOL m_autosimulateAutoInc;//自动累加
	bool SetTagInvalid(char*tagName);
	CLuaRuntime m_luaRuntime;
	int Output(void*handle);
	int Input(void*handle);
	CRITICAL_SECTION m_criticalIOMemAccess;
	bool Init(void*handle,void*&driverContext,char*cmdLine,fpAddTag AddTag);
	string m_cmdLine;
	fpAddTag m_AddTag;
	fpIsMaster m_isMaster;//不是主不采集
	fpSetLoginfo m_pSetLogInfo;
	fpMastertThreadRunningFlag m_pMastertThreadRunningFlag;
	fpInitMemQuality m_pInitMemQuality;
	void*m_handle;//用来指向IOServer的tagManangerClient对象。

	void PollSlave();
	void ReleaseFrame();

	DWORD m_cycleCounter;
	DWORD m_cycleDelay;
	bool ReadCSV();
	int m_dataLengthI ;//bit 为单位.
	int m_dataLengthO ;//bit 为单位.
	char *m_dataI;//Input mem block
	char *m_dataO;//output mem block
	char *m_dataQualityI;//Input mem block Quality, 0-ok,1-Invalid. 只有质量好时才能用于计算.
	char *m_dataQualityO;//output mem block Quality, 0-ok,1-Invalid;只有质量好时才能输出到从站.
	
	COPCUATag *m_OPCTagI[MAX_TAG];//输入tag名，只用于初始化与IOServer的通讯
	COPCUATag *m_OPCTagO[MAX_TAG];//输出tag名
	CTagHash m_tagHashIO;//用于快速定位
	DWORD m_tagNumerI;//
	DWORD m_tagNumerO;//
	volatile DWORD m_dwLastOutputTick;// GetTickCount() of the last host call to Output(), 0 = never called
	DWORD m_tagOffsetI;//bits
	DWORD m_tagOffsetO;//bits

	COPCUAFrame* m_pOPCFrame;
	CMyArray m_OPCSlaveArray;
	COPCUAMaster();
	virtual ~COPCUAMaster();
	//线程主循环（是可以重载的虚函数）
	//virtual void Run();
	int m_cc;
	int m_nURLType;
	char m_chAddress[100]; //IP或计算机名
	int m_nPort;
	intptr_t* m_pGrpTagBufLocal;//用于保存给ioserver返回的信息
	int m_iCSVGrpCnt;//实际的组个数
	eDEVSTATUS m_iDevStatus;
	char m_log_Source[256];

	bool OPCUAServerStart(string strServerConfigfileName);
	bool OPCUAServerStop();
	UaString m_path;
	bool UAServerRun();
	ShutdownSignal m_shutdownSignal;
	MyAppNodeManager m_nodeManager;
	MyAppCallback m_callback;
	UaGatewayServer m_server;

	bool m_bEnableAnonymou;
	bool m_bEnableUserPw;
	char m_chUser[100];
	char m_chPassWord[100];
	int m_nDisplayNameType;
};

#endif // !defined(AFX_OPCMASTER_H__FB801AC6_89CB_41AB_BC2F_D72E62FD2CA5__INCLUDED_)
