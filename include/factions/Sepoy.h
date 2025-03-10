#ifndef SEPOY_H
#define SEPOY_H

#include "Faction.h"

class Sepoy : public Faction {
public:
    Sepoy();
    void executeSpecialAction() override; // Overrides the base class method
};

#endif