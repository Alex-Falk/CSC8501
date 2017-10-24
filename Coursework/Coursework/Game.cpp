#include "Game.h"
#include <iostream>
#include <string>
#include <time.h>

Game::Game(string fileA, string fileB) {
	A = new Prisoner();
	B = new Prisoner();

	stratA = new Strategy();
	stratB = new Strategy();

	stratA->read(fileA);

	try {
		stratA->interpret();
	}
	catch (const runtime_error& rte) {
		cout << "Error interpreting file " << stratA->getFile() << " " << rte.what();
		stratA->terminate();
		delete stratA;
		stratA = nullptr;
	}

	stratB->read(fileB);
	try {
		stratB->interpret();
	}
	catch (const runtime_error& rte) {
		cout << "Error interpreting file " << stratB->getFile() << " " << rte.what();
		stratB->terminate();
		delete stratB;
		stratB = nullptr;
	}

	if (stratA && stratB) {
		A->set_strategy(stratA);
		B->set_strategy(stratB);
	}
}


Game::~Game() {
	delete A, B;
	A = nullptr;
	B = nullptr;

	stratA->terminate();
	stratB->terminate();

	delete stratA;
	delete stratB;
	stratA = nullptr;
	stratB = nullptr;
}

void Game::run(int iterations) {
	for (int i = 0; i < iterations; i++) {

		find_outcome(i);

	}

	cout << "A: w:" << A->get_allw() << " x:" << A->get_allx() << " y:" << A->get_ally() << " z:" << A->get_allz() << " score:" << A->get_score() << "\n";
	cout << "B: w:" << B->get_allw() << " x:" << B->get_allx() << " y:" << B->get_ally() << " z:" << B->get_allz() << " score:" << B->get_score() << "\n";

	totalresults.push_back(A->get_score());
	totalresults.push_back(B->get_score());

}

void Game::find_outcome(int iteration)
{
	Decision resultA = A->get_decision(iteration);
	Decision resultB = B->get_decision(iteration);
	//cout << "A: " << resultA << "\n";
	//cout << "B: " << resultB << "\n";

	if (resultA == Decision::SILENCE && resultB == Decision::SILENCE) {
		A->sentence(W);
		B->sentence(W);
	}
	else if (resultA == Decision::SILENCE && resultB == Decision::BETRAY) {
		A->sentence(X);
		B->sentence(Y);
	}
	else if (resultA == Decision::BETRAY && resultB == Decision::SILENCE) {
		A->sentence(Y);
		B->sentence(X);
	}
	else if (resultA == Decision::BETRAY && resultB == Decision::BETRAY) {
		A->sentence(Z);
		B->sentence(Z);
	}
}


vector<int> Game::getResults() {
	return totalresults;
}

