#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class StrategyGenerator
{
protected:
	struct line {
		string command;
		int lineno;
		line * next;	//left
		line * jump;	//right
	};
	line * root = nullptr;
	vector<string> all_lines;

	// Tokens to use for the generation, separated into categories called in different parts of the generator
	string commands[4] = { "IF","BETRAY","SILENCE","RANDOM" };
	vector<string> nrvars = { "ALLOUTCOMES_W","ALLOUTCOMES_X","ALLOUTCOMES_Y","ALLOUTCOMES_Z","ITERATIONS","MYSCORE","NUMBER" };
	vector<string> outcomevars = { "W","X", "Y", "Z" };
	string comparisonOps[3] = { ">","<","=" };
	string ops[2] = { "-","+" };

	virtual void terminate_tree(line ** tree);

public:
	StrategyGenerator();
	~StrategyGenerator();
	virtual void generateStrategy(int lines, string file);						// Function that is called to generate a strategy: Takes the maximum allowed number of lines and a file name to store it to.
	virtual void generateLine(line ** tree, int lineno, int lines);				// Generates the Binary Tree which stores the lines and logic of the generated strategy. 
	virtual string generateIf();												// Generates an IF statement to use for the strategy
	virtual void toFile(string file, int lines);								// Prints the strategy to a file.
};

