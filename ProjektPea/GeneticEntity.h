#pragma once
#include <vector>
class GeneticEntity
{
public:

	// Koszt �cie�ki
	int pathCost;

	// �cie�ka
	std::vector<int> path;


	GeneticEntity();
	GeneticEntity(std::vector<int> path, int pathCost);
	~GeneticEntity();
};

