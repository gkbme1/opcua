#include "shutdownsignal.h"
#include "uathread.h"

# ifndef WIN32
#  include <unistd.h>
#  include <limits.h>
# endif

/* shutdown flag */
static volatile unsigned int g_ShutDown = 0;

#ifdef _WIN32_WCE
#  include <windows.h>
#elif defined(_WIN32) && !defined(USE_CTRLC_ON_WINDOWS)
#  include <conio.h> /* DOS header for _kbhit() and _getch() */
#endif

/* Return shutdown flag. */
unsigned int ShutDownFlag()
{
#if defined(_WIN32) && !defined(USE_CTRLC_ON_WINDOWS)
#ifndef _WIN32_WCE
    if (_kbhit() && _getch() == 'x') return 1;
    else return 0;
#else
    if (GetAsyncKeyState(VK_ESCAPE)) return 1;
    else return 0;
#endif
#else
    return g_ShutDown;
#endif
}

/****************************************
 * Linux SIGINT Handler implementation. *
 ****************************************/
#ifdef __linux__
#include <signal.h>

 /** Signal handler for SIG_INT and SIGTERM. */
void signal_handler(int signo)
{
    SHUTDOWN_TRACE("Received signal %i\n", signo);
    g_ShutDown = 1;
}

void RegisterSignalHandler()
{
    /* register signal handlers. */
    struct sigaction new_action, old_action;

    /* Set up the structure to specify the new action. */
    new_action.sa_handler = signal_handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;

    /* install new signal handler for SIGINT */
    sigaction(SIGINT, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
    {
        sigaction(SIGINT, &new_action, NULL);
    }
    /* install new signal handler for SIGTERM */
    sigaction(SIGTERM, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
    {
        sigaction(SIGTERM, &new_action, NULL);
    }

    /* Set up the structure to prevent program termination on interrupted connections. */
    new_action.sa_handler = SIG_IGN;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;

    /* install new signal handler for SIGPIPE*/
    sigaction(SIGPIPE, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
    {
        sigaction(SIGPIPE, &new_action, NULL);
    }
}
#elif defined(_WIN32)
 /******************************************
  * Windows CTRL-C Handler implementation. *
  ******************************************/
# ifdef USE_CTRLC_ON_WINDOWS
#  include <windows.h>
#  include <conio.h>
BOOL CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
        SHUTDOWN_TRACE("Received CTRL-C signal.\n");
        g_ShutDown = 1;
        return(TRUE);
    default:
        break;
    }
    return FALSE;
}
void RegisterSignalHandler()
{
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
}
# else /* USE_CTRLC_ON_WINDOWS */
void RegisterSignalHandler()
{
}
# endif /* USE_CTRLC_ON_WINDOWS */
#else /* __linux__ */
 /********************************************************************
  * Dummy implementation for embedded systems. They never shut down. *
  ********************************************************************/
void RegisterSignalHandler()
{
}
#endif



ShutdownSignal::ShutdownSignal()
{
    RegisterSignalHandler();
}

ShutdownSignal::~ShutdownSignal()
{}

bool ShutdownSignal::isShutdownSignalSet()
{
    return (0 != ShutDownFlag()) ? true : false;
}

void ShutdownSignal::sleep(unsigned int msec)
{
    UaThread::msleep(msec);
}