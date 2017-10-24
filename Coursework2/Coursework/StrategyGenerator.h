#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class StrategyGenerator
{
private:
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
	string nrvars[7] = { "ALLOUTCOMES_W","ALLOUTCOMES_X","ALLOUTCOMES_Y","ALLOUTCOMES_Z","ITERATIONS","MYSCORE","NUMBER" };
	string outcomevars[4] = { "W","X", "Y", "Z" };
	string comparisonOps[3] = { ">","<","=" };
	string ops[2] = { "-","+" };

	void terminate_tree(line ** tree);

public:
	StrategyGenerator();
	~StrategyGenerator();
	void generateStrategy(int lines, string file);						// Function that is called to generate a strategy: Takes the maximum allowed number of lines and a file name to store it to.
	void generateLine(line ** tree, int lineno, int lines);				// Generates the Binary Tree which stores the lines and logic of the generated strategy. 
	string generateIf();												// Generates an IF statement to use for the strategy
	void toFile(string file, int lines);								// Prints the strategy to a file.
};

