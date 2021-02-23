#include <string.h>
#include <omnetpp.h>
#include "Token.h"

using namespace omnetpp;

class Sink : public cSimpleModule {
private:
    simsignal_t pathDistance;
    simsignal_t regularPathDistance;
    simsignal_t specialPathDistance;
    simsignal_t pathDelay;
    simsignal_t regularPathDelay;
    simsignal_t specialPathDelay;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Sink);

void Sink::initialize() {
    this->pathDistance = registerSignal("pathDistance");
    this->regularPathDistance = registerSignal("regularPathDistance");
    this->specialPathDistance = registerSignal("specialPathDistance");
    this->pathDelay = registerSignal("pathDelay");
    this->regularPathDelay = registerSignal("regularPathDelay");
    this->specialPathDelay = registerSignal("specialPathDelay");
}

void Sink::handleMessage(cMessage *msg) {
    Token *token = (Token *)msg;
    double distance = token->totalDistance;
    simtime_t delay = simTime() - (token->timestamp);

    emit(this->pathDistance, distance);
    emit(this->pathDelay, delay);
    if (token->special) {
        emit(this->specialPathDistance, distance);
        emit(this->specialPathDelay, delay);
    } else {
        emit(this->regularPathDistance, distance);
        emit(this->regularPathDelay, delay);
    }

    delete msg;
}
