#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <ostream>
#include <iostream>

class Problem {
  public:
    Problem();
    ~Problem();
    std::string getQuestion() const;
    std::string printQuestion() const;
    bool askUserProblem();

    friend std::ostream& operator<<(std::ostream& os, Problem& problem);

  private:
    std::string question;
    std::string answer;
};

std::string Problem::getQuestion() const {
  return question;
}

std::string Problem::printQuestion() const {
  std::cout << "Question: " << question << std::endl;
}

bool Problem::askUserProblem() {
  printQuestion();
  std::cout << "Your Answer: ";
  std::string studentAnswer;
  getline(std::cin, studentAnswer);

  if (studentAnswer == answer) {
    std::cout << "Correct!" << std::endl;
    return true;
  } else {
    std::cout << "Incorrect! The correct answer was " << answer << std::endl;
    return false;
  }
}


#endif // PROBLEM_H
