#include "Plane.h"
#include <stdexcept>
#include <iostream>

// Constructor: Load texture and set initial position to (0, 0)
Plane::Plane(const std::string& texturePath) : FUEL{100.0f}, FLYING_STATUS{0}, isDragging(false), amount{0} 
{
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load plane texture: " + texturePath);
    }   
    SPRITE.setTexture(texture);
    SPRITE.setPosition(0.0f, 0.0f); // Default position
    SPRITE.setScale(0.5f, 0.5f);   // Scale the sprite
}


// Get the sprite for rendering
sf::Sprite& Plane::getSprite() {
    return SPRITE;
}

// Set the plane's position
void Plane::setPosition(const sf::Vector2f& position) {
    SPRITE.setPosition(position);
}

// Get the plane's current position
sf::Vector2f Plane::getPosition() const {
    return SPRITE.getPosition();
}

// Start dragging the plane
void Plane::startDragging() {
    isDragging = true;
}

// Stop dragging the plane
void Plane::stopDragging() {
    isDragging = false;
}

// Check if the plane is being dragged
bool Plane::isBeingDragged() const {
    return isDragging;
}

// Update the position of the plane while dragging
void Plane::updatePosition(const sf::Vector2f& mousePosition) {
    if (isDragging) {
        SPRITE.setPosition(mousePosition);
    }
}

const sf::FloatRect Plane::getGlobalBounds() const{
    return SPRITE.getGlobalBounds();
}


//PassengerPlane constructor
PassengerPlane::PassengerPlane(const std::string texturePath, int capacity,int cost): Plane(texturePath), CAPACITY{capacity}{
    // float scaleFactor{70/SPRITE.getGlobalBounds().width};
    // SPRITE.scale(scaleFactor,scaleFactor);
    setAmount(cost);
}

//Passenger Plane display
void PassengerPlane::displayInfo(sf::RenderWindow& window) const{
    sf::RectangleShape DisplayBox;
    DisplayBox.setFillColor(sf::Color::White);
    DisplayBox.setSize(sf::Vector2f(200.0f,100.0f));
    DisplayBox.setPosition(1000-200, 0);

    std::string INFO;
    sf::Font font;
    if(!font.loadFromFile("../fonts/ARIALN.TTF")){
        std::runtime_error("Error Loading font in Display Box");
    }

    INFO += "PASSENGER_PLANE\n\n";
    INFO += "Passenger Capacity: " + std::to_string(CAPACITY) + '\n';
    INFO += "Fuel: " + std::to_string(FUEL) + '\n';
    if (TerminalGate)
        INFO += "Terminal Gate: " + std::to_string(TerminalGate) + '\n';
    switch (FLYING_STATUS)
    {
    case 1:
        INFO += "Flying_Status: Taking Off\n";
        break;
    case 2:
        INFO += "Flying_Status: Landing\n";
        break;
    default:
        INFO += "FLying_Status: On Ground\n";
        break;
    }

    sf::Text displayText;
    displayText.setFont(font);
    displayText.setPosition(DisplayBox.getPosition().x, DisplayBox.getPosition().y);
    displayText.setFillColor(sf::Color::Black);
    displayText.setString(INFO);
    displayText.setCharacterSize(15);
    window.draw(DisplayBox);
    window.draw(displayText);    
}

std::unique_ptr<Plane> PassengerPlane::clone() const{
    std::unique_ptr<Plane> result = std::make_unique<PassengerPlane>(*this);
    return std::move(result);
}

// get amount
int Plane::getAmount()const{
    return amount;
}
void Plane::setAmount(int a){
    amount=a;
}

//Set Terminal Gate num
void PassengerPlane::setGate(const short parked_gate){
    TerminalGate =  parked_gate;   
}