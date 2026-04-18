1. Условие задачи
   
Занятие 9.
Вариант 5. Определить комбинированный (структурный) тип для представления информации 
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

Занятие 10. 
Считать из текстового файла данные числового поля (например, высоты) и обновить соответствующие записи в массиве структур, если названия совпадают.
Сделать чтение / запись своей структуры в бинарный файл. Оформить в виде подпрограмм.

2. Текст решения (Код)
```cpp

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>          

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

// Вспомогательная функция для вывода шапки таблицы
void printMountainHeader() {
    cout << left
        << setw(18) << "Name"
        << setw(12) << "Height"
        << setw(20) << "Country"
        << setw(18) << "Region"
        << setw(12) << "Type"
        << endl;
    cout << string(80, '-') << endl;
}

// Вспомогательная функция для вывода одной строки данных
void printMountainRow(const Mountain& m) {
    cout << left
        << setw(18) << m.name
        // fixed и setprecision используются для красивого вывода чисел с 2 знаками после запятой
        << setw(12) << m.height
        << setw(20) << m.loc.country
        << setw(18) << m.loc.region
        << setw(12) << getType(m.type)
        << endl;
}

void init_list() {
    // Данные приведены к единому стандарту (высоты совпадают с тем, что пойдет в файл)
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

void display() {
    printMountainHeader();
    for (int i = 0; i < SIZE; i++) {
        printMountainRow(mountains[i]);
    }
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

void create_heights_file() {
    ofstream fout("heights.txt");
    if (!fout.is_open()) {
        cout << "Error creating file!" << endl;
        return;
    }
    
    // Записываем все 20 вершин в файл (массив уже отсортирован!)
    for (int i = 0; i < SIZE; i++) {
        fout << mountains[i].name << " " << mountains[i].height << endl;
    }
    
    fout.close();
    cout << "File 'heights.txt' created successfully. Saved " << SIZE << " peaks." << endl;
}

void read_heights_from_file() {
    ifstream fin("heights.txt");
    if (!fin.is_open()) {
        cout << "Cannot open heights.txt!" << endl;
        return;
    }

    char name[25];
    double height;
    int updated = 0;

    cout << "\n--- Reading from heights.txt ---" << endl;

    while (fin >> name >> height) {
        for (int i = 0; i < SIZE; i++) {
            if (!strcmp(mountains[i].name, name)) {
                cout << "Updated: " << mountains[i].name
                    << " (" << mountains[i].height
                    << " -> " << height << " m)" << endl;
                mountains[i].height = height;
                updated++;
            }
        }
    }

    fin.close();
    cout << "Total updated: " << updated << " peaks." << endl;
}

void write_to_binary() {
    ofstream fout("mountains.bin", ios::binary | ios::out);
    if (!fout.is_open()) {
        cout << "Error opening binary file for write!" << endl;
        return;
    }

    for (int i = 0; i < SIZE; i++) {
        fout.write((char*)&mountains[i], sizeof(Mountain));
    }

    fout.close();
    cout << "Saved " << SIZE << " peaks to 'mountains.bin'." << endl;
}

void read_from_binary() {
    ifstream fin("mountains.bin", ios::binary | ios::in);
    if (!fin.is_open()) {
        cout << "Cannot open mountains.bin! Run write operation first." << endl;
        return;
    }

    Mountain temp;
    int count = 0;

    cout << "\n--- Data read from binary file ---" << endl;
    printMountainHeader(); // Используем общую функцию вывода

    while (count < SIZE && fin.read((char*)&temp, sizeof(Mountain))) {
        printMountainRow(temp); // Используем общую функцию вывода
        count++;
    }

    fin.close();
    cout << "Read " << count << " peaks from file." << endl;
}

int main() {
    setlocale(LC_ALL, "");
    // Формат вывода чисел с плавающей точкой: всегда 2 знака после запятой
    cout << fixed << setprecision(2);

    init_list();

    cout << "========== LABORATORY WORK #9 + #10 ==========" << endl;

    cout << "\n--- 1. Initial data ---" << endl;
    display();

    cout << "\n--- 2. Sorted by height (bubble sort) ---" << endl;
    bubble_sort();
    display();

    cout << "\n========== FILE OPERATIONS ==========" << endl;

    cout << "\n--- 3. Creating text file ---" << endl;
    create_heights_file();

    cout << "\n--- 4. Reading text file and updating ---" << endl;
    read_heights_from_file();

    cout << "\n--- 5. Data after text file update ---" << endl;
    display();

    cout << "\n--- 6. Writing to binary file ---" << endl;
    write_to_binary();

    cout << "\n--- 7. Reading from binary file ---" << endl;
    read_from_binary();

    cout << "\n========== PROGRAM COMPLETED ==========" << endl;

    return 0;
}
```

