#ifndef __MS_TOKEN_H
#define __MS_TOKEN_H

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

//representa um "token" que irá trafegar pelo grafo. O token pode ser regular o especial
//o token deverá armazenar a distância total percorrida. Assim, a cada "edge", a distância do "edge" será adicionada ao token.
class Token : public cMessage {
    public:
        double totalDistance = 0.0;
        simtime_t timestamp;
        bool special;
        Token(bool special=false, std::string name=("Msg "+simTime().str()));
        void append(double distance) {
            this->totalDistance += distance;
        }
};

#endif
