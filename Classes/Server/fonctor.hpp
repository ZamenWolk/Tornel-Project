#ifndef CLASSES_SERVER_FONCTOR_HPP
#define CLASSES_SERVER_FONCTOR_HPP

#include "Subservers.hpp"

class InputFonctor
{
public:

    InputFonctor(std::vector<FightSubserver *> *subservers, bool &stopServer);

    void operator()();

private:

    std::vector<FightSubserver *> *subservers;
    bool                          &stopServer;
};

#endif