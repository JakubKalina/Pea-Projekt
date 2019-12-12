#include "pch.h"
#include "simulatedAnnealing.h"


simulatedAnnealing::simulatedAnnealing()
{

}

simulatedAnnealing::~simulatedAnnealing()
{
}

// Wyliczenie algorytmu
int simulatedAnnealing::calculateSimulatedAnnealing(dataSet data, std::vector<int> nodes, float initialTemperature, float finalTemperature, float coolingTemperature, int numberOfIterations, int coolingOption, int shufflePath)
{
	//Mieszanie wektora œcie¿ki
	if (shufflePath == 2)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine e(seed);
		std::shuffle(nodes.begin(), nodes.end(), e);
	}
	else if (shufflePath == 3) // Algorytm zach³anny
	{
		for (int i = 1; i < nodes.size() - 1; i++)
		{
			int nearest = i;
			for (int j = nearest + 1; j < nodes.size(); j++)
			{
				if (data.data[i][j] < data.data[i][nearest])
				{
					nearest = j;
				}

				std::swap(nodes[i + 1], nodes[nearest]);
			}
		}
	}

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

	// Do czasu ostygniêcia
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

		// Wych³adzanie
		if (coolingOption == 1)
		{
			currentTemerature *= coolingTemperature;
		}
		else if (coolingOption == 2)
		{
			currentTemerature -= coolingTemperature;
		}
		else if (coolingOption == 3)
		{
			currentTemerature = (log(currentTemerature) / log(coolingTemperature));
		}
	}

	return bestPathResult;
}

// Wyliczenie prawdopodobieñstwa
float simulatedAnnealing::countProbability()
{
	double calculatedPower = ((bestPathResult - currentPathResult) / currentTemerature);
	return exp(calculatedPower);
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


