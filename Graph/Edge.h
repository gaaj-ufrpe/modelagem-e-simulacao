#ifndef __MS_EDGE_H
#define __MS_EDGE_H

#include <string.h>
#include <omnetpp.h>
#include "Token.h"

using namespace omnetpp;

class Edge : public cChannel {
    private:
        double distance;
        bool special;

    protected:
        bool isTransmissionChannel() const override {return false;}
        simtime_t getTransmissionFinishTime() const override {return SimTime::ZERO;}
        double getNominalDatarate() const override {return 0.0;}
        simtime_t calculateDuration(cMessage *msg) const override {return SimTime::ZERO;}
        void forceTransmissionFinishTime(simtime_t t) override {}

        virtual void initialize() override {
            this->distance = par("distance");
            this->special = par("special");
        }

        void processMessage(cMessage *msg, simtime_t t, result_t& result) override {
            Token *token = (Token *)msg;
            if (!isAllowed(token)) {
                delete msg;
            }

            token->append(this->distance);
            //se o token for regular, o delay � igual � dist�ncia. Se n�o, � a metade da dist�ncia.
            double delay = this->distance;
            if (token->special) {
                delay = this->distance/2.0;
            }
            result.delay = delay;
        }

    public:
        //o token s� � permitido pelo caminho se for um token "special" ou se o caminho N�O for special (ou seja,
        //o caminho suporta tokens especiais e n�o especiais).
        bool isAllowed(Token *token) {
            return token->special || !(this->special);
        }
};
Define_Channel(Edge);

#endif
