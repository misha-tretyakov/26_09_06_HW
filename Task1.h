#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void Task1() {
    ifstream inFile("Text1.txt");
    ifstream wordsFile("BadWords.txt");

    if (!inFile.is_open() || !wordsFile.is_open()) {
        cout << "failed to open input files" << endl;
        return;
    }

    vector<string> words;
    string word;

    while (wordsFile >> word) {
        words.push_back(word);
    }

    ofstream outFile("Result1.txt");

    if (!outFile.is_open()) {
        cout << "failed to open result file" << endl;
        return;
    }

    string line;
    string separators = " \t\r\n.,!?;:()[]{}\"-";

    while (getline(inFile, line)) {
        line += '\n';
        word = "";

        for (int i = 0; i < (int)line.length(); i++) {
            bool separator = false;

            for (int j = 0; j < (int)separators.length(); j++) {
                if (line[i] == separators[j]) {
                    separator = true;
                    break;
                }
            }

            if (!separator) {
                word += line[i];
            }
            else {
                bool bad = false;

                for (int j = 0; j < (int)words.size(); j++) {
                    if (word == words[j]) {
                        bad = true;
                        break;
                    }
                }

                if (!bad) {
                    outFile << word;
                }

                outFile << line[i];
                word = "";
            }
        }
    }

    inFile.close();
    wordsFile.close();
    outFile.close();

    cout << "task 1 done" << endl;
}