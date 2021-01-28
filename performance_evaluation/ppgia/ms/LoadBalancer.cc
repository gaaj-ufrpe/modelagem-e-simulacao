#include <string.h>
#include <omnetpp.h>
#include <math.h>

#include "JobProcessor.h"

using namespace omnetpp;
using namespace ms;

class LoadBalancer : public JobProcessor {
    private:
        int nextGate = 0;

    protected:
        virtual void process(Job *job) override;
};

Define_Module(LoadBalancer);

void LoadBalancer::process(Job *job) {
    EV << "Sending \"" << job->getFullName() <<
            "\" to Server[" << nextGate << "]." << endl;
    send(job, "out", nextGate++);
    if (nextGate == gateSize("out")) {
        nextGate = 0;
    }
}
