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

#ifndef _OpcUa_StackStatusCodes_H_
#define _OpcUa_StackStatusCodes_H_ 1

OPCUA_BEGIN_EXTERN_C

/*============================================================================
 * Begin of status codes internal to the stack.
 *===========================================================================*/
#define OpcUa_StartOfStackStatusCodes 0xA0000000

/*============================================================================
 * The message signature is invalid.
 *===========================================================================*/
#define OpcUa_BadSignatureInvalid 0xA0010000

/*============================================================================
 * The extensible parameter provided is not a valid for the service.
 *===========================================================================*/
#define OpcUa_BadExtensibleParameterInvalid 0xA0040000

/*============================================================================
 * The extensible parameter provided is valid but the server does not support it.
 *===========================================================================*/
#define OpcUa_BadExtensibleParameterUnsupported 0xA0050000

/*============================================================================
 * The hostname could not be resolved.
 *===========================================================================*/
#define OpcUa_BadHostUnknown 0xA0060000

/*============================================================================
 * Too many posts were made to a semaphore.
 *===========================================================================*/
#define OpcUa_BadTooManyPosts 0xA0070000

/*============================================================================
 * The security configuration is not valid.
 *===========================================================================*/
#define OpcUa_BadSecurityConfig 0xA0080000

/*============================================================================
 * Invalid file name specified.
 *===========================================================================*/
#define OpcUa_BadFileNotFound 0xA0090000

/*============================================================================
 * Accept bad result and continue anyway.
 *===========================================================================*/
#define OpcUa_BadContinue 0xA00A0000

/*============================================================================
 * Accept bad result and continue anyway.
 *===========================================================================*/
#define OpcUa_BadHttpMethodNotAllowed 0xA00B0000

/*============================================================================
 * File exists.
 *===========================================================================*/
#define OpcUa_BadFileExists 0xA00C0000

/*============================================================================
 * Key is too short.
 *===========================================================================*/
#define OpcUa_BadCryptoKeyTooShort 0xA0120000

 /*============================================================================
 * Key is too long.
 *===========================================================================*/
#define OpcUa_BadCryptoKeyTooLong 0xA0130000

 /*============================================================================
 * Certificate signature algorithm not allowed.
 *===========================================================================*/
#define OpcUa_BadSignatureAlgorithmNotAllowed 0xA0140000

 /*============================================================================
 * Sender provided wrong receiver certificate thumbprint.
 *===========================================================================*/
#define OpcUa_BadWrongReceiverCertificate 0xA0150000

/*============================================================================
 * Message can not be sent, because it is too large.
 *===========================================================================*/
#define OpcUa_BadMessageTooLarge 0xA0160000

OPCUA_END_EXTERN_C

#endif /* _OpcUa_StackStatusCodes_H_ */
