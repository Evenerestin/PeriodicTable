#include "../include/globals.hpp"
#include "../include/element.hpp"
#include "../include/cluster.hpp"
#include "../include/isotope.hpp"
#include "../include/displayControl.hpp"

// cursorPositioning
void DisplayControl::getConsoleProperties() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    screenWidth = csbi.srWindow.Right - csbi.srWindow.Left;
    screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top;
    centerX = screenWidth / 2;
    centerY = screenHeight / 2;
};

void DisplayControl::gotoXY(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
};
void DisplayControl::gotoXY(int x, int y, const std::string& text) {
    gotoXY(x, y);
    std::cout << text;
};
void DisplayControl::gotoXY(int x, int y, const char* text) {
    gotoXY(x, y);
    std::cout << text;
};

void DisplayControl::resetCursorPosition(int& currentX, int& currentY) {
    currentX = zeroX;
    currentY = zeroY;
    focus(1 ,2);
};


//displayManagement
void DisplayControl::setCursorVisibility(bool visible, DWORD size) {
    if(size == 0)
        size = 20;
    CONSOLE_CURSOR_INFO lpCursor;	
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console,&lpCursor);
};
void DisplayControl::colorScheme(int foregroundColor, int backgroundColor) {
    int colorScheme = (foregroundColor + (backgroundColor * 16));
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorScheme);
};
void DisplayControl::clearScreen() {
    colorScheme(15, 0);
    DWORD n;
    DWORD size;
    COORD coord = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    GetConsoleScreenBufferInfo ( h, &csbi );
    size = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
    GetConsoleScreenBufferInfo ( h, &csbi );
    FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );
    SetConsoleCursorPosition ( h, coord );
};
void DisplayControl::clearScreen(int foregroundColor, int backgroundColor) {
    colorScheme(foregroundColor, backgroundColor);
    DWORD n;
    DWORD size;
    COORD coord = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    GetConsoleScreenBufferInfo ( h, &csbi );
    size = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
    GetConsoleScreenBufferInfo ( h, &csbi );
    FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );
    SetConsoleCursorPosition ( h, coord );
};

void DisplayControl::containerDisplay(int baseX, int baseY, int width, int height, int foregroundColor, int backgroundColor, int doubleLined) {
    colorScheme(foregroundColor, backgroundColor);
    char outerLine[2][6] = {
        {'\xDA', '\xBF', '\xD9', '\xC0', '\xB3', '\xC4'},
        {'\xC9', '\xBB', '\xBC', '\xC8', '\xBA', '\xCD'}
    };
    std::string horizontalLine((width-2), outerLine[doubleLined][5]);
    std::string innerLine((width-2), ' ');

    gotoXY(baseX, baseY);
    std::cout << outerLine[doubleLined][0] << horizontalLine << outerLine[doubleLined][1];
    for (int i = 1; i < height; i++) {
        gotoXY(baseX, (baseY + i));
        std::cout << outerLine[doubleLined][4] << innerLine << outerLine[doubleLined][4]; 
    }
    gotoXY(baseX, (baseY + height));
    std::cout << outerLine[doubleLined][3] << horizontalLine << outerLine[doubleLined][2];
};

void DisplayControl::loadingScreenDisplay() {
    clearScreen(0 ,7);
    gotoXY(5 ,centerY, "P E R I O D I C    T A B L E ");
    Sleep(500);
    gotoXY(36, centerY);
    Sleep(500);
    gotoXY(38, centerY);
    Sleep(500);
    for (int i = 0; i < 3; i++) {
        gotoXY(38 + (i * 2) ,centerY, " .");
        Sleep(700);
    };
    clearScreen();
};
void DisplayControl::mainScreenDisplay(Cluster& clusterInstance) {
    gridDisplay();
    headerDisplay();
    mainMenuDisplay();
    gridPropsDisplay(clusterInstance);
};

