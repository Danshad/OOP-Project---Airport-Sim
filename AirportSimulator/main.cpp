#include "Game.h"
// #include <iostream> // Include this for std::cerr and std::cout

// int main(int argc, char* argv[]) {
//     Game game;

//     srand(time(NULL));

//     // Initialize the game
//     if (!game.init()) {
//         std::cerr << "Failed to initialize the game!" << std::endl;
//         return -1;
//     }

//     // Load media
//     if (!game.loadMedia()) {
//         std::cerr << "Failed to load media!" << std::endl;
//         return -1;
//     }

//     // Run the game loop
//     game.run();

//     return 0;
// }




int main() {
    Game game;             // Create an instance of the Game class
    
    if (!game.init()) {    // Initialize the game
        return -1;         // Exit if initialization fails
    }

    if (!game.loadMedia()) {  // Load the required media
        return -1;            // Exit if media loading fails
    }

    game.run();             // Run the game loop

    return 0;               // Exit the program successfully
}
