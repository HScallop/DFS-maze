#include <iostream>
#include <string>
#include "Maze.h"
#include <fstream>
using namespace std;

int main() {
	int row;
	int col;
	char comma;
	string filename;
	cout << "Pleas enter your filename.\n";
	cin >> filename;
	//get row and column
	fstream rowcol(filename);
	rowcol >> col >> comma >> row;

	Maze maze(row, col);

	maze.load(filename);
	maze.print();
	maze.bonus(9999999);
	maze.bonus(2);
	maze.print();
	maze.showroute();


	



	return 0;
}