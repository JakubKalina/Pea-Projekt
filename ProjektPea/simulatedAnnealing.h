#pragma once
#include "dataSet.h"
#include "pathManager.h"
#include <vector>
#include <math.h>

class simulatedAnnealing
{
public:
	simulatedAnnealing(dataSet data, std::vector<int> nodes, float initialTemperature, float finalTemperature, float coolingTemperature, int numberOfIterations);
	simulatedAnnealing(dataSet data, std::vector<int> nodes);
	int calculateSimulatedAnnealing();
	~simulatedAnnealing();
	int bestPathResult;
	std::vector<int> bestPath;
private:
	dataSet data;
	std::vector<int> nodes;
	float initialTemperature;
	float finalTemperature;
	float coolingTemperature;
	int numberOfIterations;
	float countProbability();
	void mixPath();
};

