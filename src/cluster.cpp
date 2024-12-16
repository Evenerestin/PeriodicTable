// #include "../include/cluster.hpp"

// bool Cluster::instanceFlag = false;

#include "../include/cluster.hpp"

bool Cluster::instanceFlag = false;

Cluster::Cluster() {
    if (instanceFlag)
        exit(1);
    instanceFlag = true;
    for (int i = 0; i < MAX; ++i)
        elements[i] = nullptr;
};

Cluster::~Cluster() {
    for (int i = 0; i < MAX; ++i)
        if (elements[i] != nullptr) {
            delete elements[i];
            elements[i] = nullptr;
        }
    instanceFlag = false;
};

int Cluster::loadData() {
    std::ifstream inputFile("periodicTable.dat", std::ios::binary);
    if (inputFile.is_open()) {
        for (int i = 0; i < MAX; ++i) {
            if (elements[i] == nullptr) {
                Element tempElement;
                inputFile.read(reinterpret_cast<char*>(&tempElement), sizeof(Element));
                if (!inputFile.fail()) {
                    elements[i] = new Element(tempElement);
                }
            }
        }
    }
    inputFile.close();
    return 0;
};
int Cluster::saveData() {
    std::ofstream outputFile("periodicTable.dat", std::ios::binary);
    if (outputFile.is_open()) {
        for (int i = 0; i < MAX; ++i) {
            if (elements[i] != nullptr) {
                outputFile.write(reinterpret_cast<char*>(elements[i]), sizeof(Element));
            };
        };
    }
    outputFile.close();
    return 0;
};

int Cluster::addElement(std::string name, std::string symbol, int atomicNumber, double atomicMass, int group, int period, 
                int discoveryYear, int occurrence, int elementGroup, int blockGroup) {
    if (atomicNumber < 1 || atomicNumber > MAX)
        return 1;
    name = capitalizeString(name);
    Element* newElement = new Element(name.c_str(), symbol.c_str(), atomicNumber, atomicMass, group, period, discoveryYear, occurrence, elementGroup, blockGroup);
    if (newElement == nullptr)
        return 1;
    elements[atomicNumber - 1] = newElement;
    saveData();
    return 0;
};

std::string Cluster::capitalizeString(std::string& name) {
    std::string formattedName;
    if (!name.empty()) {
        formattedName += std::toupper(name[0]);
        for (size_t i = 1; i < name.length(); ++i) {
            formattedName += std::tolower(name[i]);
        }
    }
    return formattedName;
};