//tableViewManagement
void DisplayControl::gridDisplay() {
    int p = 0, i = 0;

    char upperCorner[3] {'\xDA', '\xC2', '\xBF'}; // "┌" "┬" "┐"
    char innerCorner[3] {'\xC3', '\xC5', '\xB4'}; // "├" "┼" "┤"
    char lowerCorner[3] {'\xC0', '\xC1', '\xD9'}; // "└" "┴" "┘"
    char edgeLine[2] {'\xB3', '\xC4'};

    std::string horizontalEdge(cellWidth - 2, '\xC4'); // "───"
    std::string contentSpace(cellWidth - 2, ' '); // "   "
    std::string horizontalInner = contentSpace + "\xB3"; //    "│"
    std::string horizontalCorner = horizontalEdge + "\xC5"; // "───┼"

    // period 1
    gotoXY(displayZeroX, displayZeroY);
    std::cout << upperCorner[0] << horizontalEdge << upperCorner[2] << contentSpace;
    for (i = 0; i < 15; i++)
        std::cout << contentSpace << " ";
    std::cout << upperCorner[0] << horizontalEdge << upperCorner[2];
    gotoXY(displayZeroX, displayZeroY + 1);
    std::cout << edgeLine[0] << contentSpace << edgeLine[0] << contentSpace;
    for (i = 0; i < 15; i++)
        std::cout << " " << contentSpace;
    std::cout << edgeLine[0] << contentSpace << edgeLine[0];

    // period 2-3
    gotoXY(displayZeroX, displayZeroY + 2); //+ (cellHeight - 1)
    std::cout << innerCorner[0] << horizontalEdge << innerCorner[1] << horizontalEdge << upperCorner[2] << contentSpace;
    for (i = 0; i < 9; i++)
        std::cout << " " << contentSpace;
    std::cout << upperCorner[0] << horizontalEdge;
    for (i = 0; i < 4; i++)
        std::cout << upperCorner[1] << horizontalEdge;
    std::cout << innerCorner[1] << horizontalEdge << innerCorner[2];

    gotoXY(displayZeroX, displayZeroY + 4);
    std::cout << innerCorner[0] << horizontalCorner << horizontalEdge << innerCorner[2] << contentSpace;
    for (i = 0; i < 9; i++)
        std::cout << " " << contentSpace;
    std::cout << innerCorner[0];
    for (i = 0; i < 5; i++)
        std::cout << horizontalCorner;
    std::cout << horizontalEdge << innerCorner[2];

    for (p = 0; p < 2; p++) {
        gotoXY(displayZeroX, displayZeroY + 3 + (2 * p)); //+ (cellHeight - 1) + 1
        std::cout << edgeLine[0];
        for (i = 0; i < 2; i++)
            // std::cout << edgeLine[0] << contentSpace;
            std::cout << horizontalInner;
        std::cout << contentSpace;
        for (i = 0; i < 9; i++)
            std::cout << " " << contentSpace;
        std::cout << edgeLine[0];
        for (i = 0; i < 6; i++)
            // std::cout << edgeLine[0] << contentSpace;
            std::cout << horizontalInner;
    }

    // period 4-7
    gotoXY(displayZeroX, displayZeroY + 6);
    std::cout << innerCorner[0] << horizontalCorner << horizontalCorner << horizontalEdge;
    for (i = 0; i < 9; i++)
        std::cout << upperCorner[1] << horizontalEdge;
    std::cout << innerCorner[1];
    for (i = 0; i < 5; i++)
        std::cout << horizontalCorner;
    std::cout << horizontalEdge << innerCorner[2];

    for (p = 0; p < 3; p++) {
        gotoXY(displayZeroX, displayZeroY + 8 + (2 * p));
        std::cout << innerCorner[0];
        for (i = 0; i < 17; i++)
            std::cout << horizontalCorner;
        std::cout << horizontalEdge << innerCorner[2];
    }    

    for (p = 0; p < 4; p++) {
        gotoXY(displayZeroX, displayZeroY + 7 + (2 * p)); //+ (cellHeight - 1) + 1
        std::cout << edgeLine[0];
        for (i = 0; i <= 17; i++)
            std::cout << horizontalInner;
    }

    gotoXY(displayZeroX, displayZeroY + 14);
    std::cout << lowerCorner[0] << horizontalEdge;
    for (i = 0; i < 17; i++)
        std::cout << lowerCorner[1] << horizontalEdge;
    std::cout << lowerCorner[2];

    gotoXY(displayZeroX + 12, displayZeroY + 11, "*");
    gotoXY(displayZeroX + 12, displayZeroY + 13, "**");

    // La-Ac
    gotoXY(displayZeroX + 7, displayZeroY + 17, "*");
    gotoXY(displayZeroX + 7, displayZeroY + 19, "**");

    gotoXY(displayZeroX + 10, displayZeroY + 16);
    std::cout << upperCorner[0] << horizontalEdge;
    for (i = 0; i < 14; i++)
        std::cout << upperCorner[1] << horizontalEdge;
    std::cout << upperCorner[2];

    gotoXY(displayZeroX + 10, displayZeroY + 18);
    std::cout << innerCorner[0];
    for (i = 0; i < 14; i++)
        std::cout << horizontalCorner;
    std::cout << horizontalEdge << innerCorner[2];

    gotoXY(displayZeroX + 10, displayZeroY + 20);
    std::cout << lowerCorner[0] << horizontalEdge;
    for (i = 0; i < 14; i++)
        std::cout << lowerCorner[1] << horizontalEdge;
    std::cout << lowerCorner[2];

    for (p = 0; p < 2; p++) {
        gotoXY(displayZeroX + 10, displayZeroY + 17 + (2 * p)); //+ (cellHeight - 1) + 1
        std::cout << edgeLine[0];
        for (i = 0; i <= 14; i++)
            std::cout << horizontalInner;
    };
};

