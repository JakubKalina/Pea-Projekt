#pragma once
#include <string>

class dataSet
{
public:
	std::string name;
	int dataSize;
	int **data;
	int distanceResult;
	dataSet();
	~dataSet();
};

