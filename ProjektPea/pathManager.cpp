#include "pch.h"
#include "pathManager.h"


pathManager::pathManager()
{
}


pathManager::~pathManager()
{
}

// Wylicza koszt cyklu
int pathManager::calculateGoal(dataSet data, std::vector<int> nodes)
{
	int rozm = nodes.size();
	int totalWeight = data.data[nodes[nodes.size() - 1]][nodes[0]];

	for (int i = 0; i < nodes.size() - 1; i++)
	{
		int z = nodes[i];
		int doz = nodes[i + 1];
		int tmp = data.data[nodes[i]][nodes[i + 1]];
		totalWeight += data.data[nodes[i]][nodes[i + 1]];
	}

	return totalWeight;
}

// Zwraca wektor z numerami punktów
std::vector<int> pathManager::getVector(int size)
{
	std::vector<int> result;
	for (int i = 0; i < size; i++)
		result.push_back(i);
	return result;
}