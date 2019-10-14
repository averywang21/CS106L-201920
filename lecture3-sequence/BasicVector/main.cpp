#include <vector>
#include <string>
#include <iostream>
using std::vector;  using std::string;
using std::cout;    using std::endl;

void printVec(const vector<string>& v) {
    cout << "{";
    for(auto elem : v) {
        cout << elem << " ";
    }
    cout << "}" << endl;
}

int main() {
    vector<string> names;
    names.push_back("Anna");
    names.push_back("Avery");
    printVec(names);

    names.at(0) = "Karel";
    printVec(names);

//    names.at(3) = "Ohno";   // Throws an exception
//    printVec(names);

//    names[3] = "Ohno?";     // Fails silently
//    printVec(names);

    names.clear();
    printVec(names);
    return 0;
}
