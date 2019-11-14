#pragma once
#include "dataSet.h"
#include <vector>

class dynamicProgramming
{
public:
	int **masks;
	int **data;
	dynamicProgramming();
	~dynamicProgramming();
	int calculateDynamicProgramming(dataSet data, std::vector<int> nodes);
	int calculateInternalPath(int number, int node, int size);
};

