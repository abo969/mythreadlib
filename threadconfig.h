/*
    This file is a part of the MyThread package, which contains some Object-Oriented thread
    wrappers for different thread implementations.
*/

#ifndef _THREAD_CONFIG_H_
#define _THREAD_CONFIG_H_

#define THREAD_IMPORT
#define THREAD_EXPORT

#ifdef THREAD_COMPILING
#define THREAD_IMPORT_EXPORT THREAD_EXPORT
#else
#define THREAD_IMPORT_EXPORT THREAD_IMPORT
#endif

#endif


