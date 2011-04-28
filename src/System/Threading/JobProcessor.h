#ifndef JOBPROCESSOR_H
#define JOBPROCESSOR_H

#include "System/Containers/InQueue.h"
#include "ThreadPool.h"
#include "Job.h"

/*
===============================================================================================

 JobProcessor

===============================================================================================
*/

class JobProcessor
{
public:
    JobProcessor();
    
    void                    Start();
    void                    Stop();
    void                    Execute(Job* job);
    bool                    IsActive();
    Job*                    GetActiveJob();
    
private:
    void                    ThreadFunc();
    void                    OnComplete();

    Job*                    activeJob;
    InQueue<Job>            jobs;
    ThreadPool*             threadPool;
    Callable                threadFunc;
    Callable                onComplete;
};

#endif