#include "pch.h"
#include "bruteForceTree.h"
#include <random>
#include <ctime>


bruteForceTree::bruteForceTree()
{
}

// Wyliczenie najlepszej �cie�ki algorytmem brute force
branchAndBoundStruct bruteForceTree::calculateBranchAndBound(dataSet data, std::vector<int> nodes)
{
	pathManager pathmanager;
	srand((int)time(0));

	// Pocz�tkowy koszt najlepszej �cie�ki
	minimalPathCost = INT_MAX;

	// Koszty przej��
	pathCosts = data.data;

	// Ustawienie ilo�ci w�z��w w problemie
	numberOfNodes = nodes.size();

	// Wektor przechowuj�cy wszystkie przegl�dane �cie�ki
	std::vector<branchAndBoundStruct> allPaths;

	// Pocz�tkowy wektor
	std::vector<int> initialPath;
	initialPath.push_back(0);
	branchAndBoundStruct initialStruct = branchAndBoundStruct(initialPath, 0);
	allPaths.push_back(initialStruct);

	// Wywo�anie funkcji rekurencyjnej
	calculatePath(&allPaths);

	branchAndBoundStruct resultStruct = branchAndBoundStruct(minimalPath, minimalPathCost);
	return resultStruct;
}


// Rekurencyjna funkcja licz�ca �cie�ki
void bruteForceTree::calculatePath(std::vector<branchAndBoundStruct> * nodesVector)
{
	// Ostatni element wektora
	branchAndBoundStruct selectedStruct = nodesVector->back();
	// Usuni�cie ostatniego elementu wektora
	nodesVector->pop_back();

	// Czy �cie�ka zawiera ju� wszystkie w�z�y
	if (selectedStruct.path.size() != numberOfNodes)
	{
		// P�tla po w�z�ach
		for (int i = 1; i < numberOfNodes; i++)
		{
			// Je�li nie ma jeszcze tego w�z�a w sie�ce
			if (std::find(selectedStruct.path.begin(), selectedStruct.path.end(), i) == selectedStruct.path.end())
			{
				// Utworzenie nowej struktury ze �cie�k�
				branchAndBoundStruct brandNewStruct(selectedStruct.path, selectedStruct.pathCost);
				brandNewStruct.path.push_back(i);

				int pathResult = calculatePatchCost(brandNewStruct.path);

					nodesVector->push_back(brandNewStruct);

					// Wywo�anie samej siebie z uaktualnion� list� wektor�w
					calculatePath(nodesVector);
			}
		}
	}
	else
	{
		// Zrobienie p�tli
		selectedStruct.path.push_back(0);

		int value = calculatePatchCost(selectedStruct.path);

		// Je�li dana �cie�ka jest lepsza ni� najlepsza dotychczas
		if (value <= minimalPathCost)
		{
			// Zapis kosztu i �cie�ki
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
