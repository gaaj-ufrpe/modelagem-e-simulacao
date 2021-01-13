#ifndef __MS_JOB_H
#define __MS_JOB_H

#include <string.h>
#include <omnetpp.h>
#include <math.h>

using namespace omnetpp;

namespace ms {

    class Job : public cMessage {
        public:
            Job(const char *name=("Job "+simTime().str()).c_str());
    };

};//namespace

#endif
