#include "generalConstants.h"
#include "system.h"
#include <fstream>

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
		const char const* fileName = GENERAL_CONSTANTS::FILE_NAMES[i];
		writer.open(fileName, std::ios::app);
		if (!writer || !writer.is_open() || !writer.good())
		{
			return false;
		}
		writer.close();
	}

	return true;
}

