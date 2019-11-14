#include "pch.h"
#include "bruteForceTree.h"
#include <random>
#include <ctime>


bruteForceTree::bruteForceTree()
{
}

// Wyliczenie najlepszej œcie¿ki algorytmem brute force
branchAndBoundStruct bruteForceTree::calculateBranchAndBound(dataSet data, std::vector<int> nodes)
{
	pathManager pathmanager;
	srand((int)time(0));

	// Pocz¹tkowy koszt najlepszej œcie¿ki
	minimalPathCost = INT_MAX;

	// Koszty przejœæ
	pathCosts = data.data;

	// Ustawienie iloœci wêz³ów w problemie
	numberOfNodes = nodes.size();

	// Wektor przechowuj¹cy wszystkie przegl¹dane œcie¿ki
	std::vector<branchAndBoundStruct> allPaths;

	// Pocz¹tkowy wektor
	std::vector<int> initialPath;
	initialPath.push_back(0);
	branchAndBoundStruct initialStruct = branchAndBoundStruct(initialPath, 0);
	allPaths.push_back(initialStruct);

	// Wywo³anie funkcji rekurencyjnej
	calculatePath(&allPaths);

	branchAndBoundStruct resultStruct = branchAndBoundStruct(minimalPath, minimalPathCost);
	return resultStruct;
}


// Rekurencyjna funkcja licz¹ca œcie¿ki
void bruteForceTree::calculatePath(std::vector<branchAndBoundStruct> * nodesVector)
{
	// Ostatni element wektora
	branchAndBoundStruct selectedStruct = nodesVector->back();
	// Usuniêcie ostatniego elementu wektora
	nodesVector->pop_back();

	// Czy œcie¿ka zawiera ju¿ wszystkie wêz³y
	if (selectedStruct.path.size() != numberOfNodes)
	{
		// Pêtla po wêz³ach
		for (int i = 1; i < numberOfNodes; i++)
		{
			// Jeœli nie ma jeszcze tego wêz³a w sie¿ce
			if (std::find(selectedStruct.path.begin(), selectedStruct.path.end(), i) == selectedStruct.path.end())
			{
				// Utworzenie nowej struktury ze œcie¿k¹
				branchAndBoundStruct brandNewStruct(selectedStruct.path, selectedStruct.pathCost);
				brandNewStruct.path.push_back(i);

				int pathResult = calculatePatchCost(brandNewStruct.path);

					nodesVector->push_back(brandNewStruct);

					// Wywo³anie samej siebie z uaktualnion¹ list¹ wektorów
					calculatePath(nodesVector);
			}
		}
	}
	else
	{
		// Zrobienie pêtli
		selectedStruct.path.push_back(0);

		int value = calculatePatchCost(selectedStruct.path);

		// Jeœli dana œcie¿ka jest lepsza ni¿ najlepsza dotychczas
		if (value <= minimalPathCost)
		{
			// Zapis kosztu i œcie¿ki
			minimalPath = selectedStruct.path;
			minimalPathCost = value;
		}
	}
	return;
}


// Wyliczenie kosztu drogi
int bruteForceTree::calculatePatchCost(std::vector<int> nodes)
{
	int totalWeight = 0;
	for (int i = 0; i < nodes.size() - 1; i++)
	{
		totalWeight += pathCosts[nodes[i]][nodes[i + 1]];
	}
	return totalWeight;
}



bruteForceTree::~bruteForceTree()
{
}
