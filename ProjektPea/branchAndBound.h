#pragma once
#include "branchAndBoundStruct.h"
#include "dataSet.h"
#include "pathManager.h"
#include <vector>

class branchAndBound
{
public:
	// Metoda wyliczaj¹ca rozwi¹zanie
	branchAndBoundStruct calculateBranchAndBound(dataSet data, std::vector<int> nodes, int initialMinimalCost);
	// Koszt pocz¹tkowej œcie¿ki
	int initialPathCost;
	int count;
	// Minimalna œcie¿ka
	std::vector<int> minimalPath;
	// Koszt minimalnej œcie¿ki
	int minimalPathCost;
	// Iloœæ wêz³ów
	int numberOfNodes;
	// Tablica kosztów przejœæ
	int **pathCosts;
	branchAndBound();
	~branchAndBound();
private:
	// Metoda rekurencyjna rozwijaj¹ca œcie¿kê
	void calculatePath(std::vector<branchAndBoundStruct> * nodesVector);
	// Metoda licz¹ca koszt œcie¿ki
	int calculatePatchCost(std::vector<int> nodes);
};

