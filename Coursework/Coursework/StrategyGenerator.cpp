#include "StrategyGenerator.h"
#include <fstream>
#include <time.h>

StrategyGenerator::StrategyGenerator()
{
}


StrategyGenerator::~StrategyGenerator() {
	//terminate_tree(&root);
}


void StrategyGenerator::generateStrategy(int lines, string file) {
	// A BETRAY,SILENCE or RANDOM must be accessable through a previous line or an if statement
	cout << "Generating Strategy for file: " << file << "\n";
	if (root) { 
		terminate_tree(&root); 
		all_lines.clear();
	}
	root = nullptr;
	generateLine(&root, 0, lines);

	toFile(file, lines);
}


void StrategyGenerator::toFile(string file, int lines) {
	ofstream outFile;
	outFile.open(file);

	for (int i = 0; i < lines; ++i) {
		if (all_lines[i] != "") {
			outFile << all_lines[i] << "\n";
		}
	}

	outFile.close();
}


void StrategyGenerator::generateLine(line ** tree, int lineno, int lines) 
{	//Generates the Binary Tree which stores the lines and logic of the generated strategy. 

	all_lines.resize(lines);

	if (all_lines[lineno] == "") 
	{
		int randomCmd;

		if (lineno == 0) { randomCmd = 0; }										// If on first line - Pick if statement
		else if (lineno < lines - 2)											// If between first and third to last line, randomly choose the command.
		{													
			int randomChoice = rand() % 4;
			if (randomChoice == 0) { randomCmd = 0; }
			else { randomCmd = 1 + (rand() % 3); }
		}
		else { randomCmd = 1 + (rand() % 3); }									// If we are on the last or second last line, don't create if statement

		string cmd = commands[randomCmd];

		if (!(*tree)) {
			*tree = new line;
			(*tree)->lineno = lineno;
		}

		if (cmd == "IF") 
		{
			string statement = to_string(lineno) + " " + generateIf();
			int gotoline = lineno+2 + (rand() % (lines-lineno-2));
			statement.append("GOTO " + to_string(gotoline));

			(*tree)->command = statement;
			(*tree)->next = new line;
			(*tree)->jump = new line;

			(*tree)->next->lineno = lineno + 1;
			(*tree)->jump->lineno = gotoline;

			all_lines[lineno] = statement;

			generateLine(&((*tree)->next), lineno + 1, lines);
			generateLine(&((*tree)->jump), gotoline, lines);
		}
		else if (cmd == "BETRAY" || cmd == "SILENCE" || cmd == "RANDOM") 
		{
			(*tree)->command = to_string(lineno) + " " + cmd;
			(*tree)->next = nullptr;
			(*tree)->jump = nullptr;

			all_lines[lineno] = (*tree)->command;
		}
	}
	else 
	{
		(*tree)->command = all_lines[lineno];
		(*tree)->next = nullptr;
		(*tree)->jump = nullptr;

	}
}


string StrategyGenerator::generateIf() 
{
	string line = "IF ";
	int randomChoice = rand() % 2;

	if (randomChoice == 0)														// Choose nrvariables
	{ 
		string randomVar = nrvars[rand() % 7];
		string randomOp = comparisonOps[rand() % 3];
		string randomVar2 = nrvars[rand() % 7];

		if (randomVar == "NUMBER") { randomVar = to_string(rand() % 201); }
		if (randomVar2 == "NUMBER") { randomVar2 = to_string(rand() % 201); }

		line.append(randomVar + " " + randomOp + " " + randomVar2 + " ");
	}
	else																		// Choose outcome variable
	{	
		string randomVar = outcomevars[rand() % 3];

		line.append("LASTOUTCOME = " + randomVar + " ");
	}

	return line;
}


void StrategyGenerator::terminate_tree(line ** tree) 
{
	if (*tree) 
	{
		if (&((*tree)->next))
			terminate_tree(&((*tree)->next));
		if (&((*tree)->jump))
			terminate_tree(&((*tree)->jump));

		delete (*tree)->next;
		delete (*tree)->jump;
		(*tree)->next = nullptr;
		(*tree)->jump = nullptr;

		delete (*tree);
		*tree = nullptr;
	}
}