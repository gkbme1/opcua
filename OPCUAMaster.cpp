// OPCMaster.cpp: implementation of the COPCMaster class.
//
//////////////////////////////////////////////////////////////////////

#include <comutil.h>
#include "Md5A.h"//key相关
#include "ProjPath.h"
#include "OPCUAMaster.h"
#include "OPCUAtag.h"
#include "CommString.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "math.h"
#include "OPCUAslave.h"
#include "OPCUAframe.h"
#include "TagManagerClient.h"
#include "IODriverManager.h"

#include "xmldocument.h"


#define URLType_IP 0
#define URLType_HostName 1
int CopyConfigFile(const char* sourceFile, const char* dstFile)
{
	FILE *in_file, *out_file;
	char data[MAX_PATH];
	size_t bytes_in, bytes_out;
	long len = 0;


	if ((in_file = fopen(sourceFile, "rb")) == NULL)
	{
		//perror(sourceFile);
		return 2;
	}
	if ((out_file = fopen(dstFile, "wb")) == NULL)
	{
		//perror(dstFile);
		return 3;
	}


	while ((bytes_in = fread(data, 1, MAX_PATH, in_file)) > 0)
	{
		bytes_out = fwrite(data, 1, bytes_in, out_file);
		if (bytes_in != bytes_out)
		{
			//perror("Fatal write error.\n");
			return 4;
		}
		len += bytes_out;
		//printf("copying file .... %d bytes copy\n", len);
	}

	fclose(in_file);
	fclose(out_file);

	return 0;
}

COPCUAMaster::COPCUAMaster()
{
	m_autosimulateAutoInc=0;
	m_autosimulatequalitybad = m_autosimulatequalityok= FALSE;
	InitializeCriticalSection(&m_criticalIOMemAccess);
	m_handle = 0;
	m_tagNumerI = 0;
	m_tagNumerO = 0;
	m_tagOffsetI = 0;
	m_tagOffsetO = 0;
	m_cycleCounter = 0;
	m_dataO=0;
	m_dataQualityO=0;
	m_dataI=0;
	m_dataQualityI=0;
	m_pGrpTagBufLocal = 0;
	m_iCSVGrpCnt = 0;
	m_iDevStatus = DEVSTATUS_INIT;

	m_pOPCFrame = NULL;
	m_dataO = NULL;
	m_dataQualityO = NULL;
	m_dataI = NULL;
	m_dataQualityI = NULL;

	m_nURLType = 0;
	m_nPort = 0;
	memset(m_chAddress, 0,sizeof(m_chAddress));
	m_bEnableAnonymou = false;
	m_bEnableUserPw = false;
}

COPCUAMaster::~COPCUAMaster()
{
	COPCUAMaster *pMaster = this;
	if (NULL != pMaster->m_pGrpTagBufLocal)
	{
		for (int i = 0; i < pMaster->m_iCSVGrpCnt; ++i)
		{
			sGROUPTAG* pchgBuf = (sGROUPTAG*)(*(pMaster->m_pGrpTagBufLocal + i));//获取到sGROUPTAG的指针地址
			if (0 != pchgBuf->iTagBuf)
			{
				delete[](intptr_t*)(pchgBuf->iTagBuf);
				//pchgBuf->pTagBuf = NULL;
			}
			if (0 != pchgBuf->iTagSlaveBuf)
			{
				delete[](intptr_t*)(pchgBuf->iTagSlaveBuf);
			}
			delete[] pchgBuf;
		}
		delete[] pMaster->m_pGrpTagBufLocal;
		pMaster->m_pGrpTagBufLocal = NULL;
	}

	for(int i=0;i<m_OPCSlaveArray.GetSize();i++)
	{
		COPCUASlave*pOPCSalve = (COPCUASlave*)m_OPCSlaveArray.GetAt(i);
		if (pOPCSalve)
		{
			delete pOPCSalve;
			pOPCSalve = NULL;
		}
		
	}
	if(m_dataO) delete m_dataO;m_dataO=0;
	if(m_dataQualityO) delete m_dataQualityO;m_dataQualityO=0;
	if(m_dataI) delete m_dataI;m_dataI=0;
	if(m_dataQualityI) delete m_dataQualityI;m_dataQualityI=0;

	for(int i=0;i<(int)m_tagNumerO;i++)
	{
		COPCUATag *pOPCTag = m_OPCTagO[i];
		CTag *pTag = pOPCTag->m_pTag;
		delete pOPCTag;
		delete pTag;
	}
	for(int i=0;i<(int)m_tagNumerI;i++)
	{
		COPCUATag *pOPCTag = m_OPCTagI[i];
		CTag *pTag = pOPCTag->m_pTag;
		delete pOPCTag;
		delete pTag;
	}

	if (NULL != m_pOPCFrame)
	{
		delete m_pOPCFrame;
		m_pOPCFrame = NULL;
	}
}

void COPCUAMaster::PollSlave()
{//轮训各个OPC从站。
	const int MAX_COUNTER =5;
	static int k=0;
	if((k++%10)==0)
	{//每10次轮训周期，轮训一个故障模块。
		int totalErrStaion = 0;
		static DWORD query = 0;
		for(int i=0;i<m_OPCSlaveArray.GetSize();i++)
		{
			COPCUASlave*pOPCSalve = (COPCUASlave*)m_OPCSlaveArray.GetAt(i);
			if(pOPCSalve->m_stateCounter>MAX_COUNTER)
				totalErrStaion++;
		}
		if(totalErrStaion>0)
		{
			query = (query+1)%totalErrStaion;
			DWORD index=0;
			for(int i=0;i<m_OPCSlaveArray.GetSize();i++)
			{
				COPCUASlave*pOPCSalve = (COPCUASlave*)m_OPCSlaveArray.GetAt(i);
				if(pOPCSalve->m_stateCounter>MAX_COUNTER)
				{
					if(index==query)
						pOPCSalve->m_stateCounter = MAX_COUNTER;
					index++;
				}
			}
		}			
	}
	bool bisAllGrpOK = false;
	int iGSize = m_OPCSlaveArray.GetSize();
	if (iGSize == 0)
	{
		bisAllGrpOK = true;
	}
	for(int i=0;i<m_OPCSlaveArray.GetSize();i++)
	{//这儿是 真正主循环。每10次循环含一个fault站的轮训，所以，cycledelay每10次会有一怕多出60ms
		COPCUASlave*pOPCSalve = (COPCUASlave*)m_OPCSlaveArray.GetAt(i);
		if(pOPCSalve->m_stateCounter<=MAX_COUNTER )
		{
			pOPCSalve->StateMachineRun();
		}

		if(pOPCSalve->m_state != STATE_OK)
		{
			pOPCSalve->m_stateCounter++;
		}
		else
		{
			bisAllGrpOK = true;
			pOPCSalve->m_stateCounter = 0;
		}
	}
	if (!bisAllGrpOK)
	{
		m_iDevStatus = DEVSTATUS_ALLERR;
	}
	else
	{
		m_iDevStatus = DEVSTATUS_ALLOK;
	}

}

//******************************************************************
// Description	    : //线程主循环（是可以重载的虚函数）
//
// Argument         : 
// Return type		: 
//******************************************************************

extern CGTIODriverOPCUAServerApp theApp;

