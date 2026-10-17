#ifndef UAGATEWAYAPPLICATIONCALLBACK_H
#define UAGATEWAYAPPLICATIONCALLBACK_H

#include "uaserverapplication.h"

class UaGatewayApplicationCallback : public UaServerApplicationCallback
{
public:
	UaGatewayApplicationCallback();
	virtual ~UaGatewayApplicationCallback();

	virtual bool onUserLogin(const UaString& username, const UaString& password);
	virtual void afterNodeManagersStarted();
	virtual void afterLoadConfiguration(ServerConfig* pServerConfig);
public:
	Session* createSession(OpcUa_Int32 sessionID, const UaNodeId& authenticationToken);

	UaStatus logonSessionUser(Session* pSession, UaUserIdentityToken* pUserIdentityToken, ServerConfig* pServerConfig);
#if OPCUA_SUPPORT_PKI
	UaStatus validateCertificate(const UaByteString& certificate);
#endif //OPCUA_SUPPORT_PKI

#if OPCUA_SUPPORT_PKI
	UaString m_sCertificateTrustListLocation;
	UaString m_sCertificateRevocationListLocation;
	UaString m_sIssuersCertificatesLocation;
	UaString m_sIssuersRevocationListLocation;
	UaString m_sRejectedFolder;
	OpcUa_UInt32 m_nRejectedCertificatesCount;
	OpcUa_Boolean m_bCertificateTokenConfigured;
#endif //OPCUA_SUPPORT_PKI
};

#endif