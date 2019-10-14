/*
 * Interactive lecture code for lecture 6 - templates.
 * Warning - recommended that you look at the completed version after lecture.
 *
 * Avery Wang updated 10/13/2019.
 */

#include <iostream> // for cin, cout
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <typeinfo> // for typeid
#include "templates.h" // I defined everything you don't care about (yet) in here.
using namespace std;

// -----------------------------------
// Part 1A: template functions, guided example

// TODO: make this function a template!
pair<int, int> my_minmax(int a, int b) {
  if (a < b) return {a, b};
  else return {b, a};
}

// TODO: make this function a template!
void printMinAndMax(int min, int max) {
  cout << "Min: " << min << endl;
  cout << "Max: " << max << endl;
  cout << endl;
}

// Tests for our my_minmax function.
void minmaxTestBasic() {
    auto [min1, max1] = my_minmax(3, -2);
    printMinAndMax(min1, max1);

    auto [min2, max2] = my_minmax(6, 6);
    printMinAndMax(min2, max2);

    // These don't compile yet.
    // TODO: uncomment these after templatizing my_minmax and printMinAndMax
    /*
    auto [min3, max3] = my_minmax(8.3, 7.4);
    printMinAndMax(min3, max3);

    auto [min4, max4] = my_minmax('l', 'b');                  // ASCII comparison
    printMinAndMax(min4, max4);

    auto [min5, max5] = my_minmax("Avery", "Anna");           // string comparison "Anna" < "Avery"
    printMinAndMax(min5, max5);                               // but... min = "Avery"! Why? (cf. explicit instantiation works)
    */
}


// this doesn't compile yet - it'll only compile after making my_minmax and printMinAndMax generic
void minmaxTestExplicit() {
    // explicit instantiation - everything works!
    auto [min0, max0] = my_minmax/*<int>*/(3, 4);                 // TODO: uncomment to see the explicit initialization
    printMinAndMax(min0, max0);
    /*
    // TODO: uncomment these after templatizing my_minmax and printMinAndMax
    auto [min1, max1] = my_minmax<double>(4.2, -7.9);
    printMinAndMax(min1, max1);

    auto [min2, max2] = my_minmax<string>("Avery", "Anna");       // this works, T = string
    printMinAndMax(min2, max2);

    auto [min3, max3] = my_minmax<int>(3, 3);
    printMinAndMax(min3, max3);

    auto [min4, max4] = my_minmax<double>(2, 2.3);
    printMinAndMax(min4, max4);

    auto [min5, max5] = my_minmax<vector<int>>({1, 2}, {3, 1});
    // printMinAndMax(min5, max5);                                // this does not compile. STL vector does not have operator << (why?)

    auto [min6, max6] = my_minmax<Time>({15, 30}, {16, 20});      // this compiles - we defined operator< in templates.h
    printMinAndMax(min6, max6);                                   // this compiles - we defined operator<< for ostream and Time.

    */

    // auto [min7, max7] = my_minmax<Patient>({"Avery", 3}, {"Anna", 1}); // why doesn't this compile?
}

// this doesn't compile yet - it'll only compile after making my_minmax and printMinAndMax generic
// TODO: uncomment these after templatizing my_minmax and printMinAndMax

void minMaxTestImplicit() {
    auto [min0, max0] = my_minmax(3, 4);
    // which ones of these are bad? why? (hint: what does the compiler deduce T to be?)
    /*
    auto [min1, max1] = my_minmax(4.2, -7.9);
    auto [min2, max2] = my_minmax("Avery", "Anna");                // this does not work, T = char* (C-string)
    auto [min3, max3] = my_minmax(3, 3);
    auto [min4, max4] = my_minmax(2, 2.3);
    auto [min5, max5] = my_minmax({1, 2}, {3, 1});                 // these are vectors
    auto [min6, max6] = my_minmax({15, 30}, {16, 20});             // this are Time structs
    auto [min7, max7] = my_minmax({"Avery", 3}, {"Anna", 1});      // these are Patient structs
                                                                  // the fact that these are ambiguous means this is a problem!
    */
}





// -------------------------------------------------
// Part 1B: template functions, your turn!
/*
 * Prompts and reprompts the user until it receives a type.
 * BTW: you wrote this in lecture 2 and in assignment 1!
 * Parameters: none
 * Return Value: T (template type)
 * Usage:
 *        char c = getType<char>("Enter a character: ");
 *        Time t = getType<Time>("Enter a time (hh:mm): ");
 * Warning: implicit template instantiation not possible, since we have no parameters.
 * For simplicity (and to demonstrate typeid), I've left out the parameters
 */