//void COPCMaster::Run()
//{
//	::SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_NORMAL);
//
//	//判断一下是否真“线程退出”。
//	DWORD lastTick =GetTickCount();
//	while(m_exitFlag != FLAG_STOPING)
//	{
//		int lastTick = GetTickCount();
//
//		//2014.5.10，从IOSver不做收发数据，沉默状态
//		if(m_isMaster())
//		{//数据交换
//			//for(int i=0;i<6;i++)
//			int tt=GetTickCount();
//				//PollSlave();
//			int tokenDelay = abs((int)GetTickCount()-tt);
//			m_cycleDelay = tokenDelay;
//			int sleepTick = m_cc-tokenDelay;
//
//			if(sleepTick>0)//实时优先级线程，给别人运行的时间，万一死循环，也好有机会调试它。
//				SleepEx(sleepTick,TRUE);//这个sleepEx非常准确，1000次1ms，累计是999个tick，不差分毫。
//			else
//				Sleep(10);
//		}else
//			Sleep(100);
//	
//		m_cycleCounter++;
//		//m_cycleDelay=GetTickCount()-lastTick;//在现场，从IOSvr看这个delay就知道是否正常
//											//2014.5.10实测，10个从站，COM转485，19200bps，一圈156ms左右。9600时，加倍300ms左右
//											//2014.5.23实测，FT232RL USB转485,500000bps，30个FM，一圈78ms。每站2.5ms
//	}
//
//}
 
//opc相关
//#include "Callback.h"   // 把CALLBACK放到OPCSERVER.DLL驱动中去实现，ioserver只完成注册功能