void DisplayControl::gridPropsDisplay(Cluster& clusterInstance) {
    int La {};
    int Ac {};
    for (int i = 0; i < MAX; ++i) {
        Element* element = clusterInstance.elements[i];
        if (currentFilterBy != 0)
            filterColorScheme(element);
        if (element != nullptr) {
            if (i >= 56 && i <= 70) {
                gotoXY(displayZeroX + 12 + (La * 5), displayZeroY + 17);
                std::cout << element->getSymbol();
                La++;
            }
            else if (i >= 88 && i <= 102) {
                gotoXY(displayZeroX + 12 + (Ac * 5), displayZeroY + 19);
                std::cout << element->getSymbol();
                Ac++;
            }
            else {
                int group = element->getGroup();
                int period = element->getPeriod();
                int adjustX = (5 * (group-1)) + 2;
                int adjustY = (2 * (period-1)) + 1;
                gotoXY(displayZeroX + adjustX, displayZeroY + adjustY);
                std::cout << element->getSymbol();
            }
        };
    };
};

void DisplayControl::headerDisplay() {
    containerDisplay((displayZeroX + 23), (displayZeroY - 3), headerWidth, headerHeight, 15, 0, 1);
};   

//gridHeaderDisplay
void DisplayControl::clearHeaderDisplay() {
    std::string clearWidth(headerWidth - 2, ' ');
    for (int i = 0; i < (headerHeight - 2); ++i)
        gotoXY(displayZeroX + 24, (displayZeroY - 2) + i, clearWidth);
};  

//clearGridHeaderDisplay
void DisplayControl::headerPropsDisplay(Cluster& clusterInstance, int index) {
    Element* element = clusterInstance.elements[index];

    if (element != nullptr) {
        int adjustX = (displayZeroX + 23) + (headerWidth / 2);
        int adjustY = displayZeroY - 3;
        std::string filterKey {};
        int filterColor {};

        colorScheme(15, 0);

        gotoXY(displayZeroX + 25, adjustY + 1);
        std::cout << element->getAtomicNumber();
        if (element->getAtomicMass() >= 100) 
            gotoXY((displayZeroX + 23 + headerWidth - 9), adjustY + 1);
        else if (element->getAtomicMass() >= 10)
            gotoXY((displayZeroX + 23 + headerWidth - 8), adjustY + 1);
        else
            gotoXY((displayZeroX + 23 + headerWidth - 7), adjustY + 1);
        std::cout << std::fixed << std::setprecision(3) << element->getAtomicMass() << std::defaultfloat;
        
        std::string elementName = element->getName();

        std::string elementSymbol = element->getSymbol();
        if (elementSymbol.length() % 2 == 0)
            gotoXY(adjustX - 1, adjustY + 3, element->getSymbol());
        else
            gotoXY(adjustX, adjustY + 3, element->getSymbol());

        getFilterProps(currentFilterBy, index, element, filterKey, filterColor);

        // gotoXY(adjustX, adjustY + 3, element->getSymbol());
        gotoXY(adjustX - (elementName.length() / 2), adjustY + 4, elementName);
        if (!filterKey.empty()) {
            colorScheme(filterColor, 0);
            gotoXY(adjustX - (filterKey.length() / 2), adjustY + 5, filterKey);
            colorScheme(15, 0);
        }
        else {
            std::string clearWidth((headerWidth - 2), ' ');
            gotoXY(displayZeroX + 24, adjustY + 5, clearWidth);
        };
    };
};



