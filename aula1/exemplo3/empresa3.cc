#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Maquina3 : public cSimpleModule {
  private:
    bool on = false;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void updateDisplay();

  public:
    void switchState() {
        on = !on;
    };
};

Define_Module(Maquina3);

void Maquina3::initialize() {
    if (strcmp("m1", getName()) == 0) {
        cMessage *msg = new cMessage("switchMsg");
        send(msg, "out");
    }
}

void Maquina3::handleMessage(cMessage *msg) {
    switchState();
    updateDisplay();
    send(msg, "out");
    //TODO criar exemplo 4 com aleatoriedade na direção da mensagem
}

void Maquina3::updateDisplay() {
    const char* txt2 = "off";
    const char* color = "red";
    const char* status = "status/red";
    if (on) {
        txt2 = "on";
        color = "green";
        status = "status/green";
    }
    cDisplayString& ds = getDisplayString();
    ds.setTagArg("i2",0,status);
    ds.setTagArg("i",1,color);
    refreshDisplay();
    bubble(txt2);
}
