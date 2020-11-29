#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Maquina1 : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Maquina1);

void Maquina1::initialize()
{
    if (strcmp("m1", getName()) == 0) {
        cMessage *msg = new cMessage("switchMsg");
        send(msg, "out");
    }
}

void Maquina1::handleMessage(cMessage *msg)
{
    send(msg, "out");
}
