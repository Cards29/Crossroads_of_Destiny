#ifndef SAVELOADMANAGER_H
#define SAVELOADMANAGER_H

#include "DecisionNode.h"
#include "Faction.h"
#include <fstream>
#include <nlohmann/json.hpp>

class SaveLoadManager {
public:
    // Save & Load Decision Tree
    static void saveDecisionTree(DecisionNode* root, const std::string& filePath);
    static DecisionNode* loadDecisionTree(const std::string& filePath);

    // Save & Load Game State (Factions, Resources, Custom Effects)
    static void saveGameState(Faction* faction, const std::string& filePath);
    static void loadGameState(Faction* faction, const std::string& filePath);
};

#endif