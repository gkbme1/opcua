/******************************************************************************
** uadatasetwriterdatatype.h
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
** Portable UaDataSetWriterDataType class.
**
******************************************************************************/
#ifndef UADATASETWRITERDATATYPE_H
#define UADATASETWRITERDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaextensionobject.h"
#include "uakeyvaluepair.h"
#include "uastring.h"
#include "uaarraytemplates.h"

class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaDataSetWriterDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_DataSetWriterDataType.
 *
 *  This class encapsulates the native OpcUa_DataSetWriterDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaDataSetWriterDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared DataSetWriterDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaDataSetWriterDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaDataSetWriterDataType
{
    UA_DECLARE_PRIVATE(UaDataSetWriterDataType)
public:
    UaDataSetWriterDataType();
    UaDataSetWriterDataType(const UaDataSetWriterDataType &other);
    UaDataSetWriterDataType(const OpcUa_DataSetWriterDataType &other);
    UaDataSetWriterDataType(
        const UaString& name,
        OpcUa_Boolean enabled,
        OpcUa_UInt16 dataSetWriterId,
        OpcUa_DataSetFieldContentMask dataSetFieldContentMask,
        OpcUa_UInt32 keyFrameCount,
        const UaString& dataSetName,
        const UaKeyValuePairs &dataSetWriterProperties,
        UaExtensionObject& transportSettings,
        UaExtensionObject& messageSettings
        );
    UaDataSetWriterDataType(const UaExtensionObject &extensionObject);
    UaDataSetWriterDataType(const OpcUa_ExtensionObject &extensionObject);
    UaDataSetWriterDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaDataSetWriterDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaDataSetWriterDataType();

    void clear();

    bool operator==(const UaDataSetWriterDataType &other) const;
    bool operator!=(const UaDataSetWriterDataType &other) const;

    UaDataSetWriterDataType& operator=(const UaDataSetWriterDataType &other);

    OpcUa_DataSetWriterDataType* copy() const;
    void copyTo(OpcUa_DataSetWriterDataType *pDst) const;

    static OpcUa_DataSetWriterDataType* clone(const OpcUa_DataSetWriterDataType& source);
    static void cloneTo(const OpcUa_DataSetWriterDataType& source, OpcUa_DataSetWriterDataType& copy);

    void attach(OpcUa_DataSetWriterDataType *pValue);
    OpcUa_DataSetWriterDataType* detach(OpcUa_DataSetWriterDataType* pDst);

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

    OpcUa_StatusCode setDataSetWriterDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setDataSetWriterDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setDataSetWriterDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDataSetWriterDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setDataSetWriterDataType(
        const UaString& name,
        OpcUa_Boolean enabled,
        OpcUa_UInt16 dataSetWriterId,
        OpcUa_DataSetFieldContentMask dataSetFieldContentMask,
        OpcUa_UInt32 keyFrameCount,
        const UaString& dataSetName,
        const UaKeyValuePairs &dataSetWriterProperties,
        UaExtensionObject& transportSettings,
        UaExtensionObject& messageSettings
        );

    UaString getName() const;
    OpcUa_Boolean getEnabled() const;
    OpcUa_UInt16 getDataSetWriterId() const;
    OpcUa_DataSetFieldContentMask getDataSetFieldContentMask() const;
    OpcUa_UInt32 getKeyFrameCount() const;
    UaString getDataSetName() const;
    void getDataSetWriterProperties(UaKeyValuePairs& dataSetWriterProperties) const;
    UaExtensionObject getTransportSettings() const;
    UaExtensionObject getMessageSettings() const;

    void setName(const UaString& name);
    void setEnabled(OpcUa_Boolean enabled);
    void setDataSetWriterId(OpcUa_UInt16 dataSetWriterId);
    void setDataSetFieldContentMask(OpcUa_DataSetFieldContentMask dataSetFieldContentMask);
    void setKeyFrameCount(OpcUa_UInt32 keyFrameCount);
    void setDataSetName(const UaString& dataSetName);
    void setDataSetWriterProperties(const UaKeyValuePairs &dataSetWriterProperties);
    void setTransportSettings(UaExtensionObject& transportSettings);
    void setMessageSettings(UaExtensionObject& messageSettings);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_DataSetWriterDataType.
 *
 *  This class encapsulates an array of the native OpcUa_DataSetWriterDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaDataSetWriterDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaDataSetWriterDataTypes
{
public:
    UaDataSetWriterDataTypes();
    UaDataSetWriterDataTypes(const UaDataSetWriterDataTypes &other);
    UaDataSetWriterDataTypes(OpcUa_Int32 length, OpcUa_DataSetWriterDataType* data);
    virtual ~UaDataSetWriterDataTypes();

    UaDataSetWriterDataTypes& operator=(const UaDataSetWriterDataTypes &other);
    const OpcUa_DataSetWriterDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_DataSetWriterDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaDataSetWriterDataTypes &other) const;
    bool operator!=(const UaDataSetWriterDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_DataSetWriterDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_DataSetWriterDataType* data);
    OpcUa_DataSetWriterDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_DataSetWriterDataType* rawData() const {return m_data;}
    inline OpcUa_DataSetWriterDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setDataSetWriterDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setDataSetWriterDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setDataSetWriterDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDataSetWriterDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDataSetWriterDataTypes(OpcUa_Int32 length, OpcUa_DataSetWriterDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_DataSetWriterDataType* m_data;
};

#endif // UADATASETWRITERDATATYPE_H

