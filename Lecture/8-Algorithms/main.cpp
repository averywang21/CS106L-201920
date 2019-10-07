#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <string>
#include <fstream>
#include <numeric> // for accumulate
#include <iostream>

using namespace std;

enum class Year {FRESHMAN, SOPHOMORE, JUNIOR, SENIOR, GRAD};

struct Student {
  string name;
  Year year;
  double average;

  Student(string name, Year year, double average) : name(name), year(year), average(average) {}
};

vector<int> readNumbers() {
  return {3, 1, 4, 1, 5, 9, 2, 6, 3, 5, 3};
}

vector<Student> readStudents(string filename) {
  ifstream file(filename);
  vector<Student> result;
  string name; string year; double average;
  while (file >> name >> year >> average) {
      Year studentYear;
      if (year == "Freshman") studentYear = Year::FRESHMAN;
      else if (year == "Sophomore") studentYear = Year::SOPHOMORE;
      else if (year == "Junior") studentYear = Year::JUNIOR;
      else if (year == "Senior") studentYear = Year::SENIOR;
      else if (year == "Grad") studentYear = Year::GRAD;
      else throw "Error";

      result.emplace_back(name, studentYear, average);
    }
  return result;
}

void algorithmTests() {
  vector<int> numbers = readNumbers();
  vector<Student> students = readStudents("students.txt");

  auto compareAverage =
      [](const Student& s1, const Student& s2) {return s1.average < s2.average;};
  // range
  auto [minNum, maxNum] = minmax_element(begin(numbers), end(numbers));
      auto [minStudent, maxStudent] = minmax_element(begin(students), end(students), compareAverage);

      // average
      double average = accumulate(begin(numbers), end(numbers), 0.0) / numbers.size();
      double studentAverage = accumulate(begin(students), end(students), 0.0,
      [](double current, const Student& s) {return current + s.average;}) / students.size();

  // median
  nth_element(begin(numbers), begin(numbers) + numbers.size()/2, end(numbers));
  int medianNum = numbers[numbers.size()/2];
  nth_element(begin(students), begin(students) + students.size()/2, end(students), compareAverage);
  Student medianStudent = students[students.size()/2];

  // is there a student who failed?
  auto failedPred = [](const auto& student) {return student.average < 60;};
  bool someoneFailed = any_of(begin(students), end(students), failedPred);
  // name someone who failed
  auto failedStudent = find_if(begin(students), end(students), failedPred);
  // find everyone who failed
  vector<Student> failedStudents;
  copy_if(begin(students), end(students), back_inserter(failedStudents), failedPred);

  // find all students of a certain year, note the capture clause!
  const Year yearToSearch = Year::FRESHMAN; // you can change this
  auto searchYear = [yearToSearch](const auto& student) {return student.year == yearToSearch;};

  // let's curve everyone's grades
  auto jerryCurve = [](const auto& student) {
      return Student{student.name, student.year, student.average*0.45+0.44};}; // rip
  transform(begin(students), end(students), begin(students), jerryCurve); // overwrites original student

  // sort all students by year then by alphabetical
  auto sortByYear = [](const auto& s1, const auto& s2) {
      return s1.year < s2.year || (s1.year == s2.year && s1.name < s2.name); };
  sort(begin(students), end(students), sortByYear);

  vector<Student> students106B = readStudents("students106B.txt");
  sort(begin(students106B), end(students106B), sortByYear);

  // find students in 106L who have already taken 106B
  vector<Student> alreadyKnowsIt;
  set_difference(begin(students), end(students), begin(alreadyKnowsIt), end(alreadyKnowsIt),
                 back_inserter(alreadyKnowsIt), sortByYear);
}

int main() {
  ifstream set_input("censored_words.txt");
  static const auto eof_iterator = istream_iterator<string>();

  set<string> censoredWords{istream_iterator<string>(set_input), eof_iterator};

  ifstream input("hamilton.txt");
  ofstream output("hamilton-out.txt");

  auto shouldCensor = [&censoredWords](const string& word) {
    if(censoredWords.find(word) != censoredWords.end()) {
      return string(word.size(), '*');
    } else return word;
  };

  transform(istream_iterator<string>(input), eof_iterator,
      ostream_iterator<string>(output, " "), shouldCensor);
}
