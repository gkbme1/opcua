/*****************************************************************************
 *                                                                           *
 * Copyright (c) 2006-2020 Unified Automation GmbH. All rights reserved.     *
 *                                                                           *
 * Software License Agreement ("SLA") Version 2.7                            *
 *                                                                           *
 * Unless explicitly acquired and licensed from Licensor under another       *
 * license, the contents of this file are subject to the Software License    *
 * Agreement ("SLA") Version 2.7, or subsequent versions as allowed by the   *
 * SLA, and You may not copy or use this file in either source code or       *
 * executable form, except in compliance with the terms and conditions of    *
 * the SLA.                                                                  *
 *                                                                           *
 * All software distributed under the SLA is provided strictly on an "AS     *
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,       *
 * AND LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT      *
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR   *
 * PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the SLA for specific   *
 * language governing rights and limitations under the SLA.                  *
 *                                                                           *
 * The complete license agreement can be found here:                         *
 * http://unifiedautomation.com/License/SLA/2.7/                             *
 *                                                                           *
 * Project: Unified Automation OPC UA ANSI C Communication Stack             *
 *                                                                           *
 * This software is based in part on the ANSI C Stack of the OPC Foundation. *
 * Initial version of the ANSI C Stack was founded and copyrighted by OPC    *
 * Foundation, Inc.                                                          *
 * Copyright (C) 2008, 2014 OPC Foundation, Inc., All Rights Reserved.       *
 *****************************************************************************/
/* This are the UA Proxy/Stub internal data type definitions! */

#ifndef _OpcUa_P_Types_H_
#define _OpcUa_P_Types_H_ 1

#ifndef OPCUA_P_BYTE_ORDER
#error OPCUA_P_BYTE_ORDER not defined
#endif

#if defined(__MINGW32__) || defined(__clang__)
#include <stdint.h>
#endif /* defined(__MINGW32__) || defined(__clang__) */

/*============================================================================
* Type definitions for basic data types.
*===========================================================================*/
typedef int                 OpcUa_Int;
typedef unsigned int        OpcUa_UInt;
typedef void                OpcUa_Void;
typedef void*               OpcUa_Handle;
typedef unsigned char       OpcUa_Boolean;

#if defined(__MINGW32__) || defined(__clang__)
typedef int8_t              OpcUa_SByte;
typedef uint8_t             OpcUa_Byte;
typedef int16_t             OpcUa_Int16;
typedef uint16_t            OpcUa_UInt16;
typedef int32_t             OpcUa_Int32;
typedef uint32_t            OpcUa_UInt32;
typedef int64_t             OpcUa_Int64;
typedef uint64_t            OpcUa_UInt64;
typedef intptr_t            OpcUa_IntPtr;
typedef uintptr_t           OpcUa_UIntPtr;
#else /* defined(__MINGW32__) || defined(__clang__) */
typedef char                OpcUa_SByte;
typedef unsigned char       OpcUa_Byte;
typedef short               OpcUa_Int16;
typedef unsigned short      OpcUa_UInt16;
typedef long                OpcUa_Int32;
typedef unsigned long       OpcUa_UInt32;
typedef __int64             OpcUa_Int64;
typedef unsigned __int64    OpcUa_UInt64;
#ifdef _WIN64 
typedef OpcUa_Int64         OpcUa_IntPtr;
typedef OpcUa_UInt64        OpcUa_UIntPtr;
#else
typedef OpcUa_Int32         OpcUa_IntPtr;
typedef OpcUa_UInt32        OpcUa_UIntPtr;
#endif
#endif /* defined(__MINGW32__) || defined(__clang__) */

typedef float               OpcUa_Float;
typedef double              OpcUa_Double;
typedef char                OpcUa_CharA;
typedef unsigned char       OpcUa_UCharA;
typedef OpcUa_CharA*        OpcUa_StringA;
typedef unsigned short      OpcUa_CharW;
typedef size_t              OpcUa_Size_t;

struct _OpcUa_DateTime
{
    OpcUa_UInt32 dwLowDateTime;
    OpcUa_UInt32 dwHighDateTime;
};
typedef struct _OpcUa_DateTime OpcUa_DateTime;

/**
 * @brief OpcUa_SocketManager Type
 */
typedef OpcUa_Void* OpcUa_SocketManager;

/**
 * @brief OpcUa_Socket Type
 */
typedef OpcUa_Void* OpcUa_Socket;

/**
 * @brief OpcUa_Thread Type
 */
typedef OpcUa_Void* OpcUa_Thread;


/**
 * @brief Internally used thread main entry function.
 */
typedef OpcUa_Void      (OpcUa_PfnInternalThreadMain)(OpcUa_Void* pArguments);

/**
 * @brief The handle for the platform thread.
 */
typedef OpcUa_UInt32    OpcUa_StatusCode;

/**
 * @brief The handle for the mutex.
 */
typedef OpcUa_Void*     OpcUa_Mutex;

