#include "streams.h"

using namespace std;

void spin(size_t time);


void printBitInfo(istream& s) {
    cout << "State bits: ";

    cout << (s.good() ? "G" : "-");
    cout << (s.fail() ? "F" : "-");
    cout << (s.eof() ? "E" : "-");
    cout << (s.bad() ? "B" : "-");

    cout << endl;
    cout << "-----------" << endl;
}

void readThroughFile() {
    ifstream file("course_data.txt");
    string token;
    while (getline(file, token)) {
        cout << token << endl;
        printBitInfo(file);
    }
    printBitInfo(file);
}

void simpleInputTest() {
    string name, response;
    int age;

    cout << "Enter your name: ";
    cin >> name;

    // printBitInfo(cin);

    cout << "Enter your age: ";
    cin >> age;

    // printBitInfo(cin);

    cout << name << ", age "
         << age << endl;

    // printBitInfo(cin);

    cout << "Try again? (y/n) ";
    cin >> response;

    // printBitInfo(cin);
}

void testOutputStream(ostream& os) {
    os << "START TEST!" << endl;
    spin(1000);

    os << "CS";
    spin(1000);

    os << 106;
    spin(1000);

    os << flush;
    spin(1000);

    os << 'L';
    spin(1000);

    os << endl;
    spin(1000);

    os << "DONE!" << endl;
    spin(1000);
}



void spin(size_t time) {
    for (size_t i = 0; i < 1000000*time; i++) {
        double k = 10000000/777777.7;
        k++;
    }
}

void stringStreamTest() {
    ostringstream oss("Ito En Green Tea "); // default open mode
    cout << oss.str() << endl; // "Ito En Tea"
    //oss.tellp();
    auto pos = oss.tellp();
    oss.seekp(pos + streamoff(3));
    oss << 16.9 << " Ounce ";
    cout << oss.str() << endl; // "16.9 Ounce 1"

    oss << "(Pack of " << 12 << ")";
    cout << oss.str() << endl; // "Ito En Tea 16.9 Ounce (Pack of 12)"

    istringstream iss(oss.str());


    double ounces;
    iss >> ounces;

    cout << "After making losses for 2 years, "
         << "we have decided to cut production costs "
         << "by decreasing the size of each bottle to "
         << ounces/2 << " ounces." << endl;
}

void stringPositionTest() {
    string token;
    ostringstream oss("Ito En Green Tea"); // position is at 0
    oss << 16.9;
    cout << oss.str() << endl; // "16.9En Green Tea", position at 4


    auto pos = oss.tellp() + streamoff(3); // fpos = position, off = offset
    oss.seekp(pos); // moves the position down 3 characters, position at 7
    oss << "Black";
    cout << oss.str() << endl; // "16.9En Black Tea", position at 12


    // moves position down 1 from current, position at 13
    oss.seekp(streamoff(1), stringstream::cur);
    oss << "Milk";
    cout << oss.str() << endl; // "16.9En Black Milk", position at 17
}

