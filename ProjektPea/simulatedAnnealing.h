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
#include <chrono>       
#define _USE_MATH_DEFINES

class simulatedAnnealing
{
public:
	simulatedAnnealing();
	int calculateSimulatedAnnealing(dataSet data, std::vector<int> nodes, float initialTemperature, float finalTemperature, float coolingTemperature, int numberOfIterations, int coolingOption, int shufflePath);
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
	std::vector<int> mixPath(std::vector<int> nodesVector);
};

