#include "pch.h"
#include "fileManager.h"
#include "dataSet.h"
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


fileManager::fileManager()
{
}


fileManager::~fileManager()
{
}

// Wczytanie problemu z pliku tekstowego
dataSet fileManager::readDataFromFile(std::string fileName)
{

	std::ifstream file;
	file.open(fileName.c_str());
	if (file.good()) {
		dataSet *set = new dataSet();
		// Wczytanie nazwy zbioru danych
		file >> set->name;

		// Wczytanie rozmiaru problemu
		file >> set->dataSize;

		// Utworzenie pustej tablicy na dane
		set->data = new int *[set->dataSize];
		for (int i = 0; i < set->dataSize; i++)
			set->data[i] = new int[set->dataSize];

		// Pêtla po tablicy z odleg³oœciami miast - czytanie po wierszach
		for (int i = 0; i < set->dataSize; i++)
		{
			// Czytanie po kolumnach
			for (int j = 0; j < set->dataSize; j++)
			{
				file >> set->data[i][j];
			}
		}
		return *set;
	}
}