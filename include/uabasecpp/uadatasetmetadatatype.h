/******************************************************************************
** uadatasetmetadatatype.h
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
** Portable UaDataSetMetaDataType class.
**
******************************************************************************/
#ifndef UADATASETMETADATATYPE_H
#define UADATASETMETADATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaconfigurationversiondatatype.h"
#include "uaenumdescription.h"
#include "uafieldmetadata.h"
#include "uaguid.h"
#include "ualocalizedtext.h"
#include "uasimpletypedescription.h"
#include "uastring.h"
#include "uastructuredescription.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaDataSetMetaDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_DataSetMetaDataType.
 *
 *  This class encapsulates the native OpcUa_DataSetMetaDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaDataSetMetaDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared DataSetMetaDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaDataSetMetaDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaDataSetMetaDataType
{
    UA_DECLARE_PRIVATE(UaDataSetMetaDataType)
public:
    UaDataSetMetaDataType();
    UaDataSetMetaDataType(const UaDataSetMetaDataType &other);
    UaDataSetMetaDataType(const OpcUa_DataSetMetaDataType &other);
    UaDataSetMetaDataType(
        const UaStringArray &namespaces,
        const UaStructureDescriptions &structureDataTypes,
        const UaEnumDescriptions &enumDataTypes,
        const UaSimpleTypeDescriptions &simpleDataTypes,
        const UaString& name,
        const UaLocalizedText& description,
        const UaFieldMetaDatas &fields,
        const UaGuid& dataSetClassId,
        const UaConfigurationVersionDataType& configurationVersion
        );
    UaDataSetMetaDataType(const UaExtensionObject &extensionObject);
    UaDataSetMetaDataType(const OpcUa_ExtensionObject &extensionObject);
    UaDataSetMetaDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaDataSetMetaDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaDataSetMetaDataType();

    void clear();

    bool operator==(const UaDataSetMetaDataType &other) const;
    bool operator!=(const UaDataSetMetaDataType &other) const;

    UaDataSetMetaDataType& operator=(const UaDataSetMetaDataType &other);

    OpcUa_DataSetMetaDataType* copy() const;
    void copyTo(OpcUa_DataSetMetaDataType *pDst) const;

    static OpcUa_DataSetMetaDataType* clone(const OpcUa_DataSetMetaDataType& source);
    static void cloneTo(const OpcUa_DataSetMetaDataType& source, OpcUa_DataSetMetaDataType& copy);

    void attach(OpcUa_DataSetMetaDataType *pValue);
    OpcUa_DataSetMetaDataType* detach(OpcUa_DataSetMetaDataType* pDst);

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

    OpcUa_StatusCode setDataSetMetaDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setDataSetMetaDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setDataSetMetaDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDataSetMetaDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setDataSetMetaDataType(
        const UaStringArray &namespaces,
        const UaStructureDescriptions &structureDataTypes,
        const UaEnumDescriptions &enumDataTypes,
        const UaSimpleTypeDescriptions &simpleDataTypes,
        const UaString& name,
        const UaLocalizedText& description,
        const UaFieldMetaDatas &fields,
        const UaGuid& dataSetClassId,
        const UaConfigurationVersionDataType& configurationVersion
        );

    void getNamespaces(UaStringArray& namespaces) const;
    void getStructureDataTypes(UaStructureDescriptions& structureDataTypes) const;
    void getEnumDataTypes(UaEnumDescriptions& enumDataTypes) const;
    void getSimpleDataTypes(UaSimpleTypeDescriptions& simpleDataTypes) const;
    UaString getName() const;
    UaLocalizedText getDescription() const;
    void getFields(UaFieldMetaDatas& fields) const;
    UaGuid getDataSetClassId() const;
    UaConfigurationVersionDataType getConfigurationVersion() const;

    void setNamespaces(const UaStringArray &namespaces);
    void setStructureDataTypes(const UaStructureDescriptions &structureDataTypes);
    void setEnumDataTypes(const UaEnumDescriptions &enumDataTypes);
    void setSimpleDataTypes(const UaSimpleTypeDescriptions &simpleDataTypes);
    void setName(const UaString& name);
    void setDescription(const UaLocalizedText& description);
    void setFields(const UaFieldMetaDatas &fields);
    void setDataSetClassId(const UaGuid& dataSetClassId);
    void setConfigurationVersion(const UaConfigurationVersionDataType& configurationVersion);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_DataSetMetaDataType.
 *
 *  This class encapsulates an array of the native OpcUa_DataSetMetaDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaDataSetMetaDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaDataSetMetaDataTypes
{
public:
    UaDataSetMetaDataTypes();
    UaDataSetMetaDataTypes(const UaDataSetMetaDataTypes &other);
    UaDataSetMetaDataTypes(OpcUa_Int32 length, OpcUa_DataSetMetaDataType* data);
    virtual ~UaDataSetMetaDataTypes();

    UaDataSetMetaDataTypes& operator=(const UaDataSetMetaDataTypes &other);
    const OpcUa_DataSetMetaDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_DataSetMetaDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaDataSetMetaDataTypes &other) const;
    bool operator!=(const UaDataSetMetaDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_DataSetMetaDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_DataSetMetaDataType* data);
    OpcUa_DataSetMetaDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_DataSetMetaDataType* rawData() const {return m_data;}
    inline OpcUa_DataSetMetaDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setDataSetMetaDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setDataSetMetaDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setDataSetMetaDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDataSetMetaDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDataSetMetaDataTypes(OpcUa_Int32 length, OpcUa_DataSetMetaDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_DataSetMetaDataType* m_data;
};

#endif // UADATASETMETADATATYPE_H

