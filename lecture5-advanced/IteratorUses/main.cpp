#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

using std::string;  using std::cin;
using std::cout;    using std::endl;
using std::vector;  using std::stringstream;
using std::set;

const int elemToFind = 5;

void printVec(const vector<int>& v) {
    for (auto elem : v) {
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    vector<int> vec{3,1,4,1,5,9,2,6,5,3};

    // We can use iterators in algorithms like sort to sort a vector
    cout << "Before sort" << endl;
    printVec(vec);

    std::sort(vec.begin(), vec.end());

    cout << "After sort" << endl;
    printVec(vec);
    cout << endl;

    // We can also use the find algorithm to look for an element
    // in a collection and return an iterator to it
    cout << "Let's try to find an element in our data structure..." << endl;

    vector<int>::iterator it = std::find(vec.begin(), vec.end(), elemToFind);
    if (it == vec.end()) {
        cout << "Not found!" << endl;
    } else {
        cout << "Found elem: " << *it << endl;
    }
    cout << endl;


    set<int> mySet{4, 1, 3, 5, 55, 5, 9, 22, 19, 28};

    // We can iterate through a range of elements in a sorted collection
    set<int>::iterator iter = mySet.lower_bound(4);
    set<int>::iterator end = mySet.upper_bound(30);

    while (iter != end) {
        cout << *iter << " ";
        ++iter;
    }
    cout << endl;

    // Alternatively, we could've used a for loop:
//    for (; iter != end; ++iter) {
//        cout << *iter << " ";
//    }
//    cout << endl;

    return 0;
}
