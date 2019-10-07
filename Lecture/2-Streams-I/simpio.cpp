#include "simpio.h"

using namespace std;

// this version doesn't do error-checking
/*
int stringToInteger(const string& str) {
    istringstream iss(str);
    int result;
    iss >> result;
    return result;
}
*/

int stringToInteger(const string& str) {
  istringstream iss(str);
  int result; char remain;
  if (iss >> result || !(iss >> remain)) {
    throw domain_error("stringToInteger: error parsing \"" + str + "\"");
  }
  return result;
}

// you write this!
vector<string> stringSplit(const string& str, const string& delim) {
    (void) str, (void) delim;
    return {};
}

int getInteger(const string& prompt,
               const string& reprompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) {
            throw domain_error("getLine: End of input reached while waiting for line.");
        }
        istringstream iss(line);
        int value;
        char extra;
        if (iss >> value && !(iss >> extra)) return value;
        cerr << reprompt << endl;
    }

}

string getLine(const string& prompt) {
    string line;
    cout << prompt;
    if (!getline(cin, line)) {
        throw domain_error("getLine: End of input reached while waiting for line.");
    }
    return line;
}

// you write this!
double getReal(const string& prompt,
               const string& reprompt) {
    (void) prompt, (void) reprompt;
    return 0.0;
}

bool getYesOrNo(const string& prompt,
                const string& reprompt,
                const string& defaultValue) {
    (void) prompt, (void) reprompt, (void) defaultValue;
    return false;
}

string promptUserForFile(ifstream& stream,
                              const string& prompt,
                              const string& reprompt) {
    while (true) {
        cout << prompt;
        string filename;
        if (!getline(cin, filename)) {
            throw domain_error("getline: End of input reached while waiting for line.");
        }
        if (!filename.empty()) {
            stream.clear();
            stream.open(filename);
            if (stream) return filename;
        }
        cerr << reprompt << endl;
    }
}
