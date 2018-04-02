#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>


void menu() {
    std::cout << "###########################################################" << std::endl;
    std::cout << "#                                                         #" << std::endl;
    std::cout << "#                                                         #" << std::endl;
    std::cout << "#                     TODOLIST                            #" << std::endl;
    std::cout << "#                                                         #" << std::endl;
    std::cout << "#     Following commands are available:                   #" << std::endl;
    std::cout << "#     add, delete, list, exit                             #" << std::endl;
    std::cout << "#                                                         #" << std::endl;
    std::cout << "#                                                         #" << std::endl;
    std::cout << "###########################################################" << std::endl;
    std::cout << "Please enter what you want to do : ";
}

void clearScreen() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

std::vector<std::string> initTodolistAtStart(std::string path) {
    std::ifstream rFile(path);        // Stream for reading from file
    std::vector<std::string> vecTodoList;
    std::string line;

    while(getline(rFile, line, '\n')){
        vecTodoList.push_back(line);
    }
    return vecTodoList;
}


int main() {
    const std::string path = "todolist.txt";

    std::vector<std::string> vecTodoList = initTodolistAtStart(path);
    std::ofstream wFile;                        // Stream for writing to file
    std::string sCommand;                       // User inputs



    while (true) {
        clearScreen();                                // Empty terminal window
        menu();


        getline(std::cin, sCommand);

        if (sCommand == "add") {
            std::cout << "What task do you want to add? : ";
            getline(std::cin, sCommand);
            vecTodoList.push_back(sCommand);

        } else if (sCommand == "delete") {
            std::cout << "Which task do you want to delete? : ";
            getline(std::cin, sCommand);
            int iDelSel = std::stoi(sCommand);
            vecTodoList.erase(vecTodoList.begin()+iDelSel);

        } else if (sCommand == "list") {
            std::cout << "Here is the list with all your TODOs:\n\n";
            for (int i = 0; i < vecTodoList.size(); ++i) {
                std::cout << i  << ": " << vecTodoList[i] << std::endl;
            }
            std::cout << "\n" << "Hit return to continue!";
            getline(std::cin, sCommand);

        } else if (sCommand == "exit") {
            wFile.open(path);
            for (auto v: vecTodoList) {
                wFile << v << "\n";
            }
            wFile.close();
            clearScreen();
            std::cout << "Bye!\n";
            return 0;

        } else {
            std::cout << "You can only use one of the following commands: " << std::endl;
            std::cout << "add, delete, list, exit " << std::endl;
            std::cout << "\n" << "Hit return to continue!";
            getline(std::cin, sCommand);
        }
    }
}