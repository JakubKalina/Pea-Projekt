#include "pch.h"
#include "Genetic.h"
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>       
#include <queue>
#include "GeneticEntity.h"
#include "GeneticPair.h"
#include "pathManager.h"


Genetic::Genetic()
{
}


Genetic::~Genetic()
{
}

// Krosowanie OX
GeneticPair Genetic::CrossOx(GeneticPair pair)
{
	// Selekcja encji
	// Pierwszy index
	int k1 = (rand() % (numberOfNodes - 1)) + 1;
	// Drugi indeks
	int k2 = (rand() % (numberOfNodes - 2)) + 1;

	// Pozbycie siê duplikatów
	while (k1 == k2)
	{
		k2 = (rand() % (numberOfNodes - 2)) + 1;
	}

	// Zamiana kolejnoœci 
	if (k1 > k2) std::swap(k1, k2);

	// Pomocnicze tablice
	int* tempA = new int[numberOfNodes];
	int* tempB = new int[numberOfNodes];

	for (int i = 0; i < numberOfNodes; i++)
	{
		tempA[i] = -1;
		tempB[i] = -1;
	}

	// Przekopiowanie genów rodziców
	for (int i = k1; i <= k2; i++)
	{
		tempA[i] = pair.firstEntity.path[i];
		tempB[i] = pair.secondEntity.path[i];
	}

	// Pierwszy rodzic
	int indexInsert = k2 + 1;
	int indexNumber = k2 + 1;
	int number;

	while (tempA[k1 - 1] == -1)
	{
		if (indexInsert == numberOfNodes) indexInsert = 0;

		while (tempA[indexInsert] == -1)
		{
			if (indexNumber == numberOfNodes) indexNumber = 0;
			number = pair.secondEntity.path[indexNumber];

			if (VectorContainsNode(tempA, number) == false)
			{
				tempA[indexInsert] = number;
				break;
			}

			indexNumber++;
		}

		indexInsert++;
	}

	// Drugi rodzic
	indexInsert = k2 + 1;
	indexNumber = k2 + 1;

	while (tempB[k1 - 1] == -1)
	{
		if (indexInsert == numberOfNodes) indexInsert = 0;

		while (tempB[indexInsert] == -1)
		{
			if (indexNumber == numberOfNodes) indexNumber = 0;
			number = pair.firstEntity.path[indexNumber];

			if (VectorContainsNode(tempB, number) == false)
			{
				tempB[indexInsert] = number;
				break;
			}

			indexNumber++;
		}

		indexInsert++;
	}

	std::vector<int> permA, permB = {};

	for (int i = 0; i < numberOfNodes ; i++)
	{
		permA.push_back(tempA[i]);
		permB.push_back(tempB[i]);
	}

	GeneticEntity childA(permA, pathManager.calculateGoal(data, permA));
	GeneticEntity childB(permB, pathManager.calculateGoal(data, permB));

	GeneticPair children(childA, childB);

	delete tempA;
	delete tempB;

	return children;
}

// Krosowanie PX
GeneticPair Genetic::CrossPx(GeneticPair pair)
{
	// Wymiany
	int exchanges = numberOfNodes / 3;
	std::vector<int> citiestopushtoA = {};
	std::vector<int> citiestopushtoB = {};

	// Tablice pomocnicze
	int* tempA = new int[numberOfNodes];
	int* tempB = new int[numberOfNodes];

	for (int i = 0; i < numberOfNodes; i++)
	{
		tempA[i] = -1;
		tempB[i] = -1;
	}

	// Dla pierwszego rodzica
	for (int i = 0; i < exchanges; i++)
	{
		int r = rand() % numberOfNodes;
		while (tempA[r] != -1) r = rand() % numberOfNodes;

		tempA[r] = pair.firstEntity.path[r];
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		int check = pair.secondEntity.path[i];
		if (VectorContainsNode(tempA, check) == false)citiestopushtoA.push_back(check);
	}

	for (int i = numberOfNodes - 1; i >= 0; i--)
	{
		if (tempA[i] == -1)
		{
			tempA[i] = citiestopushtoA.back();
			citiestopushtoA.pop_back();
		}
	}

	// Dla drugiego rodzica
	for (int i = 0; i < exchanges; i++)
	{
		int r = rand() % numberOfNodes;
		while (tempB[r] != -1) r = rand() % numberOfNodes;

		tempB[r] = pair.secondEntity.path[r];
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		int check = pair.firstEntity.path[i];
		if (VectorContainsNode(tempB, check) == false)citiestopushtoB.push_back(check);
	}

	for (int i = numberOfNodes - 1; i >= 0; i--)
	{
		if (tempB[i] == -1)
		{
			tempB[i] = citiestopushtoB.back();
			citiestopushtoB.pop_back();
		}
	}

	std::vector<int> permA, permB = {};

	for (int i = 0; i < numberOfNodes; i++)
	{
		permA.push_back(tempA[i]);
		permB.push_back(tempB[i]);
	}

	// Sprawdzenie prawid³owoœci krzy¿owania
	CheckIfProper(permA);
	CheckIfProper(permB);

	GeneticEntity childA(permA, pathManager.calculateGoal(data, permA));
	GeneticEntity childB(permB, pathManager.calculateGoal(data, permB));

	GeneticPair children(childA, childB);

	delete tempA;
	delete tempB;

	return children;
}


