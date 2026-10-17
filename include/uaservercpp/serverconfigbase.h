/******************************************************************************
** serverconfigbase.h
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
** Project: C++ OPC Server SDK core module
**
** Description: Configuration management class for the OPC Server.
**
******************************************************************************/
#ifndef SERVERCONFIGBASE_H
#define SERVERCONFIGBASE_H

#include "serverconfigdata.h"

class UaCoreServerApplication;
class UaServerApplicationCallback;
class UaEndpointBase;

/** This class represent a server configuration in memory without file access.
 *
 * This implementation of the ServerConfig interface can be used if a configuration
 * file cannot be used or the configuration is set from other product specific
 * information. File access is only required for certificat management.
 *
 * The following code provides an example for the use in a server
 *
 * @code
 * // Create and initialize server object
 * OpcServer* pServer = new OpcServer;
 *
 * // Set the callback for user authentication
 * MyServerCallback serverCallback;
 * pServer->setCallback(&serverCallback);
 *
 * // Create ServerConfig object without config file access
 * ServerConfigBase* pServerConfig = new ServerConfigBase(
 *     szAppPath,                           // Application path
 *     szAppPath,                           // Configuraiton path
 *     szAppPath,                           // Trace file path
 *     "urn:UnifiedAutomation:UaServerCpp", // Product URI
 *     "Unified Automation GmbH",           // Manufacturer name
 *     "C++ SDK OPC UA Demo Server",        // Product name
 *     SERVERCONFIG_SOFTWAREVERSION,        // Software version
 *     SERVERCONFIG_BUILDNUMBER,            // Build number
 *     "urn:[NodeName]:UnifiedAutomation:UaServerCpp", // Server instance URI
 *     "UaServerCpp@[NodeName]",            // Server instance name
 *     pServer,                             // Server application object
 *     &serverCallback);                    // User application callback
 *
 *                                          // trace configuration
 * pServerConfig->setStackTraceSettings(OpcUa_True, OPCUA_TRACE_OUTPUT_LEVEL_INFO);
 * pServerConfig->setServerTraceSettings(OpcUa_True, UaTrace::InterfaceCall, 100000, 5, "trace.txt", OpcUa_False);
 *
 * // Create endpoint configuration
 * UaEndpointBase* pEndpoint = new UaEndpointBase();
 * char szHostName[256] = "127.0.0.1"; // set default
 * UA_GetHostname(szHostName, 256);
 * pEndpoint->setEndpointUrl(UaString("opc.tcp://%1:48010").arg(szHostName), OpcUa_True);
 *
 * // add Endpoint with SecurityPolicy None
 * UaEndpointSecuritySetting securitySetting;
 * securitySetting.setSecurityPolicy(OpcUa_SecurityPolicy_None);
 * securitySetting.addMessageSecurityMode(OPCUA_ENDPOINT_MESSAGESECURITYMODE_NONE);
 * pEndpoint->addSecuritySetting(securitySetting);
 *
 * // add Endpoint with SecurityPolicy Basic256Sha256
 * securitySetting.setSecurityPolicy(OpcUa_SecurityPolicy_Basic256Sha256);
 * securitySetting.clearMessageSecurityModes();
 * securitySetting.addMessageSecurityMode(OPCUA_ENDPOINT_MESSAGESECURITYMODE_SIGN);
 * securitySetting.addMessageSecurityMode(OPCUA_ENDPOINT_MESSAGESECURITYMODE_SIGNANDENCRYPT);
 * pEndpoint->addSecuritySetting(securitySetting);
 *
 * // configure rejected directory
 * pServerConfig->setRejectedCertificatesDirectory(UaString("%1/pkiserver/rejected").arg(szAppPath));
 *
 * // configure available user tokens
 * pServerConfig->setEnableUserPw(OpcUa_True);
 * pServerConfig->setEnableCertificate(OpcUa_True);
 * pServerConfig->setUserIdentityTokenSecurityPolicy(OpcUa_SecurityPolicy_Basic256Sha256);
 * pServerConfig->setRejectedUserCertificatesCount(123);
 * pServerConfig->setRejectedUserCertificatesDirectory(UaString("%1/pkiuser/rejected").arg(szAppPath));
 *
 * // configure certificate store for user certificates
 * CertificateStoreConfiguration* pCertConfig = NULL;
 * UaString sRejected;
 * OpcUa_UInt32 nNumRejected = 0;
 * OpcUa_Boolean bCertTokenconfigured = OpcUa_False;
 *
 * pServerConfig->getDefaultUserCertificateStore(
 *     &pCertConfig,
 *     sRejected,
 *     nNumRejected,
 *     bCertTokenconfigured);
 *
 * pCertConfig->m_sCertificateTrustListLocation = UaString("%1/pkiuser/trusted/certs").arg(szAppPath);
 * pCertConfig->m_sCertificateRevocationListLocation = UaString("%1/pkiuser/trusted/crl").arg(szAppPath);
 * pCertConfig->m_sIssuersCertificatesLocation = UaString("%1/pkiuser/issuers/certs").arg(szAppPath);
 * pCertConfig->m_sIssuersRevocationListLocation = UaString("%1/pkiuser/issuers/crl").arg(szAppPath);
 *
 * // add Endpoint
 * pServerConfig->addEndpoint(pEndpoint);
 * // Set the configuration object for the server
 * pServer->setServerConfig(pServerConfig);
 * @endcode
 */
