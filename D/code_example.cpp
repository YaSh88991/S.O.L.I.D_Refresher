// ===== DIP Violation Example =====
// Lamp (high-level) depends directly on MainsPower (low-level).
// You cannot change the power source without editing Lamp.

#include <iostream>

class MainsPower {
public:
    void supplyPower() {
        std::cout << "Supplying power from mains\n";
    }
};

class Lamp {
public:
    void turnOn() {
        MainsPower power;
        power.supplyPower();   // Lamp creates and uses a concrete MainsPower
        std::cout << "Lamp is on\n";
    }
};

int main() {
    Lamp lamp;
    lamp.turnOn();
    return 0;
}

/*
Output:
Supplying power from mains
Lamp is on
*/

//-------------------------------------------------------------------------------------------------------------------------------------------------


// ===== Refactoring to a DIP-Compliant Example =====
// Both Lamp (high-level) and concrete sources (low-level) depend on the IPowerSource abstraction.
// You can inject any power source without changing Lamp.

#include <iostream>

// 1) Abstraction
class IPowerSource {
public:
    virtual ~IPowerSource() = default;
    virtual void supplyPower() = 0;
};

// 2) Low-level implementations
class MainsPower : public IPowerSource {
public:
    void supplyPower() override {
        std::cout << "Supplying power from mains\n";
    }
};

class Battery : public IPowerSource {
public:
    void supplyPower() override {
        std::cout << "Supplying power from battery\n";
    }
};

// 3) High-level module depends only on the abstraction
class LampDIP {
    IPowerSource& source;
public:
    explicit LampDIP(IPowerSource& src) : source(src) {}

    void turnOn() {
        source.supplyPower();   // uses any IPowerSource
        std::cout << "Lamp is on\n";
    }
};

int main() {
    MainsPower mains;
    LampDIP lamp1(mains);
    lamp1.turnOn();

    Battery battery;
    LampDIP lamp2(battery);
    lamp2.turnOn();

    return 0;
}

/*
Output:
Supplying power from mains
Lamp is on
Supplying power from battery
Lamp is on
*/
