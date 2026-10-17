// GTIODriverOPCServer.cpp : Defines the initialization routines for the DLL.
//


#include "GTIODriverOPCUAServer.h"
#include "CommMath.h"
#include "OPCUAMaster.h"
#include "OPCUASlave.h"
#include "TagManagerClient.h"
#include "IODriverManager.h"
#include "OPCUATag.h"

#if OPCUA_DIAG_LOG
// Build stamp printed in every host-call log, to prove which DLL build is loaded.
#define OPCUA_DIAG_BUILD "diag-v3 " __DATE__ " " __TIME__

// Logs (throttled) that the host IOServer called one of the exported IODriver* functions.
static void OpcUaDiagHostCall(COPCUAMaster* pMaster, const char* func, DWORD& tick, bool& first, unsigned int& calls)
{
	calls++;
	if (NULL == pMaster || NULL == pMaster->m_pSetLogInfo) return;
	if (!OpcUaDiagDue(tick, first)) return;
	char szDiag[512];
	sprintf(szDiag, "[DIAG host-call] %s calls=%u (%s)", func, calls, OPCUA_DIAG_BUILD);
	pMaster->m_pSetLogInfo(pMaster->m_handle, INFOTYPE_RUN, pMaster->m_log_Source, szDiag, szDiag, true, true);
}
#define OPCUA_DIAG_HOST_CALL(pMaster, func) \
	{ static DWORD s_t = 0; static bool s_f = true; static unsigned int s_c = 0; OpcUaDiagHostCall(pMaster, func, s_t, s_f, s_c); }
#else
#define OPCUA_DIAG_HOST_CALL(pMaster, func)
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//
extern bool g_bOk1;
/////////////////////////////////////////////////////////////////////////////
// CGTIODriverOPCServerApp


/////////////////////////////////////////////////////////////////////////////
// CGTIODriverOPCServerApp construction

