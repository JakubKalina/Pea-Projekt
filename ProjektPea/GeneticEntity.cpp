#include "pch.h"
#include "GeneticEntity.h"
#include <vector>


GeneticEntity::GeneticEntity()
{
}

// Konstruktor z parametrami
GeneticEntity::GeneticEntity(std::vector<int> path, int pathCost)
{
	this->path = path;
	this->pathCost = pathCost;
}


GeneticEntity::~GeneticEntity()
{
}
