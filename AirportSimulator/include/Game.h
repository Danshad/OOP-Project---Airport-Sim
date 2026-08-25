#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Airport.h"
#include "Plane.h"
#include "Hangar.h"
#include "Terminal.h"
#include <memory>

// Enum for game states
enum  GameState {
    StartScreen,
    GameplayScreen
};

class Game {
private:
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 800;

    sf::RenderWindow window;
    GameState currentState;

    sf::Font font;
    sf::Text moneyText;
    int totalMoney;

    // Game Textures and sprites
    sf::Texture* startButton_texture;
    sf::Sprite ButtonSprite;
    sf::Texture* startscreenTexture = nullptr;
    sf::Sprite startscreenSprite;
    sf::Texture* gameplayTexture = nullptr;
    sf::Sprite gameplaySprite;

    // takeoff
    sf::RectangleShape flyButton; // Button for initiating takeoff
    sf::Text flyButtonText;       // Text for the Fly button
    bool isTakingOff = false; // Flag to indicate takeoff

    // landing
    sf::RectangleShape landButton; // Button for initiating landing
    sf::Text landButtonText;       // Text for the Land button
    bool isLanding = false;        // Flag to indicate landing
    std::shared_ptr<Plane> landingPlane = nullptr; // Plane currently landing


    // Plane 
    sf::RectangleShape menuBox;           // White box for the menu
    std::vector<Plane*> menuPlanes;       // Planes displayed in the menu
    std::vector<std::shared_ptr<Plane>> planes;           // Active planes on the screen
    std::vector<std::shared_ptr<Plane>> flyPlanes; 
    std::shared_ptr<Plane> selectedPlane = nullptr;       // Currently dragged plane
    std::shared_ptr<Plane> flyingPlane = nullptr;

    // Hangars
    std::vector<Hangar> hangars;          // Hangar objects

    // Airport
    Airport* airport = nullptr;           // Airport object

    //Terminal
    Terminal* terminal = nullptr;

    // Internal methods
    void close();
    void handleEvents();
    void render();
    void initializePlanes();
    void setupAirport();

    void initializeMenu();                // Initialize the menu box and its planes
    void initializeHangars();             // Initialize hangars
    void displayMousPos();
    void updateMoneyDisplay();
    void animateFly();
    void animateLand();
public:
    Game();
    ~Game();

    bool init();
    bool loadMedia();
    void run();
};

#endif // GAME_H