// TODO: make getTypeValue a template!
int getTypeValue() {
    while (true) {
        // typeid is supposed to print the name of the type. Unfortunately your compiler hides them pretty well.
        // g++ does janky things with typeid, so this probably won't work. I tried my best...feel free to Google "g++ demangling".
        cout << "Enter a " << typeid(int).name() << ": ";             // be sure to change the "int" to "T".

        string line; int result; char extra;
        if (!getline(cin, line))
           throw domain_error("Unable to get line from cin.");
        istringstream iss(line);
        if (iss >> result && !(iss >> extra)) return result;
        cout << "Invalid format." << endl;
    }
}

void getTypeTest() {
    int val0 = getTypeValue/*<int>*/();                             // TODO: uncomment after templatizing.

// This doesn't compile until getTypeValue is made generic.
// TODO: uncomment these after templatizing getTypeValue
/*
    int val1 = getTypeValue<int>();
    double val2 = getTypeValue<double>();
    Time val3 = getTypeValue<Time>();                               // this only works because >> is defined for Time in 'templates.h'
    cout << "int is: " << val1 << endl;
    cout << "double is: " << val2 << endl;
    cout << "Time is: " << val3 << endl;

*/

}

/* Concept lifting. Our goal is to make this function more generic! */

// countOccurences v1
// How many times does the integer [val] appear in vector of integers?
int countOccurences(const vector<int>& vec, int val) {
    int count = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == val) ++count;
    }
    return count;
}

// countOccurences v2
// How many times does the [DataType] [val] appear in vector of [DataType]?
// TODO: write a template function that solves the question above.

// countOccurences v3 (BAD #1)
// How many times does the [DataType] [val] appear in [collection] of [DataType]?
// Warning: this is poorly written as a template function. Why?
/*
template <typename DataType, typename Collection>
int countOccurences(const Collection& collection, DataType val) {
    int count = 0;
    for (size_t i = 0; i < collection.size(); ++i) {
        if (collection[i] == val) ++count;                              // This line is bad. Why?
    }
    return count;
}
*/

// countOccurences v3 (BAD #2)
// How many times does the [DataType] [val] appear in [collection] of [DataType]?
// Warning: this is poorly written as a template function. Why?
/*
template <typename DataType, typename Collection>
int countOccurences(const Collection& collection, DataType val) {
    int count = 0;
    for (size_t i = 0; i < collection.size(); ++i) {
        auto iter = collection.begin() + i;                             // This line is bad. Why?
        if (*iter == val) ++count;
    }
    return count;
}
*/

// countOccurences v3 (GOOD - you write this one)
// How many times does the [DataType] [val] appear in [collection] of [DataType]?
// TODO: write a template function that solves the question above.

// countOccurences v4
// How many times does the [DataType] [val] appear in [range of elements]?
// TODO: write a template function that solves the question above.

// countOccurences v5 (next time)
// How many elements in [range of elements] satisfy [equals val]? - this is v4
// How many elements in [range of elements] satisfy [predicate]? - this is v5
// TODO: wait in anticipation for the next lecture! :)




// Your Task: write a generic function countOccurences above
// Then, in each TODO, make one call to countOccurences.
// There are many different tasks below, so counOccurences needs to be very generic.
void countOccurencesTasks() {
    // Count how many times 3 appears in a vector<int>.
    vector<int> v1{3, 3, 4, 4, 1, 3};
    int times = countOccurences(v1, 3);
    // TODO: edit the line above to call the more generic countOccurences

    // Count how many times 4.7 appears in a vector<double>.
    vector<double> v2{2.3, 4.6667, 4.6666667, 4.7, 4.7, 7.4};
    // TODO: fill this in (use vector<int> v2)

    // Count how many times ‘X’ appears in a string.
    string quadratic = "AX^2 + BX + C = 0";
    // TODO: fill this in (use string quadratic)

    // Count how many times ‘X’ appears in a deque<char>.
    deque<char> quadraticDeque{'A', 'X', '^', '2', '+', 'B', 'X', '+', 'C'};
    // TODO: fill this in (use deque<char> quadraticDeque)

    // Count how many times 5 appears in the second half of a list<int>.
    list<int> phoneNumber{5, 5, 5, 8, 2, 6, 5, 5, 3, 5};
    // TODO: fill this in (use list<string> phoneNumber)

    // Count how many elements in the second half of a list<string> are at most 5.
    // TODO: fill this in (use list<string> phoneNumber)
    // Trick question - you'll need more tools to do this (namely v5 above). Wait for Thursday! :)

}

int main() {
    /* Comment these the tests out if you only want to test a particular one. */

    cout << "Starting minmax test basic:" << endl;
    minmaxTestBasic();
    cout << "Starting minmax test explicit:" << endl;
    minmaxTestExplicit();
    cout << "Starting minmax test implicit:" << endl;
    minMaxTestImplicit();
    cout << "Starting minmax type test (user input required!):" << endl;
    getTypeTest();
    cout << "Starting count occurences tests: (note, nothing is printed unless you actually add cout statements." << endl;
    countOccurencesTasks();
}