int g_pcNum;
#include "MyCSVPaser.h"
#include "common.h"
static CCommon g_common;
#include "gtutil.h"
bool g_bOk1=FALSE;//key相关
bool COPCUAMaster::ReadCSV()
{
	CIODriverManager *pCIODriverManager = (CIODriverManager*)m_handle;
	bool bRet = true;
	char *fileBuffer;
	char szTempCH[1024] = { 0 };
	char szTempEN[1024] = { 0 };
	string cmdLine = m_cmdLine;//主："Group1,Project01,run1,PC02,ControlSoftware02,ControlSoftware,控制运算软件[主],5000,200,"
	int pos1 = cmdLine.find(".exe\"");					   //从："Group1,Project01,run1,PC02,ControlSoftwareSlave02,ControlSoftwareSlave,控制运算软件[备用],5500,ControlSoftware01,"
	if (pos1 != string::npos)//vc调试cmdline
	{
		int rightnum = cmdLine.length() - pos1 - 6;
		cmdLine = GetRightLastCount(cmdLine, rightnum);//把VC直接调试时的命令行参数中的进程路径过滤掉。
	}

	//2014.5.10
	pos1 = cmdLine.find(".exe");
	if (pos1 != string::npos)//vc调试cmdline
	{
		int rightnum = cmdLine.length() - pos1 - 6;
		cmdLine = GetRightLastCount(cmdLine, rightnum);//CMD START 启动时的gtxxx.exe过滤掉。留纯cmdline
	}

	cmdLine = DealTrimFromLeft(cmdLine, "\t ,");

	string groupIDName = GetLeftFirst(cmdLine, ',');//Group1

	cmdLine = GetRight(cmdLine, ',');//Project01,run1,PC02,ModbusMaster02,ModbusMaster,Modbus主站软件,1,9600,COM1,
	string projectIDName = GetLeftFirst(cmdLine, ',');//Project01

	cmdLine = GetRight(cmdLine, ',');//          run1,PC02,ModbusMaster02,ModbusMaster,Modbus主站软件,1,9600,COM1,
	string projectName = GetLeftFirst(cmdLine, ',');//run1

	cmdLine = GetRight(cmdLine, ',');//				  PC02,ModbusMaster02,ModbusMaster,Modbus主站软件,1,9600,COM1,
	string pcIDName = GetLeftFirst(cmdLine, ',');//PC02

	cmdLine = GetRight(cmdLine, ',');//				  PC02,ModbusMaster02,ModbusMaster,Modbus主站软件,1,9600,COM1,
	string serverIDName = GetLeftFirst(cmdLine, ',');//2015.12.31 IOSoftware1

	cmdLine = GetRight(cmdLine, ',');//					   ModbusMaster02,ModbusMaster,Modbus主站软件,1,9600,COM1,
	string taskIDName = GetLeftFirst(cmdLine, ',');//ModbusMaster02

	string slavePortOffset = "";
	{//2014.5.10支持同一PC机，调试主、从IOSvr，分开串口，从IOSvr会多一个参数。
		cmdLine = GetRight(cmdLine, ',');//	ModbusMaster,Modbus主站软件,1,9600,COM1,1,
		cmdLine = GetRight(cmdLine, ',');//	Modbus主站软件,1,9600,COM1,1,
		cmdLine = GetRight(cmdLine, ',');//	1,9600,COM1,1,
		cmdLine = GetRight(cmdLine, ',');//	9600,COM1,1,
		cmdLine = GetRight(cmdLine, ',');//	COM1,1,
		cmdLine = GetRight(cmdLine, ',');//	1,
		cmdLine = GetRight(cmdLine, ',');//	1,
		slavePortOffset = GetLeftFirst(cmdLine, ',');//"1";
	}

	string filePath = GetProjectPath();//..\gtplus\bin\gtplus.exe

#ifdef _WINDOWS
	filePath = GetLeftLast(filePath, '\\');
	filePath = GetLeftLast(filePath, '\\');
	filePath += "\\Runtime\\";
	filePath += groupIDName + "\\";
	filePath += projectName + "\\";
#else
	filePath = GetLeftLast(filePath, '/');
	filePath = GetLeftLast(filePath, '/');
	filePath += "/Runtime/";
	filePath += groupIDName + "/";
	filePath += projectName + "/";
#endif

	{//2014.5.11，支持每个驱动预加载Lua脚本，用于函数定义、全局变量初始化
#ifdef _WINDOWS
		string fileNameStr = filePath + "\\Common\\IO.ST";//runtime\group32\projectaaa\Common\IO.ST 
#else
		string fileNameStr = filePath + "/Common/IO.ST";//runtime\group32\projectaaa\Common\IO.ST
#endif

		CGTUtil gtUtil;
		FILE* file = CGTUtil::OpenFileEx(fileNameStr);	//! 只读和在这个文件读写处理之外打开这个文件
		if (NULL != file)
		{
			//! 读取文件长度
			int len = GetFileLength(file);

			char *script = new char[len + 1];
			script[len] = 0;
			fread(script, 1, len, file);

			fclose(file);
			m_luaRuntime.ExecuteScriptString(script, 0);
			delete script;
		}
	}

#ifdef _WINDOWS
	string t = serverIDName + "\\";
#else
	string t = serverIDName + "/";
#endif

	{
		string fileNameStr = filePath + t + taskIDName + ".CSV";//runtime\group32\projectaaa\DPMaster02_CHS.csv

		CGTUtil gtUtil;
		FILE* file = CGTUtil::OpenFileEx(fileNameStr);	//! 只读和在这个文件读写处理之外打开这个文件
		if (NULL == file)
		{
			gtUtil.ProcessErrorMessage(fileNameStr.c_str());
			sprintf(szTempCH, "打开文件%s失败", fileNameStr.c_str());
			sprintf(szTempEN, "open file %s failed", fileNameStr.c_str());
			m_pSetLogInfo(m_handle, INFOTYPE_ERR, "IOServer", szTempCH, szTempEN, true, false);
			return false;
		}

		//! 读取文件长度
		int len = GetFileLength(file);

		fileBuffer = new char[len + 1];
		fileBuffer[len] = 0;
		fread(fileBuffer, 1, len, file);
		fclose(file);

		if (0 == len)
		{
			delete fileBuffer;
			sprintf(szTempCH, "文件%s为空，非法", fileNameStr.c_str());
			sprintf(szTempEN, "File %s is empty and Unreasonable.", fileNameStr.c_str());
			m_pSetLogInfo(m_handle, INFOTYPE_ERR, "IOServer", szTempCH, szTempEN, true, false);
			return false;
		}
	}
	/*
/*
,,,,OPCMaster01,OPCMaster,OPC主站软件,10000,Driver={SQL Server};Server=127.0.0.1\\SQLEXPRESS;DataBase=TestDB2;Uid=sa;Pwd=sa;,
,,,,,GroupYModeRead0001,GroupYModeRead,UnKnown,_T("CREATE TABLE GTTABLE (TagName varchar(12) not null PRIMARY KEY,TagValue NUMBER)"),
,,,,,,DDBTag002F,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
,,,,,,DDBTag0030,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
,,,,,GroupYModeWrite0001,GroupYModeWrite,UnKnown,_T("CREATE TABLE GTTABLE (TagName varchar(12) not null PRIMARY KEY,TagValue NUMBER)"),
,,,,,,DDBTag0031,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
,,,,,,DDBTag0032,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
,,,,,GroupXModeWrite0001,GroupXModeWrite,UnKnown,10000,_T("CREATE TABLE GTTABLE (ID number,Time timestamp,TagName NUMBER)"),
,,,,,,DDBTag0033,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
,,,,,,DDBTag0034,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
 */
	bool  bHaveAEFromDirver = false;
	{//process
		CMyCSVPaser csvPaser;
		char *pMem = fileBuffer;
		char *pLine = 0;
		csvPaser.GetItem(taskIDName, pMem, pLine);//csvPaser.GetModbusMasterMem(g_instanceNum+1,pMem,pLine);
		{//主站自身参数
			{//trim  left
				string s = pLine;
				s = DealTrimFromLeft(s, "\t ,");
				strcpy(pLine, s.c_str());
			}
			char*newToken = 0;
			char type[256];
			newToken = g_common.nextTokenIO(pLine); ; pLine = newToken;//OPCMaster01
			newToken = g_common.nextTokenIO(pLine); sscanf(pLine, "%s", type); pLine = newToken;//OPCMaster
			newToken = g_common.nextTokenIO(pLine); sprintf(m_log_Source, "%s", pLine); pLine = newToken;//OPC主站软件1 别名
			newToken = g_common.nextTokenIO(pLine);								 pLine = newToken;//OPC主站软件
			newToken = g_common.nextTokenIO(pLine);								 pLine = newToken;//是否启用
			newToken = g_common.nextTokenIO(pLine); sscanf(pLine, "%d", &m_cc); pLine = newToken;//10000
			newToken = g_common.nextTokenIO(pLine); sscanf(pLine, "%d", &m_nURLType); pLine = newToken;//URL类型
			newToken = g_common.nextTokenIO(pLine); sprintf(m_chAddress, "%s", pLine); pLine = newToken;//127.0.0.1
			newToken = g_common.nextTokenIO(pLine); sscanf(pLine, "%d", &m_nPort); pLine = newToken;//
		
			int nTemp = 0;
			newToken = g_common.nextTokenIO(pLine); sscanf(pLine, "%d", &nTemp); pLine = newToken;
			if (nTemp)
			{
				m_bEnableAnonymou = true;
			}
			newToken = g_common.nextTokenIO(pLine); sscanf(pLine, "%d", &nTemp); pLine = newToken;
			if (nTemp)
			{
				m_bEnableUserPw = true;
			}
			newToken = g_common.nextTokenIO(pLine); sprintf(m_chUser, "%s", pLine); pLine = newToken;
			newToken = g_common.nextTokenIO(pLine); sprintf(m_chPassWord, "%s", pLine); pLine = newToken;

			newToken = g_common.nextTokenIO(pLine); sscanf(pLine, "%d", &m_nDisplayNameType); pLine = newToken;//

		}
		{//从站参数
			int offsetI = 0;//bit 为单位.
			int offsetO = 0;//bit 为单位.

			string frameType;//OPCReadDO	OPCReadDI	OPCReadAO	OPCReadAI	OPCWriteDO	OPCWriteAO
			string wstrFrameType;
			int i = 0;
			m_iCSVGrpCnt = 0;
			while (csvPaser.GetNextOPCUAFrame(wstrFrameType, pMem, pLine))

			{
				string sline = pLine;
				string sMem = pMem;
				{//从站参数
					COPCUASlave* pOPCSlave = new COPCUASlave();
					m_OPCSlaveArray.Append((const char*)pOPCSlave);
					++m_iCSVGrpCnt;
					pOPCSlave->m_pOPCMaster = this;
					pOPCSlave->m_index = i;
					bool bTemp = pOPCSlave->ReadCSV(pMem, pLine);
					if (!bTemp)
					{
						bRet = bTemp;
					}
					pOPCSlave->m_offsetI = offsetI;
					pOPCSlave->m_offsetO = offsetO;
					offsetI += 8 * (pOPCSlave->m_slaveDataSizeI == 0 ? 0 : (pOPCSlave->m_slaveDataSizeI - 1) / 8 + 1);
					offsetO += 8 * (pOPCSlave->m_slaveDataSizeO == 0 ? 0 : (pOPCSlave->m_slaveDataSizeO - 1) / 8 + 1);
					i++;

					pCIODriverManager->m_ReadCSVAddTagNum += pOPCSlave->m_tagNumer;

					if (pOPCSlave->m_bWirteAndRead)
					{
						char *pLineWrite, *pLineWriteDelete;
						char *pMemWrite, *pMemWriteDelete;
						sline = DealTrimFromLeft(sline, "\t ,");
						sline = "write" + sline;

						pLineWriteDelete = pLineWrite = new char[sline.length() + 1];
						strcpy(pLineWrite, sline.c_str());

						pMemWriteDelete = pMemWrite = new char[sMem.length() + 1];
						strcpy(pMemWrite, sMem.c_str());


						COPCUASlave* pGroupSlave = new COPCUASlave();
						pGroupSlave->m_index = i++;
						pGroupSlave->m_pGroupSlave = pOPCSlave;//读组的配对组
						pOPCSlave->m_pGroupSlave = pGroupSlave;

						m_OPCSlaveArray.Append((const char*)pGroupSlave);

						pGroupSlave->m_pOPCMaster = this;
						pGroupSlave->ReadCSV(pMemWrite, pLineWrite, TRUE);
						pGroupSlave->m_bWirteAndRead = true;
						pGroupSlave->m_offsetI = offsetI;
						pGroupSlave->m_offsetO = offsetO;
						offsetI += 8 * (pGroupSlave->m_slaveDataSizeI == 0 ? 0 : (pGroupSlave->m_slaveDataSizeI - 1) / 8 + 1);
						offsetO += 8 * (pGroupSlave->m_slaveDataSizeO == 0 ? 0 : (pGroupSlave->m_slaveDataSizeO - 1) / 8 + 1);
						delete pLineWriteDelete;
						delete pMemWriteDelete;
					}
				}
			}

			m_dataLengthI = offsetI;
			m_dataLengthO = offsetO;
		}

		if (m_dataLengthI > 0)
		{
			m_dataI = new char[(m_dataLengthI - 1) / 8 + 1]; memset(m_dataI, 0, (m_dataLengthI - 1) / 8 + 1);
			m_dataQualityI = new char[m_tagNumerI]; memset(m_dataQualityI, 0, m_tagNumerI);  //一个标签一个byte品质位
		}
		if (m_dataLengthO > 0)
		{
			m_dataO = new char[(m_dataLengthO - 1) / 8 + 1]; memset(m_dataO, 0, (m_dataLengthO - 1) / 8 + 1);
			m_dataQualityO = new char[m_tagNumerO]; memset(m_dataQualityO, 0, m_tagNumerO);  //一个标签一个byte品质位
		}
		for (int i = 0; i < m_OPCSlaveArray.GetSize(); i++)
		{
			COPCUASlave*pOPCSlave = (COPCUASlave*)m_OPCSlaveArray.GetAt(i);
			if (pOPCSlave->m_bChangeModity && (0 != pOPCSlave->m_slaveDataSizeI))
			{
				for (int j = 0; j < pOPCSlave->m_tagNumer; j++)
					m_dataQualityI[pOPCSlave->m_MasterTagFristIndexI + j] |= TAG_IO_TAGQUALITY_CHANGE_MODE;
			}

			else if (pOPCSlave->m_bChangeModity && (0 != pOPCSlave->m_slaveDataSizeO))
			{
				for (int j = 0; j < pOPCSlave->m_tagNumer; j++)
					m_dataQualityO[pOPCSlave->m_MasterTagFristIndexO + j] |= TAG_IO_TAGQUALITY_CHANGE_MODE;
			}

			if (AEFromDriver == pOPCSlave->m_OPCGroupType)
			{
				bHaveAEFromDirver = true;
			}
		}




		////begin add by lixiaoming 
		//HINSTANCE hDcomDll = AfxLoadLibrary(_T("OPCDAServer.dll"));
		//if (hDcomDll)
		//{
		//	typedef BOOL(*pfSetTagData)(CRootBase*);
		//	pfSetTagData funSetTagData = (pfSetTagData)GetProcAddress(hDcomDll, "SetOpcData");
		//	if (funSetTagData != NULL)
		//	{
		//		m_iDevStatus = DEVSTATUS_ALLOK;
		//		//funSetTagData(m_pRoot);
		//	}
		//	else
		//	{
		//		m_iDevStatus = DEVSTATUS_ALLERR;
		//	}
		//}
		//else
		//{
		//	char szTempCH[1024] = { 0 };
		//	char szTempEN[1024] = { 0 };
		//	sprintf(szTempCH, "加载OPC Server通信组件失败。");
		//	sprintf(szTempEN, "Failure to load OPC Server communication component.");
		//	m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, false);
		//	return false;
		//}
		////end
	}

	{//Key相关
		char objName[200];memset(objName,0,sizeof(objName));
		objName[0]='G';
		objName[1]='T';
		objName[2]='I';
		objName[3]='O';
		objName[4]='D';
		objName[5]='r';
		objName[6]='i';
		objName[7]='v';
		objName[8]='e';
		objName[9]='r';
		objName[10]='O';
		objName[11]='P';
		objName[12]='C';
		objName[13]='S';
		objName[14]='e';
		objName[15]='r';
		objName[16]='v';
		objName[17]='e';
		objName[18]='r';
	
		//g_bOk1 = verifyKey(objName);
		//g_bOk1 = ReadAccess("OPCServer");todo
		//g_bOk2 = ReadINIFlag();//留到8小时后
	}



	if (0 == m_tagNumerO && 0 == m_tagNumerI && (!bHaveAEFromDirver))
	{
		//m_iDevStatus = 1;
		//m_RegTagList(m_handle);
		if (NULL != fileBuffer)
		{
			delete fileBuffer;
		}
		return true;
	}


	sprintf(szTempCH, "通信驱动初始化完成。");
	sprintf(szTempEN, "Communication Driver Initialization Completed.");
	m_pSetLogInfo(m_handle, INFOTYPE_RUN, m_log_Source, szTempCH, szTempEN, true, true);

	delete fileBuffer;



	string ServerConfigfileNameStr = filePath + t + taskIDName + "_ServerConfig.xml";
	this->OPCUAServerStart(ServerConfigfileNameStr);

	return bRet;
}
#include "GEInterface.h"
//extern CGEInterface *g_pCGEInterface;//2014.5.11这儿的g_pCGEInterface，
									//与AddIn中的不一样，AddIn中的被统一修改成指向App的g_pCGEInterface.
									//这儿的是各个DLL保持自己的g_pCGEInterface位置。正好各个driver相互隔离

