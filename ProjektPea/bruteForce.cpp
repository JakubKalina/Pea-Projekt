#include "pch.h"
#include "bruteForce.h"
#include "pathManager.h"
#include <iostream>
#include <conio.h>
#include <algorithm>

using namespace std;

bruteForce::bruteForce()
{
}


bruteForce::~bruteForce()
{
}

// Wyliczenie wyniku za pomoc¹ algorytmu Brute force
int bruteForce::calculateBruteForce(dataSet data, std::vector<int> nodes)
{
	pathManager pathManager;
	int minimalCost = pathManager.calculateGoal(data, nodes);
	std::vector<int> minimalPermutation = nodes;

	while (next_permutation(nodes.begin(), nodes.end()))
	{
		int currentCost = pathManager.calculateGoal(data, nodes);
		if (currentCost < minimalCost)
		{
			minimalCost = currentCost;
			minimalPermutation = nodes;
		}
	}

	// Uzyskany wynik kosztu
	cout << endl << "Uzyskany wynik: " << minimalCost;

	// Najlepsza droga
	cout << endl << "Droga : " << endl;

		for (int i = 0; i < minimalPermutation.size(); i++)
		{
			cout << minimalPermutation[i] << " - ";
		}
		cout << endl << endl;

	return minimalCost;
}
