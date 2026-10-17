/******************************************************************************
** uaconfigurationversiondatatype.h
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
** Portable UaConfigurationVersionDataType class.
**
******************************************************************************/
#ifndef UACONFIGURATIONVERSIONDATATYPE_H
#define UACONFIGURATIONVERSIONDATATYPE_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaConfigurationVersionDataTypePrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_ConfigurationVersionDataType.
 *
 *  This class encapsulates the native OpcUa_ConfigurationVersionDataType structure
 *  and handles memory allocation and cleanup for you.
 *  UaConfigurationVersionDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared ConfigurationVersionDataType it creates a copy for that (copy-on-write).
 *  So assigning another UaConfigurationVersionDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaConfigurationVersionDataType
{
    UA_DECLARE_PRIVATE(UaConfigurationVersionDataType)
public:
    UaConfigurationVersionDataType();
    UaConfigurationVersionDataType(const UaConfigurationVersionDataType &other);
    UaConfigurationVersionDataType(const OpcUa_ConfigurationVersionDataType &other);
    UaConfigurationVersionDataType(
        OpcUa_UInt32 majorVersion,
        OpcUa_UInt32 minorVersion
        );
    UaConfigurationVersionDataType(const UaExtensionObject &extensionObject);
    UaConfigurationVersionDataType(const OpcUa_ExtensionObject &extensionObject);
    UaConfigurationVersionDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaConfigurationVersionDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaConfigurationVersionDataType();

    void clear();

    bool operator==(const UaConfigurationVersionDataType &other) const;
    bool operator!=(const UaConfigurationVersionDataType &other) const;

    UaConfigurationVersionDataType& operator=(const UaConfigurationVersionDataType &other);

    OpcUa_ConfigurationVersionDataType* copy() const;
    void copyTo(OpcUa_ConfigurationVersionDataType *pDst) const;

    static OpcUa_ConfigurationVersionDataType* clone(const OpcUa_ConfigurationVersionDataType& source);
    static void cloneTo(const OpcUa_ConfigurationVersionDataType& source, OpcUa_ConfigurationVersionDataType& copy);

    void attach(OpcUa_ConfigurationVersionDataType *pValue);
    OpcUa_ConfigurationVersionDataType* detach(OpcUa_ConfigurationVersionDataType* pDst);

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

    OpcUa_StatusCode setConfigurationVersionDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setConfigurationVersionDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setConfigurationVersionDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setConfigurationVersionDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setConfigurationVersionDataType(
        OpcUa_UInt32 majorVersion,
        OpcUa_UInt32 minorVersion
        );

    OpcUa_UInt32 getMajorVersion() const;
    OpcUa_UInt32 getMinorVersion() const;

    void setMajorVersion(OpcUa_UInt32 majorVersion);
    void setMinorVersion(OpcUa_UInt32 minorVersion);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_ConfigurationVersionDataType.
 *
 *  This class encapsulates an array of the native OpcUa_ConfigurationVersionDataType structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaConfigurationVersionDataType for information about the encapsulated structure.
 */
class UABASE_EXPORT UaConfigurationVersionDataTypes
{
public:
    UaConfigurationVersionDataTypes();
    UaConfigurationVersionDataTypes(const UaConfigurationVersionDataTypes &other);
    UaConfigurationVersionDataTypes(OpcUa_Int32 length, OpcUa_ConfigurationVersionDataType* data);
    virtual ~UaConfigurationVersionDataTypes();

    UaConfigurationVersionDataTypes& operator=(const UaConfigurationVersionDataTypes &other);
    const OpcUa_ConfigurationVersionDataType& operator[](OpcUa_UInt32 index) const;
    OpcUa_ConfigurationVersionDataType& operator[](OpcUa_UInt32 index);

    bool operator==(const UaConfigurationVersionDataTypes &other) const;
    bool operator!=(const UaConfigurationVersionDataTypes &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_ConfigurationVersionDataType* data);
    void attach(OpcUa_Int32 length, OpcUa_ConfigurationVersionDataType* data);
    OpcUa_ConfigurationVersionDataType* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_ConfigurationVersionDataType* rawData() const {return m_data;}
    inline OpcUa_ConfigurationVersionDataType* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setConfigurationVersionDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setConfigurationVersionDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setConfigurationVersionDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setConfigurationVersionDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setConfigurationVersionDataTypes(OpcUa_Int32 length, OpcUa_ConfigurationVersionDataType* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_ConfigurationVersionDataType* m_data;
};

#endif // UACONFIGURATIONVERSIONDATATYPE_H

