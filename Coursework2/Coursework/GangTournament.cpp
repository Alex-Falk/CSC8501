#include "GangTournament.h"
#include "GangGame.h"
#include "Gang.h"


GangTournament::GangTournament(vector<string> files, char leaderchoice) : Tournament(files), leaderChoice(leaderchoice)
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

		method mthd = method::RANDOM;
		switch (leaderChoice)
		{
		case 'A':
			mthd == method::CUSTOM;
		case 'B':
			mthd == method::SWAP;
		case 'C':
			mthd == method::STAY;
		case 'D':
			mthd == method::RANDOM;
		}

		game->run(200,mthd);

		vector<int> game_results = game->getResults();

		cout << "Game " << i << "\n";

		cout << "GangA:\t";
		cout << game_results[0] << " years\t";

		cout << "GangB:\t";
		cout << game_results[1] << " years\n\n\n";

		delete game;

	}
}

