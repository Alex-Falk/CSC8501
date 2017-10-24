#pragma once
#include "Game.h"

enum class Decision;

class GangGame :
	public Game
{
public:
	GangGame(string fileA, string fileB, string fileC, string fileD, string fileE);
	~GangGame();
	void find_outcome(int iteration);				// Finds both the decisions of the prisoners for given iteration and sentences them accordingly.
	void run(int iterations);						// Runs the game with a given amount of iterations. It will take the filenames given in instatiation to use as strategies.
	vector<int> getResults();						// Returns the total sentences for each prisoner for this given game. 0 - Prisoner A, 1 - Prisoner B
protected:
	int iteration;
	Gang * gangA;
	Gang * gangB;
	vector<int> totalresults;
};

