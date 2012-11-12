/*
    This file is a part of the Thread package, which contains some Object-Oriented thread
    wrappers for different thread implementations.
*/

#ifndef _MYTHREAD_H_

#define _MYTHREAD_H_

#include "threadconfig.h"
#include "mymutex.h"

#define ERR_THREAD_CANT_INIT_MUTEX       -1   /* cannot init mutex */
#define ERR_THREAD_CANT_START_THREAD  -2   /* cannot start thread */
#define ERR_THREAD_THREAD_FUNC_NOTSET -3 /* thread function not set */
#define ERR_THREAD_NOTRUNNING                 -4 /* not running */
#define ERR_THREAD_ALREADY_RUNNING       -5 /* already running */

namespace mythread
{

class THREAD_IMPORT_EXPORT MyThread
{
public:
    MyThread();
    virtual ~MyThread();

    int start();
    int kill();

    virtual void* thread() = 0;    
    bool is_running();
    void* get_return_vaule();

protected:
    void thread_started();

private:

#ifdef MYTHREAD_CONFIG_WIN32THREADS

#ifdef _WIN32_WCE
    DWORD threadid_;
    static DWORD WINAPI the_thread(void* param);
#else
    UINT threadid_;
    static UINT _stdcall the_thread(void* param);
#endif

    HANDLE thread_handle_;

#else
    static void* the_thread(void* param);
    pthread_t threadid_;

#endif

    void* retval_;
    bool running_;
    bool init_mtx_;
    MyMutex mutex_;
    MyMutex continue_mtx_;
    MyMutex continue_mtx2_;
};

}


#endif


