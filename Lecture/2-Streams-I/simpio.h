#ifndef SIMPIO_H
#define SIMPIO_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

int getInteger(const std::string& prompt = "Enter an integer: ",
               const std::string& reprompt = "Illegal numeric format. Try again.");

std::string getLine(const std::string& prompt = "");

double getReal(const std::string& prompt = "",
               const std::string& reprompt = "");

bool getYesOrNo(const std::string& prompt = "",
                const std::string& reprompt = "",
                const std::string& defaultValue = "");

std::string promptUserForFile(std::ifstream& stream,
                              const std::string& prompt = "Output file: ",
                              const std::string& reprompt = "Unable to open that file.  Try again.");


#endif // SIMPIO_H
