//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <iostream>
//#include <vector>
//#include <string>
//#include <map>
//#include <fstream> 
//#include "nlohmann/json.hpp"
//
//using namespace std;
//using json = nlohmann::json;
//
//// -------------------- MapManager Class --------------------
//class MapManager {
//private:
//    map<string, sf::Texture> textures;
//public:
//    bool loadMap(const string& id, const string& filepath) {
//        sf::Texture texture;
//        if (!texture.loadFromFile(filepath)) {
//            cout << "Failed to load map \"" << id << "\" from " << filepath << endl;
//            return false;
//        }
//        textures[id] = texture;
//        return true;
//    }
//    const sf::Texture& getTexture(const string& id) const {
//        return textures.at(id);
//    }
//};
//
//// -------------------- Decision Structures --------------------
//struct DecisionNode;
//
//class DecisionOption {
//public:
//    string text;
//    int moraleEffect;
//    int resourceEffect;
//    int influenceEffect;
//    string historicalContext;
//    string mapID;
//    DecisionNode* nextNode;
//    string outcome;
//};
//
//struct DecisionNode {
//    string question;
//    string historicalContext;
//    string historicalContext_b;
//    vector<DecisionOption> options;
//};
//
//// -------------------- Revolution Class --------------------
//class Revolution {
//private:
//    int morale;
//    int resources;
//    int influence;
//public:
//    Revolution() : morale(0), resources(0), influence(0) {}
//
//    void updateAttributes(int m, int r, int inf) {
//        morale += m;
//        resources += r;
//        influence += inf;
//    }
//
//    int getMorale() const {
//        return morale;
//    }
//
//    int getResources() const {
//        return resources;
//    }
//
//    int getInfluence() const {
//        return influence;
//    }
//
//    void displayAttributes() const {
//        cout << "Morale: " << morale
//            << " | Resources: " << resources
//            << " | Influence: " << influence
//            << endl;
//    }
//};
//
//
//void drawAttributes(sf::RenderWindow& window, sf::Font& font, const Revolution& rev) {
//    sf::Text attributes;
//    attributes.setFont(font);
//    attributes.setCharacterSize(30);
//    attributes.setFillColor(sf::Color::Black);
//
//    string attrText = "Morale: " + to_string(rev.getMorale()) +
//        "\nResources: " + to_string(rev.getResources()) +
//        "\nInfluence: " + to_string(rev.getInfluence());
//
//    attributes.setString(attrText);
//    attributes.setPosition(window.getSize().x - 300, window.getSize().y - 300);
//    window.draw(attributes);
//}
//
//void updateMapSprite(sf::Sprite& mapSprite, const sf::RenderWindow& window) {
//    mapSprite.setScale(2.0f, 2.0f);
//    mapSprite.setPosition(window.getSize().x - mapSprite.getGlobalBounds().width - 20, 20);
//}
//
//void traverseDecisionTree(sf::RenderWindow& window, DecisionNode* node, Revolution& rev,
//    sf::Sprite& mapSprite, MapManager& mapManager, sf::Font& font) {
//    while (node != nullptr && window.isOpen()) {
//
//        sf::Text context1;
//        sf::Text context2;
//        context1.setFont(font);
//        context2.setFont(font);
//        context1.setCharacterSize(36);
//        context2.setCharacterSize(36);
//        context1.setFillColor(sf::Color::Blue);
//        context2.setFillColor(sf::Color::Blue);
//        context1.setString(node->historicalContext);
//        context2.setString(node->historicalContext_b);
//        context1.setPosition(20, window.getSize().y - 350);
//        context2.setPosition(20, window.getSize().y - 350);
//
//        sf::Text questionText;
//        questionText.setFont(font);
//        questionText.setCharacterSize(36);
//        questionText.setFillColor(sf::Color::Black);
//        questionText.setString(node->question);
//        questionText.setPosition(20, window.getSize().y - 300);
//
//
//
//        vector<sf::Text> optionTexts;
//        for (size_t i = 0; i < node->options.size(); i++) {
//            sf::Text optionText;
//            optionText.setFont(font);
//            optionText.setCharacterSize(30);
//            optionText.setFillColor(sf::Color::Black);
//            optionText.setString(to_string(i + 1) + ". " + node->options[i].text);
//            optionText.setPosition(20, window.getSize().y - 250 + i * 40);
//            optionTexts.push_back(optionText);
//        }
//
//        bool decisionMade = false;
//        int selectedOption = -1;
//
//        while (window.isOpen() && !decisionMade) {
//            sf::Event event;
//            while (window.pollEvent(event)) {
//                if (event.type == sf::Event::Closed)
//                    window.close();
//                else if (event.type == sf::Event::KeyPressed) {
//                    int choice = event.key.code - sf::Keyboard::Num1;
//                    if (choice >= 0 && choice < (int)node->options.size()) {
//                        selectedOption = choice;
//                        decisionMade = true;
//                    }
//                }
//            }
//            window.clear(sf::Color::White);
//            window.draw(mapSprite);
//            window.draw(context1);
//
//            window.draw(questionText);
//            for (auto& t : optionTexts)
//                window.draw(t);
//            drawAttributes(window, font, rev);
//            window.display();
//        }
//
//        if (selectedOption >= 0) {
//            //cout << "selectedOption :" << selectedOption << endl;
//            DecisionOption& option = node->options[selectedOption];
//
//            // Update attributes.
//            rev.updateAttributes(option.moraleEffect, option.resourceEffect, option.influenceEffect);
//            rev.displayAttributes();
//            cout << option.historicalContext << endl;
//
//            if (!option.mapID.empty()) {
//                mapSprite.setTexture(mapManager.getTexture(option.mapID), true);
//                updateMapSprite(mapSprite, window);
//                //cout << "new map!\n";
//            }
//            /*  cout << "Hello world 1\n";
//              cout << "\n";*/
//
//            if (!option.outcome.empty()) {
//                //cout << "Hello world 2\n";
//                sf::Text outcomeText;
//                outcomeText.setFont(font);
//                outcomeText.setCharacterSize(40);
//                outcomeText.setFillColor(sf::Color::Red);
//                outcomeText.setString(option.outcome);
//                outcomeText.setPosition(20, window.getSize().y - 150);
//
//                window.clear(sf::Color::White);
//                window.draw(mapSprite);
//                window.draw(outcomeText);
//                drawAttributes(window, font, rev);
//                window.display();
//
//                bool wait = true;
//                while (window.isOpen() && wait) {
//                    sf::Event event;
//                    while (window.pollEvent(event)) {
//                        if (event.type == sf::Event::KeyPressed)
//                            wait = false;
//                        else if (event.type == sf::Event::Closed)
//                            window.close();
//                    }
//                }
//                return;
//            }
//            // Proceed to the next node.
//            node = option.nextNode;
//
//            /*  cout << "Next node\n";
//              if (node == nullptr) cout << "null node";*/
//        }
//    }
//}
//
//// Display a main menu for faction selection.
//int displayMainMenu(sf::RenderWindow& window, sf::Font& font) {
//    sf::Text name;
//    name.setFont(font);
//    name.setCharacterSize(57);
//    name.setFillColor(sf::Color::Red);
//    name.setString("Crossroads of Destiny");
//    name.setPosition(720, 420);
//
//    sf::Text title;
//    title.setFont(font);
//    title.setCharacterSize(48);
//    title.setFillColor(sf::Color::Black);
//    title.setString("Choose your faction:");
//    title.setPosition(750, 500);
//
//    sf::Text option1;
//    option1.setFont(font);
//    option1.setCharacterSize(36);
//    option1.setFillColor(sf::Color::Black);
//    option1.setString("1. Sepoy Faction");
//    option1.setPosition(750, 600);
//
//    sf::Text option2;
//    option2.setFont(font);
//    option2.setCharacterSize(36);
//    option2.setFillColor(sf::Color::Black);
//    option2.setString("2. Deobandi Movement");
//    option2.setPosition(750, 660);
//
//    /*sf::Text option3;
//    option3.setFont(font);
//    option3.setCharacterSize(36);
//    option3.setFillColor(sf::Color::Black);
//    option3.setString("3. INA - Indian National Army");
//    option3.setPosition(750, 720);
//
//    sf::Text option4;
//    option4.setFont(font);
//    option4.setCharacterSize(36);
//    option4.setFillColor(sf::Color::Black);
//    option4.setString("4. Local Landlord");
//    option4.setPosition(750, 780);*/
//
//    int selected = -1;
//    while (window.isOpen() && selected == -1) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//            else if (event.type == sf::Event::KeyPressed) {
//                int choice = event.key.code - sf::Keyboard::Num1;
//                if (choice == 0 || choice == 1)
//                    selected = choice;
//            }
//        }
//        window.clear(sf::Color::White);
//        window.draw(name);
//        window.draw(title);
//        window.draw(option1);
//        window.draw(option2);
//        /*window.draw(option3);
//        window.draw(option4);*/
//        window.display();
//    }
//    return selected;
//}
//
//// -------------------- Main Function --------------------
//int main() {
//    sf::RenderWindow window(sf::VideoMode(2000, 2000), "Crossroads of Destiny: The Indian Uprising");
//
//
//    MapManager mapManager;
//    // Pre-loading all required maps
//    mapManager.loadMap("main", "assets/maps/main map.png");
//    mapManager.loadMap("Sepoy_Rebellion", "assets/maps/Sepoy_Rebellion.png");
//    mapManager.loadMap("Sepoy_Delayed", "assets/maps/main map.png");
//    mapManager.loadMap("Sepoy_Captured_Delhi", "assets/maps/Sepoy_Captured_Delhi.png");
//    mapManager.loadMap("Sepoy_Fragmented", "assets/maps/Sepoy_Fragmented.png");
//    mapManager.loadMap("Sepoy_Alliances", "assets/maps/Sepoy_Alliances.png");
//    mapManager.loadMap("Sepoy_Isolated", "assets/maps/Sepoy_Isolated.png");
//    mapManager.loadMap("Sepoy_Sabotage", "assets/maps/Sepoy_Sabotage.png");
//    mapManager.loadMap("Sepoy_NoSabotage", "assets/maps/Sepoy_NoSabotage.png");
//    mapManager.loadMap("Sepoy_FinalBattle", "assets/maps/Sepoy_FinalBattle.png");
//    mapManager.loadMap("Sepoy_Defensive", "assets/maps/Sepoy_Defensive.png");
//    mapManager.loadMap("Deobandi_Established", "assets/maps/Deobandi_Established.png");
//    mapManager.loadMap("Deobandi_Delayed", "assets/maps/Deobandi_Delayed.png");
//    mapManager.loadMap("Deobandi_Peaceful", "assets/maps/Deobandi_Peaceful.png");
//    mapManager.loadMap("Deobandi_Aggressive", "assets/maps/Deobandi_Aggressive.png");
//    mapManager.loadMap("Deobandi_Expansion", "assets/maps/Deobandi_Expansion.png");
//    mapManager.loadMap("Deobandi_Consolidate", "assets/maps/Deobandi_Consolidate.png");
//    mapManager.loadMap("Deobandi_Khilafat", "assets/maps/Deobandi_Khilafat.png");
//    mapManager.loadMap("Deobandi_Neutral", "assets/maps/Deobandi_Neutral.png");
//
//    ifstream file("decision_tree.json");
//    if (!file.is_open()) {
//        cerr << "Error: Could not open decision_tree.json" << endl;
//        return 1;
//    }
//
//    sf::Sprite mapSprite;
//    mapSprite.setTexture(mapManager.getTexture("main"), true);
//    updateMapSprite(mapSprite, window);
//    //cout << "Main map set on position\n";
//
//    // Load sound effect (if needed)
//    /*sf::SoundBuffer explosionBuffer;
//    if (!explosionBuffer.loadFromFile("assets/sounds/large-underwater-explosion-190270.wav")) {
//        cout << "Failed to load explosion sound!\n";
//        return -1;
//    }
//    sf::Sound explosionSound;
//    explosionSound.setBuffer(explosionBuffer);*/
//
//    // Load the font.
//    sf::Font font;
//    if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {
//        cout << "Failed to load font!\n";
//        return -1;
//    }
//
//    Revolution rev;
//    int faction = displayMainMenu(window, font);
//    DecisionNode* startingNode = nullptr;
//
//    // -------------------- Building the Decision Tree --------------------
//    if (faction == 0) {
//        // --- Sepoy Rebellion ---
//        static DecisionNode sepoyNode1;
//        sepoyNode1.question = "British distributed greased cartridges, causing religious outrage. Revolt immediately?";
//
//
//        static DecisionOption sepoyOption1;
//        sepoyOption1.text = "Launch Revolt Immediately";
//        sepoyOption1.moraleEffect += 30;
//        sepoyOption1.resourceEffect += 20;
//        sepoyOption1.influenceEffect += 20;
//        sepoyOption1.historicalContext = "In 1857, the Sepoys revolted immediately after the cartridge controversy, igniting India's first major uprising.";
//        sepoyOption1.mapID = "Sepoy_Rebellion";
//        //sepoyOption1.outcome = "Sepoy rebellion starts!";
//
//        static DecisionOption sepoyOption1b;
//        sepoyOption1b.text = "Delay Revolt";
//        sepoyOption1b.moraleEffect += -10;
//        sepoyOption1b.resourceEffect += 10;
//        sepoyOption1b.influenceEffect += -5;
//        sepoyOption1b.historicalContext = "Delaying the revolt led to missed opportunities and a fragmented resistance.";
//        sepoyOption1b.mapID = "Sepoy_Delayed";
//        //sepoyOption1b.outcome = "Sepoy rebellion is delayed!";
//
//
//        static DecisionNode sepoyNode2;
//        sepoyNode2.question = "Declare Bahadur Shah Zafar as Emperor?";
//        sepoyNode2.historicalContext = "In 1857, the Sepoys revolted immediately after the cartridge controversy, igniting India's first major uprising.";
//        sepoyNode2.historicalContext_b = "Delaying the revolt led to missed opportunities and a fragmented resistance.";
//
//
//        static DecisionOption sepoyOption2;
//        sepoyOption2.text = "Yes";
//        sepoyOption2.moraleEffect += 40;
//        sepoyOption2.resourceEffect += 10;
//        sepoyOption2.influenceEffect += 50;
//        sepoyOption2.historicalContext = "Rebels declared Zafar as their symbolic leader, lending legitimacy to the uprising.";
//        sepoyOption2.mapID = "Sepoy_Captured_Delhi";
//
//        static DecisionOption sepoyOption2b;
//        sepoyOption2b.text = "No";
//        sepoyOption2b.moraleEffect += -20;
//        sepoyOption2b.resourceEffect += 0;
//        sepoyOption2b.influenceEffect += -30;
//        sepoyOption2b.historicalContext = "Without a clear leader, the rebellion became fragmented and less cohesive.";
//        sepoyOption2b.mapID = "Sepoy_Fragmented";
//
//        static DecisionNode sepoyNode3;
//        sepoyNode3.question = "Form alliances with regional princes?";
//        sepoyNode3.historicalContext = "Rebels declared Zafar as their symbolic leader, lending legitimacy to the uprising.";
//        sepoyNode3.historicalContext_b = "Without a clear leader, the rebellion became fragmented and less cohesive.";
//
//        static DecisionOption sepoyoption3;
//        sepoyoption3.text = "Yes";
//        sepoyoption3.moraleEffect += 30;
//        sepoyoption3.resourceEffect += 40;
//        sepoyoption3.influenceEffect += 30;
//        sepoyoption3.historicalContext = "Regional alliances bolstered the rebellion with additional military and financial strength.";
//        sepoyoption3.mapID = "Sepoy_Alliances";
//
//        static DecisionOption sepoyoption3b;
//        sepoyoption3b.text = "No";
//        sepoyoption3b.moraleEffect += -15;
//        sepoyoption3b.resourceEffect += -20;
//        sepoyoption3b.influenceEffect += -25;
//        sepoyoption3b.historicalContext = "Without alliances, the rebellion struggled to sustain itself.";
//        sepoyoption3b.mapID = "Sepoy_Isolated";
//
//        static DecisionNode sepoyNode4;
//        sepoyNode4.question = "Sabotage British supply lines?";
//        sepoyNode4.historicalContext = "Regional alliances bolstered the rebellion with additional military and financial strength.";
//        sepoyNode4.historicalContext_b = "Without alliances, the rebellion struggled to sustain itself.";
//
//        static DecisionOption sepoyOption4;
//        sepoyOption4.text = "Yes";
//        sepoyOption4.moraleEffect += 20;
//        sepoyOption4.resourceEffect += -10;
//        sepoyOption4.influenceEffect += 30;
//        sepoyOption4.historicalContext = "Sabotaging supply lines disrupted British logistics and created an advantage.";
//        sepoyOption4.mapID = "Sepoy_Sabotage";
//
//        static DecisionOption sepoyOption4b;
//        sepoyOption4b.text = "No";
//        sepoyOption4b.moraleEffect += -10;
//        sepoyOption4b.resourceEffect += 0;
//        sepoyOption4b.influenceEffect += -20;
//        sepoyOption4b.historicalContext = "Not disrupting supplies allowed the British to regroup and counterattack.";
//        sepoyOption4b.mapID = "Sepoy_NoSabotage";
//
//        static DecisionNode sepoyNode5;
//        sepoyNode5.question = "Final battle at Kanpur & Lucknow?";
//        sepoyNode5.historicalContext = "Sabotaging supply lines disrupted British logistics and created an advantage.";
//        sepoyNode5.historicalContext_b = "Not disrupting supplies allowed the British to regroup and counterattack.";
//
//        static DecisionOption sepoyOption5;
//        sepoyOption5.text = "Aggressive Attack";
//        sepoyOption5.moraleEffect += -60;
//        sepoyOption5.resourceEffect += -70;
//        sepoyOption5.influenceEffect += -50;
//        sepoyOption5.historicalContext = "An aggressive attack initially yielded gains but ended in overwhelming defeat.";
//        sepoyOption5.mapID = "Sepoy_FinalBattle";
//        sepoyOption5.outcome = "Defeat - Rebellion suppressed historically.";
//
//        static DecisionOption sepoyOption5b;
//        sepoyOption5b.text = "Defensive Position";
//        sepoyOption5b.moraleEffect += 10;
//        sepoyOption5b.resourceEffect += 0;
//        sepoyOption5b.influenceEffect += 20;
//        sepoyOption5b.historicalContext = "Taking a defensive stance prolonged the conflict, avoiding immediate defeat.";
//        sepoyOption5b.mapID = "Sepoy_Defensive";
//        sepoyOption5b.outcome = "STALEMENT - Continued resistance.";
//
//
//        sepoyOption1.nextNode = &sepoyNode2;
//        sepoyOption1b.nextNode = &sepoyNode2;
//        sepoyNode1.options.push_back(sepoyOption1);
//        sepoyNode1.options.push_back(sepoyOption1b);
//
//        //sepoyOption1.nextNode = &sepoyNode2;
//        //sepoyOption1b.nextNode = &sepoyNode2;
//       /* cout << "nextnode is sepoy node 2\n";
//        if (sepoyOption1b.nextNode == nullptr) cout << "Zarif is sad\n";
//        else cout << "Zarif is happy\n";*/
//
//        sepoyOption2.nextNode = &sepoyNode3;
//        sepoyOption2b.nextNode = &sepoyNode3;
//        sepoyNode2.options.push_back(sepoyOption2);
//        sepoyNode2.options.push_back(sepoyOption2b);
//
//        sepoyoption3.nextNode = &sepoyNode4;
//        sepoyoption3b.nextNode = &sepoyNode4;
//        sepoyNode3.options.push_back(sepoyoption3);
//        sepoyNode3.options.push_back(sepoyoption3b);
//
//        sepoyOption4.nextNode = &sepoyNode5;
//        sepoyOption4b.nextNode = &sepoyNode5;
//        sepoyNode4.options.push_back(sepoyOption4);
//        sepoyNode4.options.push_back(sepoyOption4b);
//
//
//        sepoyNode5.options.push_back(sepoyOption5);
//        sepoyNode5.options.push_back(sepoyOption5b);
//
//        startingNode = &sepoyNode1;
//    }
//    else {
//        // --- Deobandi Movement Branch ---
//        static DecisionNode deobandiNode1;
//        deobandiNode1.question = "Establish Darul Uloom Seminary at Deoband immediately?";
//
//        static DecisionOption deobandiOption1;
//        deobandiOption1.text = "Establish Immediately";
//        deobandiOption1.moraleEffect += 20;
//        deobandiOption1.resourceEffect += 10;
//        deobandiOption1.influenceEffect += 40;
//        deobandiOption1.historicalContext = "Darul Uloom Deoband, founded in 1866, became a center of cultural resistance.";
//        deobandiOption1.mapID = "Deobandi_Established";
//
//        static DecisionOption deobandiOption1b;
//        deobandiOption1b.text = "Delay Establishment";
//        deobandiOption1b.moraleEffect += -10;
//        deobandiOption1b.resourceEffect += 5;
//        deobandiOption1b.influenceEffect += -20;
//        deobandiOption1b.historicalContext = "A delay allowed British cultural influence to gain a foothold, weakening early resistance.";
//        deobandiOption1b.mapID = "Deobandi_Delayed";
//
//        static DecisionNode deobandiNode2;
//        deobandiNode2.question = "Respond to British crackdown on madrasas?";
//
//        static DecisionOption deobandiOption2;
//        deobandiOption2.text = "Peaceful Civil Disobedience";
//        deobandiOption2.moraleEffect += 10;
//        deobandiOption2.resourceEffect += 0;
//        deobandiOption2.influenceEffect += 30;
//        deobandiOption2.historicalContext = "Peaceful resistance earned widespread public sympathy and legitimacy.";
//        deobandiOption2.mapID = "Deobandi_Peaceful";
//
//        static DecisionOption deobandiOption2b;
//        deobandiOption2b.text = "Resist Aggressively";
//        deobandiOption2b.moraleEffect += -20;
//        deobandiOption2b.resourceEffect += -10;
//        deobandiOption2b.influenceEffect += -30;
//        deobandiOption2b.historicalContext = "Aggressive measures resulted in a brutal crackdown and loss of support.";
//        deobandiOption2b.mapID = "Deobandi_Aggressive";
//
//        static DecisionNode deobandiNode3;
//        deobandiNode3.question = "Expand madrasa network into Bengal & Punjab?";
//
//        static DecisionOption deobandioption4;
//        deobandioption4.text = "Expand Widely";
//        deobandioption4.moraleEffect += 10;
//        deobandioption4.resourceEffect += -20;
//        deobandioption4.influenceEffect += 50;
//        deobandioption4.historicalContext = "Expanding the network boosted regional influence and resistance.";
//        deobandioption4.mapID = "Deobandi_Expansion";
//
//        static DecisionOption deobandioption4b;
//        deobandioption4b.text = "Consolidate Locally";
//        deobandioption4b.moraleEffect += -5;
//        deobandioption4b.resourceEffect += 0;
//        deobandioption4b.influenceEffect += -20;
//        deobandioption4b.historicalContext = "Focusing locally limited broader influence but maintained stability.";
//        deobandioption4b.mapID = "Deobandi_Consolidate";
//
//        static DecisionNode deobandiNode4;
//        deobandiNode4.question = "Support Khilafat Movement?";
//
//        static DecisionOption deobandiOption4;
//        deobandiOption4.text = "Support Khilafat";
//        deobandiOption4.moraleEffect += 20;
//        deobandiOption4.resourceEffect += 20;
//        deobandiOption4.influenceEffect += 50;
//        deobandiOption4.historicalContext = "Backing the Khilafat Movement raised international prestige.";
//        deobandiOption4.mapID = "Deobandi_Khilafat";
//        deobandiOption4.outcome = "Victory - Strong international reputation.";
//
//        static DecisionOption deobandiOption4b;
//        deobandiOption4b.text = "Stay Neutral";
//        deobandiOption4b.moraleEffect += -10;
//        deobandiOption4b.resourceEffect += 0;
//        deobandiOption4b.influenceEffect += -20;
//        deobandiOption4b.historicalContext = "Neutrality limited international support and slowed momentum.";
//        deobandiOption4b.mapID = "Deobandi_Neutral";
//        deobandiOption4b.outcome = "STALEMENT";
//
//
//        deobandiOption1.nextNode = &deobandiNode2;
//        deobandiOption1b.nextNode = &deobandiNode2;
//        deobandiNode1.options.push_back(deobandiOption1);
//        deobandiNode1.options.push_back(deobandiOption1b);
//
//        deobandiOption2.nextNode = &deobandiNode3;
//        deobandiOption2b.nextNode = &deobandiNode3;
//        deobandiNode2.options.push_back(deobandiOption2);
//        deobandiNode2.options.push_back(deobandiOption2b);
//
//        deobandioption4.nextNode = &deobandiNode4;
//        deobandioption4b.nextNode = &deobandiNode4;
//        deobandiNode3.options.push_back(deobandioption4);
//        deobandiNode3.options.push_back(deobandioption4b);
//
//
//        deobandiNode4.options.push_back(deobandiOption4);
//        deobandiNode4.options.push_back(deobandiOption4b);
//
//
//        startingNode = &deobandiNode1;
//    }
//
//    traverseDecisionTree(window, startingNode, rev, mapSprite, mapManager, font);
//
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
//                window.close();
//        }
//        window.clear(sf::Color::White);
//        window.draw(mapSprite);
//        drawAttributes(window, font, rev);
//        window.display();
//    }
//
//    return 0;
//}