/**
 * @brief The handle for the semaphore.
 */
typedef OpcUa_Void*     OpcUa_Semaphore;

/**
 * @brief The handle for a timer.
 */
typedef OpcUa_Void*     OpcUa_Timer;

/**
 * @brief A function used to compare elements when sorting or searching.
 *
 * @param pContext  [in] The context passed to the sorting/searching function.
 * @param pElement1 [in] The first element to compare.
 * @param pElement2 [in] The second element to compare.
 *
 * @return Zero if elements are equal, < 0 if element1 is less that element2.
 */
typedef OpcUa_Int (OPCUA_CDECL OpcUa_PfnCompare)(   const OpcUa_Void* pElement1,
                                                    const OpcUa_Void* pElement2);

/*============================================================================
* Type definitions for data types on the wire.
*===========================================================================*/
typedef OpcUa_Boolean       OpcUa_Boolean_Wire;
typedef OpcUa_SByte         OpcUa_SByte_Wire;
typedef OpcUa_Byte          OpcUa_Byte_Wire;
typedef OpcUa_Int16         OpcUa_Int16_Wire;
typedef OpcUa_UInt16        OpcUa_UInt16_Wire;
typedef OpcUa_Int32         OpcUa_Int32_Wire;
typedef OpcUa_UInt32        OpcUa_UInt32_Wire;
typedef OpcUa_Int64         OpcUa_Int64_Wire;
typedef OpcUa_UInt64        OpcUa_UInt64_Wire;
typedef OpcUa_Float         OpcUa_Float_Wire;
typedef OpcUa_Double        OpcUa_Double_Wire;
typedef OpcUa_CharA         OpcUa_Char_Wire;
typedef OpcUa_Char_Wire*    OpcUa_String_Wire;
typedef OpcUa_DateTime      OpcUa_DateTime_Wire;

/*============================================================================
* Type definitions for structured data types.
*===========================================================================*/
#define OPCUA_GUID_STATICINITIALIZER {0, 0, 0, {0,0,0,0,0,0,0,0}}
typedef struct _OpcUa_Guid
{
    OpcUa_UInt32    Data1;
    OpcUa_UInt16    Data2;
    OpcUa_UInt16    Data3;
    OpcUa_UCharA    Data4[8];
} OpcUa_Guid, *OpcUa_pGuid, OpcUa_Guid_Wire, *pOpcUa_Guid_Wire;

#define OPCUA_STRING_STATICINITIALIZER {0, 0, OpcUa_Null}
#define OPCUA_STRING_STATICINITIALIZEWITH(xText, xLength) {0,xLength,xText}
#ifdef _DEBUG
typedef struct _OpcUa_String
{
    OpcUa_UInt   flags;
#if OPCUA_STRING_SHORT
    OpcUa_UInt16 uLength;
#else /* OPCUA_STRING_SHORT */
    OpcUa_UInt32 uLength;
#endif /* OPCUA_STRING_SHORT */
    OpcUa_CharA* strContent;
} OpcUa_String, *OpcUa_pString;
#else
typedef struct _OpcUa_String
{
    OpcUa_UInt          uReserved1;     /* Content is private to String Implementation */
#if OPCUA_STRING_SHORT
    OpcUa_UInt16        uReserved2;     /* Content is private to String Implementation */
#else /* OPCUA_STRING_SHORT */
    OpcUa_UInt32        uReserved2;     /* Content is private to String Implementation */
#endif /* OPCUA_STRING_SHORT */
    OpcUa_Void*         uReserved4;     /* Content is private to String Implementation */
} OpcUa_String, *OpcUa_pString;
#endif

#define OPCUA_BYTESTRING_STATICINITIALIZER {-1, OpcUa_Null}
typedef struct _OpcUa_ByteString
{
    OpcUa_Int32 Length;
    OpcUa_Byte* Data;
} OpcUa_ByteString;

#define OPCUA_DATETIME_STATICINITIALIZER {0, 0}

/**
* @brief Holds a time value with a maximum resolution of micro seconds.
*/
typedef struct _OpcUa_TimeVal OpcUa_TimeVal;

struct _OpcUa_TimeVal
{
    /** @brief The number of full seconds since 1970. */
    OpcUa_UInt32 uintSeconds;
    /** @brief The fraction of the last second. */
    OpcUa_UInt32 uintMicroSeconds;
};

/*============================================================================
 * va_list definitions
 *===========================================================================*/
typedef va_list OpcUa_P_VA_List;

#define OPCUA_P_VA_START(ap,v)  va_start(ap,v)
#define OPCUA_P_VA_END(ap)      va_end(ap)

/*============================================================================
* constant definitions.
*===========================================================================*/
#define OpcUa_Ignore        0           /* Ignore signal */

#define OpcUa_False         0
#define OpcUa_True          (!OpcUa_False)

#ifdef __cplusplus
#define OpcUa_Null           0
#else
#define OpcUa_Null          (OpcUa_Void*)0
#endif

