#include <string.h>
#include <omnetpp.h>
#include <math.h>


using namespace omnetpp;
class ServidorFila : public cSimpleModule {
  private:
    cQueue fila;
    int capacidadeFila;
    cMessage *processando;
    cMessage *msgFimProcesso;
    virtual void processar(cMessage *msg);
    virtual void colocarFila(cMessage *msg);

  public:
    int length();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ServidorFila);


void ServidorFila::initialize() {
    msgFimProcesso = new cMessage("fim");
    capacidadeFila = par("capacidadeFila");
}

void ServidorFila::handleMessage(cMessage *msg) {
    if (msg==msgFimProcesso) {
        if (fila.isEmpty()) {
            delete processando;
            processando = nullptr;
        } else {
            processando = check_and_cast<cMessage *>(fila.pop());
            processar(processando);
        }
    } else if (!processando) {
        processando = msg;
        processar(processando);
    } else {
        colocarFila(msg);
    }
}

void ServidorFila::colocarFila(cMessage *msg) {
    EV << fila.getLength() << " tarefas na fila.\n";
    if (capacidadeFila > 0 && fila.getLength() >= capacidadeFila) {
        EV << "Fila cheia! A tarefa \""<< msg->getFullName() << "\" foi descartada.\n";
        bubble("Tarefa descartada!");
        refreshDisplay();
    } else {
        EV << "Colocando a tarefa \"" << msg->getFullName() << "\" na fila." << endl;
        fila.insert(msg);
    }
}

void ServidorFila::processar(cMessage *msg) {
    simtime_t tempoServico = exponential(1.5);
    EV << "Processando \"" << msg->getFullName() << "\" em " << tempoServico << "s." << endl;
    scheduleAt(simTime()+tempoServico, msgFimProcesso);
}