#include "mystdafx.h"

bool COPCUAMaster::Init(void *handle, void *&driverContext, char *cmdLine, fpAddTag AddTag)
{
	driverContext = this;
	m_cmdLine = cmdLine;
	m_handle = handle;
	m_AddTag = AddTag;

	return ReadCSV();
}
static int autoInc=0;

	//1-StartFSServer,在IOServer.exe的void CIODriverManager::EventProcessThread()调用
	//2-pShellCallback->m_root.AddBranch( pBranch );pBranch->AddTag( pTag );
	//3-SetCallbackObject( pShellCallback );
extern CGTIODriverOPCUAServerApp theApp;//KEY相关



int COPCUAMaster::Input(void *handle)
{
	if(m_autosimulateAutoInc)
		autoInc++;
	//read data from DataI to tags
	int offset=0;
	
	char *IOMem = NULL;//对应OPC从站选好的module一个挨一个，不含Ctag的质量位
	char *IOQualityTemp = NULL;
	int iMallocLen = (m_dataLengthI - 1) / 8 + 1;
	char *IOQuality = m_dataQualityI;//对应Ctag的质量位
	if (m_dataLengthI > 0)
	{
		IOMem = new char[iMallocLen];
		memset(IOMem, 0, iMallocLen);
		IOQualityTemp = new char[m_tagNumerI];
		memset(IOQualityTemp, 0, m_tagNumerI);
		EnterCriticalSection(&m_criticalIOMemAccess);
		memcpy(IOMem, m_dataI, iMallocLen);
		memcpy(IOQualityTemp, m_dataQualityI, m_tagNumerI);
		LeaveCriticalSection(&m_criticalIOMemAccess);
	}


	CIODriverManager *pCIODriverManager = (CIODriverManager*)handle;
	//m_bSlaveServerEnable = pCIODriverManager->m_bSlaveServerEnable;
	bool RWRDBFailed = pCIODriverManager->m_RWRDBFailed;
#if OPCUA_DIAG_LOG
	{
		static DWORD s_entryTick = 0;
		static bool s_entryFirst = true;
		static unsigned int s_entryCalls = 0;
		s_entryCalls++;
		if (OpcUaDiagDue(s_entryTick, s_entryFirst))
		{
			char szDiag[512];
			sprintf(szDiag, "[DIAG Input-entry] calls=%u, tagNumerI=%u, RWRDBFailed=%d",
				s_entryCalls, m_tagNumerI, RWRDBFailed ? 1 : 0);
			m_pSetLogInfo(m_handle, INFOTYPE_RUN, m_log_Source, szDiag, szDiag, true, true);
		}
	}
#endif
	unsigned int nWriteDDBIndex = pCIODriverManager->m_nWriteDDBIndex;
	for(int i=0;i<(int)m_tagNumerI;i++)
	{
		COPCUATag *pOPCTag = m_OPCTagI[i];
		CTag*pTag = pOPCTag->m_pTag;

//第一步，读数据位，执行 转换公式脚本，脚本可能会根据数据置质量位无效
		{//
			//从Hex读数据到double变量
			double value=0;
			char strValue[MAX_TAGSTRINGVALUE_LEN] = { 0 };
			if (pTag->type == DT_STRING)
			{
				pTag->ReadTagHex(IOMem + pOPCTag->m_offset / 8, strValue);//用type_hex，
			}
			else
			{
				pTag->ReadTagHex(IOMem + pOPCTag->m_offset / 8, value, pOPCTag->m_offset % 8);//用type_hex，
				//memcpy(strValue, (char*)&value, sizeof(double));
			}
			

//第二步，根据通讯置质量位，
			unsigned int quality = WRITEONETAG_TAGQUALITY_IOSERVERWRITE;
			//begin add by lixiaoming 先读后写的更新品质位第10位（下标从0开始）,为1
			COPCUASlave*pOPCSalve = (COPCUASlave*)m_OPCSlaveArray.GetAt(pOPCTag->m_index);
			if (!pOPCSalve->m_bWirteAndRead || pOPCSalve->m_bReadFisrt)//先读后写
			{
				quality |= WRITEONETAG_TAGQUALITY_TWOWAYFLAG;
			}
			if ((IOQualityTemp[i] & TAG_IO_TAGQUALITY_IN_OK) && pTag->m_bAuthorizationFlag)             //设备输入品质GOOD
			{
				quality |= WRITEONETAG_TAGQUALITY_OK;

				if ((IOQualityTemp[i] & TAG_IO_TAGQUALITY_CHANGE_MODE))//变化传值模式
				{
					if (RWRDBFailed && pOPCTag->m_pOpcSlave->m_bReadFisrt && pOPCTag->m_pOpcSlave->m_bWirteAndRead)
					{
						pOPCTag->m_ForceUpdateRDBbyValue = true;
					}
					if (pTag->type == DT_STRING)
					{
						if (0 == pOPCTag->m_strValue.compare(strValue) && (!pOPCTag->m_ForceUpdateRDBbyValue))
						{
							if (!pOPCTag->m_pOpcSlave->m_bWirteAndRead) //只读组的变化写值
							{
								if (nWriteDDBIndex - pOPCTag->m_nTagWriteDDBIndex <= 1)
								{
									IOQualityTemp[i] |= TAG_IO_TAGQUALITY_HAVE_CHANGED;   //标记有变化标签
								}
								else
								{
									quality |= WRITEONETAG_TAGQUALITY_CHANGEDMODIFY;  //为1时实数库不赋值
								}
							}
							else
							{
								quality |= WRITEONETAG_TAGQUALITY_CHANGEDMODIFY;  //为1时实数库不赋值
							}
						}
						else
						{
							IOQualityTemp[i] |= TAG_IO_TAGQUALITY_HAVE_CHANGED;   //标记有变化标签
	
							if (0 != pOPCTag->m_strValue.compare(strValue) || RWRDBFailed)
							{
								pOPCTag->m_nTagWriteDDBIndex = nWriteDDBIndex;
							}
						}
					}
					else
					{
						if (value == pOPCTag->m_dbValue && (!pOPCTag->m_ForceUpdateRDBbyValue))
						{
							if (!pOPCTag->m_pOpcSlave->m_bWirteAndRead) //只读组的变化写值
							{
								if (nWriteDDBIndex - pOPCTag->m_nTagWriteDDBIndex <= 1)
								{
									IOQualityTemp[i] |= TAG_IO_TAGQUALITY_HAVE_CHANGED;   //标记有变化标签
								}
								else
								{
									quality |= WRITEONETAG_TAGQUALITY_CHANGEDMODIFY;  //为1时实数库不赋值
								}
							}
							else
							{
								quality |= WRITEONETAG_TAGQUALITY_CHANGEDMODIFY;  //为1时实数库不赋值
							}
						}
						else
						{
							IOQualityTemp[i] |= TAG_IO_TAGQUALITY_HAVE_CHANGED;   //标记有变化标签
							if (value != pOPCTag->m_dbValue || RWRDBFailed)
							{
								pOPCTag->m_nTagWriteDDBIndex = nWriteDDBIndex;
							}
						}
					}
				}
			}
			else
			{
				quality &= ~WRITEONETAG_TAGQUALITY_OK;
				quality &= ~WRITEONETAG_TAGQUALITY_TWOWAYFLAG;
				quality |= WRITEONETAG_TAGQUALITY_CHANGEDMODIFY;  //为1时实数库不赋值
			}
			
			//end
			if (pOPCTag->rangeConvType != 0)
			{
				value = ProtocolUtil::RangeConvertRawToEng(pOPCTag->rangeConvType, value, pOPCTag->m_dblRawLowLimit, pOPCTag->m_dblRawHighLimit, pOPCTag->m_dblEngLowLimit, pOPCTag->m_dblEngHighLimit);
			}
			else
			{
				if (strlen(pTag->m_lua) > 0 && strcmp(pTag->m_lua, "NULL") != 0 && pTag->type != DT_STRING)
				{//Lua脚本执行，将Hex数据转换成Eng数据
					char script[1024 * 10]; script[0] = 0;
					sprintf(script, "%s=%Lf\n%s\n return %s\n", pTag->name, value, pTag->m_lua, pTag->name);//赋tag初值, TP001 = 12  TP001=TP001*2/100 return TP001
					if (!m_luaRuntime.ExecuteScriptString(script, value, 0, 0, pTag->name))//返回值，直接赋给了value
						quality &= ~WRITEONETAG_TAGQUALITY_OK;//公式转换失败，等同质量坏，不更新DDB数据
				}
			}

			//CTag::WriteTag，把Eng数据写到内存中
			if (pTag->type == DT_STRING)
			{
				pTag->WriteTagToMem(strValue, quality);
			}
			else
			{
				pTag->WriteTagToMem(value, quality);//写到DDB的buf，type而不是type_hex，且bitOffset=0
			}
			
			offset+=pTag->size-1;//pTag->size含1byte的质量位			
		}

		offset++;//质量位
	}

	//call IOServer to send data to  DDB
//第三步，/一次性回写所有内存tag数据到DDB,【每个OPCMaster有独立的pIODriverManager->m_pTagManagerClientOut】
	bool bWriteToDDB = false;

	if (NULL != pCIODriverManager->m_pRDBDriverManage)
	{
		bWriteToDDB = pCIODriverManager->m_pRDBDriverManage->m_bWriteToDDB;
	}

	//if (m_pWriteToDDB(handle, 20))//一次性回写所有内存数据
	if (bWriteToDDB)
	{
		if (RWRDBFailed)
		{
			pCIODriverManager->m_RWRDBFailed = false;
		}
		
		EnterCriticalSection(&m_criticalIOMemAccess);
		for (int i = 0; i < (int)m_tagNumerI; i++)
		{
			if (IOQualityTemp[i] & TAG_IO_TAGQUALITY_IN_OK)  //因为一把写入，如果输入的品质是bad，不能认为写入实时库是成功的
			{
				IOQuality[i] |= TAG_IO_TAGQUALITY_OUT_OK;

				COPCUATag *pOPCTag = m_OPCTagI[i];
				CTag* pTag = pOPCTag->m_pTag;
				//pOPCTag->m_bHasReadOnce = true;
				if ((IOQualityTemp[i] & TAG_IO_TAGQUALITY_CHANGE_MODE) && IOQualityTemp[i] & TAG_IO_TAGQUALITY_HAVE_CHANGED)//有变化且写成功了就修改标签值
				{

					double value = 0;
					char strValue[MAX_TAGSTRINGVALUE_LEN] = { 0 };
					//pTag->ReadTagHex(IOMem+pM6Tag->m_offset/8,value,pM6Tag->m_offset%8);//用type_hex，
					if (pTag->type == DT_STRING)
					{
						pTag->ReadTagHex(IOMem + pOPCTag->m_offset / 8, strValue);//用type_hex，
						pOPCTag->m_strValue = strValue;
					}
					else
					{
						pTag->ReadTagHex(IOMem + pOPCTag->m_offset / 8, value, pOPCTag->m_offset % 8);//用type_hex，
						pOPCTag->m_dbValue = value;
					}

					//begin add by lixiaoming 同步数值给写组
					if (pOPCTag->m_pOpcSlave->m_bWirteAndRead)
					{
						
						COPCUATag *pOPCTagW = pOPCTag->m_pOpcSlave->m_pGroupSlave->m_OPCTagO[pOPCTag->m_TagIndexOfSlave];
						CTag* pTagW = pOPCTagW->m_pTag;
						char *IOMemW = m_dataO;
						if (pTagW->type == DT_STRING)
						{
							pTagW->WriteTagHex(IOMemW + pOPCTagW->m_offset / 8, strValue);
							pOPCTagW->m_strValue = strValue;
						}
						else
						{
							pTagW->WriteTagHex(IOMemW + pOPCTagW->m_offset / 8, value, pOPCTagW->m_offset % 8);//写MACSV6的buf，用type_hex，且offset bits非0
							pOPCTagW->m_dbValue = value;
						}


						pOPCTag->m_ForceUpdateRDBbyValue = true;
						pOPCTagW->m_ForceUpdateRDBbyValue = true;

					}
				}
			}
			else
			{
				IOQuality[i] &= ~TAG_IO_TAGQUALITY_OUT_OK;
			}
		}
		LeaveCriticalSection(&m_criticalIOMemAccess);
		if (IOMem != NULL)
		{
			delete[] IOMem;
			delete[] IOQualityTemp;
		}

		return 1;//succ++;
	}
	else
	{
		EnterCriticalSection(&m_criticalIOMemAccess);
		for (int i = 0; i < (int)m_tagNumerI; i++)
		{
			IOQuality[i] &= ~TAG_IO_TAGQUALITY_OUT_OK;
		}
		LeaveCriticalSection(&m_criticalIOMemAccess);
		if (IOMem != NULL)
		{
			delete[] IOMem;
			delete[] IOQualityTemp;
		}
		char szTempCH[1024] = { 0 };
		char szTempEN[1024] = { 0 };
		sprintf(szTempCH, "写入实时库失败。");
		sprintf(szTempEN, "Write RDB Failed.");
		m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, false);
		return 0;//fail++
	}
}

