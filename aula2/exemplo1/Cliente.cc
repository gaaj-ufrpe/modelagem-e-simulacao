#include <string.h>
#include <omnetpp.h>
#include <math.h>


using namespace omnetpp;

class Cliente : public cSimpleModule {
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Cliente);

void Cliente::initialize() {
    SimTime time = simTime()+exponential(1.0);
    std::string text = "Message " + time.str();
    cMessage *postMsg = new cMessage(text.c_str());
    scheduleAt(time, postMsg);
}

void Cliente::handleMessage(cMessage *msg) {
    send(msg, "out");
    SimTime time = simTime()+exponential(1.0);
    std::string text = "Message " + time.str();
    cMessage *postMsg = new cMessage(text.c_str());
    scheduleAt(time, postMsg);
}
