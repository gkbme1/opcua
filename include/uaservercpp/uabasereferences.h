/******************************************************************************
** uabasereferences.h
**
** Copyright (c) 2006-2020 Unified Automation GmbH. All rights reserved.
**
** Software License Agreement ("SLA") Version 2.7
**
** Unless explicitly acquired and licensed from Licensor under another
** license, the contents of this file are subject to the Software License
** Agreement ("SLA") Version 2.7, or subsequent versions
** as allowed by the SLA, and You may not copy or use this file in either
** source code or executable form, except in compliance with the terms and
** conditions of the SLA.
**
** All software distributed under the SLA is provided strictly on an
** "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
** AND LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
** LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
** PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the SLA for specific
** language governing rights and limitations under the SLA.
**
** The complete license agreement can be found here:
** http://unifiedautomation.com/License/SLA/2.7/
**
** Project: C++ OPC Server SDK core module
**
** Description: OPC UA server core module base reference classes.
**
******************************************************************************/
#ifndef __UABASEREFERENCES_H__
#define __UABASEREFERENCES_H__

#include "uanodeid.h"
#include "opcuatypes.h"
#include "version_coremodule.h"

class SERVER_CORE_EXPORT UaNode;
class SERVER_CORE_EXPORT UaReferenceType;
class SERVER_CORE_EXPORT NodeManager;

/*! \addtogroup ServerCoreAddressModel
*  @{
*/

/** Interface definition of the UaReference.
 *  Abstract base class for OPC UA references between UA nodes.
 *  It is not possible to use the default constructor.
 */
class SERVER_CORE_EXPORT UaReference
{
    UA_DISABLE_COPY(UaReference);
    UaReference();
public:
     /// @brief Enumeration of cross node manager reference type
    enum CrossNodeManagerReferenceType
    {
        UA_NO_CROSSNODEMANAGER = 0, /*!< This is not a cross node manager reference */
        UA_LIST_OF_REFERENCES,      /*!< This cross node manager reference can have a list of target nodes */
        UA_SINGLE_REFERENCE         /*!< This cross node manager reference has one target node */
    };

    /** construction */
    UaReference(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaReference();

    /** Checks whether this reference is across node managers or not.
     *  @return The type of cross node manager reference or UA_NO_CROSSNODEMANAGER if it is a normal reference.
     */
    virtual CrossNodeManagerReferenceType isCrossNodeManagerRef() const { return UA_NO_CROSSNODEMANAGER; };

    /** Checks whether a Node is out of Servers References.
     *  @return FALSE if out of Server Reference.
     */
    virtual OpcUa_Boolean isOutOfServerRef() const { return OpcUa_False; }

    /** Get the source Node.
     *  @return the source Node.
     */
    inline UaNode *       pSourceNode() const { return m_pSourceNode; }

    /** Get the target Node.
     *  @return the target Node.
     */
    inline UaNode *       pTargetNode() const { return m_pTargetNode; }

    /** Get the ReferenceType NodeId of the current Reference.
     *  @return the ReferenceTypeId of the current Reference.
     */
    virtual UaNodeId      referenceTypeId() const = 0;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    virtual OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const = 0;

    virtual UaReference* createCPCopy();
    virtual void clearCPCopy();

    /** Set source node to invalid. */
    inline void       setSourceNodeInvalid() { m_pSourceNode = NULL; }

    /** Set target Node to invalid. */
    inline void       setTargetNodeInvalid() { m_pTargetNode = NULL; }

    /** Set the next reference for a list of forward references. */
    inline void       setNextForwardReference(UaReference * pNextReference) { m_pNextForwardReference = pNextReference; }

    /** Get the next reference in a list of forward references. */
    inline UaReference* pNextForwardReference() { return m_pNextForwardReference; }

    /** Set the next reference for a list of inverse references. */
    inline void       setNextInverseReference(UaReference * pNextReference) { m_pNextInverseReference = pNextReference; }

    /** Get the next reference in a list of inverse references. */
    inline UaReference* pNextInverseReference() { return m_pNextInverseReference; }

#if SUPPORT_Class_Statistic
    static int s_referenceInstanceCount;
#endif // SUPPORT_Class_Statistic

protected:
    /// @brief Source node of the reference.
    UaNode * m_pSourceNode;
    /// @brief Target node of the reference.
    UaNode * m_pTargetNode;
    /// @brief Next reference in a list of forward references.
    UaReference * m_pNextForwardReference;
    /// @brief Next reference in a list of inverse references.
    UaReference * m_pNextInverseReference;
};

/** @brief Implements a reference between nodes in two different NodeManagers.
 *  This class is used to create a reference between nodes in two different NodeManagers. The reference stores the node manager
 *  of the target node instead of the target node since the reference represents 0..N references requested by forwarding the browse
 *  request to the other target node manager.
 */
class SERVER_CORE_EXPORT UaRefCrossNodeManager : public UaReference
{
    UA_DISABLE_COPY(UaRefCrossNodeManager);
public:
    /** construction */
    UaRefCrossNodeManager(NodeManager*  pNodeManager);
    /** destruction */
    virtual ~UaRefCrossNodeManager(){}