// gridPositionManagement
void DisplayControl::moveUp() {
    if ((currentX == 14 || currentX == 99) && currentY == 7)
        currentY -= 2;
    else if ((currentX >= 14 && currentX <= 19 && (currentY == 9 || currentY == 11)) || 
            (currentX >= 74 && currentX <= 99 && (currentY == 9 || currentY == 11)))
                currentY -= 2;
    else if ((currentX >= 14 && currentX <= 99) && (currentY >= 13 && currentY <= 17))
        currentY -= 2;
    else if (currentX == 24 && currentY == 21)
        currentY = 13;
    else if ((currentX >= 29 && currentX <= 94) && currentY == 21)
        currentY = 17;
    else if ((currentX >= 24 && currentX <= 94) && currentY == 23)
        currentY -= 2;
};
void DisplayControl::moveRight() {
    if (currentX == 14 && currentY == 5)
        currentX += 85;
    else if ((currentX == 19 && currentY == 7) || (currentX == 19 && currentY == 9))
        currentX += 55;
    else if ((currentX == 14 && (currentY == 7 || currentY == 9)) || ((currentX >= 74 && currentX <= 94) && (currentY == 7 || currentY == 9)))
        currentX += 5;
    // else if ((currentX >= 14 && currentX <= 94) && (currentY >= 11 && currentY <= 19))
    //     currentX += 5;
    else if ((currentX >= 14 && currentX <= 94) && (currentY == 11 || currentY == 13))
        currentX += 5;
    else if ((currentX == 14 || (currentX >= 29 && currentX <= 94)) && (currentY == 15 || currentY == 17))
        currentX += 5;
    else if (currentX == 19 && (currentY == 15 || currentY ==17))
        currentX += 10;
    else if ((currentX >= 24 && currentX <= 89) && (currentY == 21 || currentY == 23))
        currentX += 5;
};
void DisplayControl::moveDown() {
    if ((currentX == 14 || currentX == 99) && currentY == 5)
        currentY += 2;
    else if ((currentX >= 14 && currentX <= 24 && (currentY == 7 || currentY == 9)) || 
            (currentX >= 74 && currentX <= 99 && (currentY == 7 || currentY == 9)))
                currentY += 2;
    else if (currentX == 24 && currentY == 13)
        currentY = 21;
    else if ((currentX >= 14 && currentX <= 99) && (currentY >= 11 && currentY <= 15))
        currentY += 2;
    else if ((currentX >= 14 && currentX <= 24) && currentY == 17) {
        currentX = 24;
        currentY = 21;
    }
    else if ((currentX >= 29 && currentX <= 89) && currentY == 17)
        currentY = 21;
    else if ((currentX == 94 || currentX == 99) && currentY == 17) {
        currentX = 94;
        currentY = 21;
    }
    else if ((currentX >= 14 && currentX <= 94) && currentY == 21)
        currentY += 2;
};
void DisplayControl::moveLeft() {
    if (currentX == 99 && currentY == 5)
        currentX -= 85;
    else if ((currentX == 74 && currentY == 7) || (currentX == 74 && currentY == 9))
        currentX -= 55;
    else if ((currentX == 19 && (currentY == 7 || currentY == 9)) || ((currentX >= 79 && currentX <= 99) && (currentY == 7 || currentY == 9)))
        currentX -= 5;
    // else if ((currentX >= 19 && currentX <= 99) && (currentY >= 11 && currentY <= 19))
    //     currentX -= 5;
    else if ((currentX >= 19 && currentX <= 99) && (currentY == 11 || currentY == 13))
        currentX -= 5;
    else if ((currentX == 19 || (currentX >= 34 && currentX <= 99)) && (currentY == 15 || currentY == 17))
        currentX -= 5;
    else if (currentX == 29 && (currentY == 15 || currentY ==17))
        currentX -= 10;
    else if ((currentX >= 29 && currentX <= 94) && (currentY == 21 || currentY == 23))
        currentX -= 5;
};

