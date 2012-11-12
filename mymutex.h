/*
    This file is a part of the MyThread package, which contains some Object-Oriented thread
    wrappers for different thread implementations.
*/

#ifndef _MYMUTEX_H_

#define _MYMUTEX_H_

#include "threadconfig.h"

#ifdef MYTHREAD_CONFIG_WIN32THREADS
#ifndef _WIN32_WCE
    #include <process.h>
#endif  //_WIN32_WCE
    #include <winsock2.h>
    #include <windows.h>
#else  //using pthread
    #include <pthread.h>
#endif

#define ERR_MUTEX_ALREADY_INIT          -1
#define ERR_MUTEX_NOT_INIT                  -2
#define ERR_MUTEX_CANT_CREATE_MTX  -3

namespace mythread
{

class THREAD_IMPORT_EXPORT MyMutex
{
public:
    MyMutex():initialized_(false){}
    ~MyMutex(){if (initialized_) pthread_mutex_destroy(&mutex_);}

    int init();
    int lock();
    int unlock();
    bool is_init() {return initialized_;}

private:
    bool initialized_;

#ifdef MYTHREAD_CONFIG_WIN32THREADS
#ifdef MYTHREAD_CONFIG_MUTEX_CRITICAL_SECTION
    CRITICAL_SECTION mutex_;
#else
    HANDLE mutex_;
#endif
#else
    pthread_mutex_t mutex_;
#endif
};

}

#endif

