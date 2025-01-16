#include "date.h";
#include "generalConstants.h"
#include "system.h"
#include <fstream>

bool initializeSystem()
{
	bool systemFilesAreInitialized = initializeSystemFiles();
	bool dateIsManaged = addDate();

	return systemFilesAreInitialized && dateIsManaged;
}


bool initializeSystemFiles()
{
	std::ofstream ofs;

	for (size_t i = 0; i < GENERAL_CONSTANTS::FILES_COUNT; i++)
	{
		const char const* fileName = GENERAL_CONSTANTS::FILE_NAMES[i];
		ofs.open(fileName, std::ios::app);
		if (!ofs || !ofs.is_open() || !ofs.good())
		{
			return false;
		}
		ofs.close();
	}

	return true;
}

