/*
    This file is a part of the MyThread package, which contains some Object-Oriented thread 
    wrappers for different thread implementations.
*/

#include "mythread.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>


namespace mythread
{

MyThread::MyThread():
    retval_(NULL), running_(false), init_mtx_(false)
{
}

MyThread::~MyThread()
{
    kill();
}

int MyThread::start()
{
    int status;

    if (!init_mtx_)
    {
        if (!mutex_.is_init())
        {
            if (mutex_.init() < 0)
                return ERR_THREAD_CANT_INIT_MUTEX;
        }
        if (!continue_mtx_.is_init() < 0)
        {
            if (continue_mtx_.init() < 0)
                return ERR_THREAD_CANT_INIT_MUTEX;
        }
        if (!continue_mtx2_.is_init() < 0)
        {
            if (continue_mtx2_.init() < 0)
                return ERR_THREAD_CANT_INIT_MUTEX;
        }

        init_mtx_ = true;
    }

    mutex_.lock();
    if (running_)
    {
        mutex_.unlock();
        return ERR_THREAD_ALREADY_RUNNING;
    }
    mutex_.unlock();

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    continue_mtx_.lock();
    status = pthread_create(&threadid_, &attr, the_thread, this);
    pthread_attr_destroy(&attr);
    if (status != 0)
    {
        continue_mtx_.unlock();
        return ERR_THREAD_CANT_START_THREAD;
    }

    //wait until 'running_' is set
    mutex_.lock();
    while (!running_)
    {
        mutex_.unlock();

        struct timespec req, rem;
        req.tv_sec = 0;
        req.tv_nsec = 1000000;
        nanosleep(&req, &rem);

        mutex_.lock();
    }
    mutex_.unlock();

    continue_mtx_.unlock();
    continue_mtx2_.lock();
    continue_mtx2_.unlock();
    return 0;
}

int MyThread::kill()
{
    mutex_.lock();
    if (!running_)
    {
        mutex_.unlock();
        return ERR_THREAD_NOTRUNNING;
    }

    pthread_cancel(threadid_);
    running_ = false;
    mutex_.unlock();
    return 0;
}

bool MyThread::is_running()
{
    bool status;

    mutex_.lock();
    status = running_;
    mutex_.unlock();

    return status;    
}

void* MyThread::get_return_vaule()
{
    void *val;

    mutex_.lock();
    if (running_)
        val = NULL;
    else
        val = retval_;
    mutex_.unlock();

    return val;
}

void* MyThread::the_thread(void * param)
{
    MyThread *thread;
    void *ret;

    thread = (MyThread*)param;

    thread->continue_mtx2_.lock();

    thread->mutex_.lock();
    thread->running_ = true;
    thread->mutex_.unlock();

    thread->continue_mtx_.lock();
    thread->continue_mtx_.unlock();

    ret = thread->thread();

    thread->mutex_.lock();
    thread->running_ = false;
    thread->retval_ = ret;
    thread->mutex_.unlock();

    return NULL;
}

void MyThread::thread_started()
{
    continue_mtx2_.unlock();
}

}


