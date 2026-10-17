// OPCSlave.cpp: implementation of the COPCSlave class.
//
//////////////////////////////////////////////////////////////////////
#include "mystdafx.h"
#include "OPCUASlave.h"
#include "OPCUAtag.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "common.h"
static CCommon g_common;
#include "OPCUAmaster.h"
#include "OPCUAframe.h"
#include "CommMath.h"
#include "CommString.h"
#include "TagManagerClient.h"
#include "IODriverManager.h"
#include "TagAttrHashInfo.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace
{
	template<typename T>
	T findTagAttribution(CIODriverManager *pCIODriverManager, CTag* pTag, const char *attrName)
	{
		TagAtrribition_EX* pTagAtrribition = NULL;
		if (pCIODriverManager == NULL || pCIODriverManager->tagAttrHashInfo == NULL || pTag == NULL)
		{
			return 0;
		}
		pTagAtrribition = (TagAtrribition_EX*)pCIODriverManager->tagAttrHashInfo->tagAttributeHash.Lookup(attrName);
		if (pTagAtrribition == NULL)
		{
			return 0;
		}
		T value = *(T*)(pTag->m_tagAttributeBuffer + pTagAtrribition->iOffset_Atrribition);
		return value;
	}
}

COPCUASlave::COPCUASlave()
{
	m_ID=0;
//	memset(m_tagNameStrStr,0,sizeof(m_tagNameStrStr));
	m_dataQuality = 0;//Bad
	m_stateCounter = 0;
	m_state = STATE_OK;
	m_successCounter = m_failureCounter = 0;
	m_tagNumer=0;
	m_OPCGroupType = 0xff;
	m_MasterTagFristIndexI = 0;
	m_MasterTagFristIndexO = 0;
	m_bWirteAndRead = false;     //读写
	m_bReadFisrt = false;		 //先读后写
	m_bChangeModity = false;      //如果是读写属性就只能是变化传值
	m_pGroupSlave = NULL;
	m_bStrictOut = false;
	m_bWriAndRedisWri = false;
	m_bWriteRDBValueCheck = true;
	memset(m_AESourceDriverName, 0,sizeof(m_AESourceDriverName));
}

COPCUASlave::~COPCUASlave()
{
	
}

#define MAX_FRAME_SIZE 1514
void COPCUASlave::StateMachineRun()
{

}

#include "MyCSVPaser.h"

