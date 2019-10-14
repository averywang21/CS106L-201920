#include <iostream>
#include <string>
#include <set>

using std::cout;    using std::endl;
using std::string;  using std::set;

int main() {
    // The set data structure can be thought of as a checklist of items. We can
    // add elements to a set, or remove elements from one. Then, we can ask the
    // set if it contains a particular item or not.
    set<string> groceryList;
    groceryList.insert("milk");
    groceryList.insert("eggs");

    // We can add duplicates, but only one copy of "PROTEIN!!" will be stored.
    // That is because sets are only concerned about whether an item appears in
    // the data structure or not.
    groceryList.insert("PROTEIN!!");
    groceryList.insert("PROTEIN!!");

    // This set contains "milk".
    if (groceryList.count("milk")) {
        cout << "We are getting milk!" << endl;
    } else {
        cout << "Well, no use crying..." << endl;
    }

    // This set does not contain "butter".
    if (groceryList.count("butter")) {
        cout << "We are getting butter!" << endl;
    } else {
        cout << "You had butter not..." << endl;
    }

    // This set used to contain "eggs", but the call to .erase(...) removes it
    // from the set.
    groceryList.erase("eggs");
    if (groceryList.count("eggs")) {
        cout << "We are getting eggs!" << endl;
    } else {
        cout << "Rotten choice..." << endl;
    }

    return 0;
}
