#include "Terminal.h"

Terminal::Terminal(int capacity): passengerCapacity{capacity}{}

Terminal::~Terminal(){}

bool Terminal::parkPlane(std::shared_ptr<Plane> plane){
    if (TerminalPlanes.size() >= static_cast<size_t>(gates))
        return false;
    int midX = plane->getGlobalBounds().width/2;
    plane->setPosition(sf::Vector2f(TerminalPlanes.size()*GAP + START_POINTx - midX, START_POINTy));
    TerminalPlanes.push_back(plane);
    plane->setGate(TerminalPlanes.size());
    FreeGates--;
    return true;
}

short Terminal::getFreeGates() const{
    return FreeGates;
}

void Terminal::displayInfo() const{}

short Terminal::getGates() const{
    return gates;
}