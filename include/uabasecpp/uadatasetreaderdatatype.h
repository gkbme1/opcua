/******************************************************************************
** uadatasetreaderdatatype.h
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
** Portable UaDataSetReaderDataType class.
**
******************************************************************************/
#ifndef UADATASETREADERDATATYPE_H
#define UADATASETREADERDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uadatasetmetadatatype.h"
#include "uaendpointdescription.h"
#include "uaextensionobject.h"
#include "uakeyvaluepair.h"
#include "uastring.h"
#include "uavariant.h"
#include "uaarraytemplates.h"

class UaDataValue;

class UABASE_EXPORT UaDataSetReaderDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_DataSetReaderDataType.
 *
 *  This class encapsulates the native OpcUa_DataSetReaderDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaDataSetReaderDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared DataSetReaderDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaDataSetReaderDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaDataSetReaderDataType
{
    UA_DECLARE_PRIVATE(UaDataSetReaderDataType)
public:
    UaDataSetReaderDataType();
    UaDataSetReaderDataType(const UaDataSetReaderDataType &other);
    UaDataSetReaderDataType(const OpcUa_DataSetReaderDataType &other);
    UaDataSetReaderDataType(
        const UaString& name,
        OpcUa_Boolean enabled,
        const UaVariant&publisherId,
        OpcUa_UInt16 writerGroupId,
        OpcUa_UInt16 dataSetWriterId,
        const UaDataSetMetaDataType& dataSetMetaData,
        OpcUa_DataSetFieldContentMask dataSetFieldContentMask,
        OpcUa_Double messageReceiveTimeout,
        OpcUa_UInt32 keyFrameCount,
        const UaString& headerLayoutUri,
        OpcUa_MessageSecurityMode securityMode,
        const UaString& securityGroupId,
        const UaEndpointDescriptions &securityKeyServices,
        const UaKeyValuePairs &dataSetReaderProperties,
        UaExtensionObject& transportSettings,
        UaExtensionObject& messageSettings,
        UaExtensionObject& subscribedDataSet
        );
    UaDataSetReaderDataType(const UaExtensionObject &extensionObject);
    UaDataSetReaderDataType(const OpcUa_ExtensionObject &extensionObject);
    UaDataSetReaderDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaDataSetReaderDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaDataSetReaderDataType();

    void clear();

    bool operator==(const UaDataSetReaderDataType &other) const;
    bool operator!=(const UaDataSetReaderDataType &other) const;

    UaDataSetReaderDataType& operator=(const UaDataSetReaderDataType &other);

    OpcUa_DataSetReaderDataType* copy() const;
    void copyTo(OpcUa_DataSetReaderDataType *pDst) const;

    static OpcUa_DataSetReaderDataType* clone(const OpcUa_DataSetReaderDataType& source);
    static void cloneTo(const OpcUa_DataSetReaderDataType& source, OpcUa_DataSetReaderDataType& copy);

    void attach(OpcUa_DataSetReaderDataType *pValue);
    OpcUa_DataSetReaderDataType* detach(OpcUa_DataSetReaderDataType* pDst);

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

    OpcUa_StatusCode setDataSetReaderDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setDataSetReaderDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setDataSetReaderDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDataSetReaderDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setDataSetReaderDataType(
        const UaString& name,
        OpcUa_Boolean enabled,
        const UaVariant&publisherId,
        OpcUa_UInt16 writerGroupId,
        OpcUa_UInt16 dataSetWriterId,
        const UaDataSetMetaDataType& dataSetMetaData,
        OpcUa_DataSetFieldContentMask dataSetFieldContentMask,
        OpcUa_Double messageReceiveTimeout,
        OpcUa_UInt32 keyFrameCount,
        const UaString& headerLayoutUri,
        OpcUa_MessageSecurityMode securityMode,
        const UaString& securityGroupId,
        const UaEndpointDescriptions &securityKeyServices,
        const UaKeyValuePairs &dataSetReaderProperties,
        UaExtensionObject& transportSettings,
        UaExtensionObject& messageSettings,
        UaExtensionObject& subscribedDataSet
        );

    UaString getName() const;
    OpcUa_Boolean getEnabled() const;
    UaVariant getPublisherId() const;
    OpcUa_UInt16 getWriterGroupId() const;
    OpcUa_UInt16 getDataSetWriterId() const;
    UaDataSetMetaDataType getDataSetMetaData() const;
    OpcUa_DataSetFieldContentMask getDataSetFieldContentMask() const;
    OpcUa_Double getMessageReceiveTimeout() const;
    OpcUa_UInt32 getKeyFrameCount() const;
    UaString getHeaderLayoutUri() const;
    OpcUa_MessageSecurityMode getSecurityMode() const;
    UaString getSecurityGroupId() const;
    void getSecurityKeyServices(UaEndpointDescriptions& securityKeyServices) const;
    void getDataSetReaderProperties(UaKeyValuePairs& dataSetReaderProperties) const;
    UaExtensionObject getTransportSettings() const;
    UaExtensionObject getMessageSettings() const;
    UaExtensionObject getSubscribedDataSet() const;

    void setName(const UaString& name);
    void setEnabled(OpcUa_Boolean enabled);
    void setPublisherId(const UaVariant&publisherId);
    void setWriterGroupId(OpcUa_UInt16 writerGroupId);
    void setDataSetWriterId(OpcUa_UInt16 dataSetWriterId);
    void setDataSetMetaData(const UaDataSetMetaDataType& dataSetMetaData);
    void setDataSetFieldContentMask(OpcUa_DataSetFieldContentMask dataSetFieldContentMask);
    void setMessageReceiveTimeout(OpcUa_Double messageReceiveTimeout);
    void setKeyFrameCount(OpcUa_UInt32 keyFrameCount);
    void setHeaderLayoutUri(const UaString& headerLayoutUri);
    void setSecurityMode(OpcUa_MessageSecurityMode securityMode);
    void setSecurityGroupId(const UaString& securityGroupId);
    void setSecurityKeyServices(const UaEndpointDescriptions &securityKeyServices);
    void setDataSetReaderProperties(const UaKeyValuePairs &dataSetReaderProperties);
    void setTransportSettings(UaExtensionObject& transportSettings);
    void setMessageSettings(UaExtensionObject& messageSettings);
    void setSubscribedDataSet(UaExtensionObject& subscribedDataSet);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_DataSetReaderDataType.
 *
 *  This class encapsulates an array of the native OpcUa_DataSetReaderDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaDataSetReaderDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaDataSetReaderDataTypes
{
public:
    UaDataSetReaderDataTypes();
    UaDataSetReaderDataTypes(const UaDataSetReaderDataTypes &other);
    UaDataSetReaderDataTypes(OpcUa_Int32 length, OpcUa_DataSetReaderDataType* data);
    virtual ~UaDataSetReaderDataTypes();

    UaDataSetReaderDataTypes& operator=(const UaDataSetReaderDataTypes &other);
    const OpcUa_DataSetReaderDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_DataSetReaderDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaDataSetReaderDataTypes &other) const;
    bool operator!=(const UaDataSetReaderDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_DataSetReaderDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_DataSetReaderDataType* data);
    OpcUa_DataSetReaderDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_DataSetReaderDataType* rawData() const {return m_data;}
    inline OpcUa_DataSetReaderDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setDataSetReaderDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setDataSetReaderDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setDataSetReaderDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDataSetReaderDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDataSetReaderDataTypes(OpcUa_Int32 length, OpcUa_DataSetReaderDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_DataSetReaderDataType* m_data;
};

#endif // UADATASETREADERDATATYPE_H