bool COPCUASlave::ReadCSV(char*&pMem,char*pLine, bool bWriAndRedisWri)
{
/*
,,,,OPCMaster01,OPCMaster,OPC主站软件,10000,Driver={SQL Server};Server=127.0.0.1\\SQLEXPRESS;DataBase=TestDB2;Uid=sa;Pwd=sa;,
,,,,,GroupYModeRead0001,GroupYModeRead,UnKnown,_T("CREATE TABLE GTTABLE (TagName varchar(12) not null PRIMARY KEY,TagValue NUMBER)"),
,,,,,,DDBTag002F,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
,,,,,,DDBTag0030,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
,,,,,GroupYModeWrite0001,GroupYModeWrite,UnKnown,10000,_T("CREATE TABLE GTTABLE (TagName varchar(12) not null PRIMARY KEY,TagValue NUMBER)"),
,,,,,,DDBTag0031,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
,,,,,,DDBTag0032,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
,,,,,GroupXModeWrite0001,GroupXModeWrite,UnKnown,10000,_T("CREATE TABLE GTTABLE (ID number,Time timestamp,TagName NUMBER)"),
,,,,,,DDBTag0033,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
,,,,,,DDBTag0034,DDBTag,UnKnown,Local,DRDBSoftware01,IN,YES,HDBSoftware01,1,SINGLE,0,BWORD,Unknown,
 */
	CWcharAndChar mychar;
	{// 
		{//从站本身的参数。
		//trim  left
			{
				string s = pLine;//,OPCSlave0001,OPCSlave,FM161_DI,126,01 00 ,FF 03 00 00 ,00 12 ,
					//,OPCReadDO0001,OPCReadDO,UnKnown,1,2,0,
				s = DealTrimFromLeft(s, "\t ,");
				strcpy(pLine, s.c_str());
			}
	
			char*newToken =0;
			char type[256];
			DWORD ident =0;
			newToken = g_common.nextTokenIO(pLine); strcpy(m_grpName,pLine);pLine = newToken;//OPCReadDO0001
			//CString strGroupName = m_grpName;
			newToken = g_common.nextTokenIO(pLine); sscanf(pLine,"%s",type);pLine = newToken;//OPCReadDO AI AO DI ....
														string stype =type;
														if(stype == "UAServerToClient") m_OPCGroupType = OPC_GROUP_S2C;
														if(stype == "ClientToUAServer") m_OPCGroupType = OPC_GROUP_C2S;
														if(stype == "UAServerClientRW")
														{														
															m_OPCGroupType = OPC_GROUP_C2S;
															m_bWirteAndRead = true;
														}
														if (stype == "AEFromDriver")
														{
															m_OPCGroupType = AEFromDriver;
														}
			newToken = g_common.nextTokenIO(pLine); string t=pLine;if(t!="NULL") strcpy(m_grpName,pLine); pLine = newToken;//UnKnown  
			string strGroupName = m_grpName; //使用别名作为服务标签地址空间的组名
			int nTempPara;
			newToken = g_common.nextTokenIO(pLine); 
			pLine = newToken;
			newToken = g_common.nextTokenIO(pLine); //跳过启用字段
			pLine = newToken;

			if (AEFromDriver == m_OPCGroupType)
			{
				newToken = nextTokenIO(pLine);
				stype = pLine;
				pLine = newToken;//YES
				memcpy(m_AESourceDriverName, stype.c_str(), stype.length());
				
				return true;
			}
			newToken = nextTokenIO(pLine);
			sscanf(pLine, "%s", type);
			pLine = newToken;//YES
			stype = type;
			if (stype == "YES")
				m_bStrictOut = true;
			else
				m_bStrictOut = false;

			newToken = g_common.nextTokenIO(pLine);
			sscanf(pLine, "%d", &m_nNodeIDType);
			pLine = newToken;

			newToken = g_common.nextTokenIO(pLine);
			sscanf(pLine, "%d", &nTempPara);
			pLine = newToken;

			m_bChangeModity = nTempPara == CYCLE_MODITY ? false : true;
			pLine = newToken;//0,1  周期传值，变化传值
			if (m_bWirteAndRead)  //读写设备
			{
				newToken = g_common.nextTokenIO(pLine);
				sscanf(pLine, "%d", &nTempPara);
				pLine = newToken;//0,1  读写权限及第一次通信顺序
				m_bReadFisrt = nTempPara == READ_WRITE ? true : false;
				m_bChangeModity = m_bWirteAndRead ? true : m_bChangeModity;//读写属性必须变化传值

				if (m_bReadFisrt)
				{
					newToken = nextTokenIO(pLine);
					sscanf(pLine, "%d", &nTempPara);
					pLine = newToken;//0,1  读写权限及第一次通信顺序
					m_bWriteRDBValueCheck = nTempPara == 1 ? true : false;
				}
			}

			m_bWriAndRedisWri = bWriAndRedisWri;
			//newToken = g_common.nextTokenIO(pLine); pLine = newToken;//guest.TestTable2
			//newToken = g_common.nextTokenIO(pLine); pLine = newToken;//1
			if (bWriAndRedisWri)  //读写设备的写设备修改属性
			{
				m_OPCGroupType = m_OPCGroupType == OPC_GROUP_C2S ? OPC_GROUP_S2C : m_OPCGroupType;
			}
		}

		{//tag
			CMyCSVPaser csvPaser;
			char*pLine=0;
			m_slaveDataSizeI = m_slaveDataSizeO =0;//bits
			m_MasterTagFristIndexI = m_pOPCMaster->m_tagNumerI;
			m_MasterTagFristIndexO = m_pOPCMaster->m_tagNumerO;

			DWORD inLenParsed=0;//bits
			DWORD outLenParsed =0;//bits
			while(csvPaser.GetTagMem(0,pMem,pLine))
			{//read tag info
				{//trim  left
					string s = pLine;//,OPCSlave0001,OPCSlave,FM161_DI,126,01 00 ,FF 03 00 00 ,00 12 ,
										//,OPCReadDO0001,OPCReadDO,UnKnown,1,2,0,
					s = DealTrimFromLeft(s, "\t ,");
					strcpy(pLine, s.c_str());
				} 
				char*newToken =0;
				CTag *pTag = new CTag;
				CIODriverManager *pCIODriverManager = (CIODriverManager*)(m_pOPCMaster->m_handle);
				if (bWriAndRedisWri)
				{
					string s = pLine;
					s = "Write" + s;
					char *pLineTemp = new char[s.length() + 1];
					strcpy(pLineTemp, s.c_str());
					pTag->Parse(pLineTemp, pCIODriverManager->tagAttrHashInfo, true);
					delete pLineTemp;
				}
				else
				{
					pTag->Parse(pLine, pCIODriverManager->tagAttrHashInfo, true);
				}

				string attrName = "RS";
				int rangeConvertType = findTagAttribution<unsigned char>(pCIODriverManager, pTag, attrName.c_str());
				attrName = "PMU";
				double  m_dblEngHighLimit = findTagAttribution<float>(pCIODriverManager, pTag, attrName.c_str());
				attrName = "PMD";
				double m_dblEngLowLimit = findTagAttribution<float>(pCIODriverManager, pTag, attrName.c_str());
				attrName = "OMU";
				double m_dblRawHighLimit = findTagAttribution<float>(pCIODriverManager, pTag, attrName.c_str());
				attrName = "OMD";
				double m_dblRawLowLimit = findTagAttribution<float>(pCIODriverManager, pTag, attrName.c_str());

				pTag->LuaExplain(bWriAndRedisWri);
				if ((pTag->type != pTag->type_hex) && (pTag->type == DT_STRING || pTag->type_hex == DT_STRING))
				{
					char szTempCH[1024] = { 0 };
					char szTempEN[1024] = { 0 };
					sprintf(szTempCH, "STRING标签%s类型不匹配。", pTag->name);
					sprintf(szTempEN, "Tag %s type does not match.", pTag->name);
					m_pOPCMaster->m_pSetLogInfo(m_pOPCMaster->m_handle, INFOTYPE_ERR, m_pOPCMaster->m_log_Source, szTempCH, szTempEN, true, false);

					delete pTag;
					pTag = NULL;
					continue;
				}

				if(m_OPCGroupType == OPC_GROUP_C2S)
				{
					if (pTag->size_hex / 8 > 0 && 0 != inLenParsed % 8)
					{
						inLenParsed = (inLenParsed / 8 + 1) * 8;
					}
					pTag->ioType=IOTYPE_IN;//强制成IN,减少认为错误
					COPCUATag* pOPCTag =  new COPCUATag(pTag->name,m_pOPCMaster->m_tagOffsetI+inLenParsed,pTag->size_hex,pTag->type_hex,m_index,pTag,this);
					m_pOPCMaster->m_OPCTagI[m_pOPCMaster->m_tagNumerI] = pOPCTag;
					m_OPCTagI[m_tagNumer] = m_pOPCMaster->m_OPCTagI[m_pOPCMaster->m_tagNumerI] ;
					m_OPCTagI[m_tagNumer]->m_iTagIndex = m_pOPCMaster->m_tagNumerI;
					m_pOPCMaster->m_tagNumerI++;//总tag个数
					inLenParsed+=pTag->size_hex;
					//if (!m_pOPCMaster->m_AddTag(m_pOPCMaster->m_handle, pTag, bWriAndRedisWri))
					//{
					//	pTag->m_bAuthorizationFlag = false;
					//}
					//begin add by lixiaoming for opc da
					//SetBaseTagType(pTag->type, pOPCTag);
					//pOPCTag->m_strName = pTag->name;
					//if (m_bWirteAndRead)
					//{
					//	pOPCTag->m_nAccessRight = ACCESSRIGHT_READ_WRITE;
					//}
					//else
					//{
					//	pOPCTag->m_nAccessRight = ACCESSRIGHT_WRITE_ONLY;
					//}

					pOPCTag->rangeConvType = rangeConvertType;
					pOPCTag->m_dblEngHighLimit = m_dblEngHighLimit;
					pOPCTag->m_dblEngLowLimit = m_dblEngLowLimit;
					pOPCTag->m_dblRawHighLimit = m_dblRawHighLimit;
					pOPCTag->m_dblRawLowLimit = m_dblRawLowLimit;

					m_OPCTagI[m_tagNumer]->m_TagIndexOfSlave = m_tagNumer;
					m_tagNumer++;
				}else
				if(m_OPCGroupType == OPC_GROUP_S2C||m_OPCGroupType == OPC_GROUP_S2C)
				{
					if (pTag->size_hex / 8 > 0 && 0 != outLenParsed % 8)
					{
						outLenParsed = (outLenParsed / 8 + 1) * 8;
					}
					pTag->ioType=IOTYPE_OUT;//强制成OUT,减少认为错误
					COPCUATag* pOPCTag =  new COPCUATag(pTag->name,m_pOPCMaster->m_tagOffsetO+outLenParsed,pTag->size_hex,pTag->type_hex,m_index,pTag,this);
					m_pOPCMaster->m_OPCTagO[m_pOPCMaster->m_tagNumerO] = pOPCTag;
					m_OPCTagO[m_tagNumer] = m_pOPCMaster->m_OPCTagO[m_pOPCMaster->m_tagNumerO];
					m_OPCTagO[m_tagNumer]->m_iTagIndex = m_pOPCMaster->m_tagNumerO;
					m_pOPCMaster->m_tagNumerO++;//总tag个数
					outLenParsed+=pTag->size_hex;
					//if (!m_pOPCMaster->m_AddTag(m_pOPCMaster->m_handle, pTag, bWriAndRedisWri))
					//{
					//	pTag->m_bAuthorizationFlag = false;
					//}
					//begin add by lixiaoming for opc da
					//SetBaseTagType(pTag->type_hex, pOPCTag);
					//pOPCTag->m_strName = pTag->name;
					//if (m_bWirteAndRead)
					//{
					//	pOPCTag->m_nAccessRight = ACCESSRIGHT_READ_WRITE;
					//}
					//else
					//{
					//	pOPCTag->m_nAccessRight = ACCESSRIGHT_READ_ONLY;
					//}

					pOPCTag->rangeConvType = rangeConvertType;
					pOPCTag->m_dblEngHighLimit = m_dblEngHighLimit;
					pOPCTag->m_dblEngLowLimit = m_dblEngLowLimit;
					pOPCTag->m_dblRawHighLimit = m_dblRawHighLimit;
					pOPCTag->m_dblRawLowLimit = m_dblRawLowLimit;
					m_OPCTagO[m_tagNumer]->m_TagIndexOfSlave = m_tagNumer;
					m_tagNumer++;

				}
			}
			if(m_pOPCMaster->m_tagNumerI>MAX_TAG)
			{
				//AfxMessageBox(_T("m_pOPCMaster->m_tagNumerI>MAX_TAG||m_pOPCMaster->m_tagNumerO>MAX_TAG, 50000, 请拆分成多个驱动！"));
				//exit(0);
				//CMyLog log;
				//log.WriteLog("m_pOPCMaster->m_tagNumerI>MAX_TAG||m_pOPCMaster->m_tagNumerO>MAX_TAG, 100000, 请拆分成多个驱动！");
				char szTempCH[1024] = { 0 };
				char szTempEN[1024] = { 0 };
				sprintf(szTempCH, "读取组标签总数超过限制: %d,请拆分成多个驱动。", MAX_TAG);
				sprintf(szTempEN, "The total number of read group tags exceeds the limit: %d. Please split it into multiple drivers.", MAX_TAG);
				m_pOPCMaster->m_pSetLogInfo(m_pOPCMaster->m_handle, INFOTYPE_ERR, m_pOPCMaster->m_log_Source, szTempCH, szTempEN, true, false);
				return false;
			}

			if (m_pOPCMaster->m_tagNumerO > MAX_TAG)
			{
				char szTempCH[1024] = { 0 };
				char szTempEN[1024] = { 0 };
				sprintf(szTempCH, "写入组标签总数超过限制: %d,请拆分成多个驱动。", MAX_TAG);
				sprintf(szTempEN, "The total number of write group tags exceeds the limit: %d. Please split it into multiple drivers.", MAX_TAG);
				m_pOPCMaster->m_pSetLogInfo(m_pOPCMaster->m_handle, INFOTYPE_ERR, m_pOPCMaster->m_log_Source, szTempCH, szTempEN, true, false);
				return false;
			}


			if (m_pOPCMaster->m_tagNumerO > MAX_TAG || m_pOPCMaster->m_tagNumerI> MAX_TAG)
			{
				char szTempCH[1024] = { 0 };
				char szTempEN[1024] = { 0 };
				sprintf(szTempCH, "组标签总数超过限制: %d,请拆分成多个驱动。", MAX_TAG);
				sprintf(szTempEN, "The total number of group tags exceeds the limit: %d. Please split it into multiple drivers.", MAX_TAG);
				m_pOPCMaster->m_pSetLogInfo(m_pOPCMaster->m_handle, INFOTYPE_ERR, m_pOPCMaster->m_log_Source, szTempCH, szTempEN, true, false);
				return false;
			}

			if(m_tagNumer>MAX_TAGNUMER)
			{
				//AfxMessageBox(_T("m_tagNumer>MAX_TAGNUMER, 1024*5, 请拆分成多个驱动！"));
				//exit(0);
				char szTempCH[1024] = { 0 };
				char szTempEN[1024] = { 0 };
				sprintf(szTempCH, "标签总数超过限制: %d,请拆分成多个驱动。", MAX_TAGNUMER);
				sprintf(szTempEN, "The total number of tags exceeds the limit: %d. Please split it into multiple drivers.", MAX_TAGNUMER);
				m_pOPCMaster->m_pSetLogInfo(m_pOPCMaster->m_handle, INFOTYPE_ERR, m_pOPCMaster->m_log_Source, szTempCH, szTempEN, true, false);
				return false;
			}

			{//用增加的tag作为实际长度
				inLenParsed=((inLenParsed+7)/8)*8;//取整8位的倍数。
				outLenParsed=((outLenParsed+7)/8)*8;//取整8位的倍数。
				m_slaveDataSizeI = inLenParsed;
				m_slaveDataSizeO = outLenParsed;
				m_pOPCMaster->m_tagOffsetI+=inLenParsed;
				m_pOPCMaster->m_tagOffsetO+=outLenParsed;
			}
		}

	}	
	return true;
}

