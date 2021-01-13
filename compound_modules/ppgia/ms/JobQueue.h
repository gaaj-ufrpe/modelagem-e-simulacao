#ifndef __MS_JOB_QUEUE_H
#define __MS_JOB_QUEUE_H

#include <omnetpp.h>
#include "Job.h"

using namespace omnetpp;

namespace ms {

    class JobQueue : public cQueue {
        private:
            int capacity;
        public:
            JobQueue();
            JobQueue(int capacity);
            virtual bool enqueue(Job *job);
            virtual Job* dequeue();
    };

};//namespace

#endif
