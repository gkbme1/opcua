#include "uagatewayapplicationcallback.h"
#include "serverconfigdata.h"
#include "roletypeoperations.h"
#include "sessionusercontextbase.h"
#include "uasession.h"

#if OPCUA_SUPPORT_PKI
#include "opcua_core.h"
#include "uapkicertificate.h"
#include "uadir.h"
#endif //OPCUA_SUPPORT_PKI
UaGatewayApplicationCallback::UaGatewayApplicationCallback()
{}

UaGatewayApplicationCallback::~UaGatewayApplicationCallback()
{}

bool UaGatewayApplicationCallback::onUserLogin(const UaString& username, const UaString& password)
{
	return false;
}

Session* UaGatewayApplicationCallback::createSession(OpcUa_Int32 sessionID, const UaNodeId& authenticationToken)
{
	UaSession* pSession = new UaSession(sessionID, authenticationToken);
	return pSession;
}

UaStatus UaGatewayApplicationCallback::logonSessionUser(
	Session* pSession,
	UaUserIdentityToken* pUserIdentityToken,
	ServerConfig* pServerConfig)
{
	OpcUa_Boolean  bEnableAnonymous;
	OpcUa_Boolean  bEnableUserPw;
	OpcUa_Boolean  bEnableCertificate;
	OpcUa_Boolean  bEnableKerberosTicket;

	pServerConfig->getUserIdentityTokenConfig(bEnableAnonymous, bEnableUserPw, bEnableCertificate, bEnableKerberosTicket);

	if (pUserIdentityToken->getTokenType() == OpcUa_UserTokenType_Anonymous)
	{
		if (bEnableAnonymous == OpcUa_False)
		{
			// Return error if Anonymous is not enabled
			return OpcUa_BadIdentityTokenRejected;
		}
		else
		{
			SessionUserContext* pUserContext = new SessionUserContextBase();
			pUserContext->setIdentity(pUserIdentityToken);
			pSession->setUserContext(pUserContext);
			UaStatus ret = NodeManagerRoot::CreateRootNodeManager()->pServerManager()->setRoleIds(pSession);
			UA_ASSERT(ret.isGood());
			pUserContext->releaseReference();

			return OpcUa_Good;
		}
	}
	
	else if (OpcUa_UserTokenType_UserName == pUserIdentityToken->getTokenType())
	{
		if (bEnableUserPw == OpcUa_False)
		{
			// Return error if User/Password is not enabled
			return OpcUa_BadIdentityTokenRejected;
		}
		else
		{
		
			UaUserIdentityTokenUserPassword* pUserPassword = static_cast<UaUserIdentityTokenUserPassword*>(pUserIdentityToken);

			if (!onUserLogin(pUserPassword->sUserName, pUserPassword->sPassword)) return OpcUa_BadIdentityTokenRejected;

			SessionUserContext* pUserContext = new SessionUserContextBase();
			pUserContext->setIdentity(pUserIdentityToken);
			pSession->setUserContext(pUserContext);
			UaStatus ret = NodeManagerRoot::CreateRootNodeManager()->pServerManager()->setRoleIds(pSession);
			UA_ASSERT(ret.isGood());
			pUserContext->releaseReference();
			return OpcUa_Good;
		}
	}
	else if (pUserIdentityToken->getTokenType() == OpcUa_UserTokenType_Certificate)
	{
#if OPCUA_SUPPORT_PKI
		if (bEnableCertificate == OpcUa_False || m_bCertificateTokenConfigured == OpcUa_False)
		{
			// Return error if CertificateToken is not enabled
			return OpcUa_BadIdentityTokenRejected;
		}
		else
		{
			// Just check if the certificate it trusted - we don't map this to a known user
			UaUserIdentityTokenCertificate* pUserCertToken = (UaUserIdentityTokenCertificate*)pUserIdentityToken;

			// create certificate object to get name and thumbprint
			UaPkiCertificate pkiCertificate = UaPkiCertificate::fromDER(pUserCertToken->userCertificateData);

			// validate the user certificate against the user certificate store
			UaStatus ret = validateCertificate(pUserCertToken->userCertificateData);

			// the certificate is trusted so we accept the user
			if (ret.isGood())
			{
				SessionUserContextBase* pUserContext = new SessionUserContextBase();
				pUserContext->setIdentity(pUserIdentityToken);
				pSession->setUserContext(pUserContext);
				// Set the roles for the session based on the thumbprint
				ret = NodeManagerRoot::CreateRootNodeManager()->pServerManager()->setRoleIds(pSession);
				UA_ASSERT(ret.isGood());
				pUserContext->releaseReference();
			}
			// Copy the certificate into the rejected folder
			else
			{
				// Get count of files in the directory
				UaDir dirHelper("");
				OpcUa_UInt16 rejectedCertCount = dirHelper.recursiveFileCount(m_sRejectedFolder.toUtf16());

				// Check number of rejected certifiates to respect the m_nRejectedCertificatesCount
				if (rejectedCertCount <= m_nRejectedCertificatesCount)
				{
					UaString fileName = UaString("%1/%2.der")
						.arg(m_sRejectedFolder)
						.arg(pkiCertificate.thumbPrint().toHex());

					// save certificte
					pkiCertificate.toDERFile(UaDir::fromNativeSeparators(fileName.toUtf8()).toUtf16());
				}
				ret = OpcUa_BadIdentityTokenRejected;
			}
			return ret;
		}
#else//OPCUA_SUPPORT_PKI
		// Return error if PKI is not enabled
		return OpcUa_BadIdentityTokenRejected;
#endif //OPCUA_SUPPORT_PKI
	}
	//! [User Certificate Authentication]
	return OpcUa_BadIdentityTokenInvalid;

}

