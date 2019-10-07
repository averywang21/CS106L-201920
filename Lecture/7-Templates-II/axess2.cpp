#include "axess2.h"

using namespace std;

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

bool operator<(const Time& lhs, const Time& rhs) {
    return lhs.hour < rhs.hour || (lhs.hour == rhs.hour && lhs.minute < rhs.minute);
}

bool operator>(const Time& lhs, const Time& rhs) {
    return lhs.hour > rhs.hour || (lhs.hour == rhs.hour && lhs.minute > rhs.minute);
}

ostream& operator<<(ostream& os, const Time& time) {
    os << time.hour << ":" /*<< setfill('0') << setw(2)*/ << time.minute;
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
    vector<Course> database;

    string courseCode;
    Time start, end;
    int numInstructors;
    double rating;

    while (file >> courseCode >> rating >> start >> end >> numInstructors) {
        Course course{courseCode, start, end, vector<string>{} , rating};

        for (int i = 0; i < numInstructors; ++i) {
            string instructor;
            if (!(file >> instructor)) return make_pair(false, database);
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
