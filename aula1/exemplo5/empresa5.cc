#include <string.h>
#include <omnetpp.h>
#include <math.h>


using namespace omnetpp;

class Maquina5 : public cSimpleModule {
  private:
    bool on = false;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void updateDisplay();
    virtual int choose(int choices);
    virtual int randomPortIndex();

  public:
    void switchState() {
        on = !on;
    };
};

Define_Module(Maquina5);

int Maquina5::choose(int choices) {
    //a função srand seta um seed aleatório e depois a função rand
    //gera um número aleatório. em seguida, o módulo gera um valor
    //inteiro de 0 até choices-1
    std::srand(time(NULL));
    int rnum = std::rand();
    return rnum % choices;
}

int Maquina5::randomPortIndex() {
    return choose(gateSize("port"));
}

void Maquina5::updateDisplay() {
    const char* txt2 = "off";
    const char* color = "red";
    const char* status = "status/red";
    if (on) {
        txt2 = "on";
        color = "green";
        status = "status/green";
    }
    cDisplayString& ds = getDisplayString();
    ds.setTagArg("i2", 0, status);
    ds.setTagArg("i", 1, color);
    //é preciso chamar o "refreshDisplay" para atualizar a exibição.
    //caso não chame esta função, as alterações não serão exibidas.
    refreshDisplay();
    bubble(txt2);
}

void Maquina5::initialize() {
    if (getIndex() == 0) {
        cMessage *msg = new cMessage("switchMsg");
        send(msg, "port$o", randomPortIndex());
    }
}

void Maquina5::handleMessage(cMessage *msg) {
    switchState();
    updateDisplay();
    send(msg, "port$o", randomPortIndex());
}
