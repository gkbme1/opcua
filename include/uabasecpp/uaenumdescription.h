/******************************************************************************
** uaenumdescription.h
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
** Portable UaEnumDescription class.
**
******************************************************************************/
#ifndef UAENUMDESCRIPTION_H
#define UAENUMDESCRIPTION_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaenumdefinitiondatatype.h"
#include "uanodeid.h"
#include "uaqualifiedname.h"
#include "uaarraytemplates.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

class UABASE_EXPORT UaEnumDescriptionPrivate;

/** @ingroup CppBaseLibraryClass
 *  @brief Wrapper class for the UA stack structure OpcUa_EnumDescription.
 *
 *  This class encapsulates the native OpcUa_EnumDescription structure
 *  and handles memory allocation and cleanup for you.
 *  UaEnumDescription uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared EnumDescription it creates a copy for that (copy-on-write).
 *  So assigning another UaEnumDescription or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UABASE_EXPORT UaEnumDescription
{
    UA_DECLARE_PRIVATE(UaEnumDescription)
public:
    UaEnumDescription();
    UaEnumDescription(const UaEnumDescription &other);
    UaEnumDescription(const OpcUa_EnumDescription &other);
    UaEnumDescription(
        const UaNodeId& dataTypeId,
        const UaQualifiedName& name,
        const UaEnumDefinitionDataType& enumDefinition,
        OpcUa_Byte builtInType
        );
    UaEnumDescription(const UaExtensionObject &extensionObject);
    UaEnumDescription(const OpcUa_ExtensionObject &extensionObject);
    UaEnumDescription(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    UaEnumDescription(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~UaEnumDescription();

    void clear();

    bool operator==(const UaEnumDescription &other) const;
    bool operator!=(const UaEnumDescription &other) const;

    UaEnumDescription& operator=(const UaEnumDescription &other);

    OpcUa_EnumDescription* copy() const;
    void copyTo(OpcUa_EnumDescription *pDst) const;

    static OpcUa_EnumDescription* clone(const OpcUa_EnumDescription& source);
    static void cloneTo(const OpcUa_EnumDescription& source, OpcUa_EnumDescription& copy);

    void attach(OpcUa_EnumDescription *pValue);
    OpcUa_EnumDescription* detach(OpcUa_EnumDescription* pDst);

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

    OpcUa_StatusCode setEnumDescription(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setEnumDescription(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setEnumDescription(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEnumDescription(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setEnumDescription(
        const UaNodeId& dataTypeId,
        const UaQualifiedName& name,
        const UaEnumDefinitionDataType& enumDefinition,
        OpcUa_Byte builtInType
        );

    UaNodeId getDataTypeId() const;
    UaQualifiedName getName() const;
    UaEnumDefinitionDataType getEnumDefinition() const;
    OpcUa_Byte getBuiltInType() const;

    void setDataTypeId(const UaNodeId& dataTypeId);
    void setName(const UaQualifiedName& name);
    void setEnumDefinition(const UaEnumDefinitionDataType& enumDefinition);
    void setBuiltInType(OpcUa_Byte builtInType);
};

/** @ingroup CppBaseLibraryClass
 *  @brief Array class for the UA stack structure OpcUa_EnumDescription.
 *
 *  This class encapsulates an array of the native OpcUa_EnumDescription structure
 *  and handles memory allocation and cleanup for you.
 *  @see UaEnumDescription for information about the encapsulated structure.
 */
class UABASE_EXPORT UaEnumDescriptions
{
public:
    UaEnumDescriptions();
    UaEnumDescriptions(const UaEnumDescriptions &other);
    UaEnumDescriptions(OpcUa_Int32 length, OpcUa_EnumDescription* data);
    virtual ~UaEnumDescriptions();

    UaEnumDescriptions& operator=(const UaEnumDescriptions &other);
    const OpcUa_EnumDescription& operator[](OpcUa_UInt32 index) const;
    OpcUa_EnumDescription& operator[](OpcUa_UInt32 index);

    bool operator==(const UaEnumDescriptions &other) const;
    bool operator!=(const UaEnumDescriptions &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_EnumDescription* data);
    void attach(OpcUa_Int32 length, OpcUa_EnumDescription* data);
    OpcUa_EnumDescription* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUa_EnumDescription* rawData() const {return m_data;}
    inline OpcUa_EnumDescription* rawData() {return m_data;}

    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setEnumDescriptions(const UaVariant &variant);
    OpcUa_StatusCode setEnumDescriptions(const OpcUa_Variant &variant);
    OpcUa_StatusCode setEnumDescriptions(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEnumDescriptions(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setEnumDescriptions(OpcUa_Int32 length, OpcUa_EnumDescription* data);

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_EnumDescription* m_data;
};

#endif // UAENUMDESCRIPTION_H

