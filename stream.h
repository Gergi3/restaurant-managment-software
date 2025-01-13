#pragma once

#include <fstream>

bool isValidStream(std::ofstream& ofs);

bool isValidStream(std::ifstream& ifs);

bool isValidStream(std::fstream& fs);

unsigned getLinesCount(std::ifstream& ifs);
