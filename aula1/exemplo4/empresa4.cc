#include <string.h>
#include <omnetpp.h>
#include <math.h>


using namespace omnetpp;

class Maquina4 : public cSimpleModule {
  private:
    bool on = false;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void updateDisplay();
    virtual int choose(int choices);
    virtual const char* getPort(int idx);

  public:
    void switchState() {
        on = !on;
    };
};

Define_Module(Maquina4);

void Maquina4::initialize() {
    if (strcmp("m1", getName()) == 0) {
        cMessage *msg = new cMessage("switchMsg");
        send(msg, "port1$o");
    }
}

int Maquina4::choose(int choices) {
    //a fun��o srand seta um seed aleat�rio e depois a fun��o rand
    //gera um n�mero aleat�rio. em seguida, o m�dulo gera um valor
    //inteiro de 0 at� choices-1
    std::srand(time(NULL));
    int rnum = std::rand();
    return rnum % choices;
}

std::string concat(const char* s1, const char* s2) {
    std::string result(s1);
    result.append(s2);
    return result;
}

const char* Maquina4::getPort(int idx=-1) {
    std::vector<const char *> gates = getGateNames();
    if (idx == -1) {
        //se o idx for -1, far� uma sele��o aleat�ria
        idx = choose(gates.size());
    }
    return gates.at(idx);
}

void Maquina4::handleMessage(cMessage *msg) {
    switchState();
    updateDisplay();
    //como as portas s�o do tipo inout, precisa concatenar com "$o"
    //para o envio e "$i" para o recebimento.
    std::string sendPort = concat(getPort(),"$o");
    send(msg,sendPort.c_str());
}

void Maquina4::updateDisplay() {
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
    //� preciso chamar o "refreshDisplay" para atualizar a exibi��o.
    //caso n�o chame esta fun��o, as altera��es n�o ser�o exibidas.
    refreshDisplay();
    bubble(txt2);
}
