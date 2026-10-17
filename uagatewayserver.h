#ifndef UAGATEWAYSERVER_H
#define UAGATEWAYSERVER_H

#include "uaserverapplication.h"
#include "uagatewaynodemanager.h"
#include "uagatewayapplicationcallback.h"

class UaGatewayServer : public UaServerApplication
{
public:
	UaGatewayServer();
	virtual ~UaGatewayServer();

	static bool initialize();
	static void finalize();

	bool startServer(
		const UaString& configDir,
		UaGatewayNodeManager* pNodeManager,
		UaGatewayApplicationCallback* pApplicationCallback);

	void stopServer();

protected:
	UaStatus afterStartUp();
};	

#endif