#define OpcUa_SByte_Min     (OpcUa_SByte)-128
#define OpcUa_SByte_Max     (OpcUa_SByte)127
#define OpcUa_Byte_Min      (OpcUa_Byte)0
#define OpcUa_Byte_Max      (OpcUa_Byte)255
#define OpcUa_Int16_Min     (OpcUa_Int16)-32768
#define OpcUa_Int16_Max     (OpcUa_Int16)32767
#define OpcUa_UInt16_Min    (OpcUa_UInt16)0
#define OpcUa_UInt16_Max    (OpcUa_UInt16)65535
#define OpcUa_Int32_Min     (OpcUa_Int32)(-2147483647L-1)
#define OpcUa_Int32_Max     (OpcUa_Int32)2147483647L
#define OpcUa_UInt32_Min    (OpcUa_UInt32)0UL
#define OpcUa_UInt32_Max    (OpcUa_UInt32)4294967295UL
#ifdef _MSC_VER
#define OpcUa_Int64_Min     (OpcUa_Int64)(-9223372036854775807i64-1)
#define OpcUa_Int64_Max     (OpcUa_Int64)9223372036854775807i64
#define OpcUa_UInt64_Min    (OpcUa_UInt64)0
#define OpcUa_UInt64_Max    (OpcUa_UInt64)18446744073709551615ui64
#else /* _MSC_VER */
#define OpcUa_Int64_Min     (OpcUa_Int64)(-9223372036854775807ll-1)
#define OpcUa_Int64_Max     (OpcUa_Int64)9223372036854775807ll
#define OpcUa_UInt64_Min    (OpcUa_UInt64)0
#define OpcUa_UInt64_Max    (OpcUa_UInt64)18446744073709551615ull
#endif /* _MSC_VER */
/* defined as FLT_MIN in "%ProgramFiles\Microsoft Visual Studio 8\VC\include\float.h" */
/* #define FLT_MIN         1.175494351e-38F */
#define OpcUa_Float_Min     (OpcUa_Float)1.175494351e-38F
/* defined as FLT_MAX in "%ProgramFiles\Microsoft Visual Studio 8\VC\include\float.h" */
/* #define FLT_MAX         3.402823466e+38F */
#define OpcUa_Float_Max     (OpcUa_Float)3.402823466e+38F
/* defined as DBL_MIN in "%ProgramFiles\Microsoft Visual Studio 8\VC\include\float.h" */
/* #define DBL_MIN         2.2250738585072014e-308 */
#define OpcUa_Double_Min    (OpcUa_Double)2.2250738585072014e-308
/* defined as DBL_MAX in "%ProgramFiles\Microsoft Visual Studio 8\VC\include\float.h" */
/* #define DBL_MAX         1.7976931348623158e+308 */
#define OpcUa_Double_Max    (OpcUa_Double)1.7976931348623158e+308

#ifdef _MSC_VER
#define OpcUa_DateTime_Min  0i64
#define OpcUa_DateTime_Max  2650153247990000000i64
#else /* _MSC_VER */
#define OpcUa_DateTime_Min  0ll
#define OpcUa_DateTime_Max  2650153247990000000ll
#endif /* _MSC_VER */
#define OpcUa_DateTime_Max_High 0x24c73c56
#define OpcUa_DateTime_Max_Low  0x82caa980
#define OPCUA_DATETIME_SET_MAX(xDateTime) \
    { \
        xDateTime.dwHighDateTime = OpcUa_DateTime_Max_High; \
        xDateTime.dwLowDateTime =  OpcUa_DateTime_Max_Low; \
    }

#define OpcUa_Infinity      (OpcUa_Double_Max + OpcUa_Double_Max)
#define OpcUa_NaN           (OpcUa_Infinity - OpcUa_Infinity)
#define OpcUa_IsNaN(xTest)  (int)((xTest) != (xTest))

/* set to OPCUA_CONFIG_YES to use the untested optimized byteswap */
#define OPCUA_SWAP_ALTERNATIVE OPCUA_CONFIG_NO

#if OPCUA_SWAP_ALTERNATIVE

#if OPCUA_P_BYTE_ORDER == OPCUA_P_LITTLE_ENDIAN

    /* this is the wire format */

    #define OpcUa_SwapBytes_2(xDst, xSrc) \
    { \
        *xDst = *xSrc; \
    }

    #define OpcUa_SwapBytes_4(xDst, xSrc) \
    { \
        *xDst = *xSrc; \
    }

    #define OpcUa_SwapBytes_8(xDst, xSrc) \
    { \
        *xDst = *xSrc; \
    }

