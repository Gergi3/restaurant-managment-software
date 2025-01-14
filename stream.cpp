#include "stream.h"
#include <fstream>

const unsigned MAX_BUFFER_SIZE = 1024;

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

	int startingPos = ifs.tellg();

	char emptyBuffer[MAX_BUFFER_SIZE]{};
	
	unsigned count = 0;
	while (ifs.getline(emptyBuffer, MAX_BUFFER_SIZE))
	{
		count++;
	}

	ifs.clear();
	ifs.seekg(startingPos);

	return count;
}