int COPCUAMaster::Output(void *handle)
{

	if(m_autosimulateAutoInc)
		autoInc++;
//第一步，一次全部读至内存m_bufFromDDB，【每个OPCMaster有独立的pIODriverManager->m_pTagManagerClientIn】
	bool bReadToDDB = false;
	CIODriverManager *pCIODriverManager = (CIODriverManager*)handle;
	if (NULL != pCIODriverManager->m_pRDBDriverManage)
	{
		bReadToDDB = pCIODriverManager->m_pRDBDriverManage->m_bReadToDDB;
	}
	unsigned int nWriteDDBIndex = pCIODriverManager->m_nWriteDDBIndex;
#if OPCUA_DIAG_LOG
	{
		// logged before any early return, to prove the host actually calls Output()
		static DWORD s_entryTick = 0;
		static bool s_entryFirst = true;
		static unsigned int s_entryCalls = 0;
		s_entryCalls++;
		if (OpcUaDiagDue(s_entryTick, s_entryFirst))
		{
			char szDiag[512];
			sprintf(szDiag, "[DIAG Output-entry] calls=%u, pRDBDriverManage=%p, bReadToDDB=%d, RWRDBFailed=%d, tagNumerO=%u",
				s_entryCalls, pCIODriverManager->m_pRDBDriverManage, bReadToDDB ? 1 : 0,
				pCIODriverManager->m_RWRDBFailed ? 1 : 0, m_tagNumerO);
			m_pSetLogInfo(m_handle, INFOTYPE_RUN, m_log_Source, szDiag, szDiag, true, true);
		}
	}
#endif
	if (!bReadToDDB)
	{		
		for (int i = 0; i < m_OPCSlaveArray.GetSize(); i++)
		{
			COPCUASlave *pOPCSalve = (COPCUASlave*)m_OPCSlaveArray.GetAt(i);
			if (pOPCSalve->m_slaveDataSizeO != 0) //写设备
			{
				for (int i = 0; i < (int)pOPCSalve->m_tagNumer; i++)  //读实时库失败了 先读后写的设备需要配对设备向实时库重新写值
				{
					m_dataQualityO[pOPCSalve->m_MasterTagFristIndexO + i] &= ~TAG_IO_TAGQUALITY_IN_OK;  //
					if (pOPCSalve->m_bReadFisrt & pOPCSalve->m_bWirteAndRead && NULL != pOPCSalve->m_pGroupSlave)
					{
						pOPCSalve->m_pGroupSlave->m_pOPCMaster->m_dataQualityI[pOPCSalve->m_pGroupSlave->m_MasterTagFristIndexI + i] &= ~TAG_IO_TAGQUALITY_OUT_OK;  //
					}
				}
			}
		}
		char szTempCH[1024] = { 0 };
		char szTempEN[1024] = { 0 };
		sprintf(szTempCH, "读取实时库失败。");
		sprintf(szTempEN, "Read RDB Failed.");
		m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, false);
		return 0;//fail++ 内部总是返回true，必须单独执行前面的memset语句，才能正确判质量位
	}
	//if(m_dataLengthO>0)
	//	memset(m_dataQualityO,0,(m_dataLengthO-1)/8+1);//设置成可以输出，方便下面处理：只要有一个tag无效，就不允许输出
