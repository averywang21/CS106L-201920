#include "simpio.h"

using namespace std;

int stringToInteger(const string& str) {
    istringstream iss(str);
    int result;
    iss >> result;
    return result;
}

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
            throw std::domain_error("getLine: End of input reached while waiting for line.");
        }
        istringstream iss(line);
        int value;
        char extra;
        if (iss >> value && !(iss >> extra)) return value;
        cerr << reprompt << endl;
    }

}

std::string getLine(const std::string& prompt) {
    string line;
    cout << prompt;
    if (!getline(cin, line)) {
        throw std::domain_error("getLine: End of input reached while waiting for line.");
    }
    return line;
}

double getReal(const std::string& prompt,
               const std::string& reprompt) {
    (void) prompt, (void) reprompt;
    return 0.0;
}

bool getYesOrNo(const std::string& prompt,
                const std::string& reprompt,
                const std::string& defaultValue) {
    (void) prompt, (void) reprompt, (void) defaultValue;
    return false;
}

std::string promptUserForFile(ifstream& stream,
                              const string& prompt,
                              const string& reprompt) {
    while (true) {
        cout << prompt;
        string filename;
        if (!getline(cin, filename)) {
            throw std::domain_error("getline: End of input reached while waiting for line.");
        }
        if (!filename.empty()) {
            stream.clear();
            stream.open(filename);
            if (stream) return filename;
        }
        cerr << reprompt << endl;
    }
}
