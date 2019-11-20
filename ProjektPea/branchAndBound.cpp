#include "pch.h"
#include "branchAndBound.h"
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

branchAndBound::branchAndBound()
{
}

// Wyliczenie najlepszej �cie�ki algorytmem branch and bound
branchAndBoundStruct branchAndBound::calculateBranchAndBound(dataSet data, std::vector<int> nodes, int initialMinimalCost)
{
	pathManager pathmanager;
	srand((int)time(0));

	// Ustawienie g�rnego ograniczenia - koszt pierwszej �cie�ek
	if (initialMinimalCost == 0)
	{
		minimalPathCost = pathmanager.calculateGoal(data, nodes);
	}
	else if (initialMinimalCost == 1) // G�rne ogranicznie losowe
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			int randomIndex = (rand() % (nodes.size() - 1)) + 0;
			std::swap(nodes[i], nodes[randomIndex]);
		}
		minimalPathCost = pathmanager.calculateGoal(data, nodes);
	}
	else // G�rne ograniczenie wpisane r�cznie
	{
		minimalPathCost = initialMinimalCost;
	}

	// Koszty przej��
	pathCosts = data.data;
	count = 0;

	// Ustawienie ilo�ci w�z��w w problemie
	numberOfNodes = nodes.size();

	// Wektor przechowuj�cy wszystkie przegl�dane �cie�ki
	std::vector<branchAndBoundStruct> allPaths;

	// Pocz�tkowy wektor
	std::vector<int> initialPath;
	initialPath.push_back(0);
	branchAndBoundStruct initialStruct =  branchAndBoundStruct(initialPath, 0);
	allPaths.push_back(initialStruct);

	// Wywo�anie funkcji rekurencyjnej
	calculatePath(&allPaths);
	
	branchAndBoundStruct resultStruct = branchAndBoundStruct(minimalPath, minimalPathCost);
	cout << std::endl << "ilosc: " << count;
	return resultStruct;
}

// Rekurencyjna funkcja licz�ca �cie�ki
void branchAndBound::calculatePath(std::vector<branchAndBoundStruct> * nodesVector)
{
	count++;

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

				// Je�li dana �cie�ka ma potencja� rozwoju
				if (pathResult <= minimalPathCost)
				{
					nodesVector->push_back(brandNewStruct);

					// Wywo�anie samej siebie z uaktualnion� list� wektor�w
					calculatePath(nodesVector);
				}
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

