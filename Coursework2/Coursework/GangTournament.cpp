#include "GangTournament.h"
#include "GangGame.h"


GangTournament::GangTournament(vector<string> files) : Tournament(files)
{
}


GangTournament::~GangTournament()
{
}

void GangTournament::runTournament()
{
	for (int i = 0; i < filenames.size(); ++i)
	{
		GangGame * game = new GangGame(filenames[i], filenames);

		game->run(200);

		vector<int> game_results = game->getResults();

		cout << "Game " << i << "\n";

		cout << "GangA:\t";
		cout << game_results[0] << " years\t";

		cout << "GangB:\t";
		cout << game_results[1] << " years\n\n\n";

		delete game;

	}
}