class SERVER_CORE_EXPORT ServerConfigBase : public ServerConfigData
{
    UA_DISABLE_COPY(ServerConfigBase);
public:
    ServerConfigBase(
        const UaString&              sApplicationPath,
        const UaString&              sConfigurationPath,
        const UaString&              sTracePath,
        const UaString&              sProductUri,
        const UaString&              sManufacturerName,
        const UaString&              sProductName,
        const UaString&              sSoftwareVersion,
        const UaString&              sBuildNumber,
        const UaString&              sServerInstanceUri,
        const UaString&              sServerInstanceName,
        UaCoreServerApplication*     pUaCoreServerApplication,
        UaServerApplicationCallback* pUaServerApplicationCallback);
    virtual ~ServerConfigBase();

    void addEndpoint(UaEndpointBase* pEndpoint);

    // Implement ServerConfigData
    virtual UaStatus afterLoadConfiguration();

    // Implement ServerConfig
    virtual UaStatus loadConfiguration();
    virtual UaStatus startUp(ServerManager* pServerManager);
    virtual UaStatus shutDown();
    virtual UaStatus saveConfiguration();
    virtual Session* createSession(OpcUa_Int32 sessionID, const UaNodeId &authenticationToken);
    virtual UaStatus logonSessionUser(Session* pSession, UaUserIdentityToken* pUserIdentityToken);

    // Additional Setter
    UaStatus setStackTraceSettings(
        OpcUa_Boolean bTraceEnabled,
        OpcUa_UInt32  uTraceLevel);

    UaStatus setServerTraceSettings(
        OpcUa_Boolean   bTraceEnabled,       //!< [in] Globally enable/disable trace output from the SDK
        OpcUa_UInt32    uTraceLevel,         /**< [in] Configures the level of messages traced
                                                - (0) NoTrace - No Trace
                                                - (1) Errors - Unexpected errors
                                                - (2) Warning - Unexpected behaviour that is not an error
                                                - (3) Info - Information about important activities like connection establishment
                                                - (4) InterfaceCall - Calls to module interfaces
                                                - (5) CtorDtor - Creation and destruction of objects
                                                - (6) ProgramFlow - Internal program flow
                                                - (7) Data - Data */
        OpcUa_UInt32    uMaxTraceEntries,    //!< [in] Maximum number of trace entries in one trace file
        OpcUa_UInt32    uMaxBackupFiles,     //!< [in] Maximum number of backup files
        const UaString& sTraceFile,          //!< [in] Name and path of the trace file
        OpcUa_Boolean   bDisableFlush        //!< [in] Disable flushing the trace file after each trace entry
    );

protected:
    UaCoreServerApplication*        m_pUaCoreServerApplication;
    UaServerApplicationCallback*    m_pUaServerApplicationCallback;
};

/** This class represent a endpoint configuration in memory without configuration file access.
*
* This implementation of the UaEndpoint interface can be used if a configuration
* file cannot be used or the configuration is set from other product specific
* information. File access is only required for certificat management.
*/
class SERVER_CORE_EXPORT UaEndpointBase : public UaEndpoint
{
    UA_DISABLE_COPY(UaEndpointBase);
public:
    /** construction. */
    UaEndpointBase();
    /** destruction */
    virtual ~UaEndpointBase();

    void setCertificateStore(OpcUa_UInt32 endpointCertificateStoreIndex, CertificateStoreConfiguration* pEndpointCertificateStore);
};

#endif // SERVERCONFIGBASE_H
