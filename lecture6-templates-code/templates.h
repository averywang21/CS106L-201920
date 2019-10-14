#include <iostream>
#include <iomanip>
#include <sstream>

#ifndef TEMPLATES_H
#define TEMPLATES_H

struct Time {
  int hour;
  int minute;
};

struct Patient {
  std::string name;
  int priority;
};

/*
 * The six relational comparators for the Time struct.
 */

bool operator==(const Time& lhs, const Time& rhs) {
  return lhs.hour == rhs.hour && lhs.minute == rhs.minute;
}

bool operator!=(const Time& lhs, const Time& rhs) {
  return !(lhs == rhs);
}

bool operator<(const Time& lhs, const Time& rhs) {
  return lhs.hour < rhs.hour || (lhs.hour == rhs.hour && lhs.minute < rhs.minute);
}

bool operator>(const Time& lhs, const Time& rhs) {
  return rhs < lhs;
}

bool operator<=(const Time& lhs, const Time& rhs) {
  return !(lhs > rhs);
}

bool operator>=(const Time& lhs, const Time& rhs) {
  return !(lhs < rhs);
}

/*
 * Overloading >> operator for Time struct.
 * Allows you to write:
 *    Time t;
 *    cin >> t;
 */
std::istream& operator>>(std::istream& is, Time& time) {
    if (!is) return is; // if the stream is not good, then don't do anything

    std::string timeString;
    if (!(is >> timeString)) { // try reading in a token.
        is.setstate(std::ios::failbit); // if not successful, don't do anything
        return is;
    }

    std::istringstream ss(timeString); // successful, try parsing that string
    int hour, minute; char colon;
    if (ss >> hour && hour >= 0 && hour <= 23 &&
            ss >> colon && colon == ':' &&
            ss >> minute && minute >= 0 && minute <= 59) { // get skips past the ':'
        time = Time{hour, minute};
    } else { // if any of the parsing fails, don't modify time.
        is.setstate(std::ios::failbit);
    }
    return is;
}

/*
 * Overloading << operator for Time struct.
 * Allows you to write:
 *    Time t;
 *    cout << t;
 */
std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << time.hour << ":" << std::setfill('0') << std::setw(2) << time.minute; // manipulator to add leading zeros
    return os;
}

#endif // TEMPLATES_H
