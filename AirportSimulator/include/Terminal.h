#ifndef TERMINAL_H
#define TERMINAL_H

#include <vector>
#include "Plane.h"
#include <memory>

class Terminal {
private:
    const short gates{3};
    const short START_POINTx{280};
    const short START_POINTy{273};
    const short GAP{85};
    short FreeGates;
    int passengerCapacity;
    std::vector<std::shared_ptr<Plane>> TerminalPlanes;

public:
    Terminal(int capacity);
    ~Terminal();


    bool parkPlane(std::shared_ptr<Plane>);
    void displayInfo() const;
    short getGates() const;
    short getFreeGates() const;
};

#endif
