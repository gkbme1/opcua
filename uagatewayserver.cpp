#include "uagatewayserver.h"
#include "uaplatformlayer.h"
#include "xmldocument.h"

UaGatewayServer::UaGatewayServer()
{}

UaGatewayServer::~UaGatewayServer()
{}

bool UaGatewayServer::initialize()
{    
    UaXmlDocument::initParser();
    if (0 != UaPlatformLayer::init()) return false;
    return true;
}

void UaGatewayServer::finalize()
{
    UaPlatformLayer::cleanup();
    UaXmlDocument::cleanupParser();
}

bool UaGatewayServer::startServer(
    const UaString& configDir,
    UaGatewayNodeManager* pNodeManager,
    UaGatewayApplicationCallback* pApplicationCallback)
{    
    if (OpcUa_Null == pApplicationCallback) return false;
         


    UaString configFile = configDir;
    //configFile += UaString("/ServerConfig.xml");


    setServerConfig(configFile, configDir);
    setCallback(pApplicationCallback);


    if (OpcUa_Null != pNodeManager)
    {
        this->addNodeManager(pNodeManager);
    }    
    
    if (0 != this->start()) return false;

    return true;
}

void UaGatewayServer::stopServer()
{    
    this->stop(3, UaLocalizedText("", "User shutdown"));
}

UaStatus UaGatewayServer::afterStartUp()
{
    return UaServerApplication::afterStartUp();
}