#else

    #define OpcUa_SwapBytes_2(xDst, xSrc) \
    { \
        ((unsigned char*)xDst)[0] = ((unsigned char*)xSrc)[1]; \
        ((unsigned char*)xDst)[1] = ((unsigned char*)xSrc)[0]; \
    }

    #define OpcUa_SwapBytes_4(xDst, xSrc) \
    { \
        ((unsigned char*)xDst)[0] = ((unsigned char*)xSrc)[3]; \
        ((unsigned char*)xDst)[1] = ((unsigned char*)xSrc)[2]; \
        ((unsigned char*)xDst)[2] = ((unsigned char*)xSrc)[1]; \
        ((unsigned char*)xDst)[3] = ((unsigned char*)xSrc)[0]; \
    }

    #define OpcUa_SwapBytes_8(xDst, xSrc) \
    { \
        ((unsigned char*)xDst)[0] = ((unsigned char*)xSrc)[7]; \
        ((unsigned char*)xDst)[1] = ((unsigned char*)xSrc)[6]; \
        ((unsigned char*)xDst)[2] = ((unsigned char*)xSrc)[5]; \
        ((unsigned char*)xDst)[3] = ((unsigned char*)xSrc)[4]; \
        ((unsigned char*)xDst)[4] = ((unsigned char*)xSrc)[3]; \
        ((unsigned char*)xDst)[5] = ((unsigned char*)xSrc)[2]; \
        ((unsigned char*)xDst)[6] = ((unsigned char*)xSrc)[1]; \
        ((unsigned char*)xDst)[7] = ((unsigned char*)xSrc)[0]; \
    }

#endif

#else /* OPCUA_SWAP_ALTERNATIVE */

#if OPCUA_P_BYTE_ORDER == OPCUA_P_LITTLE_ENDIAN
    #define OpcUa_SwapBytes(xDst, xSrc, xCount) \
    { \
        memcpy(xDst, xSrc, xCount); \
    }
#else
    #define OpcUa_SwapBytes(xDst, xSrc, xCount) \
    { \
        OpcUa_UInt32 ii = 0; \
        OpcUa_UInt32 jj = xCount-1; \
        OpcUa_Byte* dst = (OpcUa_Byte*)xDst; \
        OpcUa_Byte* src = (OpcUa_Byte*)xSrc; \
        \
        for (; ii < xCount; ii++, jj--) \
        { \
            dst[ii] = src[jj]; \
        } \
    }
#endif

#endif /* OPCUA_SWAP_ALTERNATIVE */

/*============================================================================
* format specifiers.
*===========================================================================*/
#define OPCUA_P_HAVE_FORMAT_SPECIFIERS 1

#ifdef _WIN64
#define OPCUA_POINTER_SIZE  "ll"
#else
#define OPCUA_POINTER_SIZE  "l"
#endif

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>

/* PRINT FORMAT MACROS */
#define OpcUa_PRId8         PRId8
#define OpcUa_PRId16        PRId16
#define OpcUa_PRId32        PRId32
#define OpcUa_PRId64        PRId64

#define OpcUa_PRIdFAST8     PRIdFAST8
#define OpcUa_PRIdFAST16    PRIdFAST16
#define OpcUa_PRIdFAST32    PRIdFAST32
#define OpcUa_PRIdFAST64    PRIdFAST64

#define OpcUa_PRIdLEAST8    PRIdLEAST8
#define OpcUa_PRIdLEAST16   PRIdLEAST16
#define OpcUa_PRIdLEAST32   PRIdLEAST32
#define OpcUa_PRIdLEAST64   PRIdLEAST64

#define OpcUa_PRIdMAX       PRIdMAX
#define OpcUa_PRIdPTR       PRIdPTR

#define OpcUa_PRIi8         PRIi8
#define OpcUa_PRIi16        PRIi16
#define OpcUa_PRIi32        PRIi32
#define OpcUa_PRIi64        PRIi64

#define OpcUa_PRIiFAST8     PRIiFAST8
#define OpcUa_PRIiFAST16    PRIiFAST16
#define OpcUa_PRIiFAST32    PRIiFAST32
#define OpcUa_PRIiFAST64    PRIiFAST64

#define OpcUa_PRIiLEAST8    PRIiLEAST8
#define OpcUa_PRIiLEAST16   PRIiLEAST16
#define OpcUa_PRIiLEAST32   PRIiLEAST32
#define OpcUa_PRIiLEAST64   PRIiLEAST64

#define OpcUa_PRIiMAX       PRIiMAX
#define OpcUa_PRIiPTR       PRIiPTR

#define OpcUa_PRIo8         PRIo8
#define OpcUa_PRIo16        PRIo16
#define OpcUa_PRIo32        PRIo32
#define OpcUa_PRIo64        PRIo64

#define OpcUa_PRIoFAST8     PRIoFAST8
#define OpcUa_PRIoFAST16    PRIoFAST16
#define OpcUa_PRIoFAST32    PRIoFAST32
#define OpcUa_PRIoFAST64    PRIoFAST64

#define OpcUa_PRIoLEAST8    PRIoLEAST8
#define OpcUa_PRIoLEAST16   PRIoLEAST16
#define OpcUa_PRIoLEAST32   PRIoLEAST32
#define OpcUa_PRIoLEAST64   PRIoLEAST64

