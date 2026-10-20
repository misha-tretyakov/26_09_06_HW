#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void Task2() {
    int choice = 0;

    cout << "1. ukrainian to english" << endl;
    cout << "2. english to ukrainian" << endl;
    cout << "choose direction: ";
    cin >> choice;

    if (choice != 1 && choice != 2) {
        cout << "wrong option" << endl;
        return;
    }

    ifstream inFile("Text2.txt");

    if (!inFile.is_open()) {
        cout << "failed to open input file" << endl;
        return;
    }

    ofstream outFile("Result2.txt");

    if (!outFile.is_open()) {
        cout << "failed to open result file" << endl;
        return;
    }

    string ukr[33] = {
        "щ", "ж", "х", "ц", "ч", "ш", "є", "ї", "ю", "я",
        "а", "б", "в", "г", "ґ", "д", "е", "з", "и", "і",
        "й", "к", "л", "м", "н", "о", "п", "р", "с", "т",
        "у", "ф", "ь"
    };

    string ukrUpper[33] = {
        "Щ", "Ж", "Х", "Ц", "Ч", "Ш", "Є", "Ї", "Ю", "Я",
        "А", "Б", "В", "Г", "Ґ", "Д", "Е", "З", "И", "І",
        "Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т",
        "У", "Ф", "Ь"
    };

    string eng[33] = {
        "shch", "zh", "kh", "ts", "ch", "sh", "ye", "yi", "yu", "ya",
        "a", "b", "v", "h", "g", "d", "e", "z", "y", "i",
        "j", "k", "l", "m", "n", "o", "p", "r", "s", "t",
        "u", "f", "'"
    };

    string line;

    while (getline(inFile, line)) {
        int i = 0;

        while (i < (int)line.length()) {
            bool found = false;

            if (choice == 1 && i + 1 < (int)line.length()) {
                for (int j = 0; j < 33; j++) {
                    bool small = line[i] == ukr[j][0] &&
                                 line[i + 1] == ukr[j][1];

                    bool big = line[i] == ukrUpper[j][0] &&
                               line[i + 1] == ukrUpper[j][1];

                    if (small || big) {
                        string temp = eng[j];

                        if (big && temp[0] >= 'a' && temp[0] <= 'z') {
                            temp[0] = temp[0] - 'a' + 'A';
                        }

                        outFile << temp;
                        i += 2;
                        found = true;
                        break;
                    }
                }
            }
            else if (choice == 2) {
                for (int j = 0; j < 33; j++) {
                    int size = (int)eng[j].length();

                    if (i + size <= (int)line.length()) {
                        bool same = true;

                        for (int k = 0; k < size; k++) {
                            char symbol = line[i + k];

                            if (symbol >= 'A' && symbol <= 'Z') {
                                symbol = symbol - 'A' + 'a';
                            }

                            if (symbol != eng[j][k]) {
                                same = false;
                                break;
                            }
                        }

                        if (same) {
                            if (line[i] >= 'A' && line[i] <= 'Z') {
                                outFile << ukrUpper[j];
                            }
                            else {
                                outFile << ukr[j];
                            }

                            i += size;
                            found = true;
                            break;
                        }
                    }
                }
            }

            if (!found) {
                outFile << line[i];
                i++;
            }
        }

        outFile << endl;
    }

    inFile.close();
    outFile.close();

    cout << "task 2 done" << endl;
}