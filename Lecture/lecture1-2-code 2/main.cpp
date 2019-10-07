/*
 * Lecture code for lectures 1-2, streams and types.
 * Created by: Avery Wang (averywang@stanford.edu)
 *
 * Post on Piazza if you have questions!
 */
#include <iostream> // for cout, cin
#include <sstream> // for istringstream
#include <fstream> // for ifstream
#include <vector>
#include <iomanip> // for manipulators

using namespace std;

struct PriceRange {
  int min;
  int max;
};

void printBitInfo(istream& s);
void stringStreamTest();
void stringPositionTest();
void stringToIntegerTest();
PriceRange findPriceRange(int dist);
pair<int, int> findPriceRangePair(int dist);

// default parameters
int getInteger(const string& prompt = "Enter an integer: ",
               const string& reprompt = "Illegal numeric format. Try again.");

string getLine(const string& prompt = "");

string promptUserForFile(ifstream& stream,
                         const string& prompt = "Output file: ",
                         const string& reprompt = "Unable to open that file.  Try again.");

void runAxess();


int main() {
  stringStreamTest();
  stringPositionTest();
  /*runAxess();*/
}

/*
 * Prints the four bits of any input stream.
 * parameter: reference to an input stream
 *
 * note: this function accepts ANY input stream.
 */
void printBitInfo(istream& s) {
  cout << "State bits: ";

  cout << (s.good() ? "G" : "-");
  cout << (s.fail() ? "F" : "-");
  cout << (s.eof() ? "E" : "-");
  cout << (s.bad() ? "B" : "-");

  cout << endl;
  cout << "-----------" << endl;
}

/*
 * Demonstrates the key extraction/insertion features of stringstreams
 */
void stringStreamTest() {
  ostringstream oss("Ito En Green Tea "); // default open mode
  // different open mode: open at end
  // ostringstream oss("Ito En Green Tea ", sstringstream::ate);

  cout << oss.str() << endl; // "Ito En Tea"

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
       << ounces/2 << " ounces." << endl; // oh hey it's a double!
}

/*
 * Demonstrates positioning functions
 */
void stringPositionTest() {
  string token;
  ostringstream oss("Ito En Green Tea"); // position is at 0
  oss << 16.9;
  cout << oss.str() << endl; // "16.9En Green Tea", position at 4


  fpos pos = oss.tellp() + streamoff(3); // fpos = position, off = offset
  oss.seekp(pos); // moves the position down 3 characters, position at 7
  oss << "Black";
  cout << oss.str() << endl; // "16.9En Black Tea", position at 12

  // moves position down 1 from current, position at 13
  oss.seekp(streamoff(1), stringstream::cur);
  oss << "Milk";
  cout << oss.str() << endl; // "16.9En Black Milk", position at 17
}


/*
 * Converts string into an integer.
 * parameter: string representing an int
 * return: integer written in the string.
 *
 * throws a domain error if string does not contain exactly an integer.
 */
int stringToInteger(const string& str) {
  istringstream iss(str);
  int result; char remain;
  if (iss >> result || !(iss >> remain)) {
      throw domain_error("stringToInteger: error parsing \"" + str + "\"");
    }
  return result;
}


/*
 * Prompts user until an integer is typed in.
 * parameter: prompt and reprompt, see default parameters in function declaration
 *
 * throws a domain error if cin is unable to read a line (eg. EOF signal)
 */
int getInteger(const string& prompt,
               const string& reprompt) {
  while (true) {
      cout << prompt;
      string line;
      if (!getline(cin, line)) {
          throw domain_error("getLine: End of input reached while waiting for line.");
        }
      istringstream iss(line);
      int value; char extra;
      if (iss >> value && !(iss >> extra)) return value;
      cerr << reprompt << endl;
    }

}

/*
 * Prompts the user for a file.
 * If file is found, the stream is opened and filename returned.
 * If file is not found, the user is reprompted.
 *
 * Parameter: stream that will be opened, prompt and reprompt
 * Return: string of the valid file the user types.
 *
 * We didn't cover this during lecture. Try writing this function yourself!
 */
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

/*
 * Demonstrates use of auto
 */
auto calculateSum(const vector<string>& v) {
  // in Qt Creator, hover over the 'auto' to see the type!
  auto copy = v; // type is vector<string>
  auto multiplier = 2.4; // type is double
  auto name = "Avery"; // type is char* (C-string)
  auto betterName = string{"Avery"}; // type is a string
  auto& refName = multiplier; // type is ref to multiplier
  auto func = [](auto i) {return 2*i;}; // type is [unknown]

  return betterName;
}

void getOutrageousLoan(int& myCreditScore) {
  myCreditScore -= 100;
}

/*
 * Demonstrates use of references
 */
void testReferences() {
  int myCreditScore = 750;
  getOutrageousLoan(myCreditScore);
  cout << myCreditScore << endl;

  int myCreditScore2 = 750;
  int copyCreditScore = myCreditScore2; // copy
  getOutrageousLoan(copyCreditScore);
  cout << myCreditScore2 << endl;

  int myCreditScore3 = 750;
  int& refCreditScore = myCreditScore3; // reference
  getOutrageousLoan(refCreditScore);
  cout << myCreditScore3 << endl;
}