// Sprawdzenie czy œcie¿ka jest w³aœciwa
bool Genetic::CheckIfProper(std::vector<int> vec)
{

	int* temp = new int[numberOfNodes];
	for (int i = 0; i < numberOfNodes; i++) temp[i] = 0;
	for (int i = 0; i < numberOfNodes; i++)
	{
		temp[vec[i]]++;
	}
	for (int i = 0; i < numberOfNodes; i++) if (temp[i] != 1)
	{
		delete temp;
		return false;
	}
	delete temp;
	return true;
}


// Sprawdzenie czy wektora zawiera dany wêze³
bool Genetic::VectorContainsNode(int* path, int node)
{
	for (int i = 0; i < numberOfNodes; i++)
	{
		if (path[i] == node)
		{
			return true;
		}
	}
	return false;
}

// Zwraca losowo wygenerowany wektor
std::vector<int> Genetic::GetRandomVector()
{
	std::vector<int> result = {};
	std::vector<int> tempVector = {};
	for (int i = 0; i < numberOfNodes; i++) tempVector.push_back(i);

	while (tempVector.size() > 0)
	{
		int randID = rand() % (tempVector.size());
		result.push_back(tempVector[randID]);

		if (tempVector.size() == 0) break;

		tempVector[randID] = tempVector[tempVector.size() - 1];
		tempVector.pop_back();
	}
	return result;
}

// Dokonanie mutacji jednostki
GeneticEntity Genetic::EntityMutation(GeneticEntity entity)
{
	//mutacja swapuje dwa miasta
	std::vector<int> result = entity.path;
	int index1 = rand() % (numberOfNodes - 1);
	int index2 = rand() % (numberOfNodes - 1);
	while (index1 == index2)
	{
		index2 = rand() % (numberOfNodes - 1);
	}
	result[index1] = entity.path[index2];
	result[index2] = entity.path[index1];
	GeneticEntity mutated(result, pathManager.calculateGoal(data, result));
	return mutated;
}


int Genetic::SolveGenetic(dataSet dataFromFile, int populationS, int numberOfG, double mutationR)
{
	this->mutationRate = mutationR;
	this->data = dataFromFile;
	this->populationSize = populationS;
	this->numberOfGenerations = numberOfG;
	this->numberOfNodes = dataFromFile.dataSize;

	// Wyczyszczenie wektorów
	currentPopulation = {};
	sortedOutPopulation = {};

	int noProgress = 0;
	int bestPathCost = INT_MAX;

	// Startowa populacja
	for (int i = 0; i < populationSize; i++)
	{
		// Wygenerowanie losowej œcie¿ki
		std::vector<int> path = GetRandomVector();

		// Utworzenie nowego osobnika
		GeneticEntity entity(path, pathManager.calculateGoal(data, path));

		// Dodanie osobkina do obecnej populacji
		currentPopulation.push(entity);
	}

	// Dla wszystkich generacji
	for (int i = 0; i < numberOfGenerations; i++)
	{
		sortedOutPopulation = {};

		// Wstawenie do tablicy posortowanej
		for (int j = 0; j < populationSize; j++)
		{
			GeneticEntity entity = currentPopulation.top();
			sortedOutPopulation.push_back(entity);
			currentPopulation.pop();
		}

		// Wyzerowanie bo mamy najlepsze, a resztê trzeba zapomnieæ
		currentPopulation = {}; 

		// Selekcja - na podstawie funkcji celu
		for (int j = 0; j < populationSize; j += 2)
		{
			{
				// Pobieranie parami
				GeneticPair parents = { sortedOutPopulation[j], sortedOutPopulation[j + 1] };

				// Krosowanie
				GeneticPair children = CrossPx(parents);
				//GeneticPair children = CrossOx(parents);

				// Mutacja jednego dziecka 
				double probablility = (rand() % 1000) / 1000;
				if (probablility < this->mutationRate)
				{
					children.firstEntity = EntityMutation(children.firstEntity);
				}

				currentPopulation.push(parents.firstEntity);
				currentPopulation.push(parents.secondEntity);
				currentPopulation.push(children.firstEntity);
				currentPopulation.push(children.secondEntity);
			}

		}

		// Aktualizacja najlepszej œcie¿ki
		if (currentPopulation.top().pathCost < bestPathCost)
		{
			bestPath = currentPopulation.top().path;
			bestPathCost = currentPopulation.top().pathCost;
		}

	}

	return bestPathCost;
}