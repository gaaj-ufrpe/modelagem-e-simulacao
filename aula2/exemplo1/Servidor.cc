#include <string.h>
#include <omnetpp.h>
#include <math.h>


using namespace omnetpp;
class Servidor : public cSimpleModule {
  protected:
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Servidor);

void Servidor::handleMessage(cMessage *msg) {
    EV << "Recebeu \"" << msg->getFullName() << "\""<< endl;
    delete msg;
}
