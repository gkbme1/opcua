/******************************************************************************
** opcuadi_transferresultdatadatatype.h
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


#ifndef __OPCUADI_TRANSFERRESULTDATADATATYPE_H__
#define __OPCUADI_TRANSFERRESULTDATADATATYPE_H__

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

class UAMODELS_EXPORT TransferResultDataDataTypePrivate;
class UAMODELS_EXPORT ParameterResultDataTypes;

/**
 *  @brief Wrapper class for the UA stack structure OpcUaDi_TransferResultDataDataType.
 *
 *  This class encapsulates the native OpcUaDi_TransferResultDataDataType structure
 *  and handles memory allocation and cleanup for you.
 *  TransferResultDataDataType uses implicit sharing to avoid needless copying and to boost the performance.
 *  Only if you modify a shared TransferResultDataDataType it creates a copy for that (copy-on-write).
 *  So assigning another TransferResultDataDataType or passing it as parameter needs constant time and is nearly as fast as assigning a pointer.
 */
class UAMODELS_EXPORT TransferResultDataDataType
{
    OPCUADI_DECLARE_PRIVATE(TransferResultDataDataType)
public:
    TransferResultDataDataType();
    TransferResultDataDataType(const TransferResultDataDataType &other);
    TransferResultDataDataType(const OpcUaDi_TransferResultDataDataType &other);
    TransferResultDataDataType(
        OpcUa_Int32 SequenceNumber,
        OpcUa_Boolean EndOfResults,
        const OpcUaDi::ParameterResultDataTypes& ParameterDefs
        );
    TransferResultDataDataType(const UaExtensionObject &extensionObject);
    TransferResultDataDataType(const OpcUa_ExtensionObject &extensionObject);
    TransferResultDataDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    TransferResultDataDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    ~TransferResultDataDataType();

    void clear();

    bool operator==(const TransferResultDataDataType &other) const;
    bool operator!=(const TransferResultDataDataType &other) const;

    TransferResultDataDataType& operator=(const TransferResultDataDataType &other);

    OpcUaDi_TransferResultDataDataType* copy() const;
    void copyTo(OpcUaDi_TransferResultDataDataType *pDst) const;

    static OpcUaDi_TransferResultDataDataType* clone(const OpcUaDi_TransferResultDataDataType& source);
    static void cloneTo(const OpcUaDi_TransferResultDataDataType& source, OpcUaDi_TransferResultDataDataType& copy);

    void attach(const OpcUaDi_TransferResultDataDataType *pValue);
    OpcUaDi_TransferResultDataDataType* detach(OpcUaDi_TransferResultDataDataType* pDst);

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

    OpcUa_StatusCode setTransferResultDataDataType(const UaExtensionObject &extensionObject);
    OpcUa_StatusCode setTransferResultDataDataType(const OpcUa_ExtensionObject &extensionObject);
    OpcUa_StatusCode setTransferResultDataDataType(UaExtensionObject &extensionObject, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setTransferResultDataDataType(OpcUa_ExtensionObject &extensionObject, OpcUa_Boolean bDetach);

    void setTransferResultDataDataType(
        OpcUa_Int32 SequenceNumber,
        OpcUa_Boolean EndOfResults,
        const OpcUaDi::ParameterResultDataTypes& ParameterDefs
        );

    OpcUa_Int32 getSequenceNumber() const;
    OpcUa_Boolean getEndOfResults() const;
    void getParameterDefs(OpcUaDi::ParameterResultDataTypes& ParameterDefs) const;

    void setSequenceNumber(OpcUa_Int32 SequenceNumber);
    void setEndOfResults(OpcUa_Boolean EndOfResults);
    void setParameterDefs(const OpcUaDi::ParameterResultDataTypes& ParameterDefs);
};

class TransferResultDataDataTypes
{
public:
    TransferResultDataDataTypes();
    TransferResultDataDataTypes(const TransferResultDataDataTypes &other);
    TransferResultDataDataTypes(OpcUa_Int32 length, OpcUaDi_TransferResultDataDataType* data);
    virtual ~TransferResultDataDataTypes();

    TransferResultDataDataTypes& operator=(const TransferResultDataDataTypes &other);
    OpcUaDi_TransferResultDataDataType& operator[](OpcUa_UInt32 index);
    const OpcUaDi_TransferResultDataDataType& operator[](OpcUa_UInt32 index) const;

    void attach(OpcUa_UInt32 length, OpcUaDi_TransferResultDataDataType* data);
    void attach(OpcUa_Int32 length, OpcUaDi_TransferResultDataDataType* data);
    OpcUaDi_TransferResultDataDataType* detach();

    bool operator==(const TransferResultDataDataTypes &other) const;
    bool operator!=(const TransferResultDataDataTypes &other) const;

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    inline const OpcUaDi_TransferResultDataDataType* rawData() const {return m_data;}
    inline OpcUaDi_TransferResultDataDataType* rawData() {return m_data;}
    void toVariant(UaVariant &variant) const;
    void toVariant(OpcUa_Variant &variant) const;
    void toVariant(UaVariant &variant, OpcUa_Boolean bDetach);
    void toVariant(OpcUa_Variant &variant, OpcUa_Boolean bDetach);

    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean updateTimeStamps) const;
    void toDataValue(UaDataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);
    void toDataValue(OpcUa_DataValue &dataValue, OpcUa_Boolean bDetach, OpcUa_Boolean updateTimeStamps);

    OpcUa_StatusCode setTransferResultDataDataTypes(const UaVariant &variant);
    OpcUa_StatusCode setTransferResultDataDataTypes(const OpcUa_Variant &variant);
    OpcUa_StatusCode setTransferResultDataDataTypes(UaVariant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setTransferResultDataDataTypes(OpcUa_Variant &variant, OpcUa_Boolean bDetach);
    OpcUa_StatusCode setTransferResultDataDataTypes(OpcUa_Int32 length, OpcUaDi_TransferResultDataDataType* data);

    static TransferResultDataDataTypes empty;
private:
    OpcUa_UInt32 m_noOfElements;
    OpcUaDi_TransferResultDataDataType* m_data;
};

} // namespace OpcUaDi

#endif // __OPCUADI_TRANSFERRESULTDATADATATYPE_H__

