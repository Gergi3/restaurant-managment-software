#include "date.h";
#include "generalConstants.h"
#include "stream.h"
#include "system.h"
#include <fstream>
#include <iostream>

bool initializeSystem()
{
	bool systemFilesAreInitialized = initializeSystemFiles();
	bool dateIsManagedProperly = addDate();

	return systemFilesAreInitialized && dateIsManagedProperly;
}

bool initializeSystemFiles()
{
	for (unsigned i = 0; i < GENERAL_CONSTANTS::FILES_COUNT; i++)
	{
		std::ofstream ofs(GENERAL_CONSTANTS::FILE_NAMES[i], std::ios::app);
		if (!isValidStream(ofs))
		{
			return false;
		}

		ofs.close();
	}

	return true;
}

