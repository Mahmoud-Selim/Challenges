/*
 * Labrinth.h
 *
 *  Created on: Mar 27, 2019
 *      Author: mahmoud
 */

#ifndef LABYRINTH_H_
#define LABYRINTH_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
// Wall and free path of the labyrinth.
#define WALL        -2
#define WALL_FILE   '#'
#define FREE        -1
#define FREE_FILE   '.'

class Labyrinth {

public:

    // Constructors.
    Labyrinth() {}
    Labyrinth(const std::vector<std::vector<int>> &board);
    Labyrinth(std::ifstream &inputFile);

    /*
     * @return A labyrinth with the solution to the maximum free path problem.
     */
    Labyrinth solveMaxPath() const;

    /*
     * @return A labyrinth with the solution to the maximum free path problem
     *         with the current position in the [i, j] position.
     */
    Labyrinth solveMaxPath(const unsigned long i, const unsigned long j) const;

    // Size of the labyrinth.
    unsigned long rows() const;
    unsigned long columns() const;

    // mMaxPath getter.
    int maxPath() const;

    // Returns labyrinth's cell at ith row and jth column.
    int at(const unsigned long i, const unsigned long j) const;
    // Sets value to the ith row and jth column of the labyrinth board.
    void set(const unsigned long i, const unsigned long j, const int value);
    // Sets value to the max path of the labyrinth
    void set_max_path(const std::pair<unsigned long, unsigned long>,const int value);
    std::pair<unsigned long, unsigned long> get_max_path_index();
    /**
     * @param l Labyrinth to compare its maximum free path.
     * @return true if l has a longer free path than this labyrinth.
     */
    bool operator<(const Labyrinth &l) const;

    /**
     * Pretty print.
     *
     * @param out Stream that will receive the labyrinth l as a string.
     * @param l Labyrinth to send to the stream as a string.
     * @return Stream with a string version of l.
     */
    friend std::ostream& operator<<(std::ostream &out, const Labyrinth &l);

private:

    /** Labyrinth board. */
    std::vector<std::vector<int>> mBoard;

    /** Length of the maximum free path of this labyrinth board. */
    int mMaxPath = 0;
    std::vector<std::vector<int > > delta;

    /* Index of the maximum discovered cell in the maze*/
    std::pair<unsigned long , unsigned long> max_path_index;

    // number of dots "." in the maze, which is also the number of spaces.
    int number_of_free_spaces = 0;
};

#endif /* LABYRINTH_H_ */
