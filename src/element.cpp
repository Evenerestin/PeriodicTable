// #include "../include/element.hpp"

#include "../include/element.hpp"

Element::Element() : atomicNumber(0), atomicMass(0), group(0), period(0), discoveryYear(0), occurrence(0), elementGroup(0), blockGroup(0) {
    strcpy(name, "");
    strcpy(symbol, "");
};

Element::Element(const char* name, const char* symbol, int atomicNumber, double atomicMass, int group, int period,
int discoveryYear, int occurrence, int elementGroup, int blockGroup)
: atomicNumber(atomicNumber), atomicMass(atomicMass), group(group), period(period),
discoveryYear(discoveryYear), occurrence(occurrence), elementGroup(elementGroup), blockGroup(blockGroup) {
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0';
    strncpy(this->symbol, symbol, sizeof(this->symbol) - 1);
    this->symbol[sizeof(this->symbol) - 1] = '\0';
};

Element::~Element() {
    for (Isotope* isotope : isotopes)
        delete isotope;
}


std::string Element::getName() { return name; };
std::string Element::getSymbol() { return symbol; };
// const char* getSymbol() { return symbol; };
int Element::getAtomicNumber() { return atomicNumber; };
double Element::getAtomicMass() { return atomicMass; };
int Element::getGroup() { return group; };
int Element::getPeriod() { return period; };
int Element::getDiscoveryYear() { return discoveryYear; };
int Element::getOccurrence() { return occurrence; };
int Element::getElementGroup() { return elementGroup; };
int Element::getBlockGroup() { return blockGroup; };

int Element::determineStability() {
    if (atomicNumber < 83)
        return 1;
    else
        return 0;
};

std::string Element::determineShellConfiguration() {
    int availableElectrons = atomicNumber;
    std::string shellConfiguration;
    for (int i = 1; i <= 7; i++) {
        int currentShellMax = 2 * (i * i);
        char shellSymbol = static_cast<char>(75 + (i - 1));
        if (availableElectrons > currentShellMax) {
            shellConfiguration += std::string(1, shellSymbol) + std::to_string(currentShellMax) + " ";
            availableElectrons -= currentShellMax;
        } else {
            shellConfiguration += std::string(1, shellSymbol) + std::to_string(availableElectrons) + " ";
            break;
        }
    }
    return shellConfiguration;
};

int Element::determineMetallicity() {
    switch (elementGroup) {
        case 0:
            return 0;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            return 1;
        case 7:
            return 2;
        case 8:
        case 9:
        case 10:
            return 3;
        default:
            return 0;
    };
};