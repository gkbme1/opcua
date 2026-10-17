/******************************************************************************
** opcuadi_transferresulterrordatatype.h
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
** Project: C++ OPC Server SDK information model for namespace http://opcfoundation.org/UA/DI/
**
** Description: OPC Unified Architecture Software Development Kit.
**
******************************************************************************/


#ifndef __OPCUADI_TRANSFERRESULTERRORDATATYPE_H__
#define __OPCUADI_TRANSFERRESULTERRORDATATYPE_H__

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaarraytemplates.h"
#include "opcuadi_identifiers.h"
#include "opcuadi_datatypes.h"

class UaExtensionObject;
class UaVariant;
class UaDataValue;

// Namespace for the UA information model http://opcfoundation.org/UA/DI/
namespace OpcUaDi {

class UAMODELS_EXPORT TransferResultErrorDataTypePrivate;

/**
 *  @brief Wrapper class for the UA stack structure OpcUaDi_TransferResultErrorDataType.
 *
 *  This class encapsulates the native OpcUaDi_TransferResultErrorDataType structure
 *  and handles memory allocation and cleanup for you.
 *  TransferResultErrorDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared TransferResultErrorDataType it creates a copy for that (copy-on-write).
 *  So assigning another TransferResultErrorDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UAMODELS_EXPORT TransferResultErrorDataType
{
    OPCUADI_DECLARE_PRIVATE(TransferResultErrorDataType)
public:
    TransferResultErrorDataType();
    TransferResultErrorDataType(const TransferResultErrorDataType &other);
    TransferResultErrorDataType(const OpcUaDi_TransferResultErrorDataType &other);
    TransferResultErrorDataType(
        OpcUa_Int32 Status,
        const OpcUa_DiagnosticInfo& Diagnostics
        );
    TransferResultErrorDataType(const UaExtensionObject &extensionObject);
    TransferResultErrorDataType(const OpcUa_ExtensionObject &extensionObject);
    TransferResultErrorDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    TransferResultErrorDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~TransferResultErrorDataType();

    void clear();

    bool operator==(const TransferResultErrorDataType &other) const;
    bool operator!=(const TransferResultErrorDataType &other) const;

    TransferResultErrorDataType& operator=(const TransferResultErrorDataType &other);

    OpcUaDi_TransferResultErrorDataType* copy() const;
    void copyTo(OpcUaDi_TransferResultErrorDataType *pDst) const;

    static OpcUaDi_TransferResultErrorDataType* clone(const OpcUaDi_TransferResultErrorDataType& source);
    static void cloneTo(const OpcUaDi_TransferResultErrorDataType& source, OpcUaDi_TransferResultErrorDataType& copy);

    void attach(const OpcUaDi_TransferResultErrorDataType *pValue);
    OpcUaDi_TransferResultErrorDataType* detach(OpcUaDi_TransferResultErrorDataType* pDst);

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

    OpcUa_StatusCode setTransferResultErrorDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setTransferResultErrorDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setTransferResultErrorDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setTransferResultErrorDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setTransferResultErrorDataType(
        OpcUa_Int32 Status,
        const OpcUa_DiagnosticInfo& Diagnostics
        );

    OpcUa_Int32 getStatus() const;
    OpcUa_DiagnosticInfo getDiagnostics() const;

    void setStatus(OpcUa_Int32 Status);
    void setDiagnostics(const OpcUa_DiagnosticInfo& Diagnostics);
};

class TransferResultErrorDataTypes
{
public:
    TransferResultErrorDataTypes();
    TransferResultErrorDataTypes(const TransferResultErrorDataTypes &other);
    TransferResultErrorDataTypes(OpcUa_Int32 length, OpcUaDi_TransferResultErrorDataType* data);
    virtual ~TransferResultErrorDataTypes();

    TransferResultErrorDataTypes& operator=(const TransferResultErrorDataTypes &other);
    OpcUaDi_TransferResultErrorDataType& operator[](OpcUa_UInt32 index);
    const OpcUaDi_TransferResultErrorDataType& operator[](OpcUa_UInt32 index) const;

    void attach(OpcUa_UInt32 length, OpcUaDi_TransferResultErrorDataType* data);
    void attach(OpcUa_Int32 length, OpcUaDi_TransferResultErrorDataType* data);
    OpcUaDi_TransferResultErrorDataType* detach();

    bool operator==(const TransferResultErrorDataTypes &other) const;
    bool operator!=(const TransferResultErrorDataTypes &other) const;

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUaDi_TransferResultErrorDataType* rawData() const {return m_data;}
    inline OpcUaDi_TransferResultErrorDataType* rawData() {return m_data;}
    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setTransferResultErrorDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setTransferResultErrorDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setTransferResultErrorDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setTransferResultErrorDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setTransferResultErrorDataTypes(OpcUa_Int32 length, OpcUaDi_TransferResultErrorDataType* data);

    static TransferResultErrorDataTypes empty;
private:
    OpcUa_UInt32 m_noOfElements;
    OpcUaDi_TransferResultErrorDataType* m_data;
};

} // namespace OpcUaDi

#endif // __OPCUADI_TRANSFERRESULTERRORDATATYPE_H__

