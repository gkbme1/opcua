/******************************************************************************
** uafieldmetadata.h
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
** Portable UaFieldMetaData class.
**
******************************************************************************/
#ifndef UAFIELDMETADATA_H
#define UAFIELDMETADATA_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaguid.h"
#include "uakeyvaluepair.h"
#include "ualocalizedtext.h"
#include "uanodeid.h"
#include "uastring.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaFieldMetaDataPrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_FieldMetaData.
 *
 *  This class encapsulates the native OpcUa_FieldMetaData structure
 *  and handles memory allocation and cleanup for you.
 *  UaFieldMetaData uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared FieldMetaData it creates a copy for that (copy-on-write).
 *  So assigning another UaFieldMetaData or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaFieldMetaData
{
    UA_DECLARE_PRIVATE(UaFieldMetaData)
public:
    UaFieldMetaData();
    UaFieldMetaData(const UaFieldMetaData &other);
    UaFieldMetaData(const OpcUa_FieldMetaData &other);
    UaFieldMetaData(
        const UaString& name,
        const UaLocalizedText& description,
        OpcUa_DataSetFieldFlags fieldFlags,
        OpcUa_Byte builtInType,
        const UaNodeId& dataType,
        OpcUa_Int32 valueRank,
        const UaUInt32Array &arrayDimensions,
        OpcUa_UInt32 maxStringLength,
        const UaGuid& dataSetFieldId,
        const UaKeyValuePairs &properties
        );
    UaFieldMetaData(const UaExtensionObject &extensionObject);
    UaFieldMetaData(const OpcUa_ExtensionObject &extensionObject);
    UaFieldMetaData(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaFieldMetaData(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaFieldMetaData();

    void clear();

    bool operator==(const UaFieldMetaData &other) const;
    bool operator!=(const UaFieldMetaData &other) const;

    UaFieldMetaData& operator=(const UaFieldMetaData &other);

    OpcUa_FieldMetaData* copy() const;
    void copyTo(OpcUa_FieldMetaData *pDst) const;

    static OpcUa_FieldMetaData* clone(const OpcUa_FieldMetaData& source);
    static void cloneTo(const OpcUa_FieldMetaData& source, OpcUa_FieldMetaData& copy);

    void attach(OpcUa_FieldMetaData *pValue);
    OpcUa_FieldMetaData* detach(OpcUa_FieldMetaData* pDst);

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

    OpcUa_StatusCode setFieldMetaData(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setFieldMetaData(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setFieldMetaData(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setFieldMetaData(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setFieldMetaData(
        const UaString& name,
        const UaLocalizedText& description,
        OpcUa_DataSetFieldFlags fieldFlags,
        OpcUa_Byte builtInType,
        const UaNodeId& dataType,
        OpcUa_Int32 valueRank,
        const UaUInt32Array &arrayDimensions,
        OpcUa_UInt32 maxStringLength,
        const UaGuid& dataSetFieldId,
        const UaKeyValuePairs &properties
        );

    UaString getName() const;
    UaLocalizedText getDescription() const;
    OpcUa_DataSetFieldFlags getFieldFlags() const;
    OpcUa_Byte getBuiltInType() const;
    UaNodeId getDataType() const;
    OpcUa_Int32 getValueRank() const;
    void getArrayDimensions(UaUInt32Array& arrayDimensions) const;
    OpcUa_UInt32 getMaxStringLength() const;
    UaGuid getDataSetFieldId() const;
    void getProperties(UaKeyValuePairs& properties) const;

    void setName(const UaString& name);
    void setDescription(const UaLocalizedText& description);
    void setFieldFlags(OpcUa_DataSetFieldFlags fieldFlags);
    void setBuiltInType(OpcUa_Byte builtInType);
    void setDataType(const UaNodeId& dataType);
    void setValueRank(OpcUa_Int32 valueRank);
    void setArrayDimensions(const UaUInt32Array &arrayDimensions);
    void setMaxStringLength(OpcUa_UInt32 maxStringLength);
    void setDataSetFieldId(const UaGuid& dataSetFieldId);
    void setProperties(const UaKeyValuePairs &properties);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_FieldMetaData.
 *
 *  This class encapsulates an array of the native OpcUa_FieldMetaData structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaFieldMetaData for information about the encapsulated structure.
 */
class UABASE_EXPORT UaFieldMetaDatas
{
public:
    UaFieldMetaDatas();
    UaFieldMetaDatas(const UaFieldMetaDatas &other);
    UaFieldMetaDatas(OpcUa_Int32 length, OpcUa_FieldMetaData* data);
    virtual ~UaFieldMetaDatas();

    UaFieldMetaDatas& operator=(const UaFieldMetaDatas &other);
    const OpcUa_FieldMetaData& operator[](OpcUa_UInt32 index) const;
    OpcUa_FieldMetaData& operator[](OpcUa_UInt32 index);

    bool operator==(const UaFieldMetaDatas &other) const;
    bool operator!=(const UaFieldMetaDatas &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_FieldMetaData* data);
    void attach(OpcUa_Int32 length, OpcUa_FieldMetaData* data);
    OpcUa_FieldMetaData* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_FieldMetaData* rawData() const {return m_data;}
    inline OpcUa_FieldMetaData* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setFieldMetaDatas(const UaVariant &variant);
    OpcUa_StatusCode setFieldMetaDatas(const OpcUa_Variant &variant);
    OpcUa_StatusCode setFieldMetaDatas(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setFieldMetaDatas(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setFieldMetaDatas(OpcUa_Int32 length, OpcUa_FieldMetaData* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_FieldMetaData* m_data;
};

#endif // UAFIELDMETADATA_H

