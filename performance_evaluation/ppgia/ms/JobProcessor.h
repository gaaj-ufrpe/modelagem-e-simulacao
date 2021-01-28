#ifndef __MS_JOB_PROCESSOR_H
#define __MS_JOB_PROCESSOR_H

#include <omnetpp.h>
#include "Job.h"
#include "JobQueue.h"

using namespace omnetpp;

namespace ms {

class JobProcessor : public cSimpleModule {
    private:
        simsignal_t queueLengthSignal;
        simsignal_t droppedSignal;
        simsignal_t busySignal;
        Job *processing;
        Job *finishJob;
        virtual void handleExternalJob(Job *job);
        virtual void startProcessing();
        virtual void finishProcessing();

    public:
        virtual ~JobProcessor() override;

    protected:
        double delay;
        JobQueue queue;
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual simtime_t serviceTime(Job *job);
        virtual void process(Job *job);
};

};//namespace

#endif
