#include <utility>
#include <iostream>
#include <QCoreApplication>
#include <vector>
#include "axess2.h"

using namespace std;

/*template <typename T, typename BinaryPredicate>
constexpr pair<T, T> my_minmax(T num1, T num2, BinaryPredicate comp) {
    if (comp(num1, num2)) {
        return make_pair(num1, num2);
    } else {
        return make_pair(num2, num1);
    }
}*/

template <typename T>
constexpr pair<T, T> my_minmax(const T& num1) {
    return make_pair(num1, num1);
}

template <typename T, typename ...Ts>
constexpr pair<T, T> my_minmax(const T& num1, const Ts&... args) {
    auto[min, max] = my_minmax(args...);
    if (num1 < min) min = num1;
    if (num1 > max) max = num1;
    return make_pair(min, max);
}

template <typename T>
T getValueType(const string& prompt, const string& reprompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) {
            throw std::domain_error("getLine: End of input reached while waiting for line.");
        }
        istringstream iss(line);
        T value;
        char extra;
        if (iss >> value && !(iss >> extra)) return value;
        cerr << reprompt << endl;
    }
}


int main() {

    auto val1 = getValueType<Time>("Enter an integer: ", "Invalid integer");
    auto val2 = getValueType<Time>("Enter an integer: ", "Invalid integer");
    auto[min, max] = my_minmax(val1, val2);
    cout << "The min is: " << min << endl;
    cout << "The max is: " << max << endl;
    //runAxess();
    auto func = [](auto val) {int hello;};
    return 0;
}


/*void runAxess() {
    auto [success, database] = createCourseDatabase("course_data2.txt");

    if (!success) {
        cout << "Invalid file input!" << endl;
        return;
    }
    Course cs106b = database[2]; // this is why you should use a map here!
    Course math51 = database[5];

    auto comp = [](const Course& c1, const Course& c2) -> bool {
        return c1.code < c2.code;
    };

    auto [min, max] = my_minmax(cs106b, math51, comp);
    cout << "The better course is: " << max.code << endl;
}*/


