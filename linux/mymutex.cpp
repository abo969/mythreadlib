/*
    This file is a part of the MyThread package, which contains some Object-Oriented thread 
    wrappers for different thread implementations.
*/

#include "mymutex.h"

namespace mythread
{

int MyMutex::init()
{
    if (initialized_)
        return ERR_MUTEX_ALREADY_INIT;

    pthread_mutex_init(&mutex_, NULL);
    initialized_ = true;
    return 0;
}

int MyMutex::lock()
{
    if (!initialized_)
        return ERR_MUTEX_NOT_INIT;

    pthread_mutex_lock(&mutex_);
    return 0;
}

int MyMutex::unlock()
{
    if (!initialized_)
        return ERR_MUTEX_NOT_INIT;

    pthread_mutex_unlock(&mutex_);
    return 0;
}

}


