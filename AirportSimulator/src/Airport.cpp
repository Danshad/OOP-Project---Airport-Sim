#include "Airport.h"

// Constructor: Initialize parking area and slots
Airport::Airport(const sf::Vector2f& position, const sf::Vector2f& size, int/* numSlots*/) {
    parkingArea.setPosition(position);
    parkingArea.setSize(size);
    parkingArea.setFillColor(sf::Color(sf::Color::Transparent)); // Semi-transparent gray

    // float slotWidth = size.x / numSlots;
    // for (int i = 0; i < numSlots; ++i) {
    //     parkingSlots.emplace_back(position.x + i * slotWidth, position.y, slotWidth, size.y);
    // }
}

// Get the parking area rectangle
const sf::RectangleShape& Airport::getParkingArea() const {
    return parkingArea;
}

// Get the parking slots
const std::vector<sf::FloatRect>& Airport::getParkingSlots() const {
    return parkingSlots;
}

// Try to park a plane in a slot
bool Airport::parkPlane(sf::Sprite& planeSprite) {
    for (const auto& slot : parkingSlots) {
        if (slot.contains(planeSprite.getPosition())) {
            planeSprite.setPosition(slot.left, slot.top); // Snap to slot
            return true;
        }
    }
    return false; // No valid slot found
}
