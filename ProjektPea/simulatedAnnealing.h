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
#define _USE_MATH_DEFINES

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
	int currentPathResult;
	float currentTemerature;
	std::vector<int> nodes;
	float initialTemperature;
	float finalTemperature;
	float coolingTemperature;
	int numberOfIterations;
	float countProbability();
	void mixPath();
};

