#include <string.h>
#include <omnetpp.h>
#include <math.h>

#include "JobProcessor.h"

using namespace omnetpp;
using namespace ms;

class Server : public JobProcessor {
    protected:
        virtual void process(Job *job) override;
};

Define_Module(Server);

void Server::process(Job *job) {
    delete job;
}
