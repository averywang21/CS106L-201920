#include <iostream>
#include <fstream>

using namespace std;

void simpleInputTest() {
    string token;
    cin >> token;
    cout << "The token was: " << token << endl;

    int number;
    cin >> number;
    number += 20;
    cout << "Twenty more than the number is: " << number << endl;

    cin >> token;
    cout << "Token was overwritten by: " << token << endl;
}

void printBitInfo(istream& s) {
    cout << "State bits: ";
    if (s.good()) {
        cout << "G";
    } else {
        cout << "-";
    }

    if (s.fail()) {
        cout << "F";
    } else {
        cout << "-";
    }

    if (s.eof()) {
        cout << "E";
    } else {
        cout << "-";
    }

    if (s.bad()) {
        cout << "B";
    } else {
        cout << "-";
    }

}

void readThroughFile() {
    ifstream file("course_data.txt");
    string token;
    while (getline(file, token)) {
        printBitInfo(file);
    }
    printBitInfo(file);
}

void nameAndAge() {
    printBitInfo(cin);
    cout << "Enter your name: ";

    string name;
    cin >> name;

    printBitInfo(cin);

    cout << "Enter your age: ";

    int age;
    cin >> age;

    printBitInfo(cin);
    cout << name << ", age " << age << endl;

    cin.clear();
    printBitInfo(cin);
    string other;
    cin >> other;
    cout << other << endl;
    printBitInfo(cin);
}
