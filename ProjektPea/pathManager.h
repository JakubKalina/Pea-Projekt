#pragma once
#include "dataSet.h"
#include <vector>

class pathManager
{
public:
	pathManager();
	~pathManager();
	int calculateGoal(dataSet data, std::vector<int> nodes);
	std::vector<int> getVector(int size);
};

