#include "generalConstants.h"
#include "stream.h"
#include "string.h"
#include <fstream>

const unsigned MAX_BUFFER_SIZE = GENERAL_CONSTANTS::INPUT_BUFFER_SIZE;

bool isValidStream(std::ofstream& ofs)
{
	return ofs && ofs.is_open();
}

bool isValidStream(std::ifstream& ifs)
{
	return ifs && ifs.is_open();
}

bool isValidStream(std::fstream& fs)
{
	return fs && fs.is_open();
}

unsigned getLinesCount(std::ifstream& ifs)
{
	if (!isValidStream(ifs))
	{
		return 0;
	}

	std::streamoff startingPos = ifs.tellg();
	ifs.seekg(startingPos, std::ios::end);

	std::streamoff endPos = ifs.tellg();
	ifs.clear();
	ifs.seekg(startingPos);

	return getCharCount(ifs, '\n', endPos);
}

unsigned getCharCountCurrentLine(
	std::ifstream& ifs,
	char ch)
{
	if (!isValidStream(ifs))
	{
		return 0;
	}

	std::streamoff startingPos = ifs.tellg();

	char emptyBuffer[MAX_BUFFER_SIZE]{};
	ifs.getline(emptyBuffer, MAX_BUFFER_SIZE, '\n');

	std::streamoff endPos = ifs.tellg();
	endPos--;

	ifs.clear();
	ifs.seekg(startingPos);

	return getCharCount(ifs, ch, endPos);
}

unsigned getCharCount(
	std::ifstream& ifs,
	char ch,
	std::streamoff endPos)
{
	if (!isValidStream(ifs))
	{
		return 0;
	}

	std::streamoff startingPos = ifs.tellg();

	char emptyBuffer[MAX_BUFFER_SIZE]{};
	ifs.read(&emptyBuffer[0], endPos - startingPos);

	unsigned count = countCharOccurances(emptyBuffer, ch);

	ifs.clear();
	ifs.seekg(startingPos);

	return count;
}