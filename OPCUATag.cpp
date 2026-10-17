// DPTag.cpp: implementation of the COPCFrame class.
//
//////////////////////////////////////////////////////////////////////

#include <comutil.h>
#include "mystdafx.h"
#include "OPCUATag.h"
#include "OPCUAMaster.h"
#include "CommMath.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


COPCUATag::~COPCUATag()
{

}
#include "common.h"
//CString COPCUATag::Value(char *IOMem,bool bDecimal )
//{
//	CString s;
//	if(m_size==1)
//	{
//		if(IOMem[m_offset/8]&(1<<m_offset%8))
//			s = _T("TRUE");
//		else
//			s = _T("FALSE");
//	}else
//	if(!bDecimal)
//	{
//		CCommon gcom;
//		char buf[100];
//		if(m_type == DT_2BITS||m_type == DT_4BITS)
//		{
//			double v;
//			m_pTag->ReadTagHex(IOMem+m_offset/8, v, m_offset%8);
//			unsigned char c = (unsigned char)v;
//			if((c>=0)&&(c<=9))
//				buf[0] =c+'0';
//			else 
//			if((c>=10)&&(c<=15))
//				buf[0]=c-10+'A';
//
//			buf[1]=0;
//		}else
//			gcom.Hex2Str(IOMem+m_offset/8,m_size/8,buf);
//		s = buf;
//	}else
//	{
////2014.5.17 1BIT 2BITS 4BITS
//		if(m_type == DT_2BITS||m_type == DT_4BITS)
//		{
//			double v;
//			m_pTag->ReadTagHex(IOMem+m_offset/8, v, m_offset%8);
//			s.Format(_T("%.0f"),v);
//		}
//
//		if(m_type == DT_BYTE/*||m_type == DT_ALM_BYTE*/)
//			s.Format(_T("%d"),*(unsigned char*)(IOMem+m_offset/8));
//		if(m_type == DT_WORD/*||m_type == DT_ALM_WORD*/)
//			s.Format(_T("%d"),*(unsigned short*)(IOMem+m_offset/8));
//		if(m_type == DT_DWORD/*||m_type == DT_ALM_DWORD*/)
//			s.Format(_T("%d"),*(unsigned long*)(IOMem+m_offset/8));
//		if(m_type == DT_SBYTE/*||m_type == DT_ALM_SBYTE*/)
//			s.Format(_T("%d"),*(char*)(IOMem+m_offset/8));
//		if(m_type == DT_SWORD/*||m_type == DT_ALM_SWORD*/)
//			s.Format(_T("%d"),*(short*)(IOMem+m_offset/8));
//		if(m_type == DT_SDWORD/*||m_type == DT_ALM_SDWORD*/)
//			s.Format(_T("%d"),*(int*)(IOMem+m_offset/8));
//		if(m_type == DT_SINGLE/*||m_type == DT_ALM_SINGLE*/)
//			s.Format(_T("%f"),*(float*)(IOMem+m_offset/8));
//		if(m_type == DT_DOUBLE/*||m_type == DT_ALM_DOUBLE*/)
//			s.Format(_T("%f"),*(double*)(IOMem+m_offset/8));
//// 		if(m_type == DT_STRING)
//// 		{
//// 			CCommon gcom;
//// 			char buf[100];
//// 			gcom.Hex2Str(IOMem+m_offset/8,m_size/8,buf);
//// 			s = buf;
//// 		}
//	}
//
//	return s;
//}
//
//void COPCUATag::SetReadValue(VARIANT var, BOOL bSetChanged, BOOL bEnableQuality)
//{
//	//先写后读
//	if (this->m_pOpcSlave->m_bWirteAndRead && (!this->m_pOpcSlave->m_bReadFisrt))
//	{
//		if (!m_bHasWriteOnce)
//			return ;
//	}
//	
//	EnterCriticalSection(&(m_pOpcSlave->m_pOPCMaster->m_criticalIOMemAccess));
//	CTagBase::SetValue(var,bSetChanged, bEnableQuality);
//	CTag*pTag = m_pTag;
//	
//	char *IOMem = NULL;
//	
//	//EnterCriticalSection(&(m_pOpcSlave->m_pOPCMaster->m_criticalIOMemAccess));
//	//if (m_pOpcSlave->m_pOPCMaster->m_dataLengthI > 0)
//	{
//		if (pTag->ioType == IOTYPE_IN && m_pOpcSlave->m_pOPCMaster->m_dataLengthI > 0)
//		{
//			IOMem = m_pOpcSlave->m_pOPCMaster->m_dataI;
//			m_pOpcSlave->m_pOPCMaster->m_dataQualityI[m_iTagIndex] |= TAG_IO_TAGQUALITY_IN_OK;
//		}
//	}
//	
//	double value;
//	char strValue[MAX_TAGSTRINGVALUE_LEN] = { 0 };
//
//	CWcharAndChar mychar;
//	
//	switch (var.vt)
//	{
//	case VT_BOOL://Boolen
//		value = var.boolVal == 0 ? 0 : 1;
//		break;
//	case VT_I1://Char
//		value = var.cVal;
//		break;
//	case VT_UI1://Byte
//		value = (char)var.bVal;
//		break;
//	case VT_I2://Short
//		value = var.iVal;
//		break;
//	case VT_UI2://Word
//		value = var.uiVal;
//		break;
//	case VT_I4://Long
//		value = var.lVal;
//		break;
//	case VT_UI4://DWORD
//		value = var.ulVal;
//		break;
//	case VT_R4://Float
//		value = var.fltVal ;
//		break;
//	case VT_R8://Double
//		value = var.dblVal ;
//		break;
//	case VT_BSTR://String
//	{
//		char* tmp = mychar.wtochar(var.bstrVal);
//		memcpy(strValue, mychar.wtochar(var.bstrVal), strlen(tmp));
//	}
//		break;
//	default:
//		value = var.fltVal;
//		break;
//	}
//
//	char*IOMemI = m_pOpcSlave->m_pOPCMaster->m_dataI;
//	if (pTag->type == DT_STRING)
//	{
//		m_strValue = "";
//		pTag->WriteTagHex(IOMem + m_offset / 8, strValue);
//		//相关组也要写
//		//if (this->m_pOpcSlave->m_bWirteAndRead)
//		//{
//		//	COPCTag* pOPCGrpTag = this->m_pOpcSlave->m_pGroupSlave->m_OPCTagI[this->m_TagIndexOfSlave];
//		//	CTag* pGrpTag = pOPCGrpTag->m_pTag;
//		//	pGrpTag->WriteTagHex(IOMemI + pOPCGrpTag->m_offset / 8, strValue);
//		//}
//	}
//	else
//	{
//		m_dbValue = 0xFFFFFFFF;
//		pTag->WriteTagHex(IOMem + m_offset / 8, value, m_offset % 8);
//		//相关组也要写
//		//if (this->m_pOpcSlave->m_bWirteAndRead)
//		//{
//		//	COPCTag* pOPCGrpTag = this->m_pOpcSlave->m_pGroupSlave->m_OPCTagI[this->m_TagIndexOfSlave];
//		//	CTag* pGrpTag = pOPCGrpTag->m_pTag;
//		//	pGrpTag->WriteTagHex(IOMemI + pOPCGrpTag->m_offset / 8, value, pOPCGrpTag->m_offset % 8);
//		//}
//	}
//	LeaveCriticalSection(&(m_pOpcSlave->m_pOPCMaster->m_criticalIOMemAccess));
//	m_wQuality = WRITEONETAG_TAGQUALITY_OK;
//	m_quality |= WRITEONETAG_TAGQUALITY_OK;
//	m_pOpcSlave->m_successCounter++;
//	m_pOpcSlave->m_dataQuality = WRITEONETAG_TAGQUALITY_OK;
//}
//#if 0
//HRESULT COPCTag::ReadValue(OPCITEMSTATE& cState, VARTYPE m_vtReqType)
//{
//	CTag*pTag = m_pTag;
//	char *IOMem;
//	if (pTag->ioType == IOTYPE_IN)
//		IOMem = m_pOpcSlave->m_pOPCMaster->m_dataI;
//	else
//		IOMem = m_pOpcSlave->m_pOPCMaster->m_dataO;
//	double value;
//	char strValue[MAX_TAGSTRINGVALUE_LEN] = { 0 };
//	if (pTag->type == DT_STRING)
//	{
//		pTag->ReadTagHex(IOMem + m_offset / 8, strValue);//用type_hex，
//	}
//	else
//	{
//		pTag->ReadTagHex(IOMem + m_offset / 8, value, m_offset % 8);//用type_hex，
//	}
//	
//	if (m_vtValue.vt == VT_BOOL)
//		m_vtValue.boolVal = value == 0 ? 0 : 1;
//	else if (m_vtValue.vt == VT_R8)
//		m_vtValue.dblVal = value;
//	else if (m_vtValue.vt == VT_BSTR)
//	{
//		//_variant_t var;
//		_bstr_t bstr;
//		char szbuf[MAX_TAGSTRINGVALUE_LEN] = { 0 };
//		strncpy(szbuf, m_pTag->m_pvalue_string, MAX_TAGSTRINGVALUE_LEN);
//		//var.vt = VT_BSTR;
//		bstr = _bstr_t(szbuf);
//		//var.bstrVal = bstr;
//
//		VariantClear(&m_vtValue);
//		//VariantInit(&m_vtValue);
//		//HRESULT hr = VariantCopy(&m_vtValue, &var);
//		m_vtValue.vt = VT_BSTR;
//		m_vtValue.bstrVal = bstr;
//	}
//	else
//	{
//		m_vtValue.fltVal = value;
//	}
//
//	GetLocalTime(&m_stTimeStamp);
//	m_wQuality = m_quality;
//	m_pOpcSlave->m_successCounter++;
//	HRESULT hRst = CTagBase::ReadValue(cState, m_vtReqType);
//	return hRst;
//}
//
//HRESULT COPCTag::ReadValue(VARIANT &vt, WORD &wQuality, FILETIME &ftTimeStamp, VARTYPE m_vtReqType)
//{
//	CTag*pTag = m_pTag;
//	char *IOMem;
//	if (pTag->ioType == IOTYPE_IN)
//		IOMem = m_pOpcSlave->m_pOPCMaster->m_dataI;
//	else
//		IOMem = m_pOpcSlave->m_pOPCMaster->m_dataO;
//	double value;
//	char strValue[MAX_TAGSTRINGVALUE_LEN] = { 0 };
//	if (pTag->type == DT_STRING)
//	{
//		pTag->ReadTagHex(IOMem + m_offset / 8, strValue);//用type_hex，
//	}
//	else
//	{
//		pTag->ReadTagHex(IOMem + m_offset / 8, value, m_offset % 8);//用type_hex，
//	}
//	
//	if (m_vtValue.vt == VT_BOOL)
//		m_vtValue.boolVal = value == 0 ? 0 : 1;
//	else if (m_vtValue.vt == VT_R8)
//		m_vtValue.dblVal = value;
//	else if (m_vtValue.vt == VT_BSTR)
//	{
//		//_variant_t var;
//		_bstr_t bstr;
//		char szbuf[MAX_TAGSTRINGVALUE_LEN] = { 0 };
//		strncpy(szbuf, m_pTag->m_pvalue_string, MAX_TAGSTRINGVALUE_LEN);
//		//var.vt = VT_BSTR;
//		bstr = _bstr_t(szbuf);
//		//var.bstrVal = bstr;
//
//		VariantClear(&m_vtValue);
//		//VariantInit(&m_vtValue);
//		//HRESULT hr = VariantCopy(&m_vtValue, &var);
//		m_vtValue.vt = VT_BSTR;
//		m_vtValue.bstrVal = bstr;
//	}
//	else
//	{
//		m_vtValue.fltVal = value;
//	}
//	GetLocalTime(&m_stTimeStamp);
//	m_wQuality = m_quality;
//	HRESULT hRst = CTagBase::ReadValue(vt, wQuality, ftTimeStamp, m_vtReqType);
//	return hRst;
//}
//#endif
//
//
//bool COPCUATag::SetWriteValue(int iQuality, double value)
//{
//	//先读后写
//	if (this->m_pOpcSlave->m_bWirteAndRead && this->m_pOpcSlave->m_bReadFisrt)
//	{
//		COPCUATag* pOPCTag = this->m_pOpcSlave->m_pGroupSlave->m_OPCTagI[this->m_TagIndexOfSlave];
//		
//		if (!pOPCTag->m_bHasReadOnce)
//			return false;
//	}
//
//
//	m_wQuality = iQuality;
//
//	if (this->m_pOpcSlave->m_bWirteAndRead)
//	{
//		COPCUATag* pOPCGrpTag = this->m_pOpcSlave->m_pGroupSlave->m_OPCTagI[this->m_TagIndexOfSlave];
//		pOPCGrpTag->m_wQuality = iQuality;
//	}
//
//	//m_bHasWriteOnce = true;
//
//	GetLocalTime(&this->m_stTimeStamp);
//	
//	if (m_pTag->type != DT_STRING)
//	{
//		if (m_dbValue == value)
//		{
//			return true;
//		}
//
//		_variant_t var;
//		switch (m_pTag->type_hex)
//		{
//		case DT_BOOL:case DT_1BIT:case DT_2BITS:case DT_4BITS:case DT_DSM6:
//
//			var.vt = VT_BOOL;
//			var.boolVal = value == 0 ? 0 : -1;
//			break;
//
//		case DT_SINGLE:case DT_AS_REAL:
//			var.vt = VT_R4;
//			var.fltVal = float(value);
//			break;
//
//		case DT_DOUBLE:
//			var.vt = VT_R8;
//			var.dblVal = value;
//			break;
//
//		case DT_BYTE:
//			var.vt = VT_UI1;
//			var.bVal = byte(value);
//			break;
//
//		case DT_SBYTE:
//			var.vt = VT_I1;
//			var.cVal = char(value);
//			break;
//
//		case DT_WORD:
//			var.vt = VT_UI2;
//			var.uiVal = WORD(value);
//			break;
//
//		case DT_SWORD:
//			var.vt = VT_I2;
//			var.iVal = short(value);
//			break;
//
//		case DT_DWORD:
//			var.vt = VT_UI4;
//			var.uintVal = DWORD(value);
//			break;
//
//		case DT_SDWORD:
//			var.vt = VT_I4;
//			var.intVal = int(value);
//			break;
//		default:
//			var.vt = VT_R4;
//			var.fltVal = value;
//			break;
//		}
//
//		if (iQuality == QUALITY_GOOD)
//		{
//			m_dbValue = value;
//			if (this->m_pOpcSlave->m_bWirteAndRead)
//			{
//				COPCUATag* pOPCGrpTag = this->m_pOpcSlave->m_pGroupSlave->m_OPCTagI[this->m_TagIndexOfSlave];
//				pOPCGrpTag->SetValue(var);
//			}
//			else
//			{
//				CTagBase::SetValue(var);
//			}
//			
//		}
//
//		return true;
//	}
//
//	else
//	{
//		_variant_t var;
//		_bstr_t bstr;
//		char szbuf[MAX_TAGSTRINGVALUE_LEN] = { 0 };
//		int iLen = strlen(m_pTag->m_pvalue_string);
//		if (iLen <= 0)
//		{
//			return true;
//		}
//
//		if (m_strValue.compare(m_pTag->m_pvalue_string) == 0)
//		{
//			return true;
//		}
//		
//		strncpy(szbuf, m_pTag->m_pvalue_string, iLen);
//		var.vt = VT_BSTR;
//		bstr = _bstr_t(szbuf);
//		var.bstrVal = bstr;
//		if (iQuality == QUALITY_GOOD)
//		{
//			if (this->m_pOpcSlave->m_bWirteAndRead)
//			{
//				COPCUATag* pOPCGrpTag = this->m_pOpcSlave->m_pGroupSlave->m_OPCTagI[this->m_TagIndexOfSlave];
//				pOPCGrpTag->SetValue(var);
//			}
//			
//			m_strValue = m_pTag->m_pvalue_string;
//			CTagBase::SetValue(var);
//		}
//
//		if (VT_BSTR == var.vt)
//		{
//			VariantClear(&var);
//		}
//		return true;
//	}
//}