#define OpcUa_PRIoMAX       PRIoMAX
#define OpcUa_PRIoPTR       PRIoPTR

#define OpcUa_PRIu8         PRIu8
#define OpcUa_PRIu16        PRIu16
#define OpcUa_PRIu32        PRIu32
#define OpcUa_PRIu64        PRIu64

#define OpcUa_PRIuFAST8     PRIuFAST8
#define OpcUa_PRIuFAST16    PRIuFAST16
#define OpcUa_PRIuFAST32    PRIuFAST32
#define OpcUa_PRIuFAST64    PRIuFAST64

#define OpcUa_PRIuLEAST8    PRIuLEAST8
#define OpcUa_PRIuLEAST16   PRIuLEAST16
#define OpcUa_PRIuLEAST32   PRIuLEAST32
#define OpcUa_PRIuLEAST64   PRIuLEAST64

#define OpcUa_PRIuMAX       PRIuMAX
#define OpcUa_PRIuPTR       PRIuPTR

#define OpcUa_PRIx8         PRIx8
#define OpcUa_PRIx16        PRIx16
#define OpcUa_PRIx32        PRIx32
#define OpcUa_PRIx64        PRIx64

#define OpcUa_PRIxFAST8     PRIxFAST8
#define OpcUa_PRIxFAST16    PRIxFAST16
#define OpcUa_PRIxFAST32    PRIxFAST32
#define OpcUa_PRIxFAST64    PRIxFAST64

#define OpcUa_PRIxLEAST8    PRIxLEAST8
#define OpcUa_PRIxLEAST16   PRIxLEAST16
#define OpcUa_PRIxLEAST32   PRIxLEAST32
#define OpcUa_PRIxLEAST64   PRIxLEAST64

#define OpcUa_PRIxMAX       PRIxMAX
#define OpcUa_PRIxPTR       PRIxPTR

#define OpcUa_PRIX8         PRIX8
#define OpcUa_PRIX16        PRIX16
#define OpcUa_PRIX32        PRIX32
#define OpcUa_PRIX64        PRIX64

#define OpcUa_PRIXFAST8     PRIXFAST8
#define OpcUa_PRIXFAST16    PRIXFAST16
#define OpcUa_PRIXFAST32    PRIXFAST32
#define OpcUa_PRIXFAST64    PRIXFAST64

#define OpcUa_PRIXLEAST8    PRIXLEAST8
#define OpcUa_PRIXLEAST16   PRIXLEAST16
#define OpcUa_PRIXLEAST32   PRIXLEAST32
#define OpcUa_PRIXLEAST64   PRIXLEAST64

#define OpcUa_PRIXMAX       PRIXMAX
#define OpcUa_PRIXPTR       PRIXPTR

/* SCAN FORMAT MACROS */
#define OpcUa_SCNd8         SCNd8
#define OpcUa_SCNd16        SCNd16
#define OpcUa_SCNd32        SCNd32
#define OpcUa_SCNd64        SCNd64

#define OpcUa_SCNdFAST8     SCNdFAST8
#define OpcUa_SCNdFAST16    SCNdFAST16
#define OpcUa_SCNdFAST32    SCNdFAST32
#define OpcUa_SCNdFAST64    SCNdFAST64

#define OpcUa_SCNdLEAST8    SCNdLEAST8
#define OpcUa_SCNdLEAST16   SCNdLEAST16
#define OpcUa_SCNdLEAST32   SCNdLEAST32
#define OpcUa_SCNdLEAST64   SCNdLEAST64

#define OpcUa_SCNdMAX       SCNdMAX
#define OpcUa_SCNdPTR       SCNdPTR

#define OpcUa_SCNi8         SCNi8
#define OpcUa_SCNi16        SCNi16
#define OpcUa_SCNi32        SCNi32
#define OpcUa_SCNi64        SCNi64

#define OpcUa_SCNiFAST8     SCNiFAST8
#define OpcUa_SCNiFAST16    SCNiFAST16
#define OpcUa_SCNiFAST32    SCNiFAST32
#define OpcUa_SCNiFAST64    SCNiFAST64

#define OpcUa_SCNiLEAST8    SCNiLEAST8
#define OpcUa_SCNiLEAST16   SCNiLEAST16
#define OpcUa_SCNiLEAST32   SCNiLEAST32
#define OpcUa_SCNiLEAST64   SCNiLEAST64

#define OpcUa_SCNiMAX       SCNiMAX
#define OpcUa_SCNiPTR       SCNiPTR

#define OpcUa_SCNo8         SCNo8
#define OpcUa_SCNo16        SCNo16
#define OpcUa_SCNo32        SCNo32
#define OpcUa_SCNo64        SCNo64

#define OpcUa_SCNoFAST8     SCNoFAST8
#define OpcUa_SCNoFAST16    SCNoFAST16
#define OpcUa_SCNoFAST32    SCNoFAST32
#define OpcUa_SCNoFAST64    SCNoFAST64

