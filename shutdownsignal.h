#ifndef SHUTDOWNSIGNAL_H
#define SHUTDOWNSIGNAL_H

class ShutdownSignal
{
public:
	ShutdownSignal();
	virtual ~ShutdownSignal();

	bool isShutdownSignalSet();

	void sleep(unsigned int msec);
};	

#endif