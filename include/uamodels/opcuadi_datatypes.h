/******************************************************************************
** opcuadi_datatypes.h
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

#ifndef __OPCUADI_DATATYPES_H__
#define __OPCUADI_DATATYPES_H__

#include <opcua_proxystub.h>
#include <opcua_builtintypes.h>
#include <opcua_exclusions.h>
#include <opcua_types.h>

#include "opcuadi_identifiers.h"

#define OPCUADI_EXTENSIONOBJECT_GET_ENCODEABLE(xExpectedType, xExtensionObject) \
    (OpcUaDi_##xExpectedType*)((((xExtensionObject)->Encoding == OpcUa_ExtensionObjectEncoding_EncodeableObject && \
    (xExtensionObject)->Body.EncodeableObject.Type != OpcUa_Null && \
    (xExtensionObject)->Body.EncodeableObject.Type->TypeId == OpcUaDiId_##xExpectedType && \
    OpcUa_StrCmpA((xExtensionObject)->Body.EncodeableObject.Type->NamespaceUri, "http://opcfoundation.org/UA/DI/") == 0 && \
    (xExtensionObject)->Body.EncodeableObject.Object != OpcUa_Null))?((xExtensionObject)->Body.EncodeableObject.Object):OpcUa_Null)


// Namespace for the UA information model http://opcfoundation.org/UA/DI/
namespace OpcUaDi {

#ifndef OPCUA_EXCLUDE_DeviceHealthEnumeration
/*============================================================================
 * The DeviceHealthEnumeration enumeration.
 *===========================================================================*/
enum DeviceHealthEnumeration
{
    DeviceHealthEnumeration_NORMAL = 0 /**<This device functions normally.*/,
    DeviceHealthEnumeration_FAILURE = 1 /**<Malfunction of the device or any of its peripherals.*/,
    DeviceHealthEnumeration_CHECK_FUNCTION = 2 /**<Functional checks are currently performed.*/,
    DeviceHealthEnumeration_OFF_SPEC = 3 /**<The device is currently working outside of its specified range or that internal diagnoses indicate deviations from measured or set values.*/,
    DeviceHealthEnumeration_MAINTENANCE_REQUIRED = 4 /**<This element is working, but a maintenance operation is required.*/
#if OPCUA_FORCE_INT32_ENUMS
    ,_DeviceHealthEnumeration_MaxEnumerationValue = OpcUa_Int32_Max
#endif
};

UAMODELS_EXPORT inline void DeviceHealthEnumeration_Clear(DeviceHealthEnumeration *pValue) {*pValue = DeviceHealthEnumeration_NORMAL;}

UAMODELS_EXPORT inline void DeviceHealthEnumeration_Initialize(DeviceHealthEnumeration *pValue) {*pValue = DeviceHealthEnumeration_NORMAL;}

UAMODELS_EXPORT extern struct ::_OpcUa_EnumeratedType DeviceHealthEnumeration_EnumeratedType;

#endif /*OPCUA_EXCLUDE_DeviceHealthEnumeration*/
}

#ifndef OPCUA_EXCLUDE_OpcUaDi_TransferResultDataDataType
/*============================================================================
 * The OpcUaDi_TransferResultDataDataType structure.
 *===========================================================================*/
typedef struct _OpcUaDi_TransferResultDataDataType
{
    OpcUa_Int32 SequenceNumber;
    OpcUa_Boolean EndOfResults;
    OpcUa_Int32 NoOfParameterDefs;
    struct _OpcUaDi_ParameterResultDataType* ParameterDefs;
} OpcUaDi_TransferResultDataDataType;

UAMODELS_EXPORT OpcUa_Void OpcUaDi_TransferResultDataDataType_Initialize(OpcUaDi_TransferResultDataDataType* pValue);

UAMODELS_EXPORT OpcUa_Void OpcUaDi_TransferResultDataDataType_Clear(OpcUaDi_TransferResultDataDataType* pValue);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_TransferResultDataDataType_GetSize(OpcUaDi_TransferResultDataDataType* pValue, struct _OpcUa_Encoder* pEncoder, OpcUa_Int32* pSize);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_TransferResultDataDataType_Encode(OpcUaDi_TransferResultDataDataType* pValue, struct _OpcUa_Encoder* pEncoder);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_TransferResultDataDataType_Decode(OpcUaDi_TransferResultDataDataType* pValue, struct _OpcUa_Decoder* pDecoder);

#if OPCUA_ENCODEABLE_OBJECT_COMPARE_SUPPORTED
UAMODELS_EXPORT OpcUa_Int        OpcUaDi_TransferResultDataDataType_Compare(const OpcUaDi_TransferResultDataDataType* pValue1, const OpcUaDi_TransferResultDataDataType* pValue2);
#endif /* OPCUA_ENCODEABLE_OBJECT_COMPARE_SUPPORTED */

#if OPCUA_ENCODEABLE_OBJECT_COPY_SUPPORTED
UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_TransferResultDataDataType_Copy(const OpcUaDi_TransferResultDataDataType* pSource, OpcUaDi_TransferResultDataDataType** ppCopy);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_TransferResultDataDataType_CopyTo(const OpcUaDi_TransferResultDataDataType* pSource, OpcUaDi_TransferResultDataDataType* pDestination);
#endif /* OPCUA_ENCODEABLE_OBJECT_COPY_SUPPORTED */

extern struct _OpcUa_EncodeableType OpcUaDi_TransferResultDataDataType_EncodeableType;
#endif /*OPCUA_EXCLUDE_OpcUaDi_TransferResultDataDataType*/

