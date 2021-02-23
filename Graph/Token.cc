#include "Token.h"

Token::Token(bool special, std::string name) : cMessage(name.c_str(), 0) {
    this->special = special;
    this->timestamp = simTime();
};
