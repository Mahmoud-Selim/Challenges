/*
 * main.cpp
 *
 *  Created on: Mar 27, 2019
 *      Author: mahmoud
 */


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Labyrinth.h"

int main(int argc, char *argv[])
{

	std::string file_name;
	if(argc ==2)
	{
		file_name = argv[1];
	}
	else
	{
		std::cout << "Please enter the file name..." << std::endl;
		std::cin >> file_name;
	}
    // Read labyrinth from input file.
    std::ifstream inputFile("data.txt");

    Labyrinth labyrinth = Labyrinth(inputFile);
    inputFile.close();

    Labyrinth result = labyrinth.solveMaxPath();

    // Write the result labyrinth.
    std::ofstream outputFile;
    outputFile.open("output.txt");
    outputFile << result.maxPath()  + 1<< std::endl;
    outputFile << result;

    return 0;

}
