#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// ANSI Escape Codes for text coloring
const string RESET   = "\033[0m";
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string BLUE    = "\033[34m";
const string CYAN    = "\033[36m";

// Cleaned up dice roller
int rollDice() {
    return 1 + rand() % 6;
}

int main() {
    // Seed the random number generator EXACTLY ONCE at the start of the program
    srand(static_cast<unsigned int>(time(0)));

    const int WINNING_TILE = 100;
    const int MAX_PLAYERS = 2;
    int currentPositions[MAX_PLAYERS] = {0};
    int playerTurn = 0;
    bool gameOver = false;

    // A 101-size array representing the board. 
    // Index = current tile. Value = destination (if it's a snake or ladder). 
    // 0 means it's a normal tile.
    int boardLookup[101] = {0};

    // Define Fixed Ladders (Start Tile -> End Tile)
    boardLookup[5]  = 25;
    boardLookup[20] = 45;
    boardLookup[35] = 60;
    boardLookup[50] = 75;
    boardLookup[65] = 90;
    boardLookup[80] = 99;

    // Define Fixed Snakes (Start Tile -> End Tile)
    boardLookup[15] = 3;
    boardLookup[25] = 10;
    boardLookup[37] = 12;
    boardLookup[52] = 22;
    boardLookup[68] = 40;
    boardLookup[85] = 55;
    boardLookup[98] = 8;

    while (!gameOver) {
        // Clear the screen depending on OS compatibility
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << CYAN << "========================================" << RESET << endl;
        cout << YELLOW << "        🐍 SNAKE AND LADDER GAME 🎲     " << RESET << endl;
        cout << CYAN << "========================================" << RESET << endl;
        
        // Display Current Leaderboard
        for (int i = 0; i < MAX_PLAYERS; i++) {
            cout << "Player " << (i + 1) << " is at position: " << BLUE << currentPositions[i] << RESET << endl;
        }
        cout << CYAN << "----------------------------------------" << RESET << endl;
        cout << "It is " << GREEN << "Player " << (playerTurn + 1) << "'s" << RESET << " turn." << endl;
        
        // Pause and wait for player to press enter to roll
        cout << "Press Enter to roll the die...";
        cin.get(); 

        // Fix: Roll the dice ONCE and store it in a variable
        int roll = rollDice();
        cout << "\n🎲 Player " << (playerTurn + 1) << " rolled a " << YELLOW << roll << RESET << "!" << endl;

        // Calculate potential new position
        int targetPosition = currentPositions[playerTurn] + roll;

        // Check if the move is valid (Must land EXACTLY on 100)
        if (targetPosition > WINNING_TILE) {
            cout << RED << "Too high! " << RESET << "You need exactly " << (WINNING_TILE - currentPositions[playerTurn]) << " to win. Turn skipped." << endl;
        } else {
            currentPositions[playerTurn] = targetPosition;

            // Check for Snakes or Ladders at the new position
            if (boardLookup[currentPositions[playerTurn]] != 0) {
                int destination = boardLookup[currentPositions[playerTurn]];
                
                if (destination > currentPositions[playerTurn]) {
                    // It's a ladder
                    cout << GREEN << "▲ Dynamic Boost! Landed on a ladder! Climbed from " 
                         << currentPositions[playerTurn] << " to " << destination << "!" << RESET << endl;
                } else {
                    // It's a snake
                    cout << RED << "▼ Oh no! Bitten by a snake! Slipped from " 
                         << currentPositions[playerTurn] << " down to " << destination << "." << RESET << endl;
                }
                currentPositions[playerTurn] = destination;
            }
        }

        // Check for victory condition
        if (currentPositions[playerTurn] == WINNING_TILE) {
            cout << "\n🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << endl;
            cout << GREEN << "PLAYER " << (playerTurn + 1) << " WINS THE GAME!!!!" << RESET << endl;
            cout << "🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉" << endl;
            gameOver = true;
        }

        // Move to the next player
        playerTurn = (playerTurn + 1) % MAX_PLAYERS;

        if (!gameOver) {
            cout << "\nPress Enter to proceed to the next turn...";
            cin.get();
        }
    }

    return 0;
}