//?应该改进，避免组态几个DO备用点导致模块输出不了。
	//write data to DataO
	//int offset=0;
	char *IOMem = m_dataO;
#if OPCUA_DIAG_LOG
	static DWORD s_diagTick = 0;
	static bool s_diagFirst = true;
	static unsigned int s_outputCalls = 0;
	s_outputCalls++;
	bool bDiag = OpcUaDiagDue(s_diagTick, s_diagFirst);
	int diagReached = 0, diagInOk = 0, diagQualityBad = 0, diagAuthFail = 0, diagDetail = 0;
	char diagLines[OPCUA_DIAG_TAG_DETAIL][512];
#endif
EnterCriticalSection(&m_criticalIOMemAccess);
char *IOQuality = m_dataQualityO;
	for(int i=0;i<(int)m_tagNumerO;i++)
	{
		COPCUATag *pOPCTag = m_OPCTagO[i];
		CTag*pTag = pOPCTag->m_pTag;
//第二步，把数据值进行公式转换，转换成OPC从站格式
//2014.5.3 支持Lua转换通讯点类型（如：OPC从模块，用byte表示一个bool）

		//CTag::ReadTag，从Hex读数据到double变量
		double value=0;unsigned int quality=0;
		char strValue[MAX_TAGSTRINGVALUE_LEN] = { 0 };
		if (pTag->type == DT_STRING)
		{
			pTag->ReadTagFromMem(strValue, quality, pTag->type);
		}
		else
		{
			pTag->ReadTagFromMem(value, quality, pTag->type);//CTagManagerCli内部会初始化清0，代表质量位为BAD，避免误使用未刷新的初始数据
		}

		if (pOPCTag->m_pOpcSlave->m_bWirteAndRead && pCIODriverManager->m_RWRDBFailed)
		{
			continue;
		}

		//读写点话就过滤一拍，修复合并写实时库模式下，从站写值引起给从站的写值的问题
		if (pOPCTag->m_ForceUpdateRDBbyValue)
		{
			COPCUATag *pOPCTagInput = this->m_OPCTagI[pOPCTag->m_pOpcSlave->m_pGroupSlave->m_MasterTagFristIndexI + pOPCTag->m_TagIndexOfSlave];
			if (pTag->type == DT_STRING)
			{
				if (0 != pOPCTag->m_strValue.compare(strValue))
				{
					if (pOPCTag->m_pOpcSlave->m_bWriteRDBValueCheck)
					{
						continue;
					}
					else
					{
						if (nWriteDDBIndex - pOPCTagInput->m_nTagWriteDDBIndex <= 1)
						{
							continue;
						}
					}
				}
				
				{					
					pOPCTag->m_ForceUpdateRDBbyValue = false;
					pOPCTagInput->m_ForceUpdateRDBbyValue = false;
				}
			}
			else if (pTag->type != DT_STRING)
			{
				COPCUATag *pOPCTagInput = m_OPCTagI[pOPCTag->m_pOpcSlave->m_pGroupSlave->m_MasterTagFristIndexI + pOPCTag->m_TagIndexOfSlave];
				double inputValue = 0;
				unsigned int inputquality = WRITEONETAG_TAGQUALITY_OK;
				pOPCTagInput->m_pTag->ReadTagFromMem(inputValue, inputquality, pOPCTagInput->m_pTag->type);
				if (value != inputValue)
				{
					if (pOPCTag->m_pOpcSlave->m_bWriteRDBValueCheck)
					{
						continue;
					}
					else
					{
						if (nWriteDDBIndex - pOPCTagInput->m_nTagWriteDDBIndex <= 1)
						{
							continue;
						}
					}
				}
				
				{					
					pOPCTag->m_ForceUpdateRDBbyValue = false;
					pOPCTagInput->m_ForceUpdateRDBbyValue = false;
				}
			}

		}


		if (pOPCTag->rangeConvType != 0)
		{
			double temp = pOPCTag->m_dbValue;
			temp = ProtocolUtil::RangeConvertRawToEng(pOPCTag->rangeConvType, temp, pOPCTag->m_dblRawLowLimit, pOPCTag->m_dblRawHighLimit, pOPCTag->m_dblEngLowLimit, pOPCTag->m_dblEngHighLimit);
			if (abs(temp - value) < 1e-6)
			{
				continue;
			}
			else
			{
				value = ProtocolUtil::RangeConvertEngToRaw(pOPCTag->rangeConvType, value, pOPCTag->m_dblRawLowLimit, pOPCTag->m_dblRawHighLimit, pOPCTag->m_dblEngLowLimit, pOPCTag->m_dblEngHighLimit);
			}
		}
		else
		{
			if (strlen(pTag->m_lua) > 0 && strcmp(pTag->m_lua, "NULL") != 0 && pTag->type != DT_STRING)
			{//Lua脚本执行，将Hex数据转换成Eng数据
				char script[1024 * 10]; script[0] = 0;
				sprintf(script, "%s=%Lf\n%s\n return %s\n", pTag->name, value, pTag->m_lua, pTag->name);//赋tag初值, TP001 = 12  TP001=TP001*2/100 return TP001
				if (!m_luaRuntime.ExecuteScriptString(script, value, 0, 0, pTag->name))//返回值，直接赋给了value
					quality &= ~WRITEONETAG_TAGQUALITY_OK;//公式转换失败，等同质量坏，不输出数据
			}
		}

		//第三步，质量位信息

		
		//pOPCTag->m_quality = quality;
		//if(m_autosimulatequalitybad)//仿真通讯坏，用于测试
		//	quality = WRITEONETAG_TAGQUALITY_BAD;
		//if(m_autosimulatequalityok)//仿真通讯好，用于测试
		//	quality = WRITEONETAG_TAGQUALITY_OK;
		//if(m_autosimulateAutoInc&& pTag->type != DT_STRING)
		//	value=value+autoInc;//仿真，启动DDB，自动增加值

			
		//offset+=pTag->size-1;//pTag->size含1byte的质量位			

//第三步，质量位信息
#if OPCUA_DIAG_LOG
		if (bDiag)
		{
			diagReached++;
			if (!(quality & WRITEONETAG_TAGQUALITY_OK)) diagQualityBad++;
			if (!pTag->m_bAuthorizationFlag) diagAuthFail++;
			if ((quality & WRITEONETAG_TAGQUALITY_OK) && pTag->m_bAuthorizationFlag) diagInOk++;
			if (diagDetail < OPCUA_DIAG_TAG_DETAIL)
			{
				_snprintf(diagLines[diagDetail], sizeof(diagLines[0]) - 1,
					"[DIAG Output] tag[%d] %s: rdbQuality=0x%X (OK=%d), auth=%d, value=%f, str=%s",
					i, pTag->name, quality, (quality & WRITEONETAG_TAGQUALITY_OK) ? 1 : 0,
					pTag->m_bAuthorizationFlag ? 1 : 0, value, strValue);
				diagLines[diagDetail][sizeof(diagLines[0]) - 1] = 0;
				diagDetail++;
			}
		}
#endif
		if ((quality&WRITEONETAG_TAGQUALITY_OK) && pTag->m_bAuthorizationFlag)
		{
			IOQuality[i] |= TAG_IO_TAGQUALITY_IN_OK;
			if (DT_STRING != pTag->type)
			{
				pTag->WriteTagHex(m_dataO + pOPCTag->m_offset / 8, value, pOPCTag->m_offset % 8);
			}
			else
			{
				pTag->WriteTagHex(m_dataO + pOPCTag->m_offset / 8, strValue);
			}
		}
		else
		{
			IOQuality[i] &= ~TAG_IO_TAGQUALITY_IN_OK;
		}
	}
