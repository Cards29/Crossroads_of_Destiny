#ifndef FACTION_H
#define FACTION_H

#include <string>
#include <map>
#include <iostream>

class Faction {
protected:
    std::string name; // Faction name
    int morale;       // Morale of the faction
    int resources;    // Economic resources
    int influence;    // Political influence
    int espionage;    // Espionage capabilities
    int reputation;   // Public reputation with population and global actors
    std::map<std::string, int> customEffects; // Custom-defined effects

public:
    // Constructor
    Faction(std::string factionName, int morale, int resources, int influence, int espionage, int reputation);

    // Virtual Destructor (since it's a base class)
    virtual ~Faction() {}

    // Methods for modifying faction attributes
    void modifyMorale(int amount);
    void modifyResources(int amount);
    void modifyInfluence(int amount);
    void modifyEspionage(int amount);
    void modifyReputation(int amount);
    void applyCustomEffect(std::string effectName, int effectValue);

    // Display current faction stats
    virtual void displayFactionStats() const;

    // Virtual method to be overridden by specific factions (e.g., special abilities)
    virtual void executeSpecialAction() = 0;
};

#endif