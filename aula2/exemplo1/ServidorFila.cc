#include <string.h>
#include <omnetpp.h>
#include <math.h>


using namespace omnetpp;
class ServidorFila : public cSimpleModule {
  private:
    cQueue fila;
    int capacidadeFila;
    double tempoProcessamento;
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
    tempoProcessamento = par("tempoProcessamento");
}

void ServidorFila::handleMessage(cMessage *msg) {
    EV << "Recebeu \"" << msg->getFullName() << "\"."<< endl;
    if (msg==msgFimProcesso) {
        EV << "Fim do processamento de \"" << processando->getFullName() << "\"." << endl;
        delete processando;
        if (fila.isEmpty()) {
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
    if (capacidadeFila > 0 && fila.getLength() == capacidadeFila) {
        EV << "Descartando \""<< msg->getFullName() << "\". Motivo: fila cheia (#fila: " << capacidadeFila << "." << endl;
        delete msg;
    } else {
        fila.insert(msg);
        EV << "Colocando \"" << msg->getFullName() << "\" na fila (#fila: " << fila.getLength() << ")." << endl;
    }
}

void ServidorFila::processar(cMessage *msg) {
    simtime_t tempoServico = exponential(tempoProcessamento);
    EV << "Processando \"" << msg->getFullName() << "\" por " << tempoServico << "s." << endl;
    scheduleAt(simTime()+tempoServico, msgFimProcesso);
}

