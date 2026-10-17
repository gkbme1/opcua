// DPTag.h: interface for the COPCFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DPTAG_H__243B9104_473F_4D95_B553_5E04CA886F88__INCLUDED_)
#define AFX_DPTAG_H__243B9104_473F_4D95_B553_5E04CA886F88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "tag.h"
#include "OpcUASlave.h"
class COPCUATag
{
public:
	//CString Value(char*IOMem,bool bDecimal = false);
	CTag*m_pTag;
enum TAGTYPE{
	TAGTYPE_BOOL,
	TAGTYPE_BYTE,TAGTYPE_SBYTE,TAGTYPE_WORD,TAGTYPE_SWORD,TAGTYPE_DWORD,TAGTYPE_SDWORD,TAGTYPE_SINGLE,TAGTYPE_DOUBLE,
	TAGTYPE_ALM_BOOL,
	TAGTYPE_ALM_BYTE,TAGTYPE_ALM_SBYTE,TAGTYPE_ALM_WORD,TAGTYPE_ALM_SWORD,TAGTYPE_ALM_DWORD,TAGTYPE_ALM_SDWORD,TAGTYPE_ALM_SINGLE,TAGTYPE_ALM_DOUBLE,	
	TAGTYPE_STRING,
};
	unsigned char m_index;//这个tag在第几个从站
	COPCUATag(char*name, unsigned int offset, unsigned int size, unsigned int type,char index,CTag *pTag,COPCUASlave*pOpcSlave)
	{
		m_index = index;
		m_name = name;
		m_offset = offset;
		m_size = size;
		m_type = type;
		m_pTag = pTag;
		m_pOpcSlave = pOpcSlave;
		m_quality = 0;
		m_dbValue = 0xFFFFFFFF;
		m_strValue = "";
		m_bChangedWrite = false;
		m_iTagIndex = 0;
		m_TagIndexOfSlave = 0;
		m_ForceUpdateRDBbyValue = false;
		m_nTagWriteDDBIndex = 0;
	};
	virtual ~COPCUATag();
	string  m_name;
	unsigned int m_offset;
	unsigned int m_size;
	unsigned int m_type;
	unsigned int m_quality;
	COPCUASlave*m_pOpcSlave;
	bool  m_bChangedWrite;
	double m_dbValue;
	string m_strValue;
	int m_iTagIndex;
	unsigned int m_TagIndexOfSlave;
	//virtual void SetReadValue(VARIANT var, BOOL bSetChanged = TRUE, BOOL bEnableQuality = TRUE);
	//virtual HRESULT ReadValue(OPCITEMSTATE& cState, VARTYPE m_vtReqType);
	//virtual HRESULT ReadValue(VARIANT &vt, WORD &wQuality, FILETIME &ftTimeStamp, VARTYPE m_vtReqType);
	//bool SetWriteValue(int iQuality, double value);
	bool m_ForceUpdateRDBbyValue;

	int rangeConvType;
	double m_dblRawLowLimit;
	double m_dblRawHighLimit;
	double m_dblEngLowLimit;
	double m_dblEngHighLimit;
	unsigned int m_nTagWriteDDBIndex;
	void* m_handle_UaVariable;
};

#endif // !defined(AFX_DPTAG_H__243B9104_473F_4D95_B553_5E04CA886F88__INCLUDED_)