void UaGatewayApplicationCallback::afterNodeManagersStarted()
{
	// add identity mapping rules
	// e.g. john has Roles: DemoRole1, Operator
	ServerManager* pServerManager = NodeManagerRoot::CreateRootNodeManager()->pServerManager();

	// Add rules for well known roles
	RoleTypeOperations* pRoleTypeOperations;

	// Observer
	UaStatus ret = pServerManager->getRoleByNodeId(OpcUaId_WellKnownRole_Observer, &pRoleTypeOperations);
	if (ret.isGood())
	{
		// add john and joe
		UaIdentityMappingRuleType ruleToAdd;
		ruleToAdd.setCriteriaType(OpcUa_IdentityCriteriaType_UserName);
		ruleToAdd.setCriteria("john");
		pRoleTypeOperations->addIdentity(ruleToAdd);
		ruleToAdd.setCriteria("joe");
		pRoleTypeOperations->addIdentity(ruleToAdd);
	}
	else
	{
		UA_ASSERT(false);
	}

	// Operator
	ret = pServerManager->getRoleByNodeId(OpcUaId_WellKnownRole_Operator, &pRoleTypeOperations);
	if (ret.isGood())
	{
		// add john and sue
		UaIdentityMappingRuleType ruleToAdd;
		//ruleToAdd.setCriteriaType(OpcUa_IdentityCriteriaType_UserName);
		//ruleToAdd.setCriteria("john");
		//pRoleTypeOperations->addIdentity(ruleToAdd);
		ruleToAdd.setCriteriaType(OpcUa_IdentityCriteriaType_UserName);
		ruleToAdd.setCriteria("sue");
		pRoleTypeOperations->addIdentity(ruleToAdd);
	}
	else
	{
		UA_ASSERT(false);
	}

	// ConfigureAdmin
	ret = pServerManager->getRoleByNodeId(OpcUaId_WellKnownRole_ConfigureAdmin, &pRoleTypeOperations);
	if (ret.isGood())
	{
		// add root john and sam
		UaIdentityMappingRuleType ruleToAdd;
		//ruleToAdd.setCriteriaType(OpcUa_IdentityCriteriaType_UserName);
		//ruleToAdd.setCriteria("john");
		//pRoleTypeOperations->addIdentity(ruleToAdd);
		ruleToAdd.setCriteria("sam");
		pRoleTypeOperations->addIdentity(ruleToAdd);
		// adding root here isn't really necessary because we set the root flag in logonSessionUser
		// we still add a mapping rule to make it visible in the address space
		ruleToAdd.setCriteria("root");
		pRoleTypeOperations->addIdentity(ruleToAdd);
	}
	else
	{
		UA_ASSERT(false);
	}

	// SecurityAdmin
	ret = pServerManager->getRoleByNodeId(OpcUaId_WellKnownRole_SecurityAdmin, &pRoleTypeOperations);
	if (ret.isGood())
	{
		// add root and sam
		UaIdentityMappingRuleType ruleToAdd;
		ruleToAdd.setCriteriaType(OpcUa_IdentityCriteriaType_UserName);
		ruleToAdd.setCriteria("sam");
		pRoleTypeOperations->addIdentity(ruleToAdd);
		// adding root here isn't really necessary because we set the root flag in logonSessionUser
		// we still add a mapping rule to make it visible in the address space
		ruleToAdd.setCriteria("root");
		pRoleTypeOperations->addIdentity(ruleToAdd);
	}
	else
	{
		UA_ASSERT(false);
	}

	// DemoRole1
	ret = pServerManager->getRoleByName("MyDemoRole1", "", &pRoleTypeOperations);
	if (ret.isGood())
	{
		// add joe and sue
		UaIdentityMappingRuleType ruleToAdd;
		ruleToAdd.setCriteriaType(OpcUa_IdentityCriteriaType_UserName);
		ruleToAdd.setCriteria("joe");
		pRoleTypeOperations->addIdentity(ruleToAdd);
		//ruleToAdd.setCriteria("sue");
		//pRoleTypeOperations->addIdentity(ruleToAdd);
	}
	else
	{
		UA_ASSERT(false);
	}

	// DemoRole2
	ret = pServerManager->getRoleByName("MyDemoRole2", "http://www.unifiedautomation.com/DemoServer/", &pRoleTypeOperations);
	if (ret.isGood())
	{
		// add Sue
		UaIdentityMappingRuleType ruleToAdd;
		ruleToAdd.setCriteriaType(OpcUa_IdentityCriteriaType_UserName);
		//ruleToAdd.setCriteria("sue");
		//pRoleTypeOperations->addIdentity(ruleToAdd);
	}
	else
	{
		UA_ASSERT(false);
	}
}

