#ifndef PLANE_H
#define PLANE_H

#include <SFML/Graphics.hpp>
#include <string>

class Plane {
protected:
    sf::Sprite SPRITE;           // Sprite for the plane
    sf::Texture texture;         // Texture for the plane
    float FUEL;                   // Declared first
    unsigned short FLYING_STATUS; // Declared second
    bool isDragging;              // Declared third
    float amount;                 // Declared fourth

public:
    Plane(const std::string& texturePath);
    virtual ~Plane() = default;
    
    // Getters and setters
    sf::Sprite& getSprite();
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
    void setAmount(int a);
    int getAmount() const;

    // Drag-and-drop mechanics
    void startDragging();
    void stopDragging();
    bool isBeingDragged() const;

    // Update plane position during dragging
    void updatePosition(const sf::Vector2f& mousePosition);
    virtual void displayInfo(sf::RenderWindow& window) const = 0;
    virtual std::unique_ptr<Plane> clone() const = 0;
    const sf::FloatRect getGlobalBounds() const;

    virtual void setGate(const short parked_gate) = 0;

};

class PassengerPlane : public Plane {
private:
    int CAPACITY;
    short TerminalGate{0};

public:
    PassengerPlane(const std::string texturePath, int capacity,int cost);
    ~PassengerPlane() = default;
    void displayInfo(sf::RenderWindow& window) const override;
    std::unique_ptr<Plane> clone() const override;
    virtual void setGate(const short parked_gate);
    
};




#endif // PLANE_H
