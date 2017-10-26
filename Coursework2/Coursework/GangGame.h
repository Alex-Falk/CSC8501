#pragma once
#include "Game.h"
#include "Matrix.h"

enum class Decision;
class Gang;
enum method;

class GangGame :
	public Game
{
public:
	GangGame(string combinationA, string combinationB);
	GangGame(string givenstrat, vector<string> strategies);
	~GangGame();
	void find_outcome(int iteration);						// Finds both the decisions of the prisoners for given iteration and sentences them accordingly.
	void run(int iterations,int nrspygames,method mthd);	// Runs the game with a given amount of iterations. It will take the filenames given in instatiation to use as strategies.
	bool spyGame(bool spy_A, bool spy_B, method mthd);
	Gang * getGangA();
	Gang * getgangB();
	vector<int> get_spyResults();
protected:
	int iteration;
	Gang * gangA;
	Gang * gangB;
	vector<int> spyResults;									// GangA: nr_with_spy nr_found_swap nr_found_stay nr_not_found nr_found_both GangB: nr_with_spy nr_found_swap nr_found_stay nr_not_found nr_found_both
};