void UaGatewayApplicationCallback::afterLoadConfiguration(ServerConfig* pServerConfig)
{
	ServerConfigData* pServerConfigData = (ServerConfigData*)pServerConfig;

	// Make sure the demo server product information can not be overwritten by the config file
	pServerConfigData->setProductUri("urn:UnifiedAutomation:UaServerCpp");
	pServerConfigData->setManufacturerName("Unified Automation GmbH");
	pServerConfigData->setProductName("C++ SDK OPC UA Demo Server");
	pServerConfigData->setSoftwareVersion(SERVERCONFIG_SOFTWAREVERSION);
	pServerConfigData->setBuildNumber(SERVERCONFIG_BUILDNUMBER);


#if OPCUA_SUPPORT_PKI
	CertificateStoreConfiguration* pCertificateStore = NULL;
	UaString sRejectedCertificateDirectory;
	OpcUa_UInt32 nRejectedCertificatesCount;
	OpcUa_Boolean bCertificateTokenConfigured = OpcUa_False;

	pServerConfigData->getDefaultUserCertificateStore(
		&pCertificateStore,
		sRejectedCertificateDirectory,
		nRejectedCertificatesCount,
		bCertificateTokenConfigured);

	m_sCertificateTrustListLocation = pCertificateStore->m_sCertificateTrustListLocation;
	m_sCertificateRevocationListLocation = pCertificateStore->m_sCertificateRevocationListLocation;
	m_sIssuersCertificatesLocation = pCertificateStore->m_sIssuersCertificatesLocation;
	m_sIssuersRevocationListLocation = pCertificateStore->m_sIssuersRevocationListLocation;
	m_sRejectedFolder = sRejectedCertificateDirectory;
	m_nRejectedCertificatesCount = nRejectedCertificatesCount;
	m_bCertificateTokenConfigured = bCertificateTokenConfigured;

	//char chbuf[1024] = { 0 };
	//memcpy(chbuf, m_sCertificateTrustListLocation.toLocal8Bit().data(), m_sCertificateTrustListLocation.toLocal8Bit().size());
	//memset(chbuf, 0,sizeof(chbuf));
	//memcpy(chbuf, m_sCertificateRevocationListLocation.toLocal8Bit().data(), m_sCertificateRevocationListLocation.toLocal8Bit().size());
	//memset(chbuf, 0, sizeof(chbuf));
	//memcpy(chbuf, m_sIssuersCertificatesLocation.toLocal8Bit().data(), m_sIssuersCertificatesLocation.toLocal8Bit().size());
	//memset(chbuf, 0, sizeof(chbuf));
	//memcpy(chbuf, m_sIssuersRevocationListLocation.toLocal8Bit().data(), m_sIssuersRevocationListLocation.toLocal8Bit().size());
	//memset(chbuf, 0, sizeof(chbuf));
	//memcpy(chbuf, m_sRejectedFolder.toLocal8Bit().data(), m_sRejectedFolder.toLocal8Bit().size());
	//memset(chbuf, 0, sizeof(chbuf));


	// make sure the paths all exist
	if (bCertificateTokenConfigured)
	{
		UaDir dirHelper("");
		UaUniString usPath;
		usPath = UaUniString(UaDir::fromNativeSeparators(m_sCertificateTrustListLocation.toUtf16()));
		dirHelper.mkpath(usPath);
		usPath = UaUniString(UaDir::fromNativeSeparators(m_sCertificateRevocationListLocation.toUtf16()));
		dirHelper.mkpath(usPath);
		usPath = UaUniString(UaDir::fromNativeSeparators(m_sIssuersCertificatesLocation.toUtf16()));
		dirHelper.mkpath(usPath);
		usPath = UaUniString(UaDir::fromNativeSeparators(m_sIssuersRevocationListLocation.toUtf16()));
		dirHelper.mkpath(usPath);
		usPath = UaUniString(UaDir::fromNativeSeparators(m_sRejectedFolder.toUtf16()));
		dirHelper.mkpath(usPath);
	}
#endif //OPCUA_SUPPORT_PKI
}

