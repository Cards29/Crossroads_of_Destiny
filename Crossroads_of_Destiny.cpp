#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

// -------------------- MapManager Class --------------------
class MapManager {
private:
    map<string, sf::Texture> textures;
public:
    bool loadMap(const string& id, const string& filepath) {
        sf::Texture texture;
        if (!texture.loadFromFile(filepath)) {
            cout << "Failed to load map \"" << id << "\" from " << filepath << endl;
            return false;
        }
        textures[id] = texture;
        return true;
    }
    const sf::Texture& getTexture(const string& id) const {
        return textures.at(id);
    }
};

// -------------------- Decision Structures --------------------
struct DecisionNode;

class DecisionOption {
public:
    string text;
    int moraleEffect;
    int resourceEffect;
    int influenceEffect;
    string historicalContext;
    string mapID;
    DecisionNode* nextNode;
    string outcome;
};

struct DecisionNode {
    string question;
    string historicalContext;
    string historicalContext_b;
    vector<DecisionOption> options;
};

// -------------------- Revolution Class --------------------
class Revolution {
private:
    int morale;
    int resources;
    int influence;
public:
    Revolution() : morale(0), resources(0), influence(0) {}

    void updateAttributes(int m, int r, int inf) {
        morale += m;
        resources += r;
        influence += inf;
    }

    int getMorale() const {
        return morale;
    }

    int getResources() const {
        return resources;
    }

    int getInfluence() const {
        return influence;
    }

    void displayAttributes() const {
        cout << "Morale: " << morale
            << " | Resources: " << resources
            << " | Influence: " << influence
            << endl;
    }
};


void drawAttributes(sf::RenderWindow& window, sf::Font& font, const Revolution& rev) {
    sf::Text attributes;
    attributes.setFont(font);
    attributes.setCharacterSize(30);
    attributes.setFillColor(sf::Color::Black);

    string attrText = "Morale: " + to_string(rev.getMorale()) +
        "\nResources: " + to_string(rev.getResources()) +
        "\nInfluence: " + to_string(rev.getInfluence());

    attributes.setString(attrText);
    attributes.setPosition(window.getSize().x - 300, window.getSize().y - 300);
    window.draw(attributes);
}

void updateMapSprite(sf::Sprite& mapSprite, const sf::RenderWindow& window) {
    mapSprite.setScale(0.5f, 0.5f);
    mapSprite.setPosition(window.getSize().x - mapSprite.getGlobalBounds().width - 20, 20);
}

void traverseDecisionTree(sf::RenderWindow& window, DecisionNode* node, Revolution& rev,
    sf::Sprite& mapSprite, MapManager& mapManager, sf::Font& font) {
    while (node != nullptr && window.isOpen()) {
        
        sf::Text questionText;
        questionText.setFont(font);
        questionText.setCharacterSize(36);
        questionText.setFillColor(sf::Color::Black);
        questionText.setString(node->question);
        questionText.setPosition(20, window.getSize().y - 300);



        vector<sf::Text> optionTexts;
        for (size_t i = 0; i < node->options.size(); i++) {
            sf::Text optionText;
            optionText.setFont(font);
            optionText.setCharacterSize(30);
            optionText.setFillColor(sf::Color::Black);
            optionText.setString(to_string(i + 1) + ". " + node->options[i].text);
            optionText.setPosition(20, window.getSize().y - 250 + i * 40);
            optionTexts.push_back(optionText);
        }

        bool decisionMade = false;
        int selectedOption = -1;

        while (window.isOpen() && !decisionMade) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed) {
                    int choice = event.key.code - sf::Keyboard::Num1;
                    if (choice >= 0 && choice < (int)node->options.size()) {
                        selectedOption = choice;
                        decisionMade = true;
                    }
                }
            }
            window.clear(sf::Color::White);
            window.draw(mapSprite);

            window.draw(questionText);
            for (auto& t : optionTexts)
                window.draw(t);
            drawAttributes(window, font, rev);
            window.display();
        }

        if (selectedOption >= 0) {
            //cout << "selectedOption :" << selectedOption << endl;
            DecisionOption& option = node->options[selectedOption];

            // Update attributes.
            rev.updateAttributes(option.moraleEffect, option.resourceEffect, option.influenceEffect);
            rev.displayAttributes();
            cout << option.historicalContext << endl;

            if (!option.mapID.empty()) {
                mapSprite.setTexture(mapManager.getTexture(option.mapID), true);
                updateMapSprite(mapSprite, window);
                //cout << "new map!\n";
            }
            /*  cout << "Hello world 1\n";
              cout << "\n";*/

            if (!option.outcome.empty()) {
                //cout << "Hello world 2\n";
                sf::Text outcomeText;
                outcomeText.setFont(font);
                outcomeText.setCharacterSize(40);
                outcomeText.setFillColor(sf::Color::Red);
                outcomeText.setString(option.outcome);
                outcomeText.setPosition(20, window.getSize().y - 150);

                window.clear(sf::Color::White);
                window.draw(mapSprite);
                window.draw(outcomeText);
                drawAttributes(window, font, rev);
                window.display();

                bool wait = true;
                while (window.isOpen() && wait) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::KeyPressed)
                            wait = false;
                        else if (event.type == sf::Event::Closed)
                            window.close();
                    }
                }
                return;
            }
            // Proceed to the next node.
            node = option.nextNode;

            /*  cout << "Next node\n";
              if (node == nullptr) cout << "null node";*/
        }
    }
}

