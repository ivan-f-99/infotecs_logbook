#pragma once

#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "library.hpp"

void ReadFromTerminal(Logbook &LB);
void WriteToFile(Logbook &LB);
bool CheckImportanceLevelCorrection(std::string level_string);
void PrintHelp();