// int findCurrentElement(int currentX, int currentY, Cluster& clusterInstance) {        
int DisplayControl::findCurrentElement(Cluster& clusterInstance) {        
    int currentGroup = ((currentX - zeroX) / 5) + 1;
    int currentPeriod = ((currentY - zeroY) / 2) + 1;
    // if (currentPeriod >= 9)
    //     currentPeriod -= 3;
    int currentAtomicNumber {};

    for (int i = 0; i < MAX; i++) {
        Element* element = clusterInstance.elements[i];
        if (element != nullptr)
            if (currentY == 21) {
                if (element->getPeriod() == 6) {
                    currentAtomicNumber = ((currentX - 24) / 5) + 57;
                    currentPeriod = 6;
                    gotoXY(1, 1);
                    // std::cout << element->getPeriod();
                };
                if (element->getAtomicNumber() == currentAtomicNumber && element->getPeriod() == currentPeriod)
                    return element->getAtomicNumber();
            }
            if (currentY == 23) {
                if (element->getPeriod() == 7) {
                    currentAtomicNumber = ((currentX - 24) / 5) + 89;
                    currentPeriod = 7;
                    gotoXY(1, 1);
                    // std::cout << element->getPeriod();
                };
                if (element->getAtomicNumber() == currentAtomicNumber && element->getPeriod() == currentPeriod)
                    return element->getAtomicNumber();
            }
            else
                if (element->getGroup() == currentGroup && element->getPeriod() == currentPeriod)
                    return element->getAtomicNumber();
    };
    return -1;
};
void DisplayControl::focus(int adjustLeft, int adjustRight) {
    gotoXY(currentX - adjustLeft, currentY, "[");
    gotoXY(currentX + adjustRight, currentY, "]");
};
void DisplayControl::clearFocus(int adjustLeft, int adjustRight) {
    gotoXY(currentX - adjustLeft, currentY, " ");
    gotoXY(currentX + adjustRight, currentY, " ");
};



//popUpWindows
// void DisplayControl::changeFilterPopUp(int& filterBy) {
void DisplayControl::changeFilterPopUp() {
    clearScreen();
    filterMenuDisplay();

    containerDisplay(45, 2, 30, 20, 15, 0, 1);
    gotoXY(51, 4, "F I L T E R   B Y :");
    gotoXY(51, 8, "Default");
    gotoXY(51, 10, "Occurrence");
    gotoXY(51, 12, "Element Group");
    gotoXY(51, 14, "Metallicity");
    gotoXY(51, 16, "Element Block Type");
    gotoXY(51, 18, "Discovery Year");
    // int currentX {51}, currentY {8};
    currentX = 51;
    currentY = 8;
    focus(3, 20);
    int input {};
    do {
        gotoXY(currentX, currentY);
        input = _getch();
        if (input == 0 || input == 224) {
            input = _getch();
                switch (input) {
                case UP:
                    clearFocus(3, 20);
                    currentY = (currentY == 8) ? (currentY + 10) : (currentY - 2); 
                    focus(3, 20);
                    break;
                case DOWN:
                    clearFocus(3, 20);
                    currentY = (currentY == 18) ? (currentY - 10) : (currentY + 2); 
                    focus(3, 20);
                    break;
            };
        }
        else {
            switch (input) {
                case ENTER:
                    if (currentY == 8)
                        currentFilterBy = 0;
                    else if (currentY == 10)
                        currentFilterBy = 1;
                    else if (currentY == 12)
                        currentFilterBy = 2;
                    else if (currentY == 14)
                        currentFilterBy = 3;
                    else if (currentY == 16)
                        currentFilterBy = 4;
                    else if (currentY == 18)
                        currentFilterBy = 5;
                    input = ESC;
                    break;
                case ESC:
                    break;
            };
        };
    } while (input != ESC);

    colorScheme(15, 0);
    clearScreen();
};

