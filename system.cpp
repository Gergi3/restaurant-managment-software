#include <fstream>
#include "system.h"

const unsigned char FILES_COUNT = 4;
const char const* FILE_NAMES[FILES_COUNT] =
{
	"orders.txt",
	"menu.txt",
	"inventory.txt",
	"dailyRevenues.txt"
};

bool initializeSystem()
{
	bool systemFilesAreInitialized = initializeSystemFiles();

	return systemFilesAreInitialized;
}

bool initializeSystemFiles()
{
	std::ofstream writer;

	for (size_t i = 0; i < FILES_COUNT; i++)
	{
		const char const* fileName = FILE_NAMES[i];
		writer.open(fileName, std::ios::app);
		if (!writer || !writer.is_open())
		{
			return false;
		}
		writer.close();
	}

	return true;
}

