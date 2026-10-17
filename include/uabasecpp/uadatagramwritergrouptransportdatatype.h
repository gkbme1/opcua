/******************************************************************************
** uadatagramwritergrouptransportdatatype.h
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
** Portable UaDatagramWriterGroupTransportDataType class.
**
******************************************************************************/
#ifndef UADATAGRAMWRITERGROUPTRANSPORTDATATYPE_H
#define UADATAGRAMWRITERGROUPTRANSPORTDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaDatagramWriterGroupTransportDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_DatagramWriterGroupTransportDataType.
 *
 *  This class encapsulates the native OpcUa_DatagramWriterGroupTransportDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaDatagramWriterGroupTransportDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared DatagramWriterGroupTransportDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaDatagramWriterGroupTransportDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaDatagramWriterGroupTransportDataType
{
    UA_DECLARE_PRIVATE(UaDatagramWriterGroupTransportDataType)
public:
    UaDatagramWriterGroupTransportDataType();
    UaDatagramWriterGroupTransportDataType(const UaDatagramWriterGroupTransportDataType &other);
    UaDatagramWriterGroupTransportDataType(const OpcUa_DatagramWriterGroupTransportDataType &other);
    UaDatagramWriterGroupTransportDataType(
        OpcUa_Byte messageRepeatCount,
        OpcUa_Double messageRepeatDelay
        );
    UaDatagramWriterGroupTransportDataType(const UaExtensionObject &extensionObject);
    UaDatagramWriterGroupTransportDataType(const OpcUa_ExtensionObject &extensionObject);
    UaDatagramWriterGroupTransportDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaDatagramWriterGroupTransportDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaDatagramWriterGroupTransportDataType();

    void clear();

    bool operator==(const UaDatagramWriterGroupTransportDataType &other) const;
    bool operator!=(const UaDatagramWriterGroupTransportDataType &other) const;

    UaDatagramWriterGroupTransportDataType& operator=(const UaDatagramWriterGroupTransportDataType &other);

    OpcUa_DatagramWriterGroupTransportDataType* copy() const;
    void copyTo(OpcUa_DatagramWriterGroupTransportDataType *pDst) const;

    static OpcUa_DatagramWriterGroupTransportDataType* clone(const OpcUa_DatagramWriterGroupTransportDataType& source);
    static void cloneTo(const OpcUa_DatagramWriterGroupTransportDataType& source, OpcUa_DatagramWriterGroupTransportDataType& copy);

    void attach(OpcUa_DatagramWriterGroupTransportDataType *pValue);
    OpcUa_DatagramWriterGroupTransportDataType* detach(OpcUa_DatagramWriterGroupTransportDataType* pDst);

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

    OpcUa_StatusCode setDatagramWriterGroupTransportDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setDatagramWriterGroupTransportDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setDatagramWriterGroupTransportDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDatagramWriterGroupTransportDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setDatagramWriterGroupTransportDataType(
        OpcUa_Byte messageRepeatCount,
        OpcUa_Double messageRepeatDelay
        );

    OpcUa_Byte getMessageRepeatCount() const;
    OpcUa_Double getMessageRepeatDelay() const;

    void setMessageRepeatCount(OpcUa_Byte messageRepeatCount);
    void setMessageRepeatDelay(OpcUa_Double messageRepeatDelay);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_DatagramWriterGroupTransportDataType.
 *
 *  This class encapsulates an array of the native OpcUa_DatagramWriterGroupTransportDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaDatagramWriterGroupTransportDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaDatagramWriterGroupTransportDataTypes
{
public:
    UaDatagramWriterGroupTransportDataTypes();
    UaDatagramWriterGroupTransportDataTypes(const UaDatagramWriterGroupTransportDataTypes &other);
    UaDatagramWriterGroupTransportDataTypes(OpcUa_Int32 length, OpcUa_DatagramWriterGroupTransportDataType* data);
    virtual ~UaDatagramWriterGroupTransportDataTypes();

    UaDatagramWriterGroupTransportDataTypes& operator=(const UaDatagramWriterGroupTransportDataTypes &other);
    const OpcUa_DatagramWriterGroupTransportDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_DatagramWriterGroupTransportDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaDatagramWriterGroupTransportDataTypes &other) const;
    bool operator!=(const UaDatagramWriterGroupTransportDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_DatagramWriterGroupTransportDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_DatagramWriterGroupTransportDataType* data);
    OpcUa_DatagramWriterGroupTransportDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_DatagramWriterGroupTransportDataType* rawData() const {return m_data;}
    inline OpcUa_DatagramWriterGroupTransportDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setDatagramWriterGroupTransportDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setDatagramWriterGroupTransportDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setDatagramWriterGroupTransportDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDatagramWriterGroupTransportDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setDatagramWriterGroupTransportDataTypes(OpcUa_Int32 length, OpcUa_DatagramWriterGroupTransportDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_DatagramWriterGroupTransportDataType* m_data;
};

#endif // UADATAGRAMWRITERGROUPTRANSPORTDATATYPE_H

