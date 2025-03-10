#ifndef DEOBANDI_H
#define DEOBANDI_H

#include "Faction.h"

class Deobandi : public Faction {
public:
    Deobandi();
    void executeSpecialAction() override;
};

#endif