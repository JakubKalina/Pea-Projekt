#pragma once
#include "dataSet.h"
#include "pathManager.h"
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

class Genetic
{
public:

	// Zestaw danych wej�ciowych
	dataSet data;

	// Liczba miast
	int numberOfNodes;

	// Rozmiar populacji
	int populationSize;

	// Ilo�� generacji
	int numberOfGenerations;

	// Wsp�czynnik ilo�ci mutacji
	double mutationRate;

	// Najlepsza �cie�ka
	std::vector<int> bestPath;

	// Wynik
	int result;

	// Warunek sortowania kolejki priorytetowej
	struct CompareGeneticCosts
	{
		bool operator() (const GeneticEntity& fitstEntity, const GeneticEntity& secondEntity)
		{
			if (fitstEntity.pathCost > secondEntity.pathCost)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};

	// Posortowana populacja
	std::vector<GeneticEntity> sortedOutPopulation;

	// Aktualna populacja
	std::priority_queue<GeneticEntity, std::vector<GeneticEntity>, CompareGeneticCosts> currentPopulation;

	// Klasa pomocnicza do liczenia d�ugo�ci �cie�ek
	pathManager pathManager;

	// Metoda rozpoczynaj�ca dzia�anie algorytmu
	int SolveGenetic(dataSet dataFromFile, int populationSize, int numberOfGenerations, double mutationRate);

	// Zwraca losowo wygenerowany wektor
	std::vector<int> GetRandomVector();

	// Sprawdza czy w�ze� znajduje si� ju� w �cie�ce
	bool VectorContainsNode(int* path, int node);
	
	// Meroda krosuj�ca algorytmem OX
	GeneticPair CrossOx(GeneticPair pair);

	// Metoda krosuj�ca algorytmem PX
	GeneticPair CrossPx(GeneticPair pair);

	// Sprawdzenie czy �cie�ka jest w�a�ciwa
	bool CheckIfProper(std::vector<int> vector);

	// Dokonanie mutacji elementu
	GeneticEntity EntityMutation(GeneticEntity entity);

	Genetic();
	~Genetic();
};

