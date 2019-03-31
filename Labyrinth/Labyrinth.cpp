/*
 * Labrinth.cpp
 *
 *  Created on: Mar 27, 2019
 *      Author: mahmoud
 */



#include "Labyrinth.h"
#include <stack>
#include <utility>

Labyrinth::Labyrinth(const std::vector<std::vector<int>> &board)
{
    mBoard = board;
    mMaxPath = 0;
	delta = { {-1, 0},  // move up
			  {1, 0} ,  // move down
			  {0, -1},  // move left
			  {0, 1} }; // move right
	number_of_free_spaces = 0;
}

Labyrinth::Labyrinth(std::ifstream &inputFile)
{
	number_of_free_spaces = 0;
    mMaxPath = 0;
	delta = { {-1, 0},  // move up
			  {1, 0} ,  // move down
			  {0, -1},  // move left
			  {0, 1} }; // move right
    // Loop all lines
    std::string fileLine;
    while (!inputFile.eof()) {
        std::vector<int> line;
        line.reserve(fileLine.size());
        inputFile >> fileLine;
        // Loop all characters in the current line.
        for (unsigned long i = 0; i < fileLine.size(); ++i) {
            switch (fileLine[i]) {
                // It's a wall.
                case WALL_FILE:
                    line.push_back(WALL);
                    break;
                    // It's a free path.
                case FREE_FILE:
                    line.push_back(FREE);
                    number_of_free_spaces++;
                    break;
                    // Character not valid.
                default:
                    std::cout << "'" << fileLine[i] << "' is not a valid input character." << std::endl;
                    throw 1;
            }
        }
        mBoard.push_back(line);
    }
}

Labyrinth Labyrinth::solveMaxPath() const
{
    Labyrinth max = *this;
    // First row.
    for (unsigned long j = 0; j < columns(); ++j)
    {
    	if(mBoard[0][j] == FREE)
    	{
            max = std::max(max, solveMaxPath(0, j));
            if(max.maxPath() + 1 == number_of_free_spaces)
            	return max;
    	}
    }
    // First and last column.
    for (unsigned long i = 1; i < rows()-1; ++i) {
    	if(mBoard[i][0] == FREE)
    	{
            max = std::max(max, solveMaxPath(i, 0));
            if(max.maxPath() + 1 == number_of_free_spaces)
            	return max;
    	}
    	if(mBoard[i][columns()-1] == FREE)
    	{
            max = std::max(max, solveMaxPath(i, columns()-1));
            if(max.maxPath() + 1 == number_of_free_spaces)
            	return max;
    	}
    }
    // Last row.
    for (unsigned long j = 0; j < columns(); ++j)
    {
    	if(mBoard[rows()-1][j] == FREE)
    	{
        	max = std::max(max, solveMaxPath(rows()-1, j));
            if(max.maxPath() + 1 == number_of_free_spaces)
            	return max;
    	}
    }
    return max;
}

Labyrinth Labyrinth::solveMaxPath(const unsigned long i, const unsigned long j) const
{
	// create a stack to push the possible casses.
	std::stack <Labyrinth> solution;
	Labyrinth start = *this;
	start.set(i, j, 0);
	start.set_max_path({i, j}, 0);

	// push the starting point and start exploring from there.
	solution.push(start);
	Labyrinth max = *this;
	while(!solution.empty())
	{
		Labyrinth temp = solution.top();
		solution.pop();

		// create 4 possible cases. move up, down, left & right.
		Labyrinth up = temp, down = temp, left = temp, right = temp;

		// a vector to store the indeces of the max path and the length of the max discovered path
		std::vector<int> new_data(3);
		new_data = {int(temp.get_max_path_index().first) + int(delta[0][0]),
				int(temp.get_max_path_index().second) + int(delta[0][1]), mMaxPath + 1};

		// start processing the 4 casses. up then down then left then right.
		if(new_data[0] >= 0 && new_data[0] < int(this->rows()) && new_data[1] >= 0 && new_data[1] < int(this->columns()) &&
				temp.at(new_data[0], new_data[1]) == FREE)
		{
			up.set_max_path({new_data[0], new_data[1]}, temp.maxPath() + 1);
			up.set(new_data[0], new_data[1], temp.maxPath() + 1);
			solution.push(up);
		}
		new_data[0] = temp.get_max_path_index().first + delta[1][0];
		new_data[1] = temp.get_max_path_index().second + delta[1][1];
		if(new_data[0] >= 0 && new_data[0] < int(this->rows()) && new_data[1] >= 0 && new_data[1] < int(this->columns()) &&
				temp.at(new_data[0], new_data[1]) == FREE)
		{
			down.set_max_path({new_data[0], new_data[1]}, temp.maxPath() + 1);
			down.set( new_data[0], new_data[1], temp.maxPath() + 1);
			solution.push(down);
		}
		new_data[0] = temp.get_max_path_index().first + delta[2][0];
		new_data[1] = temp.get_max_path_index().second + delta[2][1];
		if(new_data[0] >= 0 && new_data[0] < int(this->rows()) && new_data[1] >= 0 && new_data[1] < int(this->columns()) &&
				temp.at(new_data[0], new_data[1]) == FREE)
		{
			left.set_max_path({new_data[0], new_data[1]}, temp.maxPath() + 1);
			left.set(new_data[0], new_data[1], temp.maxPath() + 1);
			solution.push(left);
		}
		new_data[0] = temp.get_max_path_index().first + delta[3][0];
		new_data[1] = temp.get_max_path_index().second + delta[3][1];
		if(new_data[0] >= 0 && new_data[0] < int(this->rows()) && new_data[1] >= 0 && new_data[1] < int(this->columns()) &&
				temp.at(new_data[0], new_data[1]) == FREE)
		{
			right.set_max_path({new_data[0], new_data[1]}, temp.maxPath() + 1);
			right.set(new_data[0], new_data[1], temp.maxPath() + 1);
			solution.push(right);
		}

		// compare the current case with the previously stored maximum and choose the max one of them both.
		if(max < temp)
			max = temp;
	}
	return max;

}

unsigned long Labyrinth::rows() const
{
    return mBoard.size();
}

unsigned long Labyrinth::columns() const
{
    return mBoard[0].size();
}

int Labyrinth::maxPath() const
{
    return mMaxPath;
}

int Labyrinth::at(const unsigned long i, const unsigned long j) const
{
    return mBoard[i][j];
}

void Labyrinth::set(const unsigned long i, const unsigned long j, const int value)
{
    mBoard[i][j] = value;
}

void Labyrinth::set_max_path(const std::pair<unsigned long, unsigned long> index, const int value)
{
	max_path_index = index;
    mMaxPath = value;
}

std::pair<unsigned long, unsigned long> Labyrinth::get_max_path_index()
{
	return max_path_index;
}

bool Labyrinth::operator<(const Labyrinth &l) const
{
    return mMaxPath < l.mMaxPath;
}

std::ostream& operator<<(std::ostream &out, const Labyrinth &l)
{
    for (unsigned long i = 0; i < l.rows(); ++i) {
        for (unsigned long j = 0; j < l.columns(); ++j) {
            switch (l.at(i, j)) {
                case WALL:
                    out << WALL_FILE;
                    break;
                case FREE:
                    out << FREE_FILE;
                    break;
                default:
                    out << l.at(i, j);
            }
        }
        out << std::endl;
    }
    return out;
}
