#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "DecisionNode.h"
#include "MapRenderer.h"

class GameEngine {
private:
    DecisionNode* decisionTree;
    MapRenderer mapRenderer;

public:
    GameEngine();
    void runGame();
};

#endif
