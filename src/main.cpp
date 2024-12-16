//! g++ src/main.cpp src/cluster.cpp src/displayControl.cpp src/element.cpp src/isotope.cpp -o periodicTable

#include <conio.h>
#include "../include/common_includes.hpp"
#include "../include/cluster.hpp"
#include "../include/globals.hpp"
#include "../include/displayControl.hpp"

int zeroX = 14;
int zeroY = 5;
int currentX = 14;
int currentY = 5;
int currentAtomicNumber = 1;
int currentFilterBy = 0;

int main() {
    Cluster periodicTable;
    DisplayControl view;

    periodicTable.loadData();

    int input {};

    view.getConsoleProperties();
    view.setCursorVisibility(0, 0);
    // view.loadingScreenDisplay();

    // view.gridDisplay();
    // view.headerDisplay();
    // view.mainMenuDisplay();
    // view.gridPropsDisplay(periodicTable);
    view.mainScreenDisplay(periodicTable);

    do {
        view.clearHeaderDisplay();
        // currentAtomicNumber = view.findCurrentElement(currentX, currentY, periodicTable)
        currentAtomicNumber = view.findCurrentElement(periodicTable);
        if (currentAtomicNumber != -1)
            view.headerPropsDisplay(periodicTable, (currentAtomicNumber - 1));
        view.focus(1, 2);

        input = _getch();
        if (input == 0 || input == 224) {
            input = _getch();
            switch(input) {
                case UP: {
                    view.clearFocus(1, 2);
                    view.moveUp();
                    view.focus(1, 2);
                    break;
                    // std::cout << "up" << std caseTest::endl;
                };
                case RIGHT: {
                    view.clearFocus(1, 2);
                    view.moveRight();
                    view.focus(1, 2);
                    break;
                    // std::cout << "right" << std::endl;   caseTest
                };
                case DOWN: {
                    view.clearFocus(1, 2);
                    view.moveDown();
                    view.focus(1, 2);
                    break;
                    // std::cout << "down" << std::endl;    caseTest
                };
                case LEFT: {
                    view.clearFocus(1, 2);
                    view.moveLeft();
                    view.focus(1, 2);
                    break;
                    // std::cout << "left" << std::endl;    caseTest
                };
            };
        }
        else {
            input = toupper(input);
            switch(input) {
                case ENTER: {
                    view.propertiesPopUp(periodicTable, (currentAtomicNumber - 1));
                    view.mainScreenDisplay(periodicTable);
                    view.resetCursorPosition(currentX, currentY);
                    break;
                    // std::cout << "enter" << std::endl;   caseTest
                };
                case F: {
                    // view.changeFilterPopUp(currentFilterBy);
                    view.changeFilterPopUp();
                    view.mainScreenDisplay(periodicTable);
                    view.resetCursorPosition(currentX, currentY);
                    break;
                    // std::cout << "f" << std::endl;   caseTest
                };
                case D: {
                    break;
                    // std::cout << "d" << std::endl;   caseTest
                };
                case EXIT: {
                    break;
                    // std::cout << "exit" << std::endl;    caseTest
                };
            };
        }
    } while (input != EXIT);

    return 0;
};


    // periodicTable.addElement("Hydrogen", "H", 1, 1.008, 1, 1, 1766, 1, 1, 1);
    // periodicTable.addElement("Helium", "He", 2, 4.0026, 18, 1, 1895, 1, 10, 1);
    // periodicTable.addElement("Lithium", "Li", 3, 6.94, 1, 2, 1817, 1, 1, 1);
    // periodicTable.addElement("Beryllium", "Be", 4, 9.0122, 2, 2, 1797, 1, 2, 1);
    // periodicTable.addElement("Boron", "B", 5, 10.81, 13, 2, 1808, 1, 8, 2);
    // periodicTable.addElement("Carbon", "C", 6, 12.011, 14, 2, -1, 1, 8, 2);
    // periodicTable.addElement("Nitrogen", "N", 7, 14.007, 15, 2, 1772, 1, 8, 2);
    // periodicTable.addElement("Oxygen", "O", 8, 15.999, 16, 2, 1774, 1, 8, 2);
    // periodicTable.addElement("Fluorine", "F", 9, 18.998, 17, 2, 1886, 1, 9, 2);
    // periodicTable.addElement("Neon", "Ne", 10, 20.180, 18, 2, 1898, 1, 10, 2);
    // periodicTable.addElement("Sodium", "Na", 11, 22.990, 1, 3, 1807, 1, 1, 1);
    // periodicTable.addElement("Magnesium", "Mg", 12, 24.305, 2, 3, 1755, 1, 2, 1);
    // periodicTable.addElement("Aluminum", "Al", 13, 26.982, 13, 3, 1825, 1, 6, 2);
    // periodicTable.addElement("Silicon", "Si", 14, 28.085, 14, 3, 1824, 1, 7, 2);
    // periodicTable.addElement("Phosphorus", "P", 15, 30.974, 15, 3, 1669, 1, 8, 2);
    // periodicTable.addElement("Sulfur", "S", 16, 32.06, 16, 3, -1, 1, 8, 2);
    // periodicTable.addElement("Chlorine", "Cl", 17, 35.45, 17, 3, 1774, 1, 9, 2);
    // periodicTable.addElement("Argon", "Ar", 18, 39.948, 18, 3, 1894, 1, 10, 2);
    // periodicTable.addElement("Potassium", "K", 19, 39.098, 1, 4, 1807, 1, 1, 1);
    // periodicTable.addElement("Calcium", "Ca", 20, 40.078, 2, 4, 1808, 1, 2, 1);
    // periodicTable.addElement("Scandium", "Sc", 21, 44.956, 3, 4, 1879, 1, 5, 3);
    // periodicTable.addElement("Titanium", "Ti", 22, 47.867, 4, 4, 1791, 1, 5, 3);
    // periodicTable.addElement("Vanadium", "V", 23, 50.942, 5, 4, 1801, 1, 5, 3);
    // periodicTable.addElement("Chromium", "Cr", 24, 51.996, 6, 4, 1797, 1, 5, 3);
    // periodicTable.addElement("Manganese", "Mn", 25, 54.938, 7, 4, 1774, 1, 5, 3);
    // periodicTable.addElement("Iron", "Fe", 26, 55.845, 8, 4, -1, 1, 5, 3);
    // periodicTable.addElement("Cobalt", "Co", 27, 58.933, 9, 4, 1735, 1, 5, 3);
    // periodicTable.addElement("Nickel", "Ni", 28, 58.693, 10, 4, 1751, 1, 5, 3);
    // periodicTable.addElement("Copper", "Cu", 29, 63.546, 11, 4, -1, 1, 5, 3);
    // periodicTable.addElement("Zinc", "Zn", 30, 65.38, 12, 4, 1746, 1, 5, 3);
    // periodicTable.addElement("Gallium", "Ga", 31, 69.723, 13, 4, 1875, 1, 6, 2);
    // periodicTable.addElement("Germanium", "Ge", 32, 72.63, 14, 4, 1886, 1, 7, 2);
    // periodicTable.addElement("Arsenic", "As", 33, 74.922, 15, 4, -1, 1, 7, 2);
    // periodicTable.addElement("Selenium", "Se", 34, 78.96, 16, 4, 1817, 1, 8, 2);
    // periodicTable.addElement("Bromine", "Br", 35, 79.904, 17, 4, 1826, 1, 9, 2);
    // periodicTable.addElement("Krypton", "Kr", 36, 83.798, 18, 4, 1898, 1, 10, 2);
    // periodicTable.addElement("Rubidium", "Rb", 37, 85.468, 1, 5, 1861, 1, 1, 1);
    // periodicTable.addElement("Strontium", "Sr", 38, 87.62, 2, 5, 1790, 1, 2, 1);
    // periodicTable.addElement("Yttrium", "Y", 39, 88.906, 3, 5, 1794, 1, 5, 3);
    // periodicTable.addElement("Zirconium", "Zr", 40, 91.224, 4, 5, 1789, 1, 5, 3);
    // periodicTable.addElement("Niobium", "Nb", 41, 92.906, 5, 5, 1801, 1, 5, 3);
    // periodicTable.addElement("Molybdenum", "Mo", 42, 95.95, 6, 5, 1778, 1, 5, 3);
    // periodicTable.addElement("Technetium", "Tc", 43, 98, 7, 5, 1937, 2, 5, 3);
    // periodicTable.addElement("Ruthenium", "Ru", 44, 101.07, 8, 5, 1844, 1, 5, 3);
    // periodicTable.addElement("Rhodium", "Rh", 45, 102.91, 9, 5, 1803, 1, 5, 3);
    // periodicTable.addElement("Palladium", "Pd", 46, 106.42, 10, 5, 1803, 1, 5, 3);
    // periodicTable.addElement("Silver", "Ag", 47, 107.87, 11, 5, -1, 1, 5, 3);
    // periodicTable.addElement("Cadmium", "Cd", 48, 112.41, 12, 5, 1817, 1, 5, 3);
    // periodicTable.addElement("Indium", "In", 49, 114.82, 13, 5, 1863, 1, 6, 2);
    // periodicTable.addElement("Tin", "Sn", 50, 118.71, 14, 5, -1, 1, 6, 2);
    // periodicTable.addElement("Antimony", "Sb", 51, 121.76, 15, 5, -1, 1, 7, 2);
    // periodicTable.addElement("Tellurium", "Te", 52, 127.60, 16, 5, 1782, 1, 7, 2);
    // periodicTable.addElement("Iodine", "I", 53, 126.90, 17, 5, 1811, 1, 9, 2);
    // periodicTable.addElement("Xenon", "Xe", 54, 131.29, 18, 5, 1898, 1, 10, 2);
    // periodicTable.addElement("Cesium", "Cs", 55, 132.91, 1, 6, 1860, 1, 1, 1);
    // periodicTable.addElement("Barium", "Ba", 56, 137.33, 2, 6, 1808, 1, 2, 1);
    // periodicTable.addElement("Lanthanum", "La", 57, 138.91, 3, 6, 1839, 1, 3, 4);
    // periodicTable.addElement("Cerium", "Ce", 58, 140.12, 3, 6, 1803, 1, 3, 4);
    // periodicTable.addElement("Praseodymium", "Pr", 59, 140.91, 3, 6, 1885, 1, 3, 4);
    // periodicTable.addElement("Neodymium", "Nd", 60, 144.24, 3, 6, 1885, 1, 3, 4);
    // periodicTable.addElement("Promethium", "Pm", 61, 145, 3, 6, 1945, 2, 3, 4);
    // periodicTable.addElement("Samarium", "Sm", 62, 150.36, 3, 6, 1879, 1, 3, 4);
    // periodicTable.addElement("Europium", "Eu", 63, 151.96, 3, 6, 1901, 1, 3, 4);
    // periodicTable.addElement("Gadolinium", "Gd", 64, 157.25, 3, 6, 1880, 1, 3, 4);
    // periodicTable.addElement("Terbium", "Tb", 65, 158.93, 3, 6, 1843, 1, 3, 4);
    // periodicTable.addElement("Dysprosium", "Dy", 66, 162.50, 3, 6, 1886, 1, 3, 4);
    // periodicTable.addElement("Holmium", "Ho", 67, 164.93, 3, 6, 1878, 1, 3, 4);
    // periodicTable.addElement("Erbium", "Er", 68, 167.26, 3, 6, 1842, 1, 3, 4);
    // periodicTable.addElement("Thulium", "Tm", 69, 168.93, 3, 6, 1879, 1, 3, 4);
    // periodicTable.addElement("Ytterbium", "Yb", 70, 173.05, 3, 6, 1878, 1, 3, 4);
    // periodicTable.addElement("Lutetium", "Lu", 71, 174.97, 3, 6, 1907, 1, 3, 4);
    // periodicTable.addElement("Hafnium", "Hf", 72, 178.49, 4, 6, 1923, 1, 5, 3);
    // periodicTable.addElement("Tantalum", "Ta", 73, 180.95, 5, 6, 1802, 1, 5, 3);
    // periodicTable.addElement("Tungsten", "W", 74, 183.84, 6, 6, 1783, 1, 5, 3);
    // periodicTable.addElement("Rhenium", "Re", 75, 186.21, 7, 6, 1925, 1, 5, 3);
    // periodicTable.addElement("Osmium", "Os", 76, 190.23, 8, 6, 1803, 1, 5, 3);
    // periodicTable.addElement("Iridium", "Ir", 77, 192.22, 9, 6, 1803, 1, 5, 3);
    // periodicTable.addElement("Platinum", "Pt", 78, 195.08, 10, 6, 1735, 1, 5, 3);
    // periodicTable.addElement("Gold", "Au", 79, 196.97, 11, 6, -1, 1, 5, 3);
    // periodicTable.addElement("Mercury", "Hg", 80, 200.59, 12, 6, -1, 1, 5, 3);
    // periodicTable.addElement("Thallium", "Tl", 81, 204.38, 13, 6, 1861, 1, 6, 2);
    // periodicTable.addElement("Lead", "Pb", 82, 207.2, 14, 6, -1, 1, 6, 2);
    // periodicTable.addElement("Bismuth", "Bi", 83, 208.98, 15, 6, -1, 1, 6, 2);
    // periodicTable.addElement("Polonium", "Po", 84, 209, 16, 6, 1898, 1, 7, 2);
    // periodicTable.addElement("Astatine", "At", 85, 210, 17, 6, 1940, 2, 9, 2);
    // periodicTable.addElement("Radon", "Rn", 86, 222, 18, 6, 1900, 1, 10, 2);
    // periodicTable.addElement("Francium", "Fr", 87, 223, 1, 7, 1939, 2, 1, 1);
    // periodicTable.addElement("Radium", "Ra", 88, 226, 2, 7, 1898, 1, 2, 1);
    // periodicTable.addElement("Actinium", "Ac", 89, 227, 3, 7, 1899, 1, 4, 4);
    // periodicTable.addElement("Thorium", "Th", 90, 232.04, 3, 7, 1829, 1, 4, 4);
    // periodicTable.addElement("Protactinium", "Pa", 91, 231.04, 3, 7, 1913, 1, 4, 4);
    // periodicTable.addElement("Uranium", "U", 92, 238.03, 3, 7, 1789, 1, 4, 4);
    // periodicTable.addElement("Neptunium", "Np", 93, 237, 3, 7, 1940, 2, 4, 4);
    // periodicTable.addElement("Plutonium", "Pu", 94, 244, 3, 7, 1940, 2, 4, 4);
    // periodicTable.addElement("Americium", "Am", 95, 243, 3, 7, 1944, 2, 4, 4);
    // periodicTable.addElement("Curium", "Cm", 96, 247, 3, 7, 1944, 2, 4, 4);
    // periodicTable.addElement("Berkelium", "Bk", 97, 247, 3, 7, 1949, 2, 4, 4);
    // periodicTable.addElement("Californium", "Cf", 98, 251, 3, 7, 1950, 2, 4, 4);
    // periodicTable.addElement("Einsteinium", "Es", 99, 252, 3, 7, 1952, 2, 4, 4);
    // periodicTable.addElement("Fermium", "Fm", 100, 257, 3, 7, 1952, 2, 4, 4);
    // periodicTable.addElement("Mendelevium", "Md", 101, 258, 3, 7, 1955, 2, 4, 4);
    // periodicTable.addElement("Nobelium", "No", 102, 259, 3, 7, 1966, 2, 4, 4);
    // periodicTable.addElement("Lawrencium", "Lr", 103, 262, 3, 7, 1961, 2, 4, 4);
    // periodicTable.addElement("Rutherfordium", "Rf", 104, 267, 4, 7, 1969, 2, 5, 3);
    // periodicTable.addElement("Dubnium", "Db", 105, 270, 5, 7, 1967, 2, 5, 3);
    // periodicTable.addElement("Seaborgium", "Sg", 106, 271, 6, 7, 1974, 2, 5, 3);
    // periodicTable.addElement("Bohrium", "Bh", 107, 274, 7, 7, 1981, 2, 5, 3);
    // periodicTable.addElement("Hassium", "Hs", 108, 277, 8, 7, 1984, 2, 5, 3);
    // periodicTable.addElement("Meitnerium", "Mt", 109, 278, 9, 7, 1982, 2, 5, 3);
    // periodicTable.addElement("Darmstadtium", "Ds", 110, 281, 10, 7, 1994, 2, 5, 3);
    // periodicTable.addElement("Roentgenium", "Rg", 111, 282, 11, 7, 1994, 2, 5, 3);
    // periodicTable.addElement("Copernicium", "Cn", 112, 285, 12, 7, 1996, 2, 5, 3);
    // periodicTable.addElement("Nihonium", "Nh", 113, 286, 13, 7, 2003, 2, 6, 2);
    // periodicTable.addElement("Flerovium", "Fl", 114, 289, 14, 7, 1998, 2, 6, 2);
    // periodicTable.addElement("Moscovium", "Mc", 115, 290, 15, 7, 2003, 2, 6, 2);
    // periodicTable.addElement("Livermorium", "Lv", 116, 293, 16, 7, 2000, 2, 6, 2);
    // periodicTable.addElement("Tennessine", "Ts", 117, 294, 17, 7, 2010, 2, 9, 2);
    // periodicTable.addElement("Oganesson", "Og", 118, 294, 18, 7, 2002, 2, 10, 2);
    // periodicTable.saveData();