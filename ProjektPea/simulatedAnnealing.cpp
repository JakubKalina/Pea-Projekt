#include "pch.h"
#include "simulatedAnnealing.h"


simulatedAnnealing::simulatedAnnealing(dataSet data, std::vector<int> nodes, float initialTemperature, float finalTemperature, float coolingTemperature, int numberOfIterations)
{


}

simulatedAnnealing::simulatedAnnealing(dataSet data, std::vector<int> nodes)
{

}

simulatedAnnealing::~simulatedAnnealing()
{
}

// Wyliczenie algorytmu
int simulatedAnnealing::calculateSimulatedAnnealing(dataSet data, std::vector<int> nodes, float initialTemperature, float finalTemperature, float coolingTemperature, int numberOfIterations)
{
	srand((unsigned int)time(NULL));
	pathManager pathManager;
	this->data = data;
	this->nodes = nodes;
	this->currentTemerature = initialTemperature;
	this->finalTemperature = finalTemperature;
	this->coolingTemperature = coolingTemperature;
	this->numberOfIterations = numberOfIterations;
	bestPath = nodes;
	currentPathResult = pathManager.calculateGoal(data, nodes);
	bestPathResult = currentPathResult;
	srand((unsigned int)time(NULL));

	while (currentTemerature > finalTemperature)
	{
		for (int i = 0; i < numberOfIterations; i++)
		{
			nodes = mixPath(nodes);
			currentPathResult = pathManager.calculateGoal(data, nodes);

			if (currentPathResult < bestPathResult || ((float)rand() / (float)RAND_MAX) < countProbability())
			{
				bestPath = nodes;
				bestPathResult = currentPathResult;
			}
		}
		currentTemerature *= coolingTemperature;
	}

	return bestPathResult;
}

// Wyliczenie prawdopodobieñstwa
float simulatedAnnealing::countProbability()
{
	double calculatedPower = ((currentPathResult - bestPathResult) / currentTemerature);
	return pow(exp(1.0), calculatedPower);
}

// Wymieszanie œcie¿ki
std::vector<int> simulatedAnnealing::mixPath(std::vector<int> nodesVector)
{
	int firstIndex = std::rand() % nodes.size();
	int secondIndex = std::rand() % nodes.size();

	// Zapobieganie powtarzaj¹cym siê indeksom
	while (firstIndex == secondIndex)
	{
		secondIndex = std::rand() % nodes.size();
	}

	nodes = bestPath;
	int tmp = nodes[firstIndex];
	nodes[firstIndex] = nodes[secondIndex];
	nodes[secondIndex] = tmp;
	return nodes;
}