    /** Checks whether this reference is across node managers or not.
     *  @return The type of cross node manager reference or UA_NO_CROSSNODEMANAGER if it is a normal reference.
     */
    CrossNodeManagerReferenceType isCrossNodeManagerRef() const { return UA_LIST_OF_REFERENCES; }

    /** Get the ReferenceType NodeId of the current Reference.
     *  @return the ReferenceTypeId of the current Reference.
     */
    UaNodeId      referenceTypeId() const { return UaNodeId(); }

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;

    /** Get the actual NodeManager.
     *  @return Interface pointer of NodeManager.
     */
    inline NodeManager*  pNodeManager() const { return m_pNodeManager; }

private:
    NodeManager*  m_pNodeManager;
};

/** @brief Implements a reference between two nodes in two different NodeManagers.
 *  This class is used to create a reference between two nodes in different NodeManagers.
 */
class SERVER_CORE_EXPORT UaRefCrossNodeManagerSingle : public UaReference
{
public:
    /** construction */
    UaRefCrossNodeManagerSingle(UaNode * pSourceNode, const UaNodeId& targetNodeId, const UaNodeId& referenceTypeId, OpcUa_NodeClass targetNodeClass);
    UaRefCrossNodeManagerSingle(UaRefCrossNodeManagerSingle * pOther);
    /** destruction */
    virtual ~UaRefCrossNodeManagerSingle(){}

    /** Checks whether this reference is across node managers or not.
     *  @return The type of cross node manager reference or UA_NO_CROSSNODEMANAGER if it is a normal reference.
     */
    CrossNodeManagerReferenceType isCrossNodeManagerRef() const { return UA_SINGLE_REFERENCE; }

    /** Get the ReferenceType NodeId of the current Reference.
     *  @return the ReferenceTypeId of the current Reference.
     */
    UaNodeId      referenceTypeId() const { return m_referenceTypeId; }

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;

    /** Get the NodeId of the target node.
     *  @return NodeId of the target node.
     */
    inline UaNodeId targetNodeId() const { return m_targetNodeId; }

    /** Get the node class of the target node.
     *  @return Node class of the target node.
     */
    inline OpcUa_NodeClass targetNodeClass() const { return m_targetNodeClass; }

private:
    UaNodeId        m_targetNodeId;
    UaNodeId        m_referenceTypeId;
    OpcUa_NodeClass m_targetNodeClass;
};

/** @brief Class definition of the UaRefOutOfServer.
 *  Creates references out of the server.
 *  Derived from UaReference.
 */
class SERVER_CORE_EXPORT UaRefOutOfServer : public UaReference
{
    UA_DISABLE_COPY(UaRefOutOfServer);
public:
    /** construction */
    UaRefOutOfServer(UaRefOutOfServer * pOther);
    UaRefOutOfServer(UaReferenceType * pReferenceTypeNode);
    /** destruction */
    virtual ~UaRefOutOfServer(){}

    /** Checks whether a Node is out of Servers References.
     *  @return FALSE if out of Server Reference.
     */
    OpcUa_Boolean isOutOfServerRef() const { return OpcUa_True; }

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const { return m_referenceTypeId; }

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;

