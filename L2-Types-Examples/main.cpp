
#include <QCoreApplication>
#include <iostream>
#include <cmath>
#include "quadratic.cpp"
#include "datingrange.cpp"
#include "axess1.cpp"
// #include "ioexamples.cpp"

void runQuadratic();
void runDatingRange();
void runAxess();
void simpleInputTest();
void nameAndAge();
void readThroughFile();
void testCIN();
int getInteger();


using SearchResult = tuple<bool, Time, Time>;

int main() {

    //runAxess();
//    runQuadratic();
//    runDatingRange();
 //   simpleInputTest();
    //nameAndAge();
    // readThroughFile();
    //testCIN();
    cout << getInteger() << endl;
}

void runAxess() {
    auto [success, database] = createCourseDatabase("course_data.txt");

    if (!success) {
        cout << "Invalid file input!" << endl;
        return;
    }
    for (const auto& course : database) {
        cout << course << endl;
        cout << "----" << endl;
    }

    string searchCourse = "CS106B";
    auto [found, start, end] = findCourseTime(database, searchCourse);

    if (found) {
        cout << searchCourse << " happens from " << start << " to " << end << "." << endl;
    } else {
        cout << searchCourse << " was not found in database." << endl;
    }
}

int getInteger() {
    while(true) {
        /* First we get a line of input from the user. */
        string line;
        std::getline(cin, line);
        std::istringstream converter(line);
        int result;
        if(converter >> result) {
            char remaining;
            if(converter >> remaining) {
                cout << "Unexpected character. Try again." << endl;
            } else {
                return result;
            }
        } else {
            cout << "Not a valid integer. Try again." << endl;
        }
    }
}


void runQuadratic() {
    constexpr int a = 3;
    constexpr int b = 5;
    constexpr int c = 10;

    auto [foundRoot, root1, root2] = quadraticChecked(a, b, c);

    if (foundRoot) {
        std::cout << "The roots found are " << root1 << " and " << root2 << "." << std::endl;
    } else {
        std::cout << "No roots found." << std::endl;
    }
}

void runDatingRange() {
    int young;
    int old;
    datingRange(48, young, old);
    std::cout << "A 48-year-old could date someone from "
         << young << " to " << old << " years old." << std::endl;

    std::tie(young, old) = datingRangePair(48);
    std::cout << "A 48-year-old could date someone from "
         << young << " to " << old << " years old." << std::endl;

    //auto[young2, old2] = datingRangeStruct(48);
}

void testCIN() {
    string name;
    int age;
    string satisfied;

    cout << "Enter your name: ";
    cin >> name;

    cout << "Enter your age: ";

    if (cin >> age) {
        cout << name << ", age " << age << endl;
    } else {
        cout << "Error with reading input!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Were you satisfied with this experience? (y/n): ";
    cin >> satisfied;
    cout << "You said: " << satisfied << endl;

}