//void COPCUASlave::SetBaseTagType(unsigned char type, COPCUATag* pOPCTag)
//{
//
//
//	switch (type) 
//	{
//		case DT_BOOL:case DT_1BIT:case DT_2BITS:case DT_4BITS:case DT_DSM6:
//
//			pOPCTag->m_nDataType = VT_BOOL;
//			pOPCTag->m_vtValue.vt = VT_BOOL;
//			break;
//	
//		case DT_SINGLE:case DT_AS_REAL:
//			pOPCTag->m_nDataType = VT_R4;
//			pOPCTag->m_vtValue.vt = VT_R4;
//			break;
//
//		case DT_DOUBLE:
//			pOPCTag->m_nDataType = VT_R8;
//			pOPCTag->m_vtValue.vt = VT_R8;
//			break;
//
//		case DT_BYTE:
//			pOPCTag->m_nDataType = VT_UI1;
//			pOPCTag->m_vtValue.vt = VT_UI1;
//			break;
//
//		case DT_SBYTE:
//			pOPCTag->m_nDataType = VT_I1;
//			pOPCTag->m_vtValue.vt = VT_I1;
//			break;
//
//		case DT_WORD:
//			pOPCTag->m_nDataType = VT_UI2;
//			pOPCTag->m_vtValue.vt = VT_UI2;
//			break;
//
//		case DT_SWORD:
//			pOPCTag->m_nDataType = VT_I2;
//			pOPCTag->m_vtValue.vt = VT_I2;
//			break;
//
//		case DT_DWORD:
//			pOPCTag->m_nDataType = VT_UI4;
//			pOPCTag->m_vtValue.vt = VT_UI4;
//			break;
//
//		case DT_SDWORD:
//			pOPCTag->m_nDataType = VT_I4;
//			pOPCTag->m_vtValue.vt = VT_I4;
//			break;
//
//		case DT_STRING:
//			pOPCTag->m_nDataType = VT_BSTR;
//			pOPCTag->m_vtValue.vt = VT_BSTR;
//			pOPCTag->m_vtValue.bstrVal = NULL;
//			break;
//
//		default:
//			pOPCTag->m_nDataType = VT_R4;
//			pOPCTag->m_vtValue.vt = VT_R4;
//			break;
//	}
//}