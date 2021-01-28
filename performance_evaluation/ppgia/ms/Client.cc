#include <string.h>
#include <omnetpp.h>
#include <math.h>
#include "Job.h"

using namespace omnetpp;
using namespace ms;

class Client : public cSimpleModule {
    private:
        double delay;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void sendMsg();
};

Define_Module(Client);

void Client::initialize() {
    delay = par("delay");
    sendMsg();
}

void Client::handleMessage(cMessage *msg) {
    EV << "Sent \"" << msg->getFullName() << "\"" << endl;
    send(msg, "out");
    sendMsg();
}

void Client::sendMsg() {
    SimTime time = simTime() + exponential(delay);
    std::string text = "Task " + time.str();
    Job *job = new Job(text.c_str());
    scheduleAt(time, job);
}