/*
 * Demonstrates structured bindings and pairs
 */
void typesTest() {
  int dist = 6528;
  auto [min, max] = findPriceRange(dist);
  // auto [min, max] = findPriceRangePair(dist);
  cout << "You can find tickets between " << min << " and " << max << " dollars." << endl;
}

PriceRange findPriceRange(int dist) {
  int min = static_cast<int>(0.08*dist + 100);
  int max = static_cast<int>(0.36*dist + 750);
  return {min, max};
}

pair<int, int> findPriceRangePair(int dist) {
  int min = static_cast<int>(0.08*dist + 100);
  int max = static_cast<int>(0.36*dist + 750);
  return {min, max};
}



/* Axess example we did not go over. Ask on Piazza if you have questions. Interesting read! */

/*
 * Struct representing a time
 */
struct Time {
    int hour;
    int minute;
};

/*
 * Struct representing a course
 */
struct Course {
    string code;

    Time startTime;
    Time endTime;
    vector<string> instructors;
};

/*
 * Overloading >> operator for Time struct.
 * Allows you to write:
 *    Time t;
 *    cin >> t;
 */
istream& operator>>(istream& is, Time& time) {
    if (!is) return is; // if the stream is not good, then don't do anything

    string timeString;
    if (!(is >> timeString)) { // try reading in a token.
        is.setstate(ios::failbit); // if not successful, don't do anything
        return is;
    }

    istringstream ss(timeString); // successful, try parsing that string
    int hour, minute; char colon;
    if (ss >> hour && hour >= 0 && hour <= 23 &&
            ss >> colon && colon == ':' &&
            ss >> minute && minute >= 0 && minute <= 59) { // get skips past the ':'
        time = Time{hour, minute};
    } else { // if any of the parsing fails, don't modify time.
        is.setstate(ios::failbit);
    }
    return is;
}

/*
 * Overloading << operator for Time struct.
 * Allows you to write:
 *    Time t;
 *    cout << t;
 */
ostream& operator<<(ostream& os, const Time& time) {
    os << time.hour << ":" << setfill('0') << setw(2) << time.minute; // manipulator to add leading zeros
    return os;
}

/*
 * Overloading << operator for Course struct.
 * Allows you to write:
 *    Course c;
 *    cout << c;
 */
ostream& operator<<(ostream& os, const Course& course) {
    os << course.code << endl;
    for (const auto& instructor : course.instructors) {
        os << instructor << " ";
    }
    os << endl;
    os << course.startTime << " - " << course.endTime;
    return os;
}

/*
 * Creates a course database from file given by filename courseFile.
 * Parameter: name of file to read from.
 * Return: pair of bool (was the file well formmatted?), vector<Course> (the actual database).
 * vector<Course> is only valid if the first component of the pair is true.
 */
pair<bool, vector<Course>> createCourseDatabase(const string& courseFile) {
    ifstream file(courseFile);
    vector<Course> database;


    string line;
    while (getline(file, line)) {
        string courseCode;
        Time start, end;
        int numInstructors;
        istringstream iss(line);
        if (!(iss >> courseCode >> start >> end >> numInstructors)) {
            return {false, {}}; // fail is ill-formatted
        }
        Course course{courseCode, start, end, {}};

        for (int i = 0; i < numInstructors; ++i) {
            string instructor;
            if (!(iss >> instructor)) return {false, {}}; // must contain those instructors
            course.instructors.push_back(instructor);
        }
        string trash;
        if (iss >> trash) return {false, {}}; // no more characters remaining

        database.push_back(course);
    }

    return {true, database};
}

/*
 * Finds the start and end time of a course in the course database.
 * Parameter: coursedatabase, and the courseCode to find.
 * Return: boolean (true if course found, false otherwise), and start time and end time.
 */
tuple<bool, Time, Time> findCourseTime(const vector<Course>& courseDatabase, const string& courseCode) {

    for (const auto& course : courseDatabase) {
        if (courseCode == course.code) {
            return make_tuple(true, course.startTime, course.endTime);
        }
    }

    return {false, {}, {}}; //make_tuple(false, Time{}, Time{});
}

void transformToDST(vector<Course>& courseDatabase) {
  /*
   * Equivalent:
   * for (auto& course : courseDatabase) {
   *   course.start.hour += 1; // and mod 24
   *   course.end.hour += 1; // and mod 24
   * }
  }
  */

  /*
   * Incorrect (must pass by reference):
   * for (auto course : courseDatabase)
   * for (auto [code, start, end, instructors] : courseDatabase)
   */

  for (auto& [code, start, end, instructors] : courseDatabase) {
      start.hour = (start.hour + 1) % 24;
      end.hour = (end.hour + 1) % 24;
  }
}

/*
 * Runs the Axess example demonstrating structures, type inference, initialization,
 * file streams, stringstreams, state bits, stream operator overloading, and manipulators.
 */
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

    string searchCourse = "CS106L";
    auto [found, start, end] = findCourseTime(database, searchCourse);

    if (found) {
        cout << searchCourse << " happens from " << start << " to " << end << "." << endl;
    } else {
        cout << searchCourse << " was not found in database." << endl;
    }
}