// void DisplayControl::filterColorScheme(int filterBy, Element* element) {
void DisplayControl::filterColorScheme(Element* element) {
    int index = (element->getAtomicNumber()) - 1;
    int discoveryYear = element->getDiscoveryYear();
    // switch (filterBy) {
    switch (currentFilterBy) {
        case 1:
            switch (element->getOccurrence()) {
                case 0:
                    colorScheme(15, 0);
                    break;
                case 1:
                    colorScheme(2, 0);
                    break;
                case 2:
                    colorScheme(5, 0);
                    break;
                default:
                    colorScheme(15, 0);
                    break;
            };
            break;
        case 2:
            switch (element->getElementGroup()) {
                case 0:
                    colorScheme(15, 0);
                    break;
                case 1:
                    colorScheme(4, 0);
                    break;
                case 2:
                    colorScheme(1, 0);
                    break;
                case 3:
                    colorScheme(11, 0);
                    break;
                case 4:
                    colorScheme(1, 0);
                    break;
                case 5:
                    colorScheme(3, 0);
                    break;
                case 6:
                    colorScheme(2, 0);
                    break;
                case 7:
                    colorScheme(6, 0);
                    break;
                case 8:
                    colorScheme(14, 0);
                    break;
                case 9:
                    colorScheme(13, 0);
                    break;
                case 10:
                    colorScheme(5, 0);
                    break;
                default:
                    colorScheme(15, 0);
                    break;
            };
            break;
        case 3:
            switch (element->determineMetallicity()) {
            case 0:
                colorScheme(15, 0);
                break;
            case 1:
                colorScheme(1, 0);
                break;
            case 2:
                colorScheme(14, 0);
                break;
            case 3:
                colorScheme(4, 0);
                break;
            default:
                colorScheme(15, 0);
                break;
            };
            break;
        case 4:
            switch (element->getBlockGroup()) {
                case 0:
                    colorScheme(15, 0);
                    break;
                case 1:
                    colorScheme(4, 0);
                    break;
                case 2:
                    colorScheme(14, 0);
                    break;
                case 3:
                    colorScheme(1, 0);
                    break;
                case 4:
                    colorScheme(5, 0);
                    break;
                default:
                    colorScheme(15, 0);
                    break;
            };
            if ((index >= 56 && index <= 70) || (index >= 88 && index <= 102)) 
                colorScheme(5, 0);
            break;
        case 5:
            if (discoveryYear == -1)
                colorScheme(15, 0);
            else if (discoveryYear < 1000)
                colorScheme(2, 0);
            else if (discoveryYear < 2000)
                colorScheme(3, 0);
            else
                colorScheme(1, 0);
            break;
        default:
            colorScheme(15, 0);
            break;
    };
}; //filterElementBy
void DisplayControl::getFilterProps(int filterBy, int index, Element* element, std::string& filterKey, int& filterColor) {
    int discoveryYear = element->getDiscoveryYear();
    switch (filterBy) {
        case 1:
            switch (element->getOccurrence()) {
                case 0:                            
                    filterKey = "Unknown";
                    filterColor = 15;
                    break;
                case 1:                            
                    filterKey = "Natural";
                    filterColor = 2;
                    break;
                case 2:                            
                    filterKey = "Synthetic";
                    filterColor = 5;
                    break;
                default:                            
                    filterKey = "";
                    filterColor = 15;
                    break;
            };
            break;
        case 2:
            switch (element->getElementGroup()) {
                case 0:
                    filterKey = elementGroup.at(0);
                    filterColor = 15;
                    break;
                case 1:
                    filterKey = elementGroup.at(1);
                    filterColor = 4;
                    break;
                case 2:
                    filterKey = elementGroup.at(2);
                    filterColor = 1;
                    break;
                case 3:
                    filterKey = elementGroup.at(3);
                    filterColor = 11;
                    break;
                case 4:
                    filterKey = elementGroup.at(4);
                    filterColor = 10;
                    break;
                case 5:
                    filterKey = elementGroup.at(5);
                    filterColor = 3;
                    break;
                case 6:
                    filterKey = elementGroup.at(6);
                    filterColor = 2;
                    break;
                case 7:
                    filterKey = elementGroup.at(7);
                    filterColor = 6;
                    break;
                case 8:
                    filterKey = elementGroup.at(8);
                    filterColor = 14;
                    break;
                case 9:
                    filterKey = elementGroup.at(9);
                    filterColor = 13;
                    break;
                case 10:
                    filterKey = elementGroup.at(10);
                    filterColor = 5;
                    break;
                default:
                    filterKey = "";
                    filterColor = 15;
                    break;
            };
            break;
        case 3:
            switch (element->determineMetallicity()) {
                case 0:
                    filterKey = "Unknown";
                    filterColor = 15;
                    break;
                case 1:
                    filterKey = "Metal";
                    filterColor = 1;
                    break;
                case 2:
                    filterKey = "Metalloid";
                    filterColor = 14;
                    break;
                case 3:
                    filterKey = "Non Metal";
                    filterColor = 4;
                    break;
                default:
                    filterKey = "";
                    filterColor = 15;
                    break;
                };
            break;
        case 4:
            switch (element->getBlockGroup()) {
                case 0:
                    filterKey = "Unknown";
                    filterColor = 15;
                    break;
                case 1:
                    filterKey = "Block s";
                    filterColor = 4;
                    break;
                case 2:
                    filterKey = "Block p";
                    filterColor = 14;
                    break;
                case 3:
                    filterKey = "Block d";
                    filterColor = 1;
                    break;
                case 4:
                    filterKey = "Block f";
                    filterColor = 5;
                    break;
                default:
                    filterKey = "";
                    filterColor = 15;
                    break;
            };
            if ((index >= 56 && index <= 70) || (index >= 88 && index <= 102)) {
                filterKey = "Block f";
                filterColor = 5;
            };
            break;
        case 5:
            filterKey = "Discovered in " + std::to_string(discoveryYear);
            if (discoveryYear == -1) {
                filterKey = "Unknown";
                filterColor = 15;
            }
            else if (discoveryYear < 1000)
                filterColor = 2;
            else if (discoveryYear < 2000)
                filterColor = 3;
            else { 
                filterColor = 1;
            break;
        default:
            filterKey = "";
            filterColor = 15;
            break;
        };
    };
};

