#include "pch.h"
#include "branchAndBoundStruct.h"


branchAndBoundStruct::branchAndBoundStruct(std::vector<int> path, int pathCost)
{
	this->path = path;
	this->pathCost = pathCost;
}

branchAndBoundStruct::branchAndBoundStruct()
{

}

branchAndBoundStruct::~branchAndBoundStruct()
{
}
