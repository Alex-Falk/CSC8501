#include "GlobalFunctions.h"

string shortenStrategyList(string strats)
{
	string result = "";

	string strategy;
	string subcombination = strats;

	for (int j = 0; j < 5; ++j)
	{
		strategy = subcombination.substr(0, subcombination.find_first_of(" "));
		subcombination = subcombination.substr(subcombination.find_first_of(" ") + 1);

		int first_nr_idx = strategy.find_first_of("0123456789");
		result = result + strategy.substr(first_nr_idx, strategy.size() - first_nr_idx - 4);
		if (j != 4) { result = result + " "; }
	}

	return result;
}

string shortenStrategyName(string strat)
{
	string result;
	int first_nr_idx = strat.find_first_of("0123456789");
	result = strat.substr(first_nr_idx, strat.size() - first_nr_idx - 4);
	return result;

}
