/*
Вариант 5. 
Определить комбинированный (структурный) тип для представления информации 
по горным вершинам, состоящей из названия вершины, ее высоты, стране 
местонахождения, типе горы (вулканическая, складчатая, платообразная и др.). 
Ввести информацию по 20 вершинам. Вывести среднее значение высот всех 20 
вершин. Затем вывести информацию, отсортированную по возрастанию высоты 
вершины (рационально переставлять все поля структуры разом). Вывести сведения 
по странам местонахождения 3-х восьмитысячников. Реализовать функцию 
изменения данных горной вершины по ее высоте, а не по названию. В отдельный 
массив поместить все горные вершины в одной стране (страну вводить с 
клавиатуры). Реализовать вывод отфильтрованных данных в виде оберточной 
функции.
*/

#include <iostream>
#include <cstring>
using namespace std;

enum MountainType { VOLCANIC, FOLDED, PLATEAU, FAULT_BLOCK };

const int SIZE = 20;

struct Location {
    char country[30];
    char region[25];
};

struct Mountain {
    char name[25];
    double height;
    Location loc;
    MountainType type;
};

Mountain mountains[SIZE];

const char* getType(MountainType t) {
    if (t == VOLCANIC)    return "Volcanic";
    if (t == FOLDED)      return "Folded";
    if (t == PLATEAU)     return "Plateau";
    if (t == FAULT_BLOCK) return "FaultBlock";
    return "?";
}

void init_list() {
    mountains[0] = { "Everest",        8848.86, {"Nepal/China",       "Himalai"},    FOLDED };
    mountains[1] = { "K2",             8611.00, {"Pakistan/China",    "Karakorum"},  FOLDED };
    mountains[2] = { "Kanchendzanga",  8586.00, {"Nepal/India",       "Himalai"},    FOLDED };
    mountains[3] = { "Lhotse",         8516.00, {"Nepal/China",       "Himalai"},    FOLDED };
    mountains[4] = { "Makalu",         8485.00, {"Nepal/China",       "Himalai"},    FOLDED };
    mountains[5] = { "Cho Oyu",        8188.00, {"Nepal/China",       "Himalai"},    FOLDED };
    mountains[6] = { "Dhaulagiri",     8167.00, {"Nepal",             "Himalai"},    FOLDED };
    mountains[7] = { "Manaslu",        8163.00, {"Nepal",             "Himalai"},    FOLDED };
    mountains[8] = { "Nanga Parbat",   8126.00, {"Pakistan",          "Himalai"},    FOLDED };
    mountains[9] = { "Annapurna I",    8091.00, {"Nepal",             "Himalai"},    FOLDED };
    mountains[10] = { "Mont Blanc",     4807.00, {"France/Italy",      "Alps"},       FOLDED };
    mountains[11] = { "Elbrus",         5642.00, {"Russia",            "Kavkaz"},     VOLCANIC };
    mountains[12] = { "Kilimanjaro",    5895.00, {"Tanzania",          "E.Africa"},   VOLCANIC };
    mountains[13] = { "Kazbek",         5047.00, {"Russia/Georgia",    "Kavkaz"},     VOLCANIC };
    mountains[14] = { "Matterhorn",     4478.00, {"Switzerland/Italy", "Alps"},       FOLDED };
    mountains[15] = { "Aconcagua",      6961.00, {"Argentina",         "Andes"},      FOLDED };
    mountains[16] = { "Denali",         6190.00, {"USA",               "Alaska"},     FOLDED };
    mountains[17] = { "Popocatepetl",   5426.00, {"Mexico",            "Pop.Sierra"}, VOLCANIC };
    mountains[18] = { "Table Mountain", 1086.00, {"South Africa",      "Cape Mts"},   PLATEAU };
    mountains[19] = { "Vesuvius",       1281.00, {"Italy",             "Apennines"},  VOLCANIC };
}

void display_one(int i) {
    cout << mountains[i].name << "\t"
        << mountains[i].height << " m\t"
        << mountains[i].loc.country << "\t"
        << mountains[i].loc.region << "\t"
        << getType(mountains[i].type) << endl;
}

void display() {
    cout << "\nName\t\t\tHeight\t\tCountry\t\t\tRegion\t\t\tType" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    for (int i = 0; i < SIZE; i++)
        display_one(i);
}

double avg_height() {
    double sum = 0;
    for (int i = 0; i < SIZE; i++)
        sum += mountains[i].height;
    return sum / SIZE;
}

void bubble_sort() {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - i - 1; j++) {
            if (mountains[j].height > mountains[j + 1].height) {
                Mountain tmp = mountains[j];
                mountains[j] = mountains[j + 1];
                mountains[j + 1] = tmp;
            }
        }
    }
}

void top3_countries() {
    Mountain temp[SIZE];
    for (int i = 0; i < SIZE; i++) temp[i] = mountains[i];

    for (int i = 0; i < SIZE - 1; i++)
        for (int j = 0; j < SIZE - i - 1; j++)
            if (temp[j].height < temp[j + 1].height) {
                Mountain t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }

    cout << "\n--- Top-3 highest peaks ---" << endl;
    for (int i = 0; i < 3; i++)
        cout << i + 1 << ". " << temp[i].name
        << "  " << temp[i].height << " m"
        << "  " << temp[i].loc.country << endl;
}

void update_by_height() {
    double h;
    cout << "\nEnter height to find: ";
    cin >> h;

    for (int i = 0; i < SIZE; i++) {
        if (mountains[i].height == h) {
            cout << "Found: " << mountains[i].name << endl;
            cout << "Enter new name: ";
            cin >> mountains[i].name;
            cout << "Enter new height: ";
            cin >> mountains[i].height;
            cout << "Enter new country: ";
            cin >> mountains[i].loc.country;
            cout << "Updated." << endl;
            return;
        }
    }
    cout << "Not found." << endl;
}

void filter_by_country() {
    char country[30];
    cout << "\nEnter country: ";
    cin >> country;

    Mountain result[SIZE];
    int count = 0;

    for (int i = 0; i < SIZE; i++) {
        if (!strcmp(mountains[i].loc.country, country))
            result[count++] = mountains[i];
    }

    if (count == 0) {
        cout << "No peaks found in " << country << endl;
        return;
    }

    cout << "\n--- Peaks in " << country << " (" << count << " found) ---" << endl;
    for (int i = 0; i < count; i++)
        cout << result[i].name << "  "
        << result[i].height << " m  "
        << result[i].loc.region << endl;
}

char menu() {
    char ch;
    cout << "\n(D)Display all" << endl;
    cout << "(A)Average height" << endl;
    cout << "(S)Sort by height" << endl;
    cout << "(T)Top-3 countries" << endl;
    cout << "(U)Update by height" << endl;
    cout << "(F)Filter by country" << endl;
    cout << "(Q)Quit" << endl;
    cout << "Choice: ";
    cin >> ch;
    return ch;
}

int main() {

            init_list();

            char choice;
            for (;;) {
                choice = menu();
                switch (choice) {
                case 'd': case 'D':
                    display();
                    break;
                case 'a': case 'A':
                    cout << "\nAverage height: " << avg_height() << " m" << endl;
                    break;
                case 's': case 'S':
                    bubble_sort();
                    cout << "Sorted! Use (D) to display." << endl;
                    break;
                case 't': case 'T':
                    top3_countries();
                    break;
                case 'u': case 'U':
                    update_by_height();
                    break;
                case 'f': case 'F':
                    filter_by_country();
                    break;
                case 'q': case 'Q':
                    return 0;
                }
            }
        }
    
