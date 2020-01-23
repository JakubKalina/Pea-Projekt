#pragma once
#include <vector>
class GeneticEntity
{
public:

	// Koszt œcie¿ki
	int pathCost;

	// Œcie¿ka
	std::vector<int> path;


	GeneticEntity();
	GeneticEntity(std::vector<int> path, int pathCost);
	~GeneticEntity();
};

