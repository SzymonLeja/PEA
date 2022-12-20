#include <windows.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <basetsd.h>
#include <psapi.h>
#include "../inc/containers/AdjacencyMatrix.h"
#include "../inc/utils/FileManager.h"
#include "../inc/utils/Menu.h"
#include "../inc/algorithms/BranchAndBound.h"
#include "../inc/algorithms/DynamicProgramming.h"
#include "../inc/utils/RandomGenerator.h"
#include "../inc/algorithms/SimulatedAnnealing.h"
#include "../inc/utils/testing/MatrixGenerator.h"
#include "../inc/algorithms/TabuSearch.h"
#include "../inc/utils/testing/ErrorTests.h"

#define var auto

void getNumberFromString(std::string s) {
    std::stringstream str_strm;
    str_strm << s; //convert the string s into stringstream
    std::string temp_str;
    int temp_int;
    while (!str_strm.eof()) {
        str_strm >> temp_str; //take words into temp_str one by one
        if (std::stringstream(temp_str) >> temp_int) { //try to convert string to int
            std::cout << temp_int << " ";
        }
        temp_str = ""; //clear temp string
    }
}

int main() {

    std::string coolingType = "geometric";
    std::string shuffleType = "quick";
    int epochs = 691;

    std::ifstream configFile;

    std::fstream outputFile;

    outputFile.open("results_ts11_" + coolingType + "_" + shuffleType + "_" + std::to_string(epochs) + ".csv",
                    std::ios::out);

    std::string fileName;
    int repetitions = 3;
    int optimalCost;


    outputFile << "Nazwa pliku" << ";";
    outputFile << "Powtorzenia algorytmu" << ";";
    outputFile << "Optymalny koszt" << ";";
    outputFile << "Schemat chłodzenia" << ";";
    outputFile << "Sposób zamiany" << ";";
    outputFile << "Liczba epok" << ";";
    outputFile << "Temperatura startowa" << ";";
    outputFile << "Wyspółczynnik wychładzania" << ";";

    for (int i = 0; i < repetitions; i++) {
//        outputFile << "Limit iteracji " << i + 1 << ";";
//        outputFile << "Rozmiar listy ruchów zakazanych " << i + 1 << ";";
//        outputFile << "Rozmiar listy sąsiedztwa " << i + 1 << ";";
        outputFile << "Czas " << i + 1 << ";";
        outputFile << "Koszt " << i + 1 << ";";
        outputFile << "Strata " << i + 1 << ";";
    }
    outputFile << "Średnia strata;\n";

    std::string line;
// SA
//   for(int xd=1; xd<=10; xd++){
//    for (int h = 0; h < 4; h++) {
//        if (h == 0) {
//            coolingType = "geometric";
//            shuffleType = "two-opt";
//        } else if (h == 1) {
//            coolingType = "boltzmann";
//            shuffleType = "two-opt";
//        } else if (h == 2) {
//            coolingType = "boltzmann";
//            shuffleType = "arc";
//        } else {
//            coolingType = "geometric";
//            shuffleType = "arc";
//        }
        configFile.open("config.ini", std::ios::in);
        while (getline(configFile, line)) {
            int numb;


            std::istringstream iss(line);
            iss >> fileName;
            iss >> repetitions;
            iss >> optimalCost;
            sscanf(fileName.c_str(), "%*[^_]_%d", &numb);
            epochs = numb * 150;
//            int iterator = 0;
//            for (int g = 0; g <= epochs; g += (epochs / 5)) {

                outputFile << fileName << ";";
                outputFile << repetitions << ";";
                outputFile << optimalCost << ";";
                outputFile << coolingType << ";";
                outputFile << shuffleType << ";";

                std::cout << fileName << "\n";
                std::cout << numb << "\n";
                int totalCost = 0;
                int startHeat;
                float coolingRate;
                startHeat = 1250;
                coolingRate = 0.999;

            outputFile << epochs << ";";

//                   if(xd==0){
////                       startHeat = 1000;
//                       coolingRate = 0.999;
//                   } else {
//                       coolingRate = 0;
//                   }

                std::cout << coolingRate << "\n";


                outputFile << startHeat << ";";
                if (coolingType == "geometric") {
                    outputFile << coolingRate << ";";
                } else {
                    outputFile << "boltzmann" << ";";
                }
                for (int i = 0; i < repetitions; i++) {
                    SimulatedAnnealing saEntity(startHeat, coolingRate);
                    AdjacencyMatrix *graph = nullptr;
                    FileManager::readData(fileName);

                    if (FileManager::data == nullptr) {
                        system("cls");

                        std::cout << "File not found!\n";
                        system("Pause");
                        return 0;
                    }

                    delete graph;
                    graph = new AdjacencyMatrix(FileManager::verticesNum, FileManager::data);

                    Timer timer;
                    timer.start();

                    Path *path = saEntity.execute(*graph, shuffleType, coolingType, epochs);
                    std::cout << path->toString() << std::endl;
                    outputFile << timer.getTime(MILLISECONDS) << ";" << path->getCost() << ";"
                               << float(float(float(path->getCost()) / float(optimalCost)) - 1) * 100 << ";";
                    totalCost += path->getCost();
                }
                float averageLoss = float(float(float(float(totalCost) / float(repetitions)) / optimalCost) - 1) * 100;
                outputFile << averageLoss << ";\n";
//                iterator++;
//            }
//           }
            configFile.close();
//        }
    }
// END SA

//######TABU
//    configFile.open("config.ini", std::ios::in);
//    while (std::getline(configFile, line).good()) {
//        std::istringstream iss(line);
//        iss >> fileName;
//        iss >> repetitions;
//        iss >> optimalCost;
//
//            outputFile << fileName << ";";
//            outputFile << repetitions << ";";
//            outputFile << optimalCost << ";";
//
//            int totalCost = 0;
//            float loss=9999.99;
//            int i=0;
//            bool goNext = false;
//            int worstThenLast = 0;
//            float bestLoss = 9999.99;
//            while(loss > 50.1 && goNext == false){
//                std::cout << fileName << std::endl;
//                std::cout << "Iteracja: " << i << std::endl;
////            for (int i = 0; i < repetitions; i++) {
//                outputFile << 1000*(i+1) << ";";
//                outputFile << 20*(i+1) << ";";
//                outputFile << 10*(i+1) << ";";
//                TabuSearch tsEntity(1000*(i+1),20*(i+1),10*(i+1));
//                AdjacencyMatrix *graph = nullptr;
//                FileManager::readData(fileName);
//
//                if (FileManager::data == nullptr) {
//                    system("cls");
//
//                    std::cout << "File not found!\n";
//                    system("Pause");
//                    return 0;
//                }
//
//                delete graph;
//                graph = new AdjacencyMatrix(FileManager::verticesNum, FileManager::data);
//
//                Timer timer;
//                timer.start();
//
//                Path *path = tsEntity.execute(*graph);
//                std::cout << path->toString() << std::endl;
//                outputFile << timer.getTime(MILLISECONDS) << ";" << path->getCost() << ";";
//                float prevLoss = loss;
//                loss = float(float(float(path->getCost()) / float(optimalCost)) - 1) * 100;
//                if(loss > prevLoss){
//                    worstThenLast++;
//                }
//                if(loss < bestLoss){
//                    bestLoss = loss;
//                }
//                if(worstThenLast > 8 || (i > 15 && worstThenLast > 3)){
//                    goNext = true;
//                }
//                outputFile << loss << ";";
//                totalCost += path->getCost();
//                i++;
//            }
//            float averageLoss = float(float(float(float(totalCost) / float(repetitions)) / optimalCost) - 1) * 100;
//            outputFile << averageLoss << ";best loss;"<< bestLoss<<"\n";
//    }
}