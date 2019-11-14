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

using namespace std;


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
	cout << "6. Branch and bound (gorne ograniczenie wprowadzane recznie)" << endl << endl << endl;

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
		result= bruteForce.calculateBruteForce(data, nodes);
		cout << "Broute force - wynik: " << result << endl << endl;
		break;

	case 3:
		resultBnb = bruteForceTree.calculateBranchAndBound(data, nodes);
		cout << "Brute force - wynik: " << resultBnb.pathCost << endl << endl;
		break;

	case 4:
		resultBnb = branchAndBound.calculateBranchAndBound(data, nodes, 0);
		cout << "Branch and bound - wynik: " << resultBnb.pathCost << endl << endl;
		break;
	case 5:
		resultBnb = branchAndBound.calculateBranchAndBound(data, nodes, 1);
		cout << "Branch and bound - wynik: " << resultBnb.pathCost << endl << endl;
		break;

	case 6:
		cout << endl << "Wprowadz gorne ograniczenie: ";
		cin >> upperBound;
		cout << endl << endl;
		resultBnb = branchAndBound.calculateBranchAndBound(data, nodes, upperBound);
		cout << "Branch and bound - wynik: " << resultBnb.pathCost << endl << endl;
		break;

	}

	
	return 0;
}