#ifndef OPCUA_EXCLUDE_OpcUaDi_TransferResultErrorDataType
/*============================================================================
 * The OpcUaDi_TransferResultErrorDataType structure.
 *===========================================================================*/
typedef struct _OpcUaDi_TransferResultErrorDataType
{
    OpcUa_Int32 Status;
    OpcUa_DiagnosticInfo Diagnostics;
} OpcUaDi_TransferResultErrorDataType;

UAMODELS_EXPORT OpcUa_Void OpcUaDi_TransferResultErrorDataType_Initialize(OpcUaDi_TransferResultErrorDataType* pValue);

UAMODELS_EXPORT OpcUa_Void OpcUaDi_TransferResultErrorDataType_Clear(OpcUaDi_TransferResultErrorDataType* pValue);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_TransferResultErrorDataType_GetSize(OpcUaDi_TransferResultErrorDataType* pValue, struct _OpcUa_Encoder* pEncoder, OpcUa_Int32* pSize);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_TransferResultErrorDataType_Encode(OpcUaDi_TransferResultErrorDataType* pValue, struct _OpcUa_Encoder* pEncoder);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_TransferResultErrorDataType_Decode(OpcUaDi_TransferResultErrorDataType* pValue, struct _OpcUa_Decoder* pDecoder);

#if OPCUA_ENCODEABLE_OBJECT_COMPARE_SUPPORTED
UAMODELS_EXPORT OpcUa_Int        OpcUaDi_TransferResultErrorDataType_Compare(const OpcUaDi_TransferResultErrorDataType* pValue1, const OpcUaDi_TransferResultErrorDataType* pValue2);
#endif /* OPCUA_ENCODEABLE_OBJECT_COMPARE_SUPPORTED */

#if OPCUA_ENCODEABLE_OBJECT_COPY_SUPPORTED
UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_TransferResultErrorDataType_Copy(const OpcUaDi_TransferResultErrorDataType* pSource, OpcUaDi_TransferResultErrorDataType** ppCopy);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_TransferResultErrorDataType_CopyTo(const OpcUaDi_TransferResultErrorDataType* pSource, OpcUaDi_TransferResultErrorDataType* pDestination);
#endif /* OPCUA_ENCODEABLE_OBJECT_COPY_SUPPORTED */

extern struct _OpcUa_EncodeableType OpcUaDi_TransferResultErrorDataType_EncodeableType;
#endif /*OPCUA_EXCLUDE_OpcUaDi_TransferResultErrorDataType*/

#ifndef OPCUA_EXCLUDE_OpcUaDi_ParameterResultDataType
/*============================================================================
 * The OpcUaDi_ParameterResultDataType structure.
 *===========================================================================*/
typedef struct _OpcUaDi_ParameterResultDataType
{
    OpcUa_Int32 NoOfNodePath;
    OpcUa_QualifiedName* NodePath;
    OpcUa_StatusCode StatusCode;
    OpcUa_DiagnosticInfo Diagnostics;
} OpcUaDi_ParameterResultDataType;

UAMODELS_EXPORT OpcUa_Void OpcUaDi_ParameterResultDataType_Initialize(OpcUaDi_ParameterResultDataType* pValue);

UAMODELS_EXPORT OpcUa_Void OpcUaDi_ParameterResultDataType_Clear(OpcUaDi_ParameterResultDataType* pValue);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_ParameterResultDataType_GetSize(OpcUaDi_ParameterResultDataType* pValue, struct _OpcUa_Encoder* pEncoder, OpcUa_Int32* pSize);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_ParameterResultDataType_Encode(OpcUaDi_ParameterResultDataType* pValue, struct _OpcUa_Encoder* pEncoder);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_ParameterResultDataType_Decode(OpcUaDi_ParameterResultDataType* pValue, struct _OpcUa_Decoder* pDecoder);

#if OPCUA_ENCODEABLE_OBJECT_COMPARE_SUPPORTED
UAMODELS_EXPORT OpcUa_Int        OpcUaDi_ParameterResultDataType_Compare(const OpcUaDi_ParameterResultDataType* pValue1, const OpcUaDi_ParameterResultDataType* pValue2);
#endif /* OPCUA_ENCODEABLE_OBJECT_COMPARE_SUPPORTED */

#if OPCUA_ENCODEABLE_OBJECT_COPY_SUPPORTED
UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_ParameterResultDataType_Copy(const OpcUaDi_ParameterResultDataType* pSource, OpcUaDi_ParameterResultDataType** ppCopy);

UAMODELS_EXPORT OpcUa_StatusCode OpcUaDi_ParameterResultDataType_CopyTo(const OpcUaDi_ParameterResultDataType* pSource, OpcUaDi_ParameterResultDataType* pDestination);
#endif /* OPCUA_ENCODEABLE_OBJECT_COPY_SUPPORTED */

extern struct _OpcUa_EncodeableType OpcUaDi_ParameterResultDataType_EncodeableType;
#endif /*OPCUA_EXCLUDE_OpcUaDi_ParameterResultDataType*/


/*============================================================================
 * Table of known types.
 *===========================================================================*/
extern struct _OpcUa_EncodeableType** OpcUaDi_KnownEncodeableTypes;

/*============================================================================
 * Register known types.
 *===========================================================================*/
namespace OpcUaDi
{
    /** Class used to handle data type registration
    */
    class DataTypes
    {
    public:
        static void registerStructuredTypes();
    private:
        static bool s_dataTypesAdded;
    };
}

#endif // __OPCUADI_DATATYPES_H__