// Display a main menu for faction selection.
int displayMainMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::Text name;
    name.setFont(font);
    name.setCharacterSize(57);
    name.setFillColor(sf::Color::Red);
    name.setString("Crossroads of Destiny");
    name.setPosition(720, 420);

    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Black);
    title.setString("Choose your faction:");
    title.setPosition(750, 500);

    sf::Text option1;
    option1.setFont(font);
    option1.setCharacterSize(36);
    option1.setFillColor(sf::Color::Black);
    option1.setString("1. Sepoy Faction");
    option1.setPosition(750, 600);

    sf::Text option2;
    option2.setFont(font);
    option2.setCharacterSize(36);
    option2.setFillColor(sf::Color::Black);
    option2.setString("2. Deobandi Movement");
    option2.setPosition(750, 660);

    /*sf::Text option3;
    option3.setFont(font);
    option3.setCharacterSize(36);
    option3.setFillColor(sf::Color::Black);
    option3.setString("3. INA - Indian National Army");
    option3.setPosition(750, 720);

    sf::Text option4;
    option4.setFont(font);
    option4.setCharacterSize(36);
    option4.setFillColor(sf::Color::Black);
    option4.setString("4. Local Landlord");
    option4.setPosition(750, 780);*/

    int selected = -1;
    while (window.isOpen() && selected == -1) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                int choice = event.key.code - sf::Keyboard::Num1;
                if (choice == 0 || choice == 1)
                    selected = choice;
            }
        }
        window.clear(sf::Color::White);
        window.draw(name);
        window.draw(title);
        window.draw(option1);
        window.draw(option2);
        /*window.draw(option3);
        window.draw(option4);*/
        window.display();
    }
    return selected;
}

// -------------------- Main Function --------------------
int main() {
    sf::RenderWindow window(sf::VideoMode(2000, 1700), "Crossroads of Destiny: The Indian Uprising");


    MapManager mapManager;
    // Pre-loading all required maps
    mapManager.loadMap("main", "assets/temp/brave_rebel.png");
    mapManager.loadMap("Sepoy_Rebellion", "assets/temp/havildar.png");
    mapManager.loadMap("Sepoy_Delayed", "assets/maps/main map.png");
    mapManager.loadMap("Sepoy_Captured_Delhi", "assets/maps/Sepoy_Captured_Delhi.png");
    mapManager.loadMap("Sepoy_Fragmented", "assets/maps/Sepoy_Fragmented.png");
    mapManager.loadMap("Sepoy_Alliances", "assets/maps/Sepoy_Alliances.png");
    mapManager.loadMap("Sepoy_Isolated", "assets/maps/Sepoy_Isolated.png");
    mapManager.loadMap("Sepoy_Sabotage", "assets/maps/Sepoy_Sabotage.png");
    mapManager.loadMap("Sepoy_NoSabotage", "assets/maps/Sepoy_NoSabotage.png");
    mapManager.loadMap("Sepoy_FinalBattle", "assets/maps/Sepoy_FinalBattle.png");
    mapManager.loadMap("Sepoy_Defensive", "assets/maps/Sepoy_Defensive.png");
    mapManager.loadMap("Deobandi_Established", "assets/maps/Deobandi_Established.png");
    mapManager.loadMap("Deobandi_Delayed", "assets/maps/Deobandi_Delayed.png");
    mapManager.loadMap("Deobandi_Peaceful", "assets/maps/Deobandi_Peaceful.png");
    mapManager.loadMap("Deobandi_Aggressive", "assets/maps/Deobandi_Aggressive.png");
    mapManager.loadMap("Deobandi_Expansion", "assets/maps/Deobandi_Expansion.png");
    mapManager.loadMap("Deobandi_Consolidate", "assets/maps/Deobandi_Consolidate.png");
    mapManager.loadMap("Deobandi_Khilafat", "assets/maps/Deobandi_Khilafat.png");
    mapManager.loadMap("Deobandi_Neutral", "assets/maps/Deobandi_Neutral.png");

    // Load the font.
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {
        cout << "Failed to load font!\n";
        return -1;
    }

    sf::Sprite mapSprite;
    mapSprite.setTexture(mapManager.getTexture("main"), true);
    updateMapSprite(mapSprite, window);


    Revolution rev;
    int faction = displayMainMenu(window, font);
    DecisionNode* startingNode = nullptr;

    ifstream file("decision_tree.json");
    if (!file.is_open()) {
        cerr << "Error: Could not open decision_tree.json" << endl;
        return 1;
    }

    json decisionTree;
    file >> decisionTree;
    string currentNode = "start";
    

    // -------------------- Building the Decision Tree --------------------
    while (true) {
        auto node = decisionTree[currentNode];

        if (node.contains("question")) {
            std::cout << node["question"].get<std::string>() << std::endl;
            int choiceNum = 1;
            for (const auto& choice : node["choices"]) {
                std::cout << choiceNum++ << ". " << choice["text"].get<std::string>() << std::endl;
            }
            
            int choice;
            std::cin >> choice;
            if (choice < 1 || choice > node["choices"].size()) {
                std::cout << "Invalid choice." << std::endl;
                continue;
            }
            
            currentNode = node["choices"][choice - 1]["next"].get<std::string>();
        }
        else if (node.contains("outcome")) {
            std::cout << node["outcome"].get<std::string>() << std::endl;
            break;
        }
        else {
            std::cout << "Error: Invalid Node" << std::endl;
            break;
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
                window.close();
        }
        window.clear(sf::Color::White);
        window.draw(mapSprite);
        drawAttributes(window, font, rev);
        window.display();
    }

    return 0;
}