void DisplayControl::propertiesPopUp(Cluster& clusterInstance, int index) {
    clearScreen();
    propertiesMenuDisplay();
    containerDisplay(28, 2, 74, 20, 15, 0, 1);

    Element* element = clusterInstance.elements[index];

    // int adjustX, currentY;
    int propertyWidth, propertiesSize;
    int containerWidth = 70;
    int containerHeight = 20;


    // propertiesPropsDisplay(clusterInstance, index, containerWidth, containerHeight, adjustX, currentY, propertyWidth);
    propertiesPropsDisplay(clusterInstance, index, containerWidth, containerHeight, propertyWidth);
    // currentX = adjustX;
    currentY = 7;

    int input {};
    do {
        focus(3, propertyWidth + 2);
        // gotoXY(adjustX, currentY);
        gotoXY(currentX, currentY);
        input = _getch();
        if (input == 0 || input == 224) {
            input = _getch();
            switch (input) {
                case UP:
                    clearFocus(3, propertyWidth + 2);
                    if (currentY == 7)
                        currentY = 19;
                    else if (currentY >= 8 && currentY <= 19)
                        currentY -= 1;
                    focus(3, propertyWidth + 2); 
                    break;
                case DOWN:
                    clearFocus(3, propertyWidth + 2);
                    if (currentY == 19)
                        currentY = 7;
                    else if (currentY >= 7 && currentY <= 18)
                        currentY += 1;
                    focus(3, propertyWidth + 2);
                    break;
                case LEFT: 
                    clearFocus(3, propertyWidth + 5);
                    index = (index == 0) ? 117 : (index - 1);
                    // propertiesPropsDisplay(clusterInstance, index, containerWidth, containerHeight, adjustX, currentY, propertyWidth);
                    propertiesPropsDisplay(clusterInstance, index, containerWidth, containerHeight, propertyWidth);
                    break;
                case RIGHT:
                    clearFocus(3, propertyWidth + 2);
                    index = (index == 117) ? 0 : (index + 1);
                    // propertiesPropsDisplay(clusterInstance, index, containerWidth, containerHeight, adjustX, currentY, propertyWidth);
                    propertiesPropsDisplay(clusterInstance, index, containerWidth, containerHeight, propertyWidth);
                    break;
            }
        } else {
            switch (input) {
                case E:
                    break;
                case ESC:
                    break;
            };
        };
    } while (input != ESC);

    colorScheme(15, 0);
    clearScreen();
};

