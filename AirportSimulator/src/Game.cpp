#include "Game.h"
#include "Plane.h"
#include "Airport.h"
#include <iostream>
#include <stdexcept>

// Constructor
Game::Game() : currentState(GameState::StartScreen), totalMoney(1000) {}

// Destructor
Game::~Game() {
    close();
}

// Initialize the game
bool Game::init() {
    // Create the game window
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Airport Simulator");
    if (!window.isOpen()) {
        std::cerr << "Failed to create the window!" << std::endl;
        return false;
    }

    // Load media (textures and other resources)
    if (!this->loadMedia()) {
        return false;
    }

    updateMoneyDisplay();

    // Set up the airport
    setupAirport();

    // Initialize the menu (planes in the menu)
    initializeMenu();

    // Initialize the hangars
    initializeHangars(); // Add this to create and position hangars

    return true;
}


// Load media for the game
bool Game::loadMedia() {
    try {
        // Load start screen texture
        startscreenTexture = new sf::Texture();
        if (!startscreenTexture->loadFromFile("assets/airport_start.jpg")) {
            throw std::runtime_error("Failed to load start screen texture");
        }
        startscreenSprite.setTexture(*startscreenTexture);

        // Scale start screen sprite
        sf::Vector2u textureSize = startscreenTexture->getSize();
        startscreenSprite.setScale(
            static_cast<float>(SCREEN_WIDTH) / textureSize.x,
            static_cast<float>(SCREEN_HEIGHT) / textureSize.y
        );

        // Load gameplay texture
        gameplayTexture = new sf::Texture();
        if (!gameplayTexture->loadFromFile("assets/Airport design.png")) {
            throw std::runtime_error("Failed to load gameplay screen texture");
        }
        gameplaySprite.setTexture(*gameplayTexture);
        gameplaySprite.setScale(
            static_cast<float>(SCREEN_WIDTH) / gameplayTexture->getSize().x,
            static_cast<float>(SCREEN_HEIGHT) / gameplayTexture->getSize().y
        );

        //Start_Button
        startButton_texture = new sf::Texture;
        if(!startButton_texture->loadFromFile("assets/start_button.png")){
            throw std::runtime_error("Failed to load Start Button texture");   
        }
        ButtonSprite.scale(0.9, 0.9);
        ButtonSprite.setTexture(*startButton_texture);
        sf::FloatRect buttonBox = ButtonSprite.getGlobalBounds();
        ButtonSprite.setPosition(500 - buttonBox.width/2, 400 - buttonBox.height/2);

        if (!font.loadFromFile("fonts/ARIALNB.TTF")) {
        throw std::runtime_error("Failed to load font for money display!");
        }

        //Money Text
        moneyText.setFont(font);
        moneyText.setCharacterSize(20);
        moneyText.setFillColor(sf::Color::Black);
        moneyText.setPosition(SCREEN_WIDTH - 150, 50); // Top-right corner
        updateMoneyDisplay();


        // Set up the Fly button
        flyButton.setSize(sf::Vector2f(100.0f, 50.0f));
        flyButton.setFillColor(sf::Color::Red);
        flyButton.setPosition(SCREEN_WIDTH - 120.0f, 100.0f); // Positioned in the top-right corner

        // Set up the Fly button text
        flyButtonText.setFont(font);
        flyButtonText.setString("Fly");
        flyButtonText.setCharacterSize(20);
        flyButtonText.setFillColor(sf::Color::White);
        flyButtonText.setPosition(SCREEN_WIDTH - 100.0f, 105.0f);

        // Set up the Land button
        landButton.setSize(sf::Vector2f(100.0f, 50.0f));
        landButton.setFillColor(sf::Color::Blue);
        landButton.setPosition(SCREEN_WIDTH - 120.0f, 170.0f); // Positioned below the Fly button

        // Set up the Land button text
        landButtonText.setFont(font);
        landButtonText.setString("Land");
        landButtonText.setCharacterSize(20);
        landButtonText.setFillColor(sf::Color::White);
        landButtonText.setPosition(SCREEN_WIDTH - 100.0f, 175.0f);

        std::cout << "Textures loaded successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

// Initialize the menu
void Game::initializeMenu() {
    // Create the transparent Box
    menuBox.setSize(sf::Vector2f(200.0f, 100.0f));
    menuBox.setFillColor(sf::Color(100, 100, 100, 240));
    menuBox.setPosition(0.0f, 0.0f);

    // Add planes to the menu
    Plane* plane1 = new PassengerPlane("assets/red_plane.png",100,200);
    float scaleFactor{70/plane1->getSprite().getGlobalBounds().width};
    plane1->getSprite().scale(scaleFactor,scaleFactor);
    plane1->setPosition(sf::Vector2f(70.0f, 20.0f));
    menuPlanes.push_back(plane1);

    Plane* plane2 = new PassengerPlane("assets/jet.png",10,75);
    scaleFactor = 50/plane2->getSprite().getGlobalBounds().width;
    plane2->getSprite().scale(scaleFactor,scaleFactor);
    plane2->setPosition(sf::Vector2f(20.0f, 20.0f));
    menuPlanes.push_back(plane2);
    
    Plane* plane3 = new PassengerPlane("assets/big_plane.png",250,400);
    scaleFactor = 95/plane3->getSprite().getGlobalBounds().width;
    plane3->getSprite().scale(scaleFactor,scaleFactor);
    plane3->setPosition(sf::Vector2f(100.0f, 20.0f));
    // plane3->getSprite().setRotation(90);
    menuPlanes.push_back(plane3);
}

// Set up the airport object
void Game::setupAirport() {
    airport = new Airport(sf::Vector2f(36.0f, 262.0f), sf::Vector2f(754.0f, 189.0f), 5);
    terminal = new Terminal(500);
}

void Game::initializeHangars() {
    std::vector<sf::Vector2f> hangarPositions = {
        {150.0f, 390.0f}, {300.0f, 390.0f}, {450.0f, 390.0f} // Example positions
    };

    for (const auto& position : hangarPositions) {
        try {
            Hangar hangar("Storage", 2, "assets/hanger.png");
            hangar.setPosition(position);
            hangars.push_back(hangar);
        } catch (const std::exception& e) {
            std::cerr << "Error initializing hangar: " << e.what() << std::endl;
        }
    }
}

void Game::updateMoneyDisplay() {
    moneyText.setString("Money: $" + std::to_string(static_cast<int>(totalMoney)));
}

void Game::animateFly() {
    if (flyingPlane) {
        sf::Vector2f currentPos = flyingPlane->getPosition();

        if (isTakingOff) {
            // Move the plane towards the target coordinates
            if (currentPos.x < 50.0f) {
                flyingPlane->getSprite().move(1.0f, 0.0f); // Use getSprite().move()
            }
            else if (currentPos.x > 50.0f) {
                flyingPlane->getSprite().move(-1.0f, 0.0f); // Use getSprite().move()
            }
             else if (currentPos.y > 517.0f) {
                flyingPlane->getSprite().move(0.0f, -1.0f); // Use getSprite().move()
            }
            else if (currentPos.y < 517.0f) {
                flyingPlane->getSprite().move(0.0f, 1.0f); // Use getSprite().move()
            }
             else {
                // When the plane reaches the target, rotate and start flying horizontally
                isTakingOff = false;
                flyingPlane->getSprite().setRotation(90.0f); // Rotate the sprite
            }
        } else {
            // Move the plane horizontally
            flyingPlane->getSprite().move(2.0f, 0.0f); // Use getSprite().move()

            // Check if the plane leaves the screen
            if (flyingPlane->getPosition().x > SCREEN_WIDTH + 100) {
                std::shared_ptr<Plane> tempPlane = flyingPlane;
                flyPlanes.push_back(tempPlane);
                flyingPlane = nullptr;  // Reset the flying plane
            }
        }
    }
}

void Game::animateLand() {
    if (landingPlane) {
        sf::Vector2f currentPos = landingPlane->getPosition();
        landingPlane->getSprite().setRotation(270.0f); // Rotate the sprite
        if (isLanding) {
            // Move the plane towards the parking spot
            if (currentPos.y < 517.0f) {
                landingPlane->getSprite().move(0.0f, 1.0f); // Move down
            } else if (currentPos.x > 253.0f) {
                landingPlane->getSprite().move(-1.0f, 0.0f); // Move left
            } else if (currentPos.x < 253.0f) {
                landingPlane->getSprite().move(1.0f, 0.0f); // Move right
            } else {
                // When the plane reaches the parking spot
                landingPlane->setPosition(sf::Vector2f(253.0f, 517.0f)); // Final position
                planes.push_back(landingPlane); // Move the plane back to parked planes
                flyPlanes.erase(std::remove(flyPlanes.begin(), flyPlanes.end(), landingPlane), flyPlanes.end());
                landingPlane = nullptr;  // Reset the landing plane
                isLanding = false;       // Reset landing state
            }
        }
    }
}




// Main game loop
void Game::run() {
    while (window.isOpen()) {
        // std::cout << "Running main game loop." << std::endl;
        handleEvents();
        render();
    }
    std::cout << "Exiting main game loop." << std::endl;
}

void Game::displayMousPos(){
    sf::Vector2f MousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    sf::RectangleShape DisplayBox;
    DisplayBox.setFillColor(sf::Color::White);
    DisplayBox.setSize(sf::Vector2f(200.0f,100.0f));
    DisplayBox.setPosition(1000-200, 0);

    sf::Font font; 
    if(!font.loadFromFile("fonts/ARIALN.TTF")){
        std::runtime_error("Error Loading font in Display Box");
    }
    sf::Text displayText;
    displayText.setFont(font);
    displayText.setPosition(DisplayBox.getPosition().x, DisplayBox.getPosition().y);
    displayText.setFillColor(sf::Color::Black);
    displayText.setCharacterSize(15);

    std::string POS = "X: "+ std::to_string(MousePos.x) + "\nY: " + std::to_string(MousePos.y);
    displayText.setString(POS);

    window.draw(DisplayBox);
    window.draw(displayText);       
}


void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        if (currentState == GameState::StartScreen) {
            // Handle mouse click on the start screen
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (ButtonSprite.getGlobalBounds().contains(mousePos)) {
                    currentState = GameState::GameplayScreen; // Transition to gameplay
                }
            }
        } else if (currentState == GameState::GameplayScreen) {
            // Handle gameplay-related events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                window.setMouseCursorGrabbed(true);
                //loop to access the pointers by reference
                for (auto& plane : menuPlanes) {
                    if (plane->getSprite().getGlobalBounds().contains(mousePos)) {
                        // Create a copy of the plane
                        std::shared_ptr<Plane> newPlane = plane->clone();
                        newPlane->setPosition(sf::Vector2f(mousePos.x - plane->getGlobalBounds().width/2,
                                            mousePos.y - plane->getGlobalBounds().height/2));
                        selectedPlane = newPlane;
                        selectedPlane->startDragging();
                        return;
                    }
                }


            }

            // Handle mouse release for dropping planes
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                if (selectedPlane) {
                    if((airport->getParkingArea().getGlobalBounds().contains(mousePos))&&(totalMoney>=selectedPlane->getAmount())){
                        totalMoney-=selectedPlane->getAmount();
                        updateMoneyDisplay();
                        selectedPlane->stopDragging();
                        if (terminal->parkPlane(selectedPlane))
                            planes.push_back(selectedPlane);
                    }
                    else{
                        selectedPlane->stopDragging();
                    }
                    selectedPlane = nullptr;
                }
                window.setMouseCursorGrabbed(false);
            }

            // Update plane position during drag
            if (event.type == sf::Event::MouseMoved && selectedPlane && selectedPlane->isBeingDragged()) {
                selectedPlane->updatePosition(sf::Vector2f(mousePos.x - selectedPlane->getGlobalBounds().width/2,
                                            mousePos.y - selectedPlane->getGlobalBounds().height/2));
            }
        }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                // Check if the Fly button is clicked
                if (flyButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    for (auto& plane : planes) {
                        if (airport->getParkingArea().getGlobalBounds().contains(plane->getPosition()) && !flyingPlane) {
                            flyingPlane = plane;  // Assign the plane in the parking area to fly
                            isTakingOff = true;  // Set the takeoff animation state
                            break;
                        }
                    }
                // Select a plane in the parking area by clicking on it
                // for (auto& plane : planes) {
                //     if (plane->getSprite().getGlobalBounds().contains(mousePos) &&
                //         airport->getParkingArea().getGlobalBounds().contains(plane->getPosition())) {
                //         selectedPlane = std::move(plane); // Store the clicked plane as the selected plane
                //         return;
                //     }
                // }
    }
            if (landButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                for (auto& plane : flyPlanes) {
                    if (!landingPlane) {
                        landingPlane = plane;  // Assign the plane currently flying to land
                        isLanding = true;      // Set the landing animation state
                        break;
                    }
                }
            }
}}}



