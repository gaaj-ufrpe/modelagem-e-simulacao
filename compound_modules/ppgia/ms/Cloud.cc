#include <string.h>
#include <omnetpp.h>
#include <math.h>

using namespace omnetpp;

class Cloud: public cSimpleModule {
    protected:
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Cloud);

void Cloud::handleMessage(cMessage *msg) {
    send(msg, msg->getArrivalGate());
}