#define OpcUa_SCNoLEAST8    SCNoLEAST8
#define OpcUa_SCNoLEAST16   SCNoLEAST16
#define OpcUa_SCNoLEAST32   SCNoLEAST32
#define OpcUa_SCNoLEAST64   SCNoLEAST64

#define OpcUa_SCNoMAX       SCNoMAX
#define OpcUa_SCNoPTR       SCNoPTR

#define OpcUa_SCNu8         SCNu8
#define OpcUa_SCNu16        SCNu16
#define OpcUa_SCNu32        SCNu32
#define OpcUa_SCNu64        SCNu64

#define OpcUa_SCNuFAST8     SCNuFAST8
#define OpcUa_SCNuFAST16    SCNuFAST16
#define OpcUa_SCNuFAST32    SCNuFAST32
#define OpcUa_SCNuFAST64    SCNuFAST64

#define OpcUa_SCNuLEAST8    SCNuLEAST8
#define OpcUa_SCNuLEAST16   SCNuLEAST16
#define OpcUa_SCNuLEAST32   SCNuLEAST32
#define OpcUa_SCNuLEAST64   SCNuLEAST64

#define OpcUa_SCNuMAX       SCNuMAX
#define OpcUa_SCNuPTR       SCNuPTR

#define OpcUa_SCNx8         SCNx8
#define OpcUa_SCNx16        SCNx16
#define OpcUa_SCNx32        SCNx32
#define OpcUa_SCNx64        SCNx64

#define OpcUa_SCNxFAST8     SCNxFAST8
#define OpcUa_SCNxFAST16    SCNxFAST16
#define OpcUa_SCNxFAST32    SCNxFAST32
#define OpcUa_SCNxFAST64    SCNxFAST64

#define OpcUa_SCNxLEAST8    SCNxLEAST8
#define OpcUa_SCNxLEAST16   SCNxLEAST16
#define OpcUa_SCNxLEAST32   SCNxLEAST32
#define OpcUa_SCNxLEAST64   SCNxLEAST64

#define OpcUa_SCNxMAX       SCNxMAX
#define OpcUa_SCNxPTR       SCNxPTR
#else /* HAVE_INTTYPES */
/* PRINT FORMAT MACROS */
#define OpcUa_PRId8         "hhd"
#define OpcUa_PRId16        "hd"
#define OpcUa_PRId32        "ld"
#define OpcUa_PRId64        "lld"

#define OpcUa_PRIdFAST8     "hhd"
#define OpcUa_PRIdFAST16    "hd"
#define OpcUa_PRIdFAST32    "ld"
#define OpcUa_PRIdFAST64    "lld"

#define OpcUa_PRIdLEAST8    "hhd"
#define OpcUa_PRIdLEAST16   "hd"
#define OpcUa_PRIdLEAST32   "ld"
#define OpcUa_PRIdLEAST64   "lld"

#define OpcUa_PRIdMAX       "lld"
#define OpcUa_PRIdPTR       OPCUA_POINTER_SIZE "d"

#define OpcUa_PRIi8         "hhi"
#define OpcUa_PRIi16        "hi"
#define OpcUa_PRIi32        "li"
#define OpcUa_PRIi64        "lli"

#define OpcUa_PRIiFAST8     "hhi"
#define OpcUa_PRIiFAST16    "hi"
#define OpcUa_PRIiFAST32    "li"
#define OpcUa_PRIiFAST64    "lli"

#define OpcUa_PRIiLEAST8    "hhi"
#define OpcUa_PRIiLEAST16   "hi"
#define OpcUa_PRIiLEAST32   "li"
#define OpcUa_PRIiLEAST64   "lli"

#define OpcUa_PRIiMAX       "lli"
#define OpcUa_PRIiPTR       OPCUA_POINTER_SIZE "i"

#define OpcUa_PRIo8         "hho"
#define OpcUa_PRIo16        "ho"
#define OpcUa_PRIo32        "lo"
#define OpcUa_PRIo64        "llo"

#define OpcUa_PRIoFAST8     "hho"
#define OpcUa_PRIoFAST16    "ho"
#define OpcUa_PRIoFAST32    "lo"
#define OpcUa_PRIoFAST64    "llo"

#define OpcUa_PRIoLEAST8    "hho"
#define OpcUa_PRIoLEAST16   "ho"
#define OpcUa_PRIoLEAST32   "lo"
#define OpcUa_PRIoLEAST64   "llo"

#define OpcUa_PRIoMAX       "llo"
#define OpcUa_PRIoPTR       OPCUA_POINTER_SIZE "o"

#define OpcUa_PRIu8         "hhu"
#define OpcUa_PRIu16        "hu"
#define OpcUa_PRIu32        "lu"
#define OpcUa_PRIu64        "llu"

#define OpcUa_PRIuFAST8     "hhu"
#define OpcUa_PRIuFAST16    "hu"
#define OpcUa_PRIuFAST32    "lu"
#define OpcUa_PRIuFAST64    "llu"

