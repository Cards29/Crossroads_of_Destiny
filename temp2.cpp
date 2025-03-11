//#include <iostream>
//#include <fstream>
//#include <string>
//#include "nlohmann/json.hpp"
//
//using json = nlohmann::json;
//
//int main() {
//    std::ifstream file("decision_tree.json");
//    if (!file.is_open()) {
//        std::cerr << "Error: Could not open decision_tree.json" << std::endl;
//        return 1;
//    }
//
//    json decisionTree;
//    file >> decisionTree;
//
//    std::string currentNode = "start";
//
//    while (true) {
//        auto node = decisionTree[currentNode];
//
//        if (node.contains("question")) {
//            std::cout << node["question"].get<std::string>() << std::endl;
//            int choiceNum = 1;
//            for (const auto& choice : node["choices"]) {
//                std::cout << choiceNum++ << ". " << choice["text"].get<std::string>() << std::endl;
//            }
//
//            int choice;
//            std::cin >> choice;
//            if (choice < 1 || choice > node["choices"].size()) {
//                std::cout << "Invalid choice." << std::endl;
//                continue;
//            }
//
//            currentNode = node["choices"][choice - 1]["next"].get<std::string>();
//        }
//        else if (node.contains("outcome")) {
//            std::cout << node["outcome"].get<std::string>() << std::endl;
//            break;
//        }
//        else {
//            std::cout << "Error: Invalid Node" << std::endl;
//            break;
//        }
//    }
//
//    return 0;
//}