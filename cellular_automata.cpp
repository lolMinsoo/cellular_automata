#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <fstream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <iomanip>

using namespace std;
using namespace std::chrono_literals;

int main(void) {
    // Const
    const int MATRIX_SIZE = 100;
    bool check_wall;
    bool DEBUG = false;

    // Init
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> random_cell(0, MATRIX_SIZE - 1);
    std::uniform_int_distribution<int> random_adj(1, 4);

    // Create file
    ofstream output_file;
    ofstream final_state;

    // Variables
    int random_x, random_y;
    int adjacent;
    int hold_state;

    // Initialize State, Set All 0
    vector<vector<int>> state(MATRIX_SIZE, vector<int>(MATRIX_SIZE));

    output_file.open("sweeps.txt");

    // Set half to 1
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE / 2; j++) {
            state[j][i] = 1;
        }
    }

    // Write initial state to file
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            output_file << state[j][i];
        }
        output_file << "\n";
    }
    output_file << "\n";

    // Do the things
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 10000; j++) {
            system("cls");
            std::cout << "Currently on iteration " << i << "/10000 and on sweep " << j << "/10000." << endl;
            std::cout << std::setprecision(3) << ((i + 1) * (j + 1)/(10000*10000)) * 100 << "% done";

            if (DEBUG) {
                cout << "does it get here";
            }

            // Generate random values
            random_x = random_cell(mt);
            random_y = random_cell(mt);

            check_wall = false;

            while (!check_wall) {
                adjacent = random_adj(mt);
                // cout << "looping";

                // Check x-axis walls and y-axis walls
                if (!((random_x == 0 && adjacent == 1 || random_x == MATRIX_SIZE - 1 && adjacent == 3) || (random_y == 0 && adjacent == 4 || random_y == MATRIX_SIZE - 1 && adjacent == 2))) {
                    check_wall = true;
                }

            }

            if (DEBUG) {
                cout << random_x;
                cout << random_y;
                cout << adjacent;
            }

            // Update states
            hold_state = state[random_x][random_y];
            switch (adjacent) {
            case 1:
                // cout << "case 1";
                state[random_x][random_y] = state[random_x - 1][random_y];
                state[random_x - 1][random_y] = hold_state;
                break;
            case 2:
                // cout << "case 2";
                state[random_x][random_y] = state[random_x][random_y + 1];
                state[random_x][random_y + 1] = hold_state;
                break;
            case 3:
                // cout << "case 3";
                state[random_x][random_y] = state[random_x + 1][random_y];
                state[random_x + 1][random_y] = hold_state;
                break;
            case 4:
                // cout << "case 4";
                state[random_x][random_y] = state[random_x][random_y - 1];
                state[random_x][random_y] = hold_state;
                break;
            }
            
            if (DEBUG) {
                std::this_thread::sleep_for(1s);
            }
            

        }

        for (int k = 0; k < MATRIX_SIZE; k++) {
            for (int l = 0; l < MATRIX_SIZE; l++) {
                output_file << state[l][k];
            }
            output_file << "\n";
        }
        output_file << "\n";

        if (i == 9999) {
            final_state.open("final_sweep.txt");
            for (int k = 0; k < MATRIX_SIZE; k++) {
                for (int l = 0; l < MATRIX_SIZE; l++) {
                    final_state << state[l][k];
                }
                final_state << "\n";
            }
            final_state << "\n";
            final_state.close();
        }
    }

    output_file.close();
}