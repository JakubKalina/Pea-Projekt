#include "pch.h"
#include "branchAndBound.h"
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

branchAndBound::branchAndBound()
{
}

// Wyliczenie najlepszej œcie¿ki algorytmem branch and bound
branchAndBoundStruct branchAndBound::calculateBranchAndBound(dataSet data, std::vector<int> nodes, int initialMinimalCost)
{
	pathManager pathmanager;
	srand((int)time(0));

	// Ustawienie górnego ograniczenia - koszt pierwszej œcie¿ek
	if (initialMinimalCost == 0)
	{
		minimalPathCost = pathmanager.calculateGoal(data, nodes);
	}
	else if (initialMinimalCost == 1) // Górne ogranicznie losowe
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			int randomIndex = (rand() % (nodes.size() - 1)) + 0;
			std::swap(nodes[i], nodes[randomIndex]);
		}
		minimalPathCost = pathmanager.calculateGoal(data, nodes);
	}
	else // Górne ograniczenie wpisane rêcznie
	{
		minimalPathCost = initialMinimalCost;
	}

	// Koszty przejœæ
	pathCosts = data.data;
	count = 0;

	// Ustawienie iloœci wêz³ów w problemie
	numberOfNodes = nodes.size();

	// Wektor przechowuj¹cy wszystkie przegl¹dane œcie¿ki
	std::vector<branchAndBoundStruct> allPaths;

	// Pocz¹tkowy wektor
	std::vector<int> initialPath;
	initialPath.push_back(0);
	branchAndBoundStruct initialStruct =  branchAndBoundStruct(initialPath, 0);
	allPaths.push_back(initialStruct);

	// Wywo³anie funkcji rekurencyjnej
	calculatePath(&allPaths);
	
	branchAndBoundStruct resultStruct = branchAndBoundStruct(minimalPath, minimalPathCost);
	cout << std::endl << "ilosc: " << count;
	return resultStruct;
}

// Rekurencyjna funkcja licz¹ca œcie¿ki
void branchAndBound::calculatePath(std::vector<branchAndBoundStruct> * nodesVector)
{
	count++;

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

				// Jeœli dana œcie¿ka ma potencja³ rozwoju
				if (pathResult <= minimalPathCost)
				{
					nodesVector->push_back(brandNewStruct);

					// Wywo³anie samej siebie z uaktualnion¹ list¹ wektorów
					calculatePath(nodesVector);
				}
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
int branchAndBound::calculatePatchCost(std::vector<int> nodes)
{
	int totalWeight = 0;
	for (int i = 0; i < nodes.size() - 1; i++)
	{
		totalWeight += pathCosts[nodes[i]][nodes[i+1]];
	}
	return totalWeight;
}


branchAndBound::~branchAndBound()
{
}

