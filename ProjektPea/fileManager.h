#pragma once
#include "dataSet.h"
#include <string>
class fileManager
{
public:
	dataSet readDataFromFile(std::string fileName);
	fileManager();
	~fileManager();
};

