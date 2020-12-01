#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Maquina2 : public cSimpleModule {
  private:
    bool on = false;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Maquina2);

void Maquina2::initialize() {
    if (strcmp("m1", getName()) == 0) {
        cMessage *msg = new cMessage("switchMsg");
        send(msg, "out");
    }
}

void Maquina2::handleMessage(cMessage *msg) {
    this->on = !this->on;
    const char* txt = (this->on ? "on" : "off");
    const char* color = (this->on ? "green" : "red");
    bubble(txt);
    cDisplayString& ds = getDisplayString();
    ds.setTagArg("i",1,color);
    refreshDisplay();
    send(msg, "out");
}