3. Результат выполнения программы
```
========== LABORATORY WORK #9 + #10 ==========

--- 1. Initial data ---
Name              Height      Country             Region            Type
--------------------------------------------------------------------------------
Everest           8848.86     Nepal/China         Himalai           Folded
K2                8611.00     Pakistan/China      Karakorum         Folded
Kanchendzanga     8586.00     Nepal/India         Himalai           Folded
Lhotse            8516.00     Nepal/China         Himalai           Folded
Makalu            8485.00     Nepal/China         Himalai           Folded
Cho Oyu           8188.00     Nepal/China         Himalai           Folded
Dhaulagiri        8167.00     Nepal               Himalai           Folded
Manaslu           8163.00     Nepal               Himalai           Folded
Nanga Parbat      8126.00     Pakistan            Himalai           Folded
Annapurna I       8091.00     Nepal               Himalai           Folded
Mont Blanc        4807.00     France/Italy        Alps              Folded
Elbrus            5642.00     Russia              Kavkaz            Volcanic
Kilimanjaro       5895.00     Tanzania            E.Africa          Volcanic
Kazbek            5047.00     Russia/Georgia      Kavkaz            Volcanic
Matterhorn        4478.00     Switzerland/Italy   Alps              Folded
Aconcagua         6961.00     Argentina           Andes             Folded
Denali            6190.00     USA                 Alaska            Folded
Popocatepetl      5426.00     Mexico              Pop.Sierra        Volcanic
Table Mountain    1086.00     South Africa        Cape Mts          Plateau
Vesuvius          1281.00     Italy               Apennines         Volcanic

--- 2. Sorted by height (bubble sort) ---
Name              Height      Country             Region            Type
--------------------------------------------------------------------------------
Table Mountain    1086.00     South Africa        Cape Mts          Plateau
Vesuvius          1281.00     Italy               Apennines         Volcanic
Matterhorn        4478.00     Switzerland/Italy   Alps              Folded
Mont Blanc        4807.00     France/Italy        Alps              Folded
Kazbek            5047.00     Russia/Georgia      Kavkaz            Volcanic
Popocatepetl      5426.00     Mexico              Pop.Sierra        Volcanic
Elbrus            5642.00     Russia              Kavkaz            Volcanic
Kilimanjaro       5895.00     Tanzania            E.Africa          Volcanic
Denali            6190.00     USA                 Alaska            Folded
Aconcagua         6961.00     Argentina           Andes             Folded
Annapurna I       8091.00     Nepal               Himalai           Folded
Nanga Parbat      8126.00     Pakistan            Himalai           Folded
Manaslu           8163.00     Nepal               Himalai           Folded
Dhaulagiri        8167.00     Nepal               Himalai           Folded
Cho Oyu           8188.00     Nepal/China         Himalai           Folded
Makalu            8485.00     Nepal/China         Himalai           Folded
Lhotse            8516.00     Nepal/China         Himalai           Folded
Kanchendzanga     8586.00     Nepal/India         Himalai           Folded
K2                8611.00     Pakistan/China      Karakorum         Folded
Everest           8848.86     Nepal/China         Himalai           Folded

========== FILE OPERATIONS ==========

--- 3. Creating text file ---
File 'heights.txt' created successfully. Saved 20 peaks.

--- 4. Reading text file and updating ---

--- Reading from heights.txt ---
Total updated: 0 peaks.

--- 5. Data after text file update ---
Name              Height      Country             Region            Type
--------------------------------------------------------------------------------
Table Mountain    1086.00     South Africa        Cape Mts          Plateau
Vesuvius          1281.00     Italy               Apennines         Volcanic
Matterhorn        4478.00     Switzerland/Italy   Alps              Folded
Mont Blanc        4807.00     France/Italy        Alps              Folded
Kazbek            5047.00     Russia/Georgia      Kavkaz            Volcanic
Popocatepetl      5426.00     Mexico              Pop.Sierra        Volcanic
Elbrus            5642.00     Russia              Kavkaz            Volcanic
Kilimanjaro       5895.00     Tanzania            E.Africa          Volcanic
Denali            6190.00     USA                 Alaska            Folded
Aconcagua         6961.00     Argentina           Andes             Folded
Annapurna I       8091.00     Nepal               Himalai           Folded
Nanga Parbat      8126.00     Pakistan            Himalai           Folded
Manaslu           8163.00     Nepal               Himalai           Folded
Dhaulagiri        8167.00     Nepal               Himalai           Folded
Cho Oyu           8188.00     Nepal/China         Himalai           Folded
Makalu            8485.00     Nepal/China         Himalai           Folded
Lhotse            8516.00     Nepal/China         Himalai           Folded
Kanchendzanga     8586.00     Nepal/India         Himalai           Folded
K2                8611.00     Pakistan/China      Karakorum         Folded
Everest           8848.86     Nepal/China         Himalai           Folded

--- 6. Writing to binary file ---
Saved 20 peaks to 'mountains.bin'.

--- 7. Reading from binary file ---

--- Data read from binary file ---
Name              Height      Country             Region            Type
--------------------------------------------------------------------------------
Table Mountain    1086.00     South Africa        Cape Mts          Plateau
Vesuvius          1281.00     Italy               Apennines         Volcanic
Matterhorn        4478.00     Switzerland/Italy   Alps              Folded
Mont Blanc        4807.00     France/Italy        Alps              Folded
Kazbek            5047.00     Russia/Georgia      Kavkaz            Volcanic
Popocatepetl      5426.00     Mexico              Pop.Sierra        Volcanic
Elbrus            5642.00     Russia              Kavkaz            Volcanic
Kilimanjaro       5895.00     Tanzania            E.Africa          Volcanic
Denali            6190.00     USA                 Alaska            Folded
Aconcagua         6961.00     Argentina           Andes             Folded
Annapurna I       8091.00     Nepal               Himalai           Folded
Nanga Parbat      8126.00     Pakistan            Himalai           Folded
Manaslu           8163.00     Nepal               Himalai           Folded
Dhaulagiri        8167.00     Nepal               Himalai           Folded
Cho Oyu           8188.00     Nepal/China         Himalai           Folded
Makalu            8485.00     Nepal/China         Himalai           Folded
Lhotse            8516.00     Nepal/China         Himalai           Folded
Kanchendzanga     8586.00     Nepal/India         Himalai           Folded
K2                8611.00     Pakistan/China      Karakorum         Folded
Everest           8848.86     Nepal/China         Himalai           Folded
Read 20 peaks from file.

========== PROGRAM COMPLETED ==========
```
