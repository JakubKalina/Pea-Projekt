#include "pch.h"
#include "GeneticPair.h"


GeneticPair::GeneticPair()
{
}

// Konstruktor z parametrami
GeneticPair::GeneticPair(GeneticEntity firstEntity, GeneticEntity secondEntity)
{
	this->firstEntity = firstEntity;
	this->secondEntity = secondEntity;
}


GeneticPair::~GeneticPair()
{
}
