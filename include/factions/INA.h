#ifndef INA_H
#define INA_H

#include "Faction.h"

class INA : public Faction {
public:
    INA();
    void executeSpecialAction() override;
};

#endif