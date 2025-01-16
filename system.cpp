#include "generalConstants.h"
#include "system.h"
#include <fstream>

const char const* FILE_NAMES[GENERAL_CONSTANTS::FILES_COUNT] =
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

	for (size_t i = 0; i < GENERAL_CONSTANTS::FILES_COUNT; i++)
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

