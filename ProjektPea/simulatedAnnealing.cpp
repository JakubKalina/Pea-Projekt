#include "pch.h"
#include "simulatedAnnealing.h"


simulatedAnnealing::simulatedAnnealing(dataSet data, std::vector<int> nodes, float initialTemperature, float finalTemperature, float coolingTemperature, int numberOfIterations)
{
	this->data = data;
	this->nodes = nodes;
	this->initialTemperature = initialTemperature;
	this->finalTemperature = finalTemperature;
	this->coolingTemperature = coolingTemperature;
	this->numberOfIterations = numberOfIterations;

}

simulatedAnnealing::simulatedAnnealing(dataSet data, std::vector<int> nodes)
{
	this->initialTemperature = 100000.0f;
	this->finalTemperature = 0.0001f;
	this->coolingTemperature = 0.9999f;
	this->data = data;
	this->nodes = nodes;
	this->numberOfIterations = (int)pow(nodes.size(), 2)/4;
}


simulatedAnnealing::~simulatedAnnealing()
{
}

int simulatedAnnealing::calculateSimulatedAnnealing()
{

}

// Wyliczenie prawdopodobieñstwa
float simulatedAnnealing::countProbability()
{
	double calculatedPower = ((currentPathResult - bestPathResult) / currentTemerature);
	return pow(exp(1.0), calculatedPower);
}

void simulatedAnnealing::mixPath()
{

}


