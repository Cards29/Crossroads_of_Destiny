#ifndef DECISIONNODE_H
#define DECISIONNODE_H

#include <string>
#include <map>
#include <vector>

class DecisionNode {
public:
    std::string question;
    std::string leftOption, rightOption;
    bool correctLeft;
    int moraleEffect, resourceEffect, influenceEffect;
    std::map<std::string, int> customEffects;
    std::string mapImagePath;
    std::string historicalContext;
    DecisionNode* left;
    DecisionNode* right;

    DecisionNode(std::string question, std::string leftOption, std::string rightOption,
        bool correctLeft, int morale, int resources, int influence,
        std::string history, std::string mapImage);

    static DecisionNode* loadFromFile(const std::string& filePath);
    static void saveToFile(DecisionNode* root, const std::string& filePath);
};

#endif
