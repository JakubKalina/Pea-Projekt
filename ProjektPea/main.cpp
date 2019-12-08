// ProjektPea.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

#include "pch.h"
#include "bruteForce.h"
#include "dataSet.h"
#include "fileManager.h"
#include "pathManager.h"
#include "branchAndBoundStruct.h"
#include "branchAndBound.h"
#include "bruteForceTree.h"
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
	bruteForce bruteForce;
	bruteForceTree bruteForceTree;
	branchAndBound branchAndBound;
	branchAndBoundStruct resultBnb;
	auto rng = std::default_random_engine{};


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
	cout << "7. Symulowane wyżarzanie (parametry domyślne)" << endl;
	cout << "8. Symulowane wyżarzanie (parametry wprowadzane przez użytkownika)" << endl << endl << endl;

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

	//
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
		start = clock();

	//	cout << "Symulowane wyzarzanie - wynik: " << << endl;

		finish = clock();

		PrintCalculationTime(start, finish);

		break;

	case 8:

		start = clock();

		cout << endl << "Wprowadz parametry algorytmu " <<endl << endl;

		float initialTemperature;
		float finalTemperature;
		float coolingTemperature;

		cout << "Temperatura startowa: ";
		cin >> initialTemperature;
		cout << "Temperatura końcowa: ";
		cin >> finalTemperature;
		cout << "Temperatura chłodzenia: ";
		cin >> coolingTemperature;


	//	cout << "Symulowane wyzarzanie - wynik: " << << endl;

		finish = clock();

		PrintCalculationTime(start, finish);

		break;

	}

	
	return 0;
}


