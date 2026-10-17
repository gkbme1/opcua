/******************************************************************************
** uajsondatasetwritermessagedatatype.h
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
** Portable UaJsonDataSetWriterMessageDataType class.
**
******************************************************************************/
#ifndef UAJSONDATASETWRITERMESSAGEDATATYPE_H
#define UAJSONDATASETWRITERMESSAGEDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaJsonDataSetWriterMessageDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_JsonDataSetWriterMessageDataType.
 *
 *  This class encapsulates the native OpcUa_JsonDataSetWriterMessageDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaJsonDataSetWriterMessageDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared JsonDataSetWriterMessageDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaJsonDataSetWriterMessageDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaJsonDataSetWriterMessageDataType
{
    UA_DECLARE_PRIVATE(UaJsonDataSetWriterMessageDataType)
public:
    UaJsonDataSetWriterMessageDataType();
    UaJsonDataSetWriterMessageDataType(const UaJsonDataSetWriterMessageDataType &other);
    UaJsonDataSetWriterMessageDataType(const OpcUa_JsonDataSetWriterMessageDataType &other);
    UaJsonDataSetWriterMessageDataType(
        OpcUa_JsonDataSetMessageContentMask dataSetMessageContentMask
        );
    UaJsonDataSetWriterMessageDataType(const UaExtensionObject &extensionObject);
    UaJsonDataSetWriterMessageDataType(const OpcUa_ExtensionObject &extensionObject);
    UaJsonDataSetWriterMessageDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaJsonDataSetWriterMessageDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaJsonDataSetWriterMessageDataType();

    void clear();

    bool operator==(const UaJsonDataSetWriterMessageDataType &other) const;
    bool operator!=(const UaJsonDataSetWriterMessageDataType &other) const;

    UaJsonDataSetWriterMessageDataType& operator=(const UaJsonDataSetWriterMessageDataType &other);

    OpcUa_JsonDataSetWriterMessageDataType* copy() const;
    void copyTo(OpcUa_JsonDataSetWriterMessageDataType *pDst) const;

    static OpcUa_JsonDataSetWriterMessageDataType* clone(const OpcUa_JsonDataSetWriterMessageDataType& source);
    static void cloneTo(const OpcUa_JsonDataSetWriterMessageDataType& source, OpcUa_JsonDataSetWriterMessageDataType& copy);

    void attach(OpcUa_JsonDataSetWriterMessageDataType *pValue);
    OpcUa_JsonDataSetWriterMessageDataType* detach(OpcUa_JsonDataSetWriterMessageDataType* pDst);

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

    OpcUa_StatusCode setJsonDataSetWriterMessageDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setJsonDataSetWriterMessageDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setJsonDataSetWriterMessageDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setJsonDataSetWriterMessageDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setJsonDataSetWriterMessageDataType(
        OpcUa_JsonDataSetMessageContentMask dataSetMessageContentMask
        );

    OpcUa_JsonDataSetMessageContentMask getDataSetMessageContentMask() const;

    void setDataSetMessageContentMask(OpcUa_JsonDataSetMessageContentMask dataSetMessageContentMask);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_JsonDataSetWriterMessageDataType.
 *
 *  This class encapsulates an array of the native OpcUa_JsonDataSetWriterMessageDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaJsonDataSetWriterMessageDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaJsonDataSetWriterMessageDataTypes
{
public:
    UaJsonDataSetWriterMessageDataTypes();
    UaJsonDataSetWriterMessageDataTypes(const UaJsonDataSetWriterMessageDataTypes &other);
    UaJsonDataSetWriterMessageDataTypes(OpcUa_Int32 length, OpcUa_JsonDataSetWriterMessageDataType* data);
    virtual ~UaJsonDataSetWriterMessageDataTypes();

    UaJsonDataSetWriterMessageDataTypes& operator=(const UaJsonDataSetWriterMessageDataTypes &other);
    const OpcUa_JsonDataSetWriterMessageDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_JsonDataSetWriterMessageDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaJsonDataSetWriterMessageDataTypes &other) const;
    bool operator!=(const UaJsonDataSetWriterMessageDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_JsonDataSetWriterMessageDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_JsonDataSetWriterMessageDataType* data);
    OpcUa_JsonDataSetWriterMessageDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_JsonDataSetWriterMessageDataType* rawData() const {return m_data;}
    inline OpcUa_JsonDataSetWriterMessageDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setJsonDataSetWriterMessageDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setJsonDataSetWriterMessageDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setJsonDataSetWriterMessageDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setJsonDataSetWriterMessageDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setJsonDataSetWriterMessageDataTypes(OpcUa_Int32 length, OpcUa_JsonDataSetWriterMessageDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_JsonDataSetWriterMessageDataType* m_data;
};

#endif // UAJSONDATASETWRITERMESSAGEDATATYPE_H

