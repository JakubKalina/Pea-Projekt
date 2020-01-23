// ProjektPea.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

#include "pch.h"
#include "bruteForce.h"
#include "dataSet.h"
#include "fileManager.h"
#include "pathManager.h"
#include "branchAndBoundStruct.h"
#include "branchAndBound.h"
#include "bruteForceTree.h"
#include "simulatedAnnealing.h"
#include "Genetic.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>>

using namespace std;


// Funkcja wypisująca w konsoli czas działania algorytmu
void PrintCalculationTime(clock_t startTime, clock_t finishTime)
{
	double result = ((finishTime - startTime) / (double)CLOCKS_PER_SEC);
	cout << endl << "Czas wykonywania algorytmu to: " << result << endl;
}

int main()
{
	fileManager fileManager;
	pathManager pathManager;
	int result = 0;
	int upperBound;
	int coolingOption;
	int shufflePath;
	bruteForce bruteForce;
	bruteForceTree bruteForceTree;
	branchAndBound branchAndBound;
	simulatedAnnealing* simulatedAnnealingObject;
	branchAndBoundStruct resultBnb;
	Genetic geneticAlgorithm;
	auto rng = std::default_random_engine{};
	int numberOfNodes;
	int populationSize;
	int numberOfGenerations;
	double mutationRate;

	float sumResults = 0;
	int minResult = INT_MAX;

	// Wyświetlane menu
	cout << "Wybierz jeden z dostepnych algorytmow: \n\n";
	cout << "--------------------------------------------" << endl << endl;
	cout << "0. Liczenie funkcji celu dla permutacji losowej" << endl;
	cout << "1. Liczenie funkcji celu dla premutacji wprowadzonej recznie" << endl;
	cout << "2. Brute force (z uzyciem next permutation)" << endl;
	cout << "3. Brute force (bez uzycia next permutation)" << endl;
	cout << "4. Branch and bound (gorne ograniczenie liczone z pierwszej sciezki)" << endl;
	cout << "5. Branch and bound (gorne ograniczenie losowane)" << endl;
	cout << "6. Branch and bound (gorne ograniczenie wprowadzane recznie)" << endl;
	cout << "7. Symulowane wyzarzanie (parametry domyslne)" << endl;
	cout << "8. Symulowane wyzarzanie (parametry wprowadzane przez uzytkownika)" << endl;
	cout << "9. Algorytm genetyczny" << endl << endl << endl;

	// Opcja wybrana przez użytkownika
	int option;
	cout << "Wybrana opcja: ";
	cin >> option;

	// Nazwa pliku z problemem
	string fileName;
	cout << "Podaj nazwe pliku z problemem do wczytania: ";
	cin >> fileName;

	// Dane wczytane z pliku
	dataSet data = fileManager.readDataFromFile(fileName);

	// Przykładowy wektor ( permutacja 0, 1, ... rozmiar problemu - 1 )
	vector<int> nodes = pathManager.getVector(data.dataSize);

	// Zmienne przechowujące czasy rozpoczęcia i zakończenia pomiaru
	clock_t start, finish;


	switch (option)
	{
	case 0:
		std::shuffle(std::begin(nodes), std::end(nodes), rng);
		result = pathManager.calculateGoal(data, nodes);
		cout << "Funkcja celu - wynik : " << result << endl << endl << endl;
		break;

	case 1:

		for (int i = 0; i < data.dataSize; i++)
		{
			int node;
			cout << "Podaj punkt o indeksie " << i << " :";
			cin >> node;
			cout << endl;
			nodes[i] = node;
		}
		result = pathManager.calculateGoal(data, nodes);
		cout << "Funkcja celu - wynik : " << result << endl << endl << endl;


		break;

	case 2:
		start = clock();

		result= bruteForce.calculateBruteForce(data, nodes);
		cout << "Broute force - wynik: " << result << endl << endl;

		finish = clock();

		PrintCalculationTime(start, finish);

		break;

	case 3:
		start = clock();


		resultBnb = bruteForceTree.calculateBranchAndBound(data, nodes);
		cout << "Brute force - wynik: " << resultBnb.pathCost << endl << endl;

		finish = clock();

		PrintCalculationTime(start, finish);


		break;

	case 4:
		start = clock();


		resultBnb = branchAndBound.calculateBranchAndBound(data, nodes, 0);
		cout << "Branch and bound - wynik: " << resultBnb.pathCost << endl << endl;

		finish = clock();

		PrintCalculationTime(start, finish);



		break;
	case 5:
		start = clock();


		resultBnb = branchAndBound.calculateBranchAndBound(data, nodes, 1);
		cout << "Branch and bound - wynik: " << resultBnb.pathCost << endl << endl;

		finish = clock();

		PrintCalculationTime(start, finish);


		break;

	case 6:
		start = clock();


		cout << endl << "Wprowadz gorne ograniczenie: ";
		cin >> upperBound;
		cout << endl << endl;
		resultBnb = branchAndBound.calculateBranchAndBound(data, nodes, upperBound);
		cout << "Branch and bound - wynik: " << resultBnb.pathCost << endl << endl;

		finish = clock();

		PrintCalculationTime(start, finish);

		break;

	case 7:

		cout << endl << "Wybierz rodzaj chlodzenia: " << endl;
		cout << "1. Geometryczne" << endl;
		cout << "2. Liniowe" << endl;
		cout << "3. Logarytmiczne" << endl;
		cout << "Wybor: ";
		cin >> coolingOption;

		cout << endl << endl << "Sciezka poczatkowa: " << endl;
		cout << "1. Naturalna" << endl;
		cout << "2. Losowa" << endl;
		cout << "3. Algorytm zachlanny" << endl;
		cin >> shufflePath;

		start = clock();

		simulatedAnnealingObject = new simulatedAnnealing();
		result = simulatedAnnealingObject->calculateSimulatedAnnealing(data, nodes, 20.0, 0.01, 0.99, (int)(pow(nodes.size(), 2) / 4), coolingOption, shufflePath);
		cout << "Symulowane wyzarzanie - wynik: " << result << endl;

		finish = clock();

		PrintCalculationTime(start, finish);
		
		break;

	case 8:

		cout << endl << "Wprowadz parametry algorytmu " <<endl << endl;

		float initialTemperature;
		float finalTemperature;
		float coolingTemperature;
		int numberOfIterations;

		cout << "Temperatura startowa (float): ";
		cin >> initialTemperature;
		cout << "Temperatura koncowa (float): ";
		cin >> finalTemperature;
		cout << "Temperatura chlodzenia (float): ";
		cin >> coolingTemperature;
		cout << "Liczba przejsc: ";
		cin >> numberOfIterations;

		cout << endl << "Wybierz rodzaj chlodzenia: " << endl;
		cout << "1. Geometryczne" << endl;
		cout << "2. Liniowe" << endl;
		cout << "3. Logarytmiczne" << endl;
		cout << "Wybor: ";
		cin >> coolingOption;

		cout << endl << endl << "Sciezka poczatkowa: " << endl;
		cout << "1. Naturalna" << endl;
		cout << "2. Losowa" << endl;
		cout << "3. Algorytm zachlanny" << endl;
		cin >> shufflePath;

		start = clock();

			simulatedAnnealingObject = new simulatedAnnealing();

			result = simulatedAnnealingObject->calculateSimulatedAnnealing(data, nodes, initialTemperature, finalTemperature, coolingTemperature, numberOfIterations, coolingOption, shufflePath);


			//cout << "Wynik: " << result << endl;
		
		cout << "Symulowane wyzarzanie - wynik: " << result << endl;
		//cout << "SA - srednia: " << (sumResults/3) << endl;
		//cout << "SA - min wynik: " << minResult << endl;

		finish = clock();

		PrintCalculationTime(start, finish);

		break;

	// Algorytm genetyczny
	case 9:

		cout << "Rozmiar populacji: ";
		cin >> populationSize;
		cout << "Ilosc generacji: ";
		cin >> numberOfGenerations;
		cout << "Procent mutacji: ";
		cin >> mutationRate;

		start = clock();

		result = geneticAlgorithm.SolveGenetic(data, populationSize, numberOfGenerations, mutationRate);
		cout << "Algorytm genetyczny - wynik: " << result << endl;

		finish = clock();

		PrintCalculationTime(start, finish);

		break;

	}

	
	return 0;
}