CGTIODriverOPCUAServerApp::CGTIODriverOPCUAServerApp()
{
	// TODO: add construction code here,
	m_pOPCMaster=0;
	//AfxEnableControlContainer();//加上这句才能显示DLL中的含控件的对话框。
	//::CoInitialize(NULL);	// Place all significant initialization in InitInstance
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGTIODriverOPCServerApp object

CGTIODriverOPCUAServerApp theApp;



bool  IODriverInit(void*handle,void*&driverContext,char*cmdLine,fpAddTag AddTag,fpIsMaster isMaster, fpSetLoginfo pFunSetInfo, fpMastertThreadRunningFlag MastertThreadRunningFlag, fpInitMemQuality InitMemQuality, int cycle)
{
	if(handle==0)//表示释放DLL
	{
		COPCUAMaster *pOPCMaster = (COPCUAMaster*)driverContext;
		//pOPCMaster->StopThread();
		delete pOPCMaster;
		return true;
	}

	COPCUAMaster *pOPCMaster = new COPCUAMaster();
	theApp.m_pOPCMaster = pOPCMaster;
	driverContext = pOPCMaster;
	pOPCMaster->m_cmdLine = cmdLine;
	pOPCMaster->m_handle = handle;
	pOPCMaster->m_AddTag = AddTag;
	pOPCMaster->m_isMaster = isMaster;	
	pOPCMaster->m_pSetLogInfo = pFunSetInfo;
	pOPCMaster->m_cc = cycle;	
	pOPCMaster->m_pMastertThreadRunningFlag = MastertThreadRunningFlag;
	pOPCMaster->m_pInitMemQuality = InitMemQuality;
	pOPCMaster->m_pMastertThreadRunningFlag(handle, true);
	bool bInit = pOPCMaster->Init(handle,driverContext,cmdLine,AddTag);
	OPCUA_DIAG_HOST_CALL(pOPCMaster, bInit ? "IODriverInit(ok)" : "IODriverInit(FAILED)");
	return bInit;
}

void IODriverInitQuality(void* handle, void* driverContext)
{
	COPCUAMaster *pMaster = (COPCUAMaster *)driverContext;
	CIODriverManager *pCIODriverManager = (CIODriverManager*)handle;
	OPCUA_DIAG_HOST_CALL(pMaster, "IODriverInitQuality");
	for (int i = 0; i < pMaster->m_tagNumerI; i++)
	{
		CTag* pTag = pMaster->m_OPCTagI[i]->m_pTag;
		pMaster->m_pInitMemQuality(handle, pTag);
	}
}

int  IODriverInput(void*handle,void*driverContext)
{
	COPCUAMaster *pOPCMaster  = (COPCUAMaster *)driverContext;
	OPCUA_DIAG_HOST_CALL(pOPCMaster, "IODriverInput");
	int ret = pOPCMaster->Input(handle);
	
	return ret;
}

int  IODriverOutput(void*handle,void*driverContext)
{
	COPCUAMaster *pOPCMaster  = (COPCUAMaster *)driverContext;
	OPCUA_DIAG_HOST_CALL(pOPCMaster, "IODriverOutput");
	int ret = pOPCMaster->Output(handle);
	
	return ret;
}

bool IODriverGrpTagInfo(void*driverContext, intptr_t*& pGrpTagBuf, int& iCount)
{
	COPCUAMaster *pMaster = (COPCUAMaster *)driverContext;
	int iGrpSize = pMaster->m_OPCSlaveArray.GetSize();
	OPCUA_DIAG_HOST_CALL(pMaster, "IODriverGrpTagInfo");

	//intptr_t* pGrpTagBufLocal = NULL;
	char* pGrpTagSubBuf = NULL;//单个sGROUPTAG的大小
	intptr_t* pTagBufSlave = NULL;
	int iGrpTagSize = 0;

	//begin 先释放
	if (pMaster->m_iCSVGrpCnt > 0 && NULL != pMaster->m_pGrpTagBufLocal)
	{
		for (int i = 0; i < pMaster->m_iCSVGrpCnt; ++i)
		{
			sGROUPTAG* pchgBuf = (sGROUPTAG*)(*(pMaster->m_pGrpTagBufLocal + i));//获取到sGROUPTAG的指针地址
			if (0 != pchgBuf->iTagBuf)
			{
				delete (intptr_t*)(pchgBuf->iTagBuf);
				//pchgBuf->pTagBuf = NULL;
			}
			if (0 != pchgBuf->iTagSlaveBuf)
			{
				delete (intptr_t*)(pchgBuf->iTagSlaveBuf);
			}
			delete pchgBuf;
		}
		delete pMaster->m_pGrpTagBufLocal;
		pMaster->m_pGrpTagBufLocal = NULL;
	}
	//end
	pMaster->m_pGrpTagBufLocal = new intptr_t[pMaster->m_iCSVGrpCnt];
	memset(pMaster->m_pGrpTagBufLocal, 0, sizeof(intptr_t)*pMaster->m_iCSVGrpCnt);
	pGrpTagBuf = pMaster->m_pGrpTagBufLocal;
	iCount = pMaster->m_iCSVGrpCnt;
	int iSetIndex = 0;
	for (int i = 0; i < iGrpSize; ++i)
	{
		sGROUPTAG groupTag;
		intptr_t* pTagBuf = NULL;
		COPCUASlave *pGroupSlave = NULL;//读写组关联组 写组
		COPCUASlave *pGroup = (COPCUASlave*)pMaster->m_OPCSlaveArray.GetAt(i);
		memcpy(groupTag.szGroupName, pGroup->m_grpName, sizeof(groupTag.szGroupName));
		groupTag.iTagCnt = pGroup->m_tagNumer;

		int iPointSize = sizeof(intptr_t);
		iGrpTagSize = 0;
		iGrpTagSize += MAX_LEN_GRPNAME;
		iGrpTagSize += sizeof(int);//组标号
		iGrpTagSize += sizeof(int);//个数
		iGrpTagSize += iPointSize;//标签指针
		iGrpTagSize += iPointSize;//读写组关联的标签指针

		//读写组，需要设置相关组的标签信息,由读组找写组
		if (pGroup->m_bWirteAndRead
			&& (pGroup->m_OPCGroupType == OPC_GROUP_C2S))
		{
			pGroupSlave = pGroup->m_pGroupSlave;
		}
		else if (pGroup->m_bWirteAndRead)
		{//读写组的写组的时候，直接返回
			continue;
		}
		pGrpTagSubBuf = new char[iGrpTagSize];
		memset(pGrpTagSubBuf, 0, iGrpTagSize);
		memcpy(pGrpTagSubBuf, groupTag.szGroupName, MAX_LEN_GRPNAME);
		groupTag.iGroupNo = IO_OPC_UA_SERVER * MAX_GROUP_TYPE + pGroup->m_OPCGroupType;

		if (pGroup->m_bWirteAndRead)
		{
			// ModbusReadDO 1 ModbusReadAO 3
			groupTag.iGroupNo = IO_OPC_UA_SERVER * MAX_GROUP_TYPE + pGroup->m_OPCGroupType + 10;
		}

		memcpy(pGrpTagSubBuf + MAX_LEN_GRPNAME, &(groupTag.iGroupNo), 4);
		memcpy(pGrpTagSubBuf + MAX_LEN_GRPNAME + 4, &(groupTag.iTagCnt), 4);

		intptr_t ulAddl = (intptr_t)pGrpTagSubBuf;
		*(pMaster->m_pGrpTagBufLocal + iSetIndex++) = ulAddl;

		if (pGroup->m_tagNumer <= 0)
		{
			continue;
		}
		pTagBuf = new intptr_t[pGroup->m_tagNumer];
		memset(pTagBuf, 0, sizeof(intptr_t)*pGroup->m_tagNumer);
		if (pGroup->m_slaveDataSizeI > 0)
		{
			for (int j = 0; j < groupTag.iTagCnt; ++j)
			{
				COPCUATag *pGrpTag = pGroup->m_OPCTagI[j];
				CTag *pTag = pGrpTag->m_pTag;
				*(pTagBuf + j) = (intptr_t)pTag;
			}

		}
		else if (pGroup->m_slaveDataSizeO > 0)
		{
			for (int j = 0; j < groupTag.iTagCnt; ++j)
			{
				COPCUATag *pGrpTag = pGroup->m_OPCTagO[j];
				CTag *pTag = pGrpTag->m_pTag;
				*(pTagBuf + j) = (intptr_t)pTag;
			}
		}

		ulAddl = (intptr_t)pTagBuf;
		memcpy((pGrpTagSubBuf + MAX_LEN_GRPNAME + 4 + 4), &ulAddl, sizeof(intptr_t));
		if (NULL != pGroupSlave)
		{
			pTagBufSlave = new intptr_t[pGroup->m_tagNumer];
			memset(pTagBufSlave, 0, sizeof(intptr_t)*pGroup->m_tagNumer);
			if (pGroupSlave->m_slaveDataSizeO > 0)
			{
				for (int j = 0; j < groupTag.iTagCnt; ++j)
				{
					COPCUATag *pGrpTag = pGroupSlave->m_OPCTagO[j];
					CTag *pTag = pGrpTag->m_pTag;
					*(pTagBufSlave + j) = (intptr_t)pTag;
				}
				ulAddl = (intptr_t)pTagBufSlave;
				memcpy(pGrpTagSubBuf + MAX_LEN_GRPNAME + 4 + 4 + sizeof(intptr_t), &ulAddl, sizeof(intptr_t));
			}
		}
	}

	return true;
}

bool  IODriverStatus(void*driverContext, void* pDriverMessage)
{
	COPCUAMaster *pMaster = (COPCUAMaster *)driverContext;

	DriverMessage *pMessage = (DriverMessage*)pDriverMessage;
	OPCUA_DIAG_HOST_CALL(pMaster, "IODriverStatus");
#if OPCUA_DIAG_LOG
	{
		// the old driver thread only exchanged data when m_isMaster() was true
		static DWORD s_t = 0;
		static bool s_f = true;
		if (OpcUaDiagDue(s_t, s_f))
		{
			char szDiag[512];
			int isMaster = (NULL == pMaster->m_isMaster) ? -1 : (pMaster->m_isMaster() ? 1 : 0);
			sprintf(szDiag, "[DIAG Status] isMaster()=%d (-1=null), m_iDevStatus=%d", isMaster, (int)pMaster->m_iDevStatus);
			pMaster->m_pSetLogInfo(pMaster->m_handle, INFOTYPE_RUN, pMaster->m_log_Source, szDiag, szDiag, true, true);
		}
	}
#endif

	pMessage->iStatus = pMaster->m_iDevStatus;
	ProtocolLogUtil logUtil;
	logUtil.recordManageLog(pMaster, pMaster->m_iDevStatus);
	return true;
}

void  IODriverMasterRun(void*driverContext)
{

	COPCUAMaster *pMaster = (COPCUAMaster *)driverContext;
	//pMaster->PollSlave();
	OPCUA_DIAG_HOST_CALL(pMaster, "IODriverMasterRun");
	if (DEVSTATUS_ALLERR == pMaster->m_iDevStatus)
	{
		pMaster->UAServerRun();
	}
	return;
}


void  IODriverAddTag(void*handle, void*driverContext)
{
	CIODriverManager *pCIODriverManager = (CIODriverManager*)handle;
	COPCUAMaster *pMaster = (COPCUAMaster *)driverContext;
	OPCUA_DIAG_HOST_CALL(pMaster, "IODriverAddTag");

	//opc da server不统计授权
	for (int i = 0; i < pMaster->m_tagNumerI; i++)
	{
		COPCUATag* pOPCTag = pMaster->m_OPCTagI[i];

		//if (!pMaster->m_AddTag(pCIODriverManager, pOPCTag->m_pTag, pOPCTag->m_pOpcSlave->m_bWriAndRedisWri))
		//{
		//	pOPCTag->m_pTag->m_bAuthorizationFlag = false;
		//}
		if (!pMaster->m_AddTag(pCIODriverManager, pOPCTag->m_pTag, true))
		{
			pOPCTag->m_pTag->m_bAuthorizationFlag = false;
		}
	}

	for (int i = 0; i < pMaster->m_tagNumerO; i++)
	{
		COPCUATag* pOPCTag = pMaster->m_OPCTagO[i];

		//if (!pMaster->m_AddTag(pCIODriverManager, pOPCTag->m_pTag, pOPCTag->m_pOpcSlave->m_bWriAndRedisWri))
		//{
		//	pOPCTag->m_pTag->m_bAuthorizationFlag = false;
		//}
		if (!pMaster->m_AddTag(pCIODriverManager, pOPCTag->m_pTag, true))
		{
			pOPCTag->m_pTag->m_bAuthorizationFlag = false;
		}
	}
	return;
}

void  IODriverUnInit(void*driverContext)
{
	COPCUAMaster *pMaster = (COPCUAMaster *)driverContext;
	delete pMaster;
}

void IOIODriverStopThreadAndCloseHandle(void*handle, void*driverContext, int ncloseStep)
{
	COPCUAMaster *pMaster = (COPCUAMaster *)driverContext;
	if (enIODriverCloseStep::BeforRunningFlag == ncloseStep)
	{
		//pMaster->m_bMasterRunningExitFlag = true;
		pMaster->OPCUAServerStop();
		return;
	}
	else if (enIODriverCloseStep::AfterRunningFlag == ncloseStep)
	{
		pMaster->ReleaseFrame();
		pMaster->m_pMastertThreadRunningFlag(handle, false);
	}
}
