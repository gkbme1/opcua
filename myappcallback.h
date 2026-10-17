#ifndef MYAPPCALLBACK_H
#define MYAPPCALLBACK_H

#include "uagatewayapplicationcallback.h"

class MyAppCallback : public UaGatewayApplicationCallback
{
public:
	MyAppCallback();
	virtual ~MyAppCallback();
	
public:	
	bool onUserLogin(const UaString& username, const UaString& password);
	void* m_opcUAMaterHandle;
};	

#endif