    /* ToDo return everything that is needed for browse like
        - ExpandedNodeId
        - BrowseName
        - DisplayName
        etc.
    */
    /* ToDo We need also a reference counter to handle several off server
       references pointing to the same node in the other server with the
       same instance of this class */
private:
    UaReferenceType * m_pReferenceTypeNode;
    UaNodeId          m_referenceTypeId;
    //ExpandedNodeId  m_nodeInOtherServer;
};

/** @brief Implements a reference betwen two nodes with the capability to set the reference type node.
 * All built-in reference types do not store the reference type node. They implement all reference
 * type related functionality in the reference type specific class. This class can be used to
 * implement user defined references.
 */
class SERVER_CORE_EXPORT UaGenericReference : public UaReference
{
    UA_DISABLE_COPY(UaGenericReference);
    UaGenericReference();
public:
    /** construction */
    UaGenericReference(UaNode * pSourceNode, UaNode * pTargetNode, UaReferenceType * pReferenceTypeNode);
    /** destruction */
    virtual ~UaGenericReference();

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;

private:
    UaReferenceType * m_pReferenceTypeNode;
};

/** @brief Implements a reference betwen two nodes with the capability to set the reference type NodeId.
 */
class SERVER_CORE_EXPORT UaReferenceCPCopy : public UaReference
{
    UaReferenceCPCopy();
public:
    /** construction */
    UaReferenceCPCopy(UaNode * pSourceNode, UaNode * pTargetNode, const UaNodeId& referenceTypeId);
    /** destruction */
    virtual ~UaReferenceCPCopy();

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;

private:
    UaNodeId m_referenceTypeId;
};

/** @brief Class implementing references of type Organizes.
 *  The semantic of this ReferenceType is to organise Nodes in the AddressSpace. It can be used to
 *  span multiple hierarchies independent of any hierarchy created with the non-looping Aggregates References.
 */
class SERVER_CORE_EXPORT UaRefOrganizes : public UaReference
{
    UaRefOrganizes();
public:
    /** construction */
    UaRefOrganizes(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefOrganizes(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasComponent.
 *  The semantic is a part-of relationship. The TargetNode of a Reference of the HasComponent ReferenceType
 *  is a part of the SourceNode. This ReferenceType is used to relate Objects or ObjectTypes with their containing Objects,
 *  DataVariables, and Methods. This ReferenceType is also used to relate complex Variables or VariableTypes with their DataVariables.
 *
 *  Like all other ReferenceTypes, this ReferenceType does not specify anything about the ownership of the parts,
 *  although it represents a part-of relationship semantic. That is, it is not specified if the TargetNode of a Reference of
 *  the HasComponent ReferenceType is deleted when the SourceNode is deleted.
 */
class SERVER_CORE_EXPORT UaRefHasComponent : public UaReference
{
    UaRefHasComponent();
public:
    /** construction */
    UaRefHasComponent(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasComponent(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check wether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasHistoricalConfiguration.
 */
class SERVER_CORE_EXPORT UaRefHasHistoricalConfiguration : public UaReference
{
    UaRefHasHistoricalConfiguration();
public:
    /** construction */
    UaRefHasHistoricalConfiguration(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasHistoricalConfiguration(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasOrderedComponent.
 */
class SERVER_CORE_EXPORT UaRefHasOrderedComponent : public UaReference
{
    UaRefHasOrderedComponent();
public:
    /** construction */
    UaRefHasOrderedComponent(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasOrderedComponent(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasArgumentDescription.
*/
class SERVER_CORE_EXPORT UaRefHasArgumentDescription : public UaReference
{
    UaRefHasArgumentDescription();
public:
    /** construction */
    UaRefHasArgumentDescription(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasArgumentDescription() {}

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasOptionalInputArgumentDescription.
*/
class SERVER_CORE_EXPORT UaRefHasOptionalInputArgumentDescription : public UaReference
{
    UaRefHasOptionalInputArgumentDescription();
public:
    /** construction */
    UaRefHasOptionalInputArgumentDescription(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasOptionalInputArgumentDescription() {}

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasGuard.
*/
class SERVER_CORE_EXPORT UaRefHasGuard : public UaReference
{
    UaRefHasGuard();
public:
    /** construction */
    UaRefHasGuard(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasGuard() {}

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasDictionaryEntry.
*/
class SERVER_CORE_EXPORT UaRefHasDictionaryEntry : public UaReference
{
    UaRefHasDictionaryEntry();
public:
    /** construction */
    UaRefHasDictionaryEntry(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasDictionaryEntry() {}

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasInterface.
*/
class SERVER_CORE_EXPORT UaRefHasInterface : public UaReference
{
    UaRefHasInterface();
public:
    /** construction */
    UaRefHasInterface(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasInterface() {}

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasAddIn.
*/
class SERVER_CORE_EXPORT UaRefHasAddIn : public UaReference
{
    UaRefHasAddIn();
public:
    /** construction */
    UaRefHasAddIn(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasAddIn() {}

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasProperty.
 * The semantic is to identify the Properties of a Node.
 */
class SERVER_CORE_EXPORT UaRefHasProperty : public UaReference
{
    UaRefHasProperty();
public:
    /** construction */
    UaRefHasProperty(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasProperty(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasSubtype.
 *  The semantic of this ReferenceType is to express a subtype relationship of types. It is used to span
 *  the ObjectTyoe, VariableType, DataType and ReferenceType hierarchy.
 */
class SERVER_CORE_EXPORT UaRefHasSubtype : public UaReference
{
    UaRefHasSubtype();
public:
    /** construction */
    UaRefHasSubtype(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasSubtype(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasEventSource.
 * The semantic of this ReferenceType is to relate event sources in a hierarchical, non-looping organization.
 * This ReferenceType and any subtypes are intended to be used for discovery of Event generation in a Server.
 * They are not required to be present for a Server to generate an Event from its source (causing the Event)
 * to its notifying Nodes. In particular, the root notifier of a Server, the Server Object is always capable
 * of supplying all Events from a Server and as such has implied HasEventSource References to every event source in a Server.
 */
class SERVER_CORE_EXPORT UaRefHasEventSource : public UaReference
{
    UaRefHasEventSource();
public:
    /** construction */
    UaRefHasEventSource(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasEventSource(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasNotifier.
 *  The semantic of this ReferenceType is to relate Object Nodes that are notifiers with other
 *  notifier Object Nodes. The ReferenceType is used to establish a hierarchical organization of
 *  event notifying Objects. It is a subtype of the HasEventSource ReferenceType
 */
class SERVER_CORE_EXPORT UaRefHasNotifier : public UaReference
{
    UaRefHasNotifier();
public:
    /** construction */
    UaRefHasNotifier(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasNotifier(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasTypeDefinition.
 *  The semantic of this ReferenceType is to bind an Object or Variable to its ObjectType or
 *  VariableType, respectively.
 */
class SERVER_CORE_EXPORT UaRefHasTypeDefinition : public UaReference
{
    UaRefHasTypeDefinition();
public:
    /** construction */
    UaRefHasTypeDefinition(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasTypeDefinition(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type GeneratesEvent.
 *  The semantic of this ReferenceType is to identify the types of Events instances of
 *  ObjectTypes or VariableTypes may generate and Methods may generate on each Method call.
 */
class SERVER_CORE_EXPORT UaRefGeneratesEvent : public UaReference
{
    UaRefGeneratesEvent();
public:
    /** construction */
    UaRefGeneratesEvent(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefGeneratesEvent(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type AlwaysGeneratesEvent.
 *  The semantic of this ReferenceType is to identify the types of Events Methods have
 *  to generate on each Method call.
 */
class SERVER_CORE_EXPORT UaRefAlwaysGeneratesEvent : public UaReference
{
    UaRefAlwaysGeneratesEvent();
public:
    /** construction */
    UaRefAlwaysGeneratesEvent(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefAlwaysGeneratesEvent(){};

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** Reference class used to represent a HasCondition reference.
 */
class SERVER_CORE_EXPORT UaRefHasCondition : public UaReference
{
    UaRefHasCondition();
public:
    /** construction */
    UaRefHasCondition(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasCondition(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasDescription.
 */
class SERVER_CORE_EXPORT UaRefHasDescription : public UaReference
{
    UaRefHasDescription();
public:
    /** construction */
    UaRefHasDescription(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasDescription(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasEncoding.
 */
class SERVER_CORE_EXPORT UaRefHasEncoding : public UaReference
{
    UaRefHasEncoding();
public:
    /** construction */
    UaRefHasEncoding(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasEncoding(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasModellingRule.
 *  The semantic of this ReferenceType is to bind the ModellingRule to an Object, Variable or Method.
 */
class SERVER_CORE_EXPORT UaRefHasModellingRule : public UaReference
{
    UaRefHasModellingRule();
public:
    /** construction */
    UaRefHasModellingRule(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasModellingRule(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type FromState.
 */
class SERVER_CORE_EXPORT UaRefFromState : public UaReference
{
    UaRefFromState();
public:
    /** construction */
    UaRefFromState(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefFromState(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasCause.
 */
class SERVER_CORE_EXPORT UaRefHasCause : public UaReference
{
    UaRefHasCause();
public:
    /** construction */
    UaRefHasCause(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasCause(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasEffect.
 */
class SERVER_CORE_EXPORT UaRefHasEffect : public UaReference
{
    UaRefHasEffect();
public:
    /** construction */
    UaRefHasEffect(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasEffect(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type ToState.
 */
class SERVER_CORE_EXPORT UaRefToState : public UaReference
{
    UaRefToState();
public:
    /** construction */
    UaRefToState(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefToState(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasSubStateMachine.
 */
class SERVER_CORE_EXPORT UaRefHasSubStateMachine : public UaReference
{
    UaRefHasSubStateMachine();
public:
    /** construction */
    UaRefHasSubStateMachine(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasSubStateMachine(){}

    /** Get the ReferenceTypeId of the current Node.
     *  @return the ReferenceTypeId of the current Node.
     */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
     *  @param pNodeId NodeId of the requested reference type.
     *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
     */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasPubSubConnection.
*/
class SERVER_CORE_EXPORT UaRefHasPubSubConnection : public UaReference
{
    UaRefHasPubSubConnection();
public:
    /** construction */
    UaRefHasPubSubConnection(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasPubSubConnection() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasWriterGroup.
*/
class SERVER_CORE_EXPORT UaRefHasWriterGroup : public UaReference
{
    UaRefHasWriterGroup();
public:
    /** construction */
    UaRefHasWriterGroup(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasWriterGroup() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasReaderGroup.
*/
class SERVER_CORE_EXPORT UaRefHasReaderGroup : public UaReference
{
    UaRefHasReaderGroup();
public:
    /** construction */
    UaRefHasReaderGroup(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasReaderGroup() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type DataSetToWriter.
*/
class SERVER_CORE_EXPORT UaRefDataSetToWriter : public UaReference
{
    UaRefDataSetToWriter();
public:
    /** construction */
    UaRefDataSetToWriter(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefDataSetToWriter() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasDataSetWriter.
*/
class SERVER_CORE_EXPORT UaRefHasDataSetWriter : public UaReference
{
    UaRefHasDataSetWriter();
public:
    /** construction */
    UaRefHasDataSetWriter(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasDataSetWriter() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasDataSetReader.
*/
class SERVER_CORE_EXPORT UaRefHasDataSetReader : public UaReference
{
    UaRefHasDataSetReader();
public:
    /** construction */
    UaRefHasDataSetReader(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasDataSetReader() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasAlarmSuppressionGroup.
*/
class SERVER_CORE_EXPORT UaRefHasAlarmSuppressionGroup : public UaReference
{
    UaRefHasAlarmSuppressionGroup();
public:
    /** construction */
    UaRefHasAlarmSuppressionGroup(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasAlarmSuppressionGroup() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type AlarmGroupMember.
*/
class SERVER_CORE_EXPORT UaRefAlarmGroupMember : public UaReference
{
    UaRefAlarmGroupMember();
public:
    /** construction */
    UaRefAlarmGroupMember(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefAlarmGroupMember() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasEffectDisable.
*/
class SERVER_CORE_EXPORT UaRefHasEffectDisable : public UaReference
{
    UaRefHasEffectDisable();
public:
    /** construction */
    UaRefHasEffectDisable(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasEffectDisable() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasEffectEnable.
*/
class SERVER_CORE_EXPORT UaRefHasEffectEnable : public UaReference
{
    UaRefHasEffectEnable();
public:
    /** construction */
    UaRefHasEffectEnable(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasEffectEnable() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasEffectSuppressed.
*/
class SERVER_CORE_EXPORT UaRefHasEffectSuppressed : public UaReference
{
    UaRefHasEffectSuppressed();
public:
    /** construction */
    UaRefHasEffectSuppressed(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasEffectSuppressed() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/** @brief Class implementing references of type HasEffectUnsuppressed.
*/
class SERVER_CORE_EXPORT UaRefHasEffectUnsuppressed : public UaReference
{
    UaRefHasEffectUnsuppressed();
public:
    /** construction */
    UaRefHasEffectUnsuppressed(UaNode * pSourceNode, UaNode * pTargetNode);
    /** destruction */
    virtual ~UaRefHasEffectUnsuppressed() {};

    /** Get the ReferenceTypeId of the current Node.
    *  @return the ReferenceTypeId of the current Node.
    */
    UaNodeId      referenceTypeId() const;

    /** Check whether the current reference is a subtype of the passed reference type node id.
    *  @param pNodeId NodeId of the requested reference type.
    *  @return TRUE if the reference is a subtype of the passed type FALSE if not.
    */
    OpcUa_Boolean isSubtypeOf(const OpcUa_NodeId * pNodeId) const;
};

/*! @} */

#endif // __UABASEREFERENCES_H__