#define OpcUa_PRIuLEAST8    "hhu"
#define OpcUa_PRIuLEAST16   "hu"
#define OpcUa_PRIuLEAST32   "lu"
#define OpcUa_PRIuLEAST64   "llu"

#define OpcUa_PRIuMAX       "llu"
#define OpcUa_PRIuPTR       OPCUA_POINTER_SIZE "u"

#define OpcUa_PRIx8         "hhx"
#define OpcUa_PRIx16        "hx"
#define OpcUa_PRIx32        "lx"
#define OpcUa_PRIx64        "llx"

#define OpcUa_PRIxFAST8     "hhx"
#define OpcUa_PRIxFAST16    "hx"
#define OpcUa_PRIxFAST32    "lx"
#define OpcUa_PRIxFAST64    "llx"

#define OpcUa_PRIxLEAST8    "hhx"
#define OpcUa_PRIxLEAST16   "hx"
#define OpcUa_PRIxLEAST32   "lx"
#define OpcUa_PRIxLEAST64   "llx"

#define OpcUa_PRIxMAX       "llx"
#define OpcUa_PRIxPTR       OPCUA_POINTER_SIZE "x"

#define OpcUa_PRIX8         "hhX"
#define OpcUa_PRIX16        "hX"
#define OpcUa_PRIX32        "lX"
#define OpcUa_PRIX64        "llX"

#define OpcUa_PRIXFAST8     "hhX"
#define OpcUa_PRIXFAST16    "hX"
#define OpcUa_PRIXFAST32    "lX"
#define OpcUa_PRIXFAST64    "llX"

#define OpcUa_PRIXLEAST8    "hhX"
#define OpcUa_PRIXLEAST16   "hX"
#define OpcUa_PRIXLEAST32   "lX"
#define OpcUa_PRIXLEAST64   "llX"

#define OpcUa_PRIXMAX       "llX"
#define OpcUa_PRIXPTR       OPCUA_POINTER_SIZE "X"

/* SCAN FORMAT MACROS */
#define OpcUa_SCNd8         "hhd"
#define OpcUa_SCNd16        "hd"
#define OpcUa_SCNd32        "ld"
#define OpcUa_SCNd64        "lld"

#define OpcUa_SCNdFAST8     "hhd"
#define OpcUa_SCNdFAST16    "hd"
#define OpcUa_SCNdFAST32    "ld"
#define OpcUa_SCNdFAST64    "lld"

#define OpcUa_SCNdLEAST8    "hhd"
#define OpcUa_SCNdLEAST16   "hd"
#define OpcUa_SCNdLEAST32   "ld"
#define OpcUa_SCNdLEAST64   "lld"

#define OpcUa_SCNdMAX       "lld"
#define OpcUa_SCNdPTR       OPCUA_POINTER_SIZE "d"

#define OpcUa_SCNi8         "hhi"
#define OpcUa_SCNi16        "hi"
#define OpcUa_SCNi32        "li"
#define OpcUa_SCNi64        "lli"

#define OpcUa_SCNiFAST8     "hhi"
#define OpcUa_SCNiFAST16    "hi"
#define OpcUa_SCNiFAST32    "li"
#define OpcUa_SCNiFAST64    "lli"

#define OpcUa_SCNiLEAST8    "hhi"
#define OpcUa_SCNiLEAST16   "hi"
#define OpcUa_SCNiLEAST32   "li"
#define OpcUa_SCNiLEAST64   "lli"

#define OpcUa_SCNiMAX       "lli"
#define OpcUa_SCNiPTR       OPCUA_POINTER_SIZE "i"

#define OpcUa_SCNo8         "hho"
#define OpcUa_SCNo16        "ho"
#define OpcUa_SCNo32        "lo"
#define OpcUa_SCNo64        "llo"

#define OpcUa_SCNoFAST8     "hho"
#define OpcUa_SCNoFAST16    "ho"
#define OpcUa_SCNoFAST32    "lo"
#define OpcUa_SCNoFAST64    "llo"

#define OpcUa_SCNoLEAST8    "hho"
#define OpcUa_SCNoLEAST16   "ho"
#define OpcUa_SCNoLEAST32   "lo"
#define OpcUa_SCNoLEAST64   "llo"

#define OpcUa_SCNoMAX       "llo"
#define OpcUa_SCNoPTR       OPCUA_POINTER_SIZE "o"

#define OpcUa_SCNu8         "hhu"
#define OpcUa_SCNu16        "hu"
#define OpcUa_SCNu32        "lu"
#define OpcUa_SCNu64        "llu"

#define OpcUa_SCNuFAST8     "hhu"
#define OpcUa_SCNuFAST16    "hu"
#define OpcUa_SCNuFAST32    "lu"
#define OpcUa_SCNuFAST64    "llu"

