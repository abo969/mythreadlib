/*
    This file is a part of the MyThread package, which contains some Object-Oriented thread
    wrappers for different thread implementations.
*/

#ifndef _THREAD_MUTEXAUTOLOCK_H_

#define _THREAD_MUTEXAUTOLOCK_H_

#include "threadconfig.h"
#include "mymutex.h"

namespace mythread
{

class THREAD_IMPORT_EXPORT MutexAutoLock
{
private:
    MyMutex &mutex_;

public:
    MutexAutoLock(MyMutex &m): mutex_(m) {mutex_.lock();}
    ~MutexAutoLock() {mutex_.unlock();}
};

}

#endif


