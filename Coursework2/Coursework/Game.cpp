#include "Game.h"
#include <iostream>
#include <string>
#include <time.h>

Game::Game() 
{
}

Game::Game(string fileA, string fileB) {
	// Create a game with 2 prisoners which get assigned the provided strategies given
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


Game::~Game() 
{	// clear up memory and terminate the trees
	delete A, B;
	A = nullptr;
	B = nullptr;

	if (stratA) { stratA->terminate(); }
	if (stratB) { stratB->terminate(); }
	

	delete stratA;
	delete stratB;
	stratA = nullptr;
	stratB = nullptr;
}

void Game::run(int iterations) 
{	// Runs the game with a given number of iterations
	for (int i = 0; i < iterations; i++) 
	{
		find_outcome(i);
	}

	totalResults = new Matrix<int>(5, 2);

	totalResults->set_element(0, 0, A->get_allw());
	totalResults->set_element(1, 0, A->get_allx());
	totalResults->set_element(2, 0, A->get_ally());
	totalResults->set_element(3, 0, A->get_allz());
	totalResults->set_element(4, 0, A->get_score());
	totalResults->set_element(0, 1, B->get_allw());
	totalResults->set_element(1, 1, B->get_allx());
	totalResults->set_element(2, 1, B->get_ally());
	totalResults->set_element(3, 1, B->get_allz());
	totalResults->set_element(4, 1, B->get_score());
}

void Game::find_outcome(int iteration)
{	// Find the decision each prisnoer makes and determine the outcome and their sentence according to this
	Decision resultA = A->get_decision(iteration);
	Decision resultB = B->get_decision(iteration);

	if (resultA == Decision::SILENCE && resultB == Decision::SILENCE) {
		A->sentence(Prisoner::W);
		B->sentence(Prisoner::W);
	}
	else if (resultA == Decision::SILENCE && resultB == Decision::BETRAY) {
		A->sentence(Prisoner::X);
		B->sentence(Prisoner::Y);
	}
	else if (resultA == Decision::BETRAY && resultB == Decision::SILENCE) {
		A->sentence(Prisoner::Y);
		B->sentence(Prisoner::X);
	}
	else if (resultA == Decision::BETRAY && resultB == Decision::BETRAY) {
		A->sentence(Prisoner::Z);
		B->sentence(Prisoner::Z);
	}
}


Matrix<int> * Game::getResults()
{
	return totalResults;
}

