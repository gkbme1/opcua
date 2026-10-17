/******************************************************************************
** uafieldtargetdatatype.h
**
** Copyright (c) 2006-2020 Unified Automation GmbH All rights reserved.
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
** Project: C++ OPC SDK base module
**
** Portable UaFieldTargetDataType class.
**
******************************************************************************/
#ifndef UAFIELDTARGETDATATYPE_H
#define UAFIELDTARGETDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaguid.h"
#include "uanodeid.h"
#include "uastring.h"
#include "uavariant.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaDataValue;

class UABASE_EXPORT UaFieldTargetDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_FieldTargetDataType.
 *
 *  This class encapsulates the native OpcUa_FieldTargetDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaFieldTargetDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared FieldTargetDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaFieldTargetDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaFieldTargetDataType
{
    UA_DECLARE_PRIVATE(UaFieldTargetDataType)
public:
    UaFieldTargetDataType();
    UaFieldTargetDataType(const UaFieldTargetDataType &other);
    UaFieldTargetDataType(const OpcUa_FieldTargetDataType &other);
    UaFieldTargetDataType(
        const UaGuid& dataSetFieldId,
        const UaString& receiverIndexRange,
        const UaNodeId& targetNodeId,
        OpcUa_UInt32 attributeId,
        const UaString& writeIndexRange,
        OpcUa_OverrideValueHandling overrideValueHandling,
        const UaVariant&overrideValue
        );
    UaFieldTargetDataType(const UaExtensionObject &extensionObject);
    UaFieldTargetDataType(const OpcUa_ExtensionObject &extensionObject);
    UaFieldTargetDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaFieldTargetDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaFieldTargetDataType();

    void clear();

    bool operator==(const UaFieldTargetDataType &other) const;
    bool operator!=(const UaFieldTargetDataType &other) const;

    UaFieldTargetDataType& operator=(const UaFieldTargetDataType &other);

    OpcUa_FieldTargetDataType* copy() const;
    void copyTo(OpcUa_FieldTargetDataType *pDst) const;

    static OpcUa_FieldTargetDataType* clone(const OpcUa_FieldTargetDataType& source);
    static void cloneTo(const OpcUa_FieldTargetDataType& source, OpcUa_FieldTargetDataType& copy);

    void attach(OpcUa_FieldTargetDataType *pValue);
    OpcUa_FieldTargetDataType* detach(OpcUa_FieldTargetDataType* pDst);

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    void toExtensionObject(UaExtensionObject &extensionObject) const;
    void toExtensionObject(OpcUa_ExtensionObject &extensionObject) const;
    void toExtensionObject(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    void toExtensionObject(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    OpcUa_StatusCode setFieldTargetDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setFieldTargetDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setFieldTargetDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setFieldTargetDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setFieldTargetDataType(
        const UaGuid& dataSetFieldId,
        const UaString& receiverIndexRange,
        const UaNodeId& targetNodeId,
        OpcUa_UInt32 attributeId,
        const UaString& writeIndexRange,
        OpcUa_OverrideValueHandling overrideValueHandling,
        const UaVariant&overrideValue
        );

    UaGuid getDataSetFieldId() const;
    UaString getReceiverIndexRange() const;
    UaNodeId getTargetNodeId() const;
    OpcUa_UInt32 getAttributeId() const;
    UaString getWriteIndexRange() const;
    OpcUa_OverrideValueHandling getOverrideValueHandling() const;
    UaVariant getOverrideValue() const;

    void setDataSetFieldId(const UaGuid& dataSetFieldId);
    void setReceiverIndexRange(const UaString& receiverIndexRange);
    void setTargetNodeId(const UaNodeId& targetNodeId);
    void setAttributeId(OpcUa_UInt32 attributeId);
    void setWriteIndexRange(const UaString& writeIndexRange);
    void setOverrideValueHandling(OpcUa_OverrideValueHandling overrideValueHandling);
    void setOverrideValue(const UaVariant&overrideValue);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_FieldTargetDataType.
 *
 *  This class encapsulates an array of the native OpcUa_FieldTargetDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaFieldTargetDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaFieldTargetDataTypes
{
public:
    UaFieldTargetDataTypes();
    UaFieldTargetDataTypes(const UaFieldTargetDataTypes &other);
    UaFieldTargetDataTypes(OpcUa_Int32 length, OpcUa_FieldTargetDataType* data);
    virtual ~UaFieldTargetDataTypes();

    UaFieldTargetDataTypes& operator=(const UaFieldTargetDataTypes &other);
    const OpcUa_FieldTargetDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_FieldTargetDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaFieldTargetDataTypes &other) const;
    bool operator!=(const UaFieldTargetDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_FieldTargetDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_FieldTargetDataType* data);
    OpcUa_FieldTargetDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_FieldTargetDataType* rawData() const {return m_data;}
    inline OpcUa_FieldTargetDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setFieldTargetDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setFieldTargetDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setFieldTargetDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setFieldTargetDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setFieldTargetDataTypes(OpcUa_Int32 length, OpcUa_FieldTargetDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_FieldTargetDataType* m_data;
};

#endif // UAFIELDTARGETDATATYPE_H

