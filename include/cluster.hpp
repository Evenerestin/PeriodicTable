// #pragma once
// #include "common_includes.hpp"
// #include "element.hpp"
// #include "isotope.hpp"

// #define MAX 118

// class Cluster {
//     private:
//         static bool instanceFlag;
//     public:
//         Element* elements[MAX] {};
// };

#pragma once
#include "common_includes.hpp"
#include "element.hpp"
#include "isotope.hpp"

#define MAX 118

class Cluster {
    private:
        static bool instanceFlag;
    public:
        Element* elements[MAX] {};
        Cluster();
        ~Cluster();

        int loadData();
        int saveData();
        int addElement(std::string name, std::string symbol, int atomicNumber, double atomicMass, int group, int period, 
        int discoveryYear, int occurrence, int elementGroup, int blockGroup);
        std::string capitalizeString(std::string& name);

        void readCompound(std::vector <std::string> compoundElements);
};