// void DisplayControl::propertiesPropsDisplay(Cluster& clusterInstance, int index, int width, int height, int& adjustX, int& currentY, int& propertyWidth) {
void DisplayControl::propertiesPropsDisplay(Cluster& clusterInstance, int index, int width, int height, int& propertyWidth) {
    std::string clearWidth(width - 2, ' ');
    for (int y = 3; y <= height; y++)
        gotoXY(31, y, clearWidth);

    Element* element = clusterInstance.elements[index];

    std::string formattedName;
    for (char c : element->getName()) {
        if (!formattedName.empty())
            formattedName += ' ';
        formattedName += std::toupper(c);
    }
    std::string windowTitle = formattedName + "   P R O P E R T I E S :";

    gotoXY((65 - (windowTitle.length() / 2)), 4, windowTitle);

    std::vector<std::pair<std::string, std::string>> properties {
        {"Name", element->getName()},
        {"Symbol", element->getSymbol()},
        {"Group Number", std::to_string(element->getGroup())},
        {"Period Number", std::to_string(element->getPeriod())},
        {"Atomic Number", std::to_string(element->getAtomicNumber())},
        {"Atomic Mass", std::to_string(element->getAtomicMass())},
        {"Metallicity", element->determineMetallicity() == 0 ? "Unknown" :
                        element->determineMetallicity() == 1 ? "Metal" :
                        element->determineMetallicity() == 2 ? "Metalloid" : "Non Metal"},
        {"Group Classification", elementGroup.at(element->getElementGroup())},
        {"Occurrence", element->getOccurrence() == 0 ? "Unknown" :
                    element->getOccurrence() == 1 ? "Natural" : "Synthetic"},
        {"Stability", element->determineStability() ? "Stable" : "Unstable"},
        {"Electron Shell Configuration", element->determineShellConfiguration()},
        {"Block Group", element->getBlockGroup() == 0 ? "Unknown" :
                        element->getBlockGroup() == 1 ? "s Block" :
                        element->getBlockGroup() == 2 ? "p Block" :
                        element->getBlockGroup() == 3 ? "d Block" : "f Block"},
        {"Year of Discovery", element->getDiscoveryYear() <= 0 ? "Unknown" : std::to_string(element->getDiscoveryYear())}
    };

    size_t maxNameLength = 0;
    size_t maxValueLength = 0;
    for (auto& property : properties) {
        property.first += " :"; 
        if (property.first.length() > maxNameLength)
            maxNameLength = property.first.length();
        if (property.second.length() > maxValueLength)
            maxValueLength = property.second.length();
    }
    maxNameLength += 6;
    // adjustX = 65 - ((maxNameLength + maxValueLength) / 2);
    currentX = 65 - ((maxNameLength + maxValueLength) / 2);
    propertyWidth = maxNameLength + maxValueLength;

    std::string clearLine(propertyWidth + 2, ' ');
    for (int y = 7; y < 7 + properties.size(); y++) {
        // gotoXY(adjustX, y);
        gotoXY(currentX, y);
        std::cout << clearLine;
    }

    currentY = 7;
    for (const auto& property : properties) {
        // gotoXY(adjustX, currentY++);
        gotoXY(currentX, currentY++);
        std::cout << std::left << std::setw(maxNameLength) << property.first;
        std::cout << property.second;
    }
    currentY = 7;
}; //updatePropertiesWindow

//menuManagement
void DisplayControl::menuDisplay(const std::vector<std::pair<std::string, std::string>>& menuOptions) {
    int maxKeyLength {};
    int maxExplanationLength {};

    for (const auto& option : menuOptions) {
        if (option.first.length() > maxKeyLength) {
            maxKeyLength = option.first.length();
        }
        if (option.second.length() > maxExplanationLength) {
            maxExplanationLength = option.second.length();
        }
    }
    int columnWidth = maxKeyLength + maxExplanationLength + 6;

    gotoXY(3, screenHeight-2);
    for (int i = 0; i < menuOptions.size(); ++i) {
        if (i == menuOptions.size() / 2) {
            gotoXY(3, screenHeight-1);
        }
        std::cout << std::left << std::setw(columnWidth) << menuOptions[i].first + " " + menuOptions[i].second;
    }
    std::cout << std::endl;
};
void DisplayControl::menuDisplay(const std::vector<std::pair<std::string, std::string>>& menuOptions, int baseX) {
    int maxKeyLength {};
    int maxExplanationLength {};

    for (const auto& option : menuOptions) {
        if (option.first.length() > maxKeyLength) {
            maxKeyLength = option.first.length();
        }
        if (option.second.length() > maxExplanationLength) {
            maxExplanationLength = option.second.length();
        }
    }
    int columnWidth = maxKeyLength + maxExplanationLength + 6;

    gotoXY(baseX, screenHeight-2);
    for (int i = 0; i < menuOptions.size(); ++i) {
        if (i == menuOptions.size() / 2) {
            gotoXY(baseX, screenHeight-1);
        }
        std::cout << std::left << std::setw(columnWidth) << menuOptions[i].first + " " + menuOptions[i].second;
    }
    std::cout << std::endl;
};

void DisplayControl::mainMenuDisplay() { menuDisplay(mainMenuOptions); };
void DisplayControl::filterMenuDisplay() { menuDisplay(filterMenuOptions, 40); };
void DisplayControl::propertiesMenuDisplay() { menuDisplay(propertiesMenuOptions, 20); };
// void DisplayControl::dataMenuDisplay() { menuDisplay(dataMenuOptions); };
// void DisplayControl::dataManagementMenuDisplay() { menuDisplay(dataMenuOptions, 20); };