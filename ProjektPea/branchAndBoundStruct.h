#pragma once
#include <vector>
class branchAndBoundStruct
{
public:
	std::vector<int> path;
	int pathCost;

	branchAndBoundStruct(std::vector<int> path, int pathCost);
	branchAndBoundStruct();
	~branchAndBoundStruct();
};

