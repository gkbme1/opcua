// DPSlave.h: interface for the COPCSlave class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DPSLAVE_H__EE8194D2_D6D7_4D5B_B962_3A9BCC0B12D7__INCLUDED_)
#define AFX_DPSLAVE_H__EE8194D2_D6D7_4D5B_B962_3A9BCC0B12D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class COPCUAMaster;
class COPCUATag;

#define OPC_GROUP_S2C 1
#define OPC_GROUP_C2S 2
#define OPC_GROUP_SC_RW 3
#define AEFromDriver  4

#define DISPLAYNAME_TAGNAME  0
#define DISPLAYNAME_DS  1
#define DISPLAYNAME_ADDRESS  2

#define NODE_ID_TYPE_S  0
#define NODE_ID_TYPE_I  1
#define NODE_ID_TYPE_GUID  2
#define NODE_ID_TYPE_BS  3

#define STATE_OK 1
#define STATE_ERR_FC 2
#define STATE_ERR_LEN 3
#define STATE_ERR_ADDRESS 4
#define STATE_ERR_CRC 5
#define STATE_ERR_UNKNOWN 6
#define STATE_ERR_TMO 7
#define STATE_ERR_BAD 8

#define MAX_TAGNUMER 10000 //每个从站最多1万个标签，多了，eng添加失败.
#define MAX_ITEM 10000 //一个组不超过10000点
class COPCUASlave
{
public:
//	char m_tagNameStrStr[MAX_ITEM*100];//最多1000个字段
	int m_ID;//记录号
	int m_index;//第几个从站
	unsigned char m_dataQuality;
	unsigned char m_OPCGroupType;
	unsigned int m_stateCounter;
	bool ReadCSV(char*&pMem,char*pLine, bool bWriAndRedisWri = false);
	void StateMachineRun();
	//void SetBaseTagType(unsigned char type, COPCUATag* pOPCTag);
	COPCUAMaster*m_pOPCMaster;
	int m_state;
	unsigned int m_successCounter;
	unsigned int m_failureCounter;
	int m_offsetI;//bit为单位. 该从站在主站数据内存块中偏移。
	int m_offsetO;//bit为单位. 该从站在主站数据内存块中偏移。
	int m_slaveDataSizeI;//bit为单位.该从站总数据大小，输入。
	int m_slaveDataSizeO;//bit为单位.该从站总数据大小，输出。
	int m_tagNumer;
	COPCUATag *m_OPCTagI[MAX_TAGNUMER];
	COPCUATag *m_OPCTagO[MAX_TAGNUMER];
	char m_grpName[256];	
	char m_AESourceDriverName[256];
	COPCUASlave();
	virtual ~COPCUASlave();

	int m_MasterTagFristIndexI;//该第一个tag在Master中的tags中位置
	int m_MasterTagFristIndexO;//该第一个tag在Master中的tags中位置
	bool m_bWirteAndRead;      //读写
	bool m_bReadFisrt;		   //先读后写
	bool m_bChangeModity;      //变化传值
	bool m_bWriAndRedisWri;
	bool m_bWriteRDBValueCheck; //开启写实时库值校验
	bool m_bStrictOut;       	//严格输出
	int m_nNodeIDType;
	COPCUASlave *m_pGroupSlave; //读组对应的写设备（写组对应的读设备）
	//unsigned char m_GroupType;

};

#endif // !defined(AFX_DPSLAVE_H__EE8194D2_D6D7_4D5B_B962_3A9BCC0B12D7__INCLUDED_)
