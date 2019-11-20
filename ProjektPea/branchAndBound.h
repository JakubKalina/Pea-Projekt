#pragma once
#include "branchAndBoundStruct.h"
#include "dataSet.h"
#include "pathManager.h"
#include <vector>

class branchAndBound
{
public:
	// Metoda wyliczaj�ca rozwi�zanie
	branchAndBoundStruct calculateBranchAndBound(dataSet data, std::vector<int> nodes, int initialMinimalCost);
	// Koszt pocz�tkowej �cie�ki
	int initialPathCost;
	int count;
	// Minimalna �cie�ka
	std::vector<int> minimalPath;
	// Koszt minimalnej �cie�ki
	int minimalPathCost;
	// Ilo�� w�z��w
	int numberOfNodes;
	// Tablica koszt�w przej��
	int **pathCosts;
	branchAndBound();
	~branchAndBound();
private:
	// Metoda rekurencyjna rozwijaj�ca �cie�k�
	void calculatePath(std::vector<branchAndBoundStruct> * nodesVector);
	// Metoda licz�ca koszt �cie�ki
	int calculatePatchCost(std::vector<int> nodes);
};