#if OPCUA_SUPPORT_PKI
UaStatus UaGatewayApplicationCallback::validateCertificate(const UaByteString& certificate)
{
	UaStatus ret;

	// create configuration for PkiProvider
	OpcUa_CertificateStoreConfiguration pkiConfig;
	OpcUa_CertificateStoreConfiguration_Initialize(&pkiConfig);
	OpcUa_UInt32 length;
	UaByteArray baTmp;

	// PkiType
	length = OpcUa_StrLenA(OPCUA_P_PKI_TYPE_OPENSSL);
	if (length > 0)
	{
		pkiConfig.strPkiType = (OpcUa_StringA)OpcUa_Alloc(length + 1);
		OpcUa_StrnCpyA(pkiConfig.strPkiType, OPCUA_P_PKI_TYPE_OPENSSL, length + 1);
	}

	// CertificateRevocationListLocation
	if (m_sCertificateRevocationListLocation.length() > 0)
	{
		baTmp = m_sCertificateRevocationListLocation.toLocal8Bit();
		pkiConfig.strRevokedCertificateListLocation = (OpcUa_StringA)OpcUa_Alloc(baTmp.size());
		OpcUa_MemCpy(pkiConfig.strRevokedCertificateListLocation, baTmp.size(), baTmp.data(), baTmp.size());
	}

	// TrustedCertificateListLocation
	if (m_sCertificateTrustListLocation.length() > 0)
	{
		baTmp = m_sCertificateTrustListLocation.toLocal8Bit();
		pkiConfig.strTrustedCertificateListLocation = (OpcUa_StringA)OpcUa_Alloc(baTmp.size());
		OpcUa_MemCpy(pkiConfig.strTrustedCertificateListLocation, baTmp.size(), baTmp.data(), baTmp.size());
	}

	// RevokedIssuerCertificateListLocation and IssuersCertificatesLocation
	if (m_sIssuersRevocationListLocation.length() > 0 && m_sIssuersCertificatesLocation.length() > 0)
	{
		baTmp = m_sIssuersRevocationListLocation.toLocal8Bit();
		pkiConfig.strRevokedIssuerCertificateListLocation = (OpcUa_StringA)OpcUa_Alloc(baTmp.size());
		OpcUa_MemCpy(pkiConfig.strRevokedIssuerCertificateListLocation, baTmp.size(), baTmp.data(), baTmp.size());

		baTmp = m_sIssuersCertificatesLocation.toLocal8Bit();
		pkiConfig.strIssuerCertificateStoreLocation = (OpcUa_StringA)OpcUa_Alloc(baTmp.size());
		OpcUa_MemCpy(pkiConfig.strIssuerCertificateStoreLocation, baTmp.size(), baTmp.data(), baTmp.size());
	}

	pkiConfig.uFlags = OPCUA_P_PKI_OPENSSL_CHECK_REVOCATION_STATUS;
	pkiConfig.pvOverride = NULL;
	pkiConfig.pfVerifyCallback = NULL;
	pkiConfig.pvVerifyCallbackUserData = NULL;

	// create Pki Provider with the configuration setup above
	OpcUa_PKIProvider pkiProvider;
	OpcUa_PKIProvider_Create(&pkiConfig, &pkiProvider);

	// open the certificate store
	OpcUa_Handle hCertificateStore;
	ret = pkiProvider.OpenCertificateStore(
		&pkiProvider,
		&hCertificateStore);

	// validate the certificate
	if (ret.isGood())
	{
		OpcUa_Int validationCode;
		ret = pkiProvider.ValidateCertificate(
			&pkiProvider,
			(const OpcUa_ByteString*)certificate,
			hCertificateStore,
			&validationCode);

		// close the certificate store
		pkiProvider.CloseCertificateStore(
			&pkiProvider,
			&hCertificateStore);
	}

	OpcUa_CertificateStoreConfiguration_Clear(&pkiConfig);
	return ret;
}
#endif //OPCUA_SUPPORT_PKI