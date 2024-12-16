// #pragma once
// #include "common_includes.hpp"
// #include <iomanip>
// #include <utility>
// #include <cctype>

// class DisplayControl {
//     private:
//         HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//         COORD CursorPosition;

//         int screenWidth {};
//         int screenHeight {};
//         int centerX {};
//         int centerY {};

//         int displayZeroX {12};
//         int displayZeroY {4}; 
//         int cellWidth {6}; // width 91
//         int cellHeight {3}; // height 15
//         int headerWidth {25};
//         int headerHeight {7};

//         std::vector<std::string> elementGroup {
//             "Undefined",
//             "Alkali Metal",
//             "Alkaline Earth Metal",
//             "Lanthanide",
//             "Actinide",
//             "Transition Metal",
//             "Post Transition Metal",
//             "Metalloid",
//             "Nonmetal",
//             "Halogen",
//             "Noble Gas"        
//         };

//         std::vector <std::pair<std::string, std::string>> mainMenuOptions = {
//             {"[LEFT]", "Move Left"},
//             {"[UP]", "Move Up"},
//             {"[DOWN]", "Move Down"},
//             {"[RIGHT]", "Move Right"},
//             {"[ENTER]", "View Properties"},
//             {"[F]", "Filter Table"},
//             {"[D]", "Data Management"},
//             {"[X]", "Exit"}
//         };
//         std::vector <std::pair<std::string, std::string>> dataMenuOptions = {
//             {"[S]", "Search By"},
//             {"[F]", "Filter By"},
//             {"[C]", "Calculator"},
//             {"[T]", "Table View"},
//             {"[A]", "Add Element"},
//             {"[D]", "Delete Element"},
//             {"[X]", "Exit"}
//         };
//         std::vector <std::pair<std::string, std::string>> filterMenuOptions = {
//             {"[UP]", "Move Up"},
//             {"[DOWN]", "Move Down"},
//             {"[ENTER]", "Choose Filter"},
//             {"[ESC]", "Close Window"}
//         };
//         std::vector <std::pair<std::string, std::string>> propertiesMenuOptions = {
//             {"[UP]", "Move Up"},
//             {"[DOWN]", "Move Down"},
//             {"[E]", "Edit Property"},
//             {"[LEFT]", "View Element Before"},
//             {"[RIGHT]", "View Element After"},
//             {"[ESC]", "Close Window"}
//         };
// };

#pragma once
#include "common_includes.hpp"
#include <iomanip>
#include <utility>
#include <cctype>

class DisplayControl {
    private:
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD CursorPosition;

        int screenWidth {};
        int screenHeight {};
        int centerX {};
        int centerY {};

        int displayZeroX {12};
        int displayZeroY {4}; 
        int cellWidth {6}; // width 91
        int cellHeight {3}; // height 15
        int headerWidth {25};
        int headerHeight {7};

        std::vector<std::string> elementGroup {
            "Undefined",
            "Alkali Metal",
            "Alkaline Earth Metal",
            "Lanthanide",
            "Actinide",
            "Transition Metal",
            "Post Transition Metal",
            "Metalloid",
            "Nonmetal",
            "Halogen",
            "Noble Gas"        
        };

        std::vector <std::pair<std::string, std::string>> mainMenuOptions = {
            {"[LEFT]", "Move Left"},
            {"[UP]", "Move Up"},
            {"[DOWN]", "Move Down"},
            {"[RIGHT]", "Move Right"},
            {"[ENTER]", "View Properties"},
            {"[F]", "Filter Table"},
            {"[X]", "Exit"}
        };
        std::vector <std::pair<std::string, std::string>> filterMenuOptions = {
            {"[UP]", "Move Up"},
            {"[DOWN]", "Move Down"},
            {"[ENTER]", "Choose Filter"},
            {"[ESC]", "Close Window"}
        };
        std::vector <std::pair<std::string, std::string>> propertiesMenuOptions = {
            {"[UP]", "Move Up"},
            {"[DOWN]", "Move Down"},
            {"[ESC]", "Close Window"},
            // {"[E]", "Edit Property"},
            {"[LEFT]", "View Element Before"},
            {"[RIGHT]", "View Element After"}
        };
        // std::vector <std::pair<std::string, std::string>> dataMenuOptions = {
        //     {"[S]", "Search Element"},
        //     {"[C]", "Calculator"},
        //     {"[ESC]", "Close Window"},
        //     {"[E]", "Electron Visualization"},
        //     {"[X]", "Exit"}
        // };
        // std::vector <std::pair<std::string, std::string>> calculatorMenuOptions = {
        //     {"[M]", "Molar Mass"},
        //     {"[S]", "Stoichiometry"},
        //     {"[G]", "Gas Law"},
        //     {"[U]", "Unit Conversion"},
        //     {"[P]", "Percentage Composition"},
        //     {"[]", ""}
        // };

    public:
    // cursorPositioning
        void getConsoleProperties();

        void gotoXY(int x, int y);
        void gotoXY(int x, int y, const std::string& text);
        void gotoXY(int x, int y, const char* text);

