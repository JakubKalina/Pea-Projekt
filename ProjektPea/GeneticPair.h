#pragma once
#include "GeneticEntity.h"

class GeneticPair
{
public:

	// Pierwsza encja
	GeneticEntity firstEntity;

	// Druga encja
	GeneticEntity secondEntity;

	GeneticPair();
	GeneticPair(GeneticEntity firstEntity, GeneticEntity secondEntity);
	~GeneticPair();
};

