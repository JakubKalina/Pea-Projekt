#include "pch.h"
#include "dynamicProgramming.h"


dynamicProgramming::dynamicProgramming()
{
}

dynamicProgramming::~dynamicProgramming()
{
}


int dynamicProgramming::calculateDynamicProgramming(dataSet data, std::vector<int> nodes)
{
	int weight = INT_MAX;
	//data = data.data;
	masks = new int *[nodes.size()];

	// Wype³nienie tablicy najwiêkszymi maskami
	for (int i = 0; i < nodes.size(); i++)
	{
		//masks[i] = new int[(1 << nodes.size()) - 1];
	}

	// Wype³nienie tablicy kosztów
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < ((1 << nodes.size()) - 1); j++)
		{
			masks[i][j] = weight;
		}
	}



	return 0;
}


int dynamicProgramming::calculateInternalPath(int number, int node, int size)
{
	// Jeœli ......... zwróæ drogê z punktu ostatniego do pocz¹tkowego czyli 0
	if (node == ((1 << size) - 1))
	{
		return data[number][0];
	}

	// Jeœli ten punkt zosta³ ju¿ odwiedzony to zwróæ wagê
	if (masks[number][node] < INT_MAX)
	{
		return masks[number][node];
	}

	// Jeœli nie zosta³ jeszcze odwiedzony
	for (int i = 0; i < size; i++)
	{
		if ( ( i == number) || ( node & ( 1 << i ) ) )
		{
			continue;
		}

		int d = calculateInternalPath(i, (node | (1 << i)) , size);
	}

	return masks[number][node];

}
