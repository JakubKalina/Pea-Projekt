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

	// Zestaw danych wejœciowych
	dataSet data;

	// Liczba miast
	int numberOfNodes;

	// Rozmiar populacji
	int populationSize;

	// Iloœæ generacji
	int numberOfGenerations;

	// Wspó³czynnik iloœci mutacji
	double mutationRate;

	// Najlepsza œcie¿ka
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

	// Klasa pomocnicza do liczenia d³ugoœci œcie¿ek
	pathManager pathManager;

	// Metoda rozpoczynaj¹ca dzia³anie algorytmu
	int SolveGenetic(dataSet dataFromFile, int populationSize, int numberOfGenerations, double mutationRate);

	// Zwraca losowo wygenerowany wektor
	std::vector<int> GetRandomVector();

	// Sprawdza czy wêze³ znajduje siê ju¿ w œcie¿ce
	bool VectorContainsNode(int* path, int node);
	
	// Meroda krosuj¹ca algorytmem OX
	GeneticPair CrossOx(GeneticPair pair);

	// Metoda krosuj¹ca algorytmem PX
	GeneticPair CrossPx(GeneticPair pair);

	// Sprawdzenie czy œcie¿ka jest w³aœciwa
	bool CheckIfProper(std::vector<int> vector);

	// Dokonanie mutacji elementu
	GeneticEntity EntityMutation(GeneticEntity entity);

	Genetic();
	~Genetic();
};