LeaveCriticalSection(&m_criticalIOMemAccess);
#if OPCUA_DIAG_LOG
	if (bDiag)
	{
		// tags not "reached" were skipped by a continue (RW + RWRDBFailed, ForceUpdateRDBbyValue, range conversion unchanged)
		char szDiag[512];
		sprintf(szDiag, "[DIAG Output] calls=%u, tagNumerO=%u, reached=%d, IN_OK=%d, rdbQualityBad=%d, authFail=%d, RWRDBFailed=%d",
			s_outputCalls, m_tagNumerO, diagReached, diagInOk, diagQualityBad, diagAuthFail,
			pCIODriverManager->m_RWRDBFailed ? 1 : 0);
		m_pSetLogInfo(m_handle, INFOTYPE_RUN, m_log_Source, szDiag, szDiag, true, true);
		for (int d = 0; d < diagDetail; d++)
			m_pSetLogInfo(m_handle, INFOTYPE_RUN, m_log_Source, diagLines[d], diagLines[d], true, true);
	}
#endif
	return 1;//succ++
}


void COPCUAMaster::ReleaseFrame()
{
	if (NULL != m_pOPCFrame)
	{
		delete m_pOPCFrame;
		m_pOPCFrame = NULL;
	}
}


bool COPCUAMaster::OPCUAServerStart(string strServerConfigfileName)
{
	m_path = UaString(strServerConfigfileName.c_str());//修改配置文件
	if (!UaGatewayServer::initialize())
	{
		char szTempCH[1024] = { 0 };
		char szTempEN[1024] = { 0 };
		sprintf(szTempCH, "初始化gateway失败。");
		sprintf(szTempEN, "Fail to initialize gateway.");
		m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, true);
		return false;
	}

	m_nodeManager.m_OPCUAMasterHandele = this;

	//查找配置文件

	if (FILE *file = fopen(strServerConfigfileName.c_str(), "r")) 
	{
		fclose(file);

	}
	else 
	{
		string strsourceFile;
		char sfileName[MAX_PATH + 1];
		GetModuleFileNameA(NULL, sfileName, MAX_PATH);

		strsourceFile = sfileName;
		strsourceFile = strsourceFile.substr(0, strsourceFile.rfind('\\'));
		strsourceFile += "\\ConfigFile\\ServerConfig.xml";//..\gtplus\Runtime\  

		int nRet = CopyConfigFile(strsourceFile.c_str(), strServerConfigfileName.c_str());
		if (0 != nRet)
		{
			char szTempCH[1024] = { 0 };
			char szTempEN[1024] = { 0 };
			sprintf(szTempCH, "CopyConfigFile 失败 nRet=%d.", nRet);
			sprintf(szTempEN, "CopyConfigFile failed nRet=%d.", nRet);
			m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, true);
			return false;
		}
	}

	//修改文件信息
	//
	{
		UaXmlDocument * pXmlDoc = new UaXmlDocument;
		UaString sXmlFileName(strServerConfigfileName.c_str());
		int nRet = pXmlDoc->loadXmlFile((char*)sXmlFileName.toUtf8());
		if (0 != nRet)
		{
			char szTempCH[1024] = { 0 };
			char szTempEN[1024] = { 0 };
			sprintf(szTempCH, "loadXmlFile 失败 nRet=%d.", nRet);
			sprintf(szTempEN, "loadXmlFile failed nRet=%d.", nRet);
			m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, true);

			return false;
		}

		UaXmlElementList uaXmlElementList;
		if (0 == pXmlDoc->getChild("UaServerConfig"))
		{
			;
		}
		else
		{
			char szTempCH[1024] = { 0 };
			char szTempEN[1024] = { 0 };
			sprintf(szTempCH, "getChild(UaServerConfig) 失败 ");
			sprintf(szTempEN, "getChild(UaServerConfig) failed ");
			m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, true);
			pXmlDoc->freeXmlDocument();
			delete pXmlDoc;
			return false;
		}


		if (0 == pXmlDoc->getChild("UserIdentityTokens"))
		{
			if (0 == pXmlDoc->getChild("EnableAnonymous"))
			{
				UaXmlElement uaXmlElement;
				pXmlDoc->getCurrentElement(uaXmlElement);
				if (m_bEnableAnonymou)
				{
					uaXmlElement.setContent("true");
				}
				else
				{
					uaXmlElement.setContent("false");
				}
			}
			else
			{
				char szTempCH[1024] = { 0 };
				char szTempEN[1024] = { 0 };
				sprintf(szTempCH, "getChild(EnableAnonymous) 失败 ");
				sprintf(szTempEN, "getChild(EnableAnonymous) failed ");
				m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, true);
				pXmlDoc->freeXmlDocument();
				delete pXmlDoc;
				return false;
			}
			pXmlDoc->getParentNode();

			if (0 == pXmlDoc->getChild("EnableUserPw"))
			{
				UaXmlElement uaXmlElement;
				pXmlDoc->getCurrentElement(uaXmlElement);
				if (m_bEnableUserPw)
				{
					uaXmlElement.setContent("true");
				}
				else
				{
					uaXmlElement.setContent("false");
				}
				pXmlDoc->getParentNode();
			}
			else
			{
				char szTempCH[1024] = { 0 };
				char szTempEN[1024] = { 0 };
				sprintf(szTempCH, "getChild(EnableAnonymous) 失败 ");
				sprintf(szTempEN, "getChild(EnableAnonymous) failed ");
				m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, true);
				pXmlDoc->freeXmlDocument();
				delete pXmlDoc;
				return false;
			}
			pXmlDoc->getParentNode();
		}
		else
		{
			char szTempCH[1024] = { 0 };
			char szTempEN[1024] = { 0 };
			sprintf(szTempCH, "getChild(UserIdentityTokens) 失败 ");
			sprintf(szTempEN, "getChild(UserIdentityTokens) failed ");
			m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, true);
			pXmlDoc->freeXmlDocument();
			delete pXmlDoc;
			return false;
		}


		if (0 == pXmlDoc->getChildElements("UaEndpoint", uaXmlElementList))
		{
			UaXmlElementListIterator it;
			for (it = uaXmlElementList.begin(); it != uaXmlElementList.end(); ++it)
			{
				if (0 == (*it).getChild("Url"))
				{
					//(*it).setContent("Url");
					char chURL[MAX_PATH] = { 0 };
					if (URLType_IP == m_nURLType)
					{
						sprintf(chURL, "opc.tcp://%s:%d", m_chAddress, m_nPort);
					}
					else
					{
						sprintf(chURL, "opc.tcp://[NodeName]:%d", m_nPort);
						
					}
					(*it).setContent(chURL);

					(*it).getParentNode();
				}
				else
				{
					char szTempCH[1024] = { 0 };
					char szTempEN[1024] = { 0 };
					sprintf(szTempCH, "getChild(Url) 失败 ");
					sprintf(szTempEN, "getChild(Url) failed ");
					m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, true);
					pXmlDoc->freeXmlDocument();
					delete pXmlDoc;
					return false;
				}
			}
			pXmlDoc->getParentNode();
		}
		else
		{
			char szTempCH[1024] = { 0 };
			char szTempEN[1024] = { 0 };
			sprintf(szTempCH, "getChildElements(UaEndpoint) 失败 ");
			sprintf(szTempEN, "getChildElements(UaEndpoint) failed ");
			m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, true);
			pXmlDoc->freeXmlDocument();
			delete pXmlDoc;
			return false;
		}


		pXmlDoc->saveXmlFile((char*)sXmlFileName.toUtf8());
		pXmlDoc->freeXmlDocument();
		delete pXmlDoc;
	}

	m_callback.m_opcUAMaterHandle = this;

	UAServerRun();
	return true;
}

bool COPCUAMaster::OPCUAServerStop()
{

	m_server.stopServer();

	UaGatewayServer::finalize();
	return TRUE;
}

bool COPCUAMaster::UAServerRun()
{
	if (m_server.startServer(m_path, &m_nodeManager, &m_callback))
	{
		char szTempCH[1024] = { 0 };
		char szTempEN[1024] = { 0 };
		sprintf(szTempCH, "OPC UA Server  startServe 成功");
		sprintf(szTempEN, "OPC UA Server  startServer success ");
		m_pSetLogInfo(m_handle, INFOTYPE_RUN, m_log_Source, szTempCH, szTempEN, true, true);
		m_iDevStatus = DEVSTATUS_ALLOK;
		return false;
	}
	else
	{
		char szTempCH[1024] = { 0 };
		char szTempEN[1024] = { 0 };
		sprintf(szTempCH, "OPC UA Server  startServer 失败 ");
		sprintf(szTempEN, "OPC UA Server  startServer failed ");
		m_pSetLogInfo(m_handle, INFOTYPE_ERR, m_log_Source, szTempCH, szTempEN, true, true);
		m_server.stopServer();
		m_iDevStatus = DEVSTATUS_ALLERR;
		return true;
	}
}