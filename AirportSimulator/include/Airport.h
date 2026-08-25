#ifndef AIRPORT_H
#define AIRPORT_H

#include <SFML/Graphics.hpp>
#include <vector>

class Airport {
private:
    sf::RectangleShape parkingArea;          // Represents the parking area
    std::vector<sf::FloatRect> parkingSlots; // Slots for planes in the parking area

public:
    Airport(const sf::Vector2f& position, const sf::Vector2f& size, int /*numSlots*/);

    // Getters
    const sf::RectangleShape& getParkingArea() const;
    const std::vector<sf::FloatRect>& getParkingSlots() const;

    // Check if a plane can be parked in a slot
    bool parkPlane(sf::Sprite& planeSprite);
};

#endif // AIRPORT_H
