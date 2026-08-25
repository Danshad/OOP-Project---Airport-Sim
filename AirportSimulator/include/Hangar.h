#ifndef HANGAR_H
#define HANGAR_H

#include <SFML/Graphics.hpp>
#include <string>

class Hangar {
private:
    sf::Sprite sprite;               // Sprite to render the hangar
    sf::Texture texture;             // Texture for the hangar
    std::string type;                // Type of hangar (e.g., "Storage", "Maintenance")
    int capacity;                    // Capacity of the hangar

public:
    Hangar(const std::string& type, int capacity, const std::string& texturePath);
    void setPosition(const sf::Vector2f& position); // Set hangar position
    void display(sf::RenderWindow& window) const;   // Draw the hangar to the window
};

#endif // HANGAR_H

