// #pragma once
// #include "common_includes.hpp"
// #include "isotope.hpp"

// class Element {
//     private:
//         char name[20];
//         char symbol[3];
//         int atomicNumber;
//         double atomicMass;
//         int group;
//         int period;
//         std::vector<Isotope*> isotopes;
//         int discoveryYear;
//         int occurrence;
//         int elementGroup;
//         int blockGroup;
// };

#pragma once
#include "common_includes.hpp"
#include "isotope.hpp"

class Element {
    private:
        char name[20];
        char symbol[3];
        int atomicNumber;
        double atomicMass;
        int group;
        int period;
        std::vector<Isotope*> isotopes;
        int discoveryYear;
        int occurrence;
        int elementGroup;
        int blockGroup;
    public:
        Element();
        Element(const char* name, const char* symbol, int atomicNumber, double atomicMass, int group, int period,
                int discoveryYear, int occurrence, int elementGroup, int blockGroup);
        ~Element();

        std::string getName();
        std::string getSymbol();
        int getAtomicNumber();
        double getAtomicMass();
        int getGroup();
        int getPeriod();
        int getDiscoveryYear();
        int getOccurrence();
        int getElementGroup();
        int getBlockGroup();

        int determineStability();
        std::string determineShellConfiguration();
        int determineMetallicity();
};