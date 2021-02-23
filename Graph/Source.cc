#include <string.h>
#include <omnetpp.h>
#include "Token.h"

using namespace omnetpp;

class Source : public cSimpleModule {
private:
    double delay;
protected:
    virtual int choose(int choices);
    virtual void sendNewMsg();
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Source);

int Source::choose(int choices) {
    std::srand(time(NULL));
    int rnum = std::rand();
    return rnum % choices;
}

//agenda para o tempo "delay" o envio de uma nova mensagem.
void Source::sendNewMsg(){
    SimTime sendTime = simTime()+delay;
    Token *msg;
    if (choose(2)==0) {
        msg = new Token(false, ("REGULAR "+simTime().str()));
    } else {
        msg = new Token(true, ("SPECIAL "+simTime().str()));
    }
    scheduleAt(sendTime, msg);
}

//recupera o parâmetro delay e chama o envio de uma mensagem
void Source::initialize(){
    this->delay = par("delay");
    sendNewMsg();
}

//recebe a mensagem que enviou para si próprio indicando para enviar a mensagem para o próximo componente.
//escolhe o caminho para o envio e envia a mensagem.
//cria uma nova mensagem e agenda para um novo tempo que é o tempo atual mais o período "delay"
void Source::handleMessage(cMessage *msg){
    int gateIndex = choose(gateSize("out"));
    send(msg, "out", gateIndex);
    sendNewMsg();
}