#define OpcUa_SCNuLEAST8    "hhu"
#define OpcUa_SCNuLEAST16   "hu"
#define OpcUa_SCNuLEAST32   "lu"
#define OpcUa_SCNuLEAST64   "llu"

#define OpcUa_SCNuMAX       "llu"
#define OpcUa_SCNuPTR       OPCUA_POINTER_SIZE "u"

#define OpcUa_SCNx8         "hhx"
#define OpcUa_SCNx16        "hx"
#define OpcUa_SCNx32        "lx"
#define OpcUa_SCNx64        "llx"

#define OpcUa_SCNxFAST8     "hhx"
#define OpcUa_SCNxFAST16    "hx"
#define OpcUa_SCNxFAST32    "lx"
#define OpcUa_SCNxFAST64    "llx"

#define OpcUa_SCNxLEAST8    "hhx"
#define OpcUa_SCNxLEAST16   "hx"
#define OpcUa_SCNxLEAST32   "lx"
#define OpcUa_SCNxLEAST64   "llx"

#define OpcUa_SCNxMAX       "llx"
#define OpcUa_SCNxPTR       OPCUA_POINTER_SIZE "x"
#endif /* HAVE_INTTYPES */

/* PRINT FORMAT MACROS for built-in scalar types */
#define OpcUa_PriInt        "i"
#define OpcUa_PriUInt       "u"
#define OpcUa_PriBoolean    OpcUa_PRIu8
#define OpcUa_PriSByte      OpcUa_PRIi8
#define OpcUa_PriByte       OpcUa_PRIu8
#define OpcUa_PriInt16      OpcUa_PRIi16
#define OpcUa_PriUInt16     OpcUa_PRIu16
#define OpcUa_PriInt32      OpcUa_PRIi32
#define OpcUa_PriUInt32     OpcUa_PRIu32
#define OpcUa_PriInt64      OpcUa_PRIi64
#define OpcUa_PriUInt64     OpcUa_PRIu64
#define OpcUa_PriXSByte     OpcUa_PRIx8
#define OpcUa_PriXByte      OpcUa_PRIx8
#define OpcUa_PriXInt16     OpcUa_PRIx16
#define OpcUa_PriXUInt16    OpcUa_PRIx16
#define OpcUa_PriXInt32     OpcUa_PRIx32
#define OpcUa_PriXUInt32    OpcUa_PRIx32
#define OpcUa_PriXInt64     OpcUa_PRIx64
#define OpcUa_PriXUInt64    OpcUa_PRIx64
#define OpcUa_PriFloat      "f"
#define OpcUa_PriDouble     "f"
#define OpcUa_PriCharA      "c"
#define OpcUa_PriUCharA     "c"
#define OpcUa_PriStringA    "s"
#ifdef _MSC_VER
# if _MSC_VER < 1800
#  define OpcUa_PriSize_t   "Iu"
# else /*  _MSC_VER < 1800 */
#  define OpcUa_PriSize_t   "zu"
# endif /*  _MSC_VER < 1800 */
#else /* _MSC_VER */
# ifdef _WIN64
#  define OpcUa_PriSize_t OpcUa_PRIu64
# else
#  define OpcUa_PriSize_t OpcUa_PRIu32
# endif
#endif /* _MSC_VER */

/* SCAN FORMAT MACROS for built-in scalar types */
#define OpcUa_ScnInt        "i"
#define OpcUa_ScnUInt       "u"
#define OpcUa_ScnBoolean    OpcUa_SCNu8
#define OpcUa_ScnSByte      OpcUa_SCNi8
#define OpcUa_ScnByte       OpcUa_SCNu8
#define OpcUa_ScnInt16      OpcUa_SCNi16
#define OpcUa_ScnUInt16     OpcUa_SCNu16
#define OpcUa_ScnInt32      OpcUa_SCNi32
#define OpcUa_ScnUInt32     OpcUa_SCNu32
#define OpcUa_ScnInt64      OpcUa_SCNi64
#define OpcUa_ScnUInt64     OpcUa_SCNu64
#define OpcUa_ScnXSByte     OpcUa_SCNx8
#define OpcUa_ScnXByte      OpcUa_SCNx8
#define OpcUa_ScnXInt16     OpcUa_SCNx16
#define OpcUa_ScnXUInt16    OpcUa_SCNx16
#define OpcUa_ScnXInt32     OpcUa_SCNx32
#define OpcUa_ScnXUInt32    OpcUa_SCNx32
#define OpcUa_ScnXInt64     OpcUa_SCNx64
#define OpcUa_ScnXUInt64    OpcUa_SCNx64
#define OpcUa_ScnFloat      "f"
#define OpcUa_ScnDouble     "f"
#define OpcUa_ScnCharA      "c"
#define OpcUa_ScnUCharA     "c"
#define OpcUa_ScnStringA    "s"

#endif /* _OpcUa_PlatformDefs_H_ */
/*----------------------------------------------------------------------------------------------------*\
|   End of File                                                                          End of File   |
\*----------------------------------------------------------------------------------------------------*/
