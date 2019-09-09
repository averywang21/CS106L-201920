#ifndef AXESS2_H
#define AXESS2_H

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

struct Time {
    int hour;
    int minute;
};

struct Course {
    std::string code;

    Time startTime;
    Time endTime;
    std::vector<std::string> instructors;
    double rating;
};

void runAxess();
std::pair<bool, std::vector<Course>> createCourseDatabase(const std::string& courseFile);
std::tuple<bool, Time, Time> findCourseTime(const std::vector<Course>& courseDatabase,
                                    const std::string& courseCode);

std::istream& operator>>(std::istream& is, Time& time);
std::ostream& operator<<(std::ostream& os, const Course& course);
std::ostream& operator<<(std::ostream& os, const Time& time);

bool operator<(const Time& lhs, const Time& rhs);
bool operator>(const Time& lhs, const Time& rhs);
#endif // AXESS2_H
