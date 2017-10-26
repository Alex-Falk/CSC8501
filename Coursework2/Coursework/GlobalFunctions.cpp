#include "GlobalFunctions.h"

// Takes a string that has 5 strategy names separated by a space
// TODO: Make this work for x amount of strategies
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
