#include "Hangar.h"
#include <stdexcept>

Hangar::Hangar(const std::string& type, int capacity, const std::string& texturePath)
    : type(type), capacity(capacity) {
    // Load texture from the provided path
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load hangar texture from " + texturePath);
    }
    sprite.setTexture(texture); // Assign the texture to the sprite
}

void Hangar::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position); // Set the position of the hangar
}

void Hangar::display(sf::RenderWindow& window) const {
    window.draw(sprite); // Render the hangar
}
