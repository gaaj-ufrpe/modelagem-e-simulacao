#include <string.h>
#include <omnetpp.h>
#include <math.h>


using namespace omnetpp;

class Cliente : public cSimpleModule {
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void enviarNovaMensagem();
};

Define_Module(Cliente);

void Cliente::initialize() {
    enviarNovaMensagem();
}

void Cliente::handleMessage(cMessage *msg) {
    EV << "Enviando \"" << msg->getFullName() << "\"" << endl;
    send(msg, "out");
    enviarNovaMensagem();
}

void Cliente::enviarNovaMensagem() {
    SimTime time = simTime()+exponential(1.0);
    std::string text = "Tarefa " + time.str();
    cMessage *postMsg = new cMessage(text.c_str());
    scheduleAt(time, postMsg);
}
