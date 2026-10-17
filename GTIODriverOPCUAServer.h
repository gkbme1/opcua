// GTIODriverOPCServer.h : main header file for the GTIODRIVEROPCSERVER DLL
//

#if !defined(AFX_GTIODRIVEROPCUASERVER_H__23EB24E3_DDFE_451D_8C02_CDA5D848A68B__INCLUDED_)
#define AFX_GTIODRIVEROPCUASERVER_H__23EB24E3_DDFE_451D_8C02_CDA5D848A68B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




/////////////////////////////////////////////////////////////////////////////
// CGTIODriverOPCServerApp
// See GTIODriverOPCServer.cpp for the implementation of this class
//
class COPCUAMaster;
class CGTIODriverOPCUAServerApp
{
public:
	COPCUAMaster *m_pOPCMaster;
	CGTIODriverOPCUAServerApp();
	//string m_keyFlag;//keyœ‡πÿ 

};

#include "tag.h"

typedef bool (*fpAddTag)(void*handle,CTag*pTag, bool bWriAndRedisWri);
typedef bool (*fpIsMaster)();
typedef bool(*fpSetLoginfo)(void* handle, int iType, const string& strModel, const string& strDes, const string& strENDes, bool bIsShowToClient, bool manageLog);
typedef void(*fpMastertThreadRunningFlag)(void* handle, bool bRunningFlag);
typedef void(*fpInitMemQuality)(void* handle, CTag*pTag);

#ifdef __cplusplus    // If used by C++ code,   
extern "C" {          // we need to export the C interface  
#endif

	MACS_DLL_EXPORT bool  IODriverInit(void*handle, void*&driverContext, char*cmdLine, fpAddTag AddTag, fpIsMaster isMaster, fpSetLoginfo pFunSetInfo, fpMastertThreadRunningFlag MastertThreadRunningFlag, fpInitMemQuality InitMemQuality, int cycle);
	MACS_DLL_EXPORT void IODriverInitQuality(void* handle, void* driverContext);
	MACS_DLL_EXPORT int  IODriverInput(void*handle, void*driverContext);
	MACS_DLL_EXPORT int  IODriverOutput(void*handle, void*driverContext);
	MACS_DLL_EXPORT bool  IODriverGrpTagInfo(void*driverContext, intptr_t*& pGrpTagBuf, int& iCount);
	MACS_DLL_EXPORT bool  IODriverStatus(void*driverContext, void* pDriverMessage);
	MACS_DLL_EXPORT void  IODriverMasterRun(void*driverContext);
	MACS_DLL_EXPORT void  IODriverAddTag(void*handle, void*driverContext);
	MACS_DLL_EXPORT void  IODriverUnInit(void*driverContext);
	MACS_DLL_EXPORT void  IOIODriverStopThreadAndCloseHandle(void*handle, void*driverContext, int ncloseStep);

#ifdef __cplusplus
}
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GTIODRIVEROPCSERVER_H__23EB24E3_DDFE_451D_8C02_CDA5D848A68B__INCLUDED_)
