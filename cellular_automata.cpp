#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <fstream>

using namespace std;

bool check(int random_x, int random_y, int adjacent) {
	try {
		// Check x
		if ((random_x == 0 && adjacent == 1) || (random_x == 99 && adjacent == 3)) {
			throw 0;
		}

		if ((random_y == 0 && adjacent == 2) || (random_y == 99 && adjacent == 4)) {
			throw 0;
		}
	}
	catch (int x) {
		return false;
	}
	return true;
}

int main(void) {


	// Initalize Variables
	int random_x;
	int random_y;
	int adjacent;
	int hold_state;
	const int matrix_size = 100; // n x n matrix

	// Create output file
	ofstream outputfile;

	// Initalize Randomizers
	std::random_device rd;
	std::mt19937 mt(rd());

	// Create random functions
	std::uniform_int_distribution<int> randomcell(0, matrix_size);
	std::uniform_int_distribution<int> randomadjacent(1, 4);

	// Create state
	int state[matrix_size][matrix_size] = { {0 } };  // Init to 0

	// Set half to 0
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 50; j++) {
			state[i][j] = 1;
		}
	}

	// Write to file
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			outputfile << state[j][i];
		}
		outputfile << "\n";
	}
	outputfile << "\n";

	// Do the thing
	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < 10000; j++) {
			
			bool check_wall = false;
			random_x = randomcell(mt);
			random_y = randomcell(mt);
			// Randomize
			while (!check_wall) {
				adjacent = randomadjacent(mt);

				check_wall = check(random_x, random_y, adjacent);
			}
			
			hold_state = state[random_x][random_y];

			//std::cout << adjacent;
			//std::cout << random_x;
			//std::cout << random_y;
			switch (adjacent) {
				case 1:
					state[random_x][random_y] = state[random_x - 1][random_y];
					state[random_x - 1][random_y] = hold_state;
				case 2:
					state[random_x][random_y] = state[random_x][random_y + 1];
					state[random_x][random_y + 1] = hold_state;
				case 3:
					state[random_x][random_y] = state[random_x + 1][random_y];
					state[random_x + 1][random_y] = hold_state;
				case 4:
					state[random_x][random_y] = state[random_x][random_y - 1];
					state[random_x][random_y] = hold_state;
			}
		}


		for (int k = 0; k < 100; k++) {
			for (int l = 0; l < 100; l++) {
				outputfile << state[l][k];
			}
			outputfile << "\n";
		}
		outputfile << "\n";
	}

	outputfile.close();

}