        void resetCursorPosition(int& currentX, int& currentY);


    //displayManagement
        void setCursorVisibility(bool visible, DWORD size);
        void colorScheme(int foregroundColor, int backgroundColor);
        void clearScreen();
        void clearScreen(int foregroundColor, int backgroundColor);

        void containerDisplay(int baseX, int baseY, int width, int height, int foregroundColor, int backgroundColor, int doubleLined);

        void loadingScreenDisplay();
        void mainScreenDisplay(Cluster& clusterInstance);

        void gridDisplay();
        void gridPropsDisplay(Cluster& clusterInstance);    //elementSymbolsDisplay
        // void gridPropsDisplay(Cluster& clusterInstance, int filterBy);  //elementSymbolsDisplay

        void headerDisplay();   //gridHeaderDisplay
        void clearHeaderDisplay();  //clearGridHeaderDisplay
        // void headerPropsDisplay(Cluster& clusterInstance, int index, int filterBy); //elementHeaderDisplay
        void headerPropsDisplay(Cluster& clusterInstance, int index); //elementHeaderDisplay



    // gridPositionManagement
        // void moveUp(int& currentX, int& currentY);
        // void moveRight(int& currentX, int& currentY);
        // void moveDown(int& currentX, int& currentY);
        // void moveLeft(int& currentX, int& currentY);
        void moveUp();
        void moveRight();
        void moveDown();
        void moveLeft();

        // int findCurrentElement(int currentX, int currentY, Cluster& clusterInstance);
        int findCurrentElement(Cluster& clusterInstance);
        // void focus(int& currentX, int& currentY, int adjustLeft, int adjustRight);
        void focus(int adjustLeft, int adjustRight);
        // void clearFocus(int& currentX, int& currentY, int adjustLeft, int adjustRight);
        void clearFocus(int adjustLeft, int adjustRight);



    //popUpWindows
        // void changeFilterPopUp(int& filterBy);  //changeFilterWindow
        void changeFilterPopUp();  //changeFilterWindow
        // void filterColorScheme(int filterBy, Element* element);
        void filterColorScheme(Element* element);
        void getFilterProps(int filterBy, int index, Element* element, std::string& filterKey, int& filterColor);

        void propertiesPopUp(Cluster& clusterInstance, int index);  //displayPropertiesWindow
        // void propertiesPropsDisplay(Cluster& clusterInstance, int index, int width, int height, int& adjustX, int& adjustY, int& currentX, int& currentY, int& propertyWidth); //updatePropertiesWindow
        // void propertiesPropsDisplay(Cluster& clusterInstance, int index, int width, int height, int& adjustX, int& currentY, int& propertyWidth); //updatePropertiesWindow
        void propertiesPropsDisplay(Cluster& clusterInstance, int index, int width, int height, int& propertyWidth); //updatePropertiesWindow



    //menuManagement
        void menuDisplay(const std::vector<std::pair<std::string, std::string>>& menuOptions);
        void menuDisplay(const std::vector<std::pair<std::string, std::string>>& menuOptions, int zeroX);

        void mainMenuDisplay();
        void dataMenuDisplay();
        void filterMenuDisplay();
        void propertiesMenuDisplay();
        void dataManagementMenuDisplay();
};

// x80: Ç    x81: ü    x82: é    x83: â    x84: ä    x85: à    x86: å    x87: ç    x88: ê    x89: ë    x8A: è    x8B: ï    x8C: î    x8D: ì    x8E: Ä    x8F: Å
// x90: É    x91: æ    x92: Æ    x93: ô    x94: ö    x95: ò    x96: û    x97: ù    x98: ÿ    x99: Ö    x9A: Ü    x9B: ¢    x9C: £    x9D: ¥    x9E: ₧    x9F: ƒ
// xA0: á    xA1: í    xA2: ó    xA3: ú    xA4: ñ    xA5: Ñ    xA6: ª    xA7: º    xA8: ¿    xA9: ⌐    xAA: ¬    xAB: ½    xAC: ¼    xAD: ¡    xAE: «    xAF: »
// xB0: ░    xB1: ▒    xB2: ▓    xB3: │    xB4: ┤    xB5: Á    xB6: Â    xB7: À    xB8: ©    xB9: ╣    xBA: ║    xBB: ╗    xBC: ╝    xBD: ¢    xBE: ¥    xBF: ┐
// xC0: └    xC1: ┴    xC2: ┬    xC3: ├    xC4: ─    xC5: ┼    xC6: ã    xC7: Ã    xC8: ╚    xC9: ╔    xCA: ╩    xCB: ╦    xCC: ╠    xCD: ═    xCE: ╬    xCF: ¤
// xD0: ð    xD1: Ð    xD2: Ê    xD3: Ë    xD4: È    xD5: ı    xD6: Í    xD7: Î    xD8: Ï    xD9: ┘    xDA: ┌    xDB: █    xDC: ▄    xDD: ¦    xDE: Ì    xDF: ▀