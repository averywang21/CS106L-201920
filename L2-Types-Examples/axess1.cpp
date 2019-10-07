#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


struct Time {
    int hour;
    int minute;
};

struct Course {
    string code;

    Time startTime;
    Time endTime;
    vector<string> instructors;
};

istream& operator>>(istream& is, Time& time) {
    if (!is) { // if the stream is not good, then don't do anything
        return is;
    }

    string timeString;
    if (!(is >> timeString)) { // try reading in a string.
        is.setstate(ios::failbit); // if not successful, don't do anything
        return is;
    }

    stringstream ss(timeString); // successful, try parsing that string
    int hour, minute;
    if (ss >> hour && ss.get() && ss >> minute
            && hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) { // get skips past the ':'
        time.hour = hour;
        time.minute = minute;
    } else { // if any of the parsing fails, don't modify time.
        is.setstate(ios::failbit);
    }
    return is;
}

ostream& operator<<(ostream& os, const Time& time) {
    auto beforeWidth = os.width();
    auto beforeFill = os.fill();
    os << time.hour << ":" << setfill('0') << setw(2) << time.minute
       << setfill(beforeFill) << setw(beforeWidth);
    return os;
}

ostream& operator<<(ostream& os, const Course& course) {
    os << course.code << endl;
    for (const auto& instructor : course.instructors) {
        os << instructor << " ";
    }
    os << endl;
    os << course.startTime << " - " << course.endTime;
    return os;
}

pair<bool, vector<Course>> createCourseDatabase(const string& courseFile) {
    ifstream file(courseFile);

    string line;
    vector<Course> database;

    string courseCode;
    Time start, end;
    int numInstructors;

    while (file >> courseCode >> start >> end >> numInstructors) {
        Course course{courseCode, start, end, vector<string>{} };
        string instructor;

        for (int i = 0; i < numInstructors; ++i) {
            if (file >> instructor) return make_pair(false, database);
            course.instructors.push_back(instructor);
        }

        database.push_back(course);
    }

    return make_pair(file.eof(), database);
}

std::tuple<bool, Time, Time> findCourseTime(const vector<Course>& courseDatabase,
                                    const string& courseCode) {

    for (const auto& course : courseDatabase) {
        if (courseCode == course.code) {
            return make_tuple(true, course.startTime, course.endTime);
        }
    }
    return make_tuple(false, Time{}, Time{});
}
