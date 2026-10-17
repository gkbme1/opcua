#ifndef UAGATEWAYNODEMANAGER_H
#define UAGATEWAYNODEMANAGER_H

#include "nodemanagerbase.h"
#include "uagatewayvariable.h"

class UaGatewayNodeManager : public NodeManagerBase, public UaThread
{
public:
	UaGatewayNodeManager(const UaString& uri);
	virtual ~UaGatewayNodeManager();
	
public:
	virtual bool onInitialize() = 0;
	virtual void onFinalize() = 0;

	virtual bool onConfigure() = 0;

	virtual void onScan(const UaDateTime& time) = 0;

	virtual void onWrite(
		UaVariant& value,
		UaGatewayVariable* pVariable) = 0;
		
	virtual OpcUa_UInt32 scanRate() const;

protected:
	// Add folder
	// nodeId :  unique id 
	// name:     folder name
	// parentId: parent folder id to attach
	bool addFolder(
		const UaNodeId& nodeId,
		const UaString& name,
		const UaNodeId& parentId = UaNodeId(OpcUaId_ObjectsFolder));

	// Add variable to folder
    // nodeId :    unique id 
	// name:       folder name
	// parentId:   parent folder id to attach
	// dataType:   indicate the data type
	// isArray:    indicate if is arrary
	// isWritable: indicate if can be write by ua client
	// pUserData:  customized data of variable, can be get by getUserData()
	UaGatewayVariable* addVariable(
		const UaNodeId&   nodeId,		
		const UaString&   name,		
		const UaNodeId&   parentId,
		OpcUa_BuiltInType dataType,
		bool              isArray,
		OpcUa_Byte        accessLevel,
		UserDataBase*     pUserData = OpcUa_Null);

public:
	UaStatus afterStartUp();
	UaStatus beforeShutDown();

	void run();

	OpcUa_Boolean beforeSetAttributeValue(
		Session* pSession,
		UaNode* pNode,
		OpcUa_Int32 attributeId,
		const UaDataValue& dataValue,
		OpcUa_Boolean& checkWriteMask);

	void afterSetAttributeValue(
		Session* pSession,
		UaNode* pNode,
		OpcUa_Int32 attributeId,
		const UaDataValue& dataValue);

private:
	UaMutexRefCounted* getSharedMutex();

private:	
	bool m_continueFlag;
	std::vector<UaMutexRefCounted*> m_mutexes;
	OpcUa_UInt32 m_mutexIndex;
};	

#endif