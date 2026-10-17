#include "myappcallback.h"
#include "OPCUAMaster.h"
MyAppCallback::MyAppCallback()
{}

MyAppCallback::~MyAppCallback()
{}

bool MyAppCallback::onUserLogin(const UaString& username, const UaString& password)
{	
	COPCUAMaster *pOPCMaster = (COPCUAMaster*)m_opcUAMaterHandle;
	
	if (UaString(pOPCMaster->m_chUser) != username ||
		UaString(pOPCMaster->m_chPassWord) != password) return false;

	//if ((username == "root" && password == "secret") ||
	//	(username == "joe" && password == "god") ||
	//	(username == "john" && password == "master") ||
	//	(username == "sue" && password == "curly") ||
	//	(username == "sam" && password == "serious"))
	//{
	//	return true;
	//}

	return true;
}

