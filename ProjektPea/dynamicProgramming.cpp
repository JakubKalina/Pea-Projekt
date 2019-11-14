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

	// Wype�nienie tablicy najwi�kszymi maskami
	for (int i = 0; i < nodes.size(); i++)
	{
		//masks[i] = new int[(1 << nodes.size()) - 1];
	}

	// Wype�nienie tablicy koszt�w
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
	// Je�li ......... zwr�� drog� z punktu ostatniego do pocz�tkowego czyli 0
	if (node == ((1 << size) - 1))
	{
		return data[number][0];
	}

	// Je�li ten punkt zosta� ju� odwiedzony to zwr�� wag�
	if (masks[number][node] < INT_MAX)
	{
		return masks[number][node];
	}

	// Je�li nie zosta� jeszcze odwiedzony
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