// Render the game objects
void Game::render() {
    window.clear();

    // sf::Vector2f MousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    if (currentState == GameState::StartScreen) {
        window.draw(startscreenSprite);
        window.draw(ButtonSprite);
    } else if (currentState == GameState::GameplayScreen) {
        window.draw(gameplaySprite); // Draw gameplay background

        // Draw the Fly button
        window.draw(flyButton);
        window.draw(flyButtonText);

        // Draw the Land button
        window.draw(landButton);
        window.draw(landButtonText);

        // Draw the money display
        window.draw(moneyText);

        // Draw the menu
        window.draw(menuBox);
        for (const auto& plane : menuPlanes) {
            window.draw(plane->getSprite());
        }

        // Draw hangars
        for (const auto& hangar : hangars) {
            hangar.display(window);
        }

        // Draw planes
        for (const auto& plane : planes) {
            window.draw(plane->getSprite());
        }

        if (selectedPlane) {
            window.draw(selectedPlane->getSprite());
        }
         // Handle the fly animation
        animateFly();

        // Handle the land animation
        animateLand();    
    }
    window.display(); // Render everything
}




// Clean up resources
void Game::close() {
    if (window.isOpen()) {
        window.close();
    }

    //Dellocating the start_screen texture
    if (startscreenTexture) {
        delete startscreenTexture;
        startscreenTexture = nullptr;
    }

    //Deallocating Airport_Texture
    if (gameplayTexture) {
        delete gameplayTexture;
        gameplayTexture = nullptr;
    }

    //Deallocating the Airport
    if (airport) {
        delete airport;
        airport = nullptr;
    }

    //Deallocating Planes(On_Screen) from the HEAP
    // for (auto& plane : planes) {
    //     delete plane;
    // }
    planes.clear();

    //Deallocating MenuPlanes from the HEAP
    for (auto& plane : menuPlanes) {
        delete plane;
    }
    menuPlanes.clear();
}
