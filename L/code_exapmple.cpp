// ===== LSP Violation Example =====
// Here, Penguin inherits fly() but cannot actually fly—breaking substitutability.

#include <iostream>
#include <vector>
#include <stdexcept>

class Bird {
public:
    virtual ~Bird() = default;
    virtual void fly() {
        std::cout << "Flying\n";
    }
    virtual void walk() {
        std::cout << "Walking\n";
    }
};

class Eagle : public Bird {
    // Inherits fly() and walk()
    void fly() override {
        std::cout<<"Eagle Flying";
    }
    void walk() override {
        std::cout << "Eagle walking\n";
    }
};

class Penguin : public Bird {
public:
    void fly() override {
        throw std::logic_error("Penguins can't fly!");
    }
    void walk() override {
        std::cout << "Penguin walking\n";
    }
};

// Client expects to call fly() on every Bird
void makeAllBirdsFly(const std::vector<Bird*>& birds) {
    for (auto b : birds) {
        b->fly();   // Crashes or misbehaves on a Penguin
    }
}

int main() {
    Eagle   eagle;
    Penguin penguin;
    std::vector<Bird*> flock = { &eagle, &penguin };
    makeAllBirdsFly(flock);
    return 0;
}

/*
Output (Violation Example):

Flying
terminate called after throwing an instance of 'std::logic_error'
  what():  Penguins can't fly!
*/

//---------------------------------------------------------------------------------------------------------------------------------------

// ===== Refactoring to a LSP-Compliant Example =====
// We separate “can fly” into its own interface, so only truly flyable birds implement it.

#include <iostream>
#include <vector>

// 1) Abstraction for flying behavior
class Flyable {
public:
    virtual ~Flyable() = default;
    virtual void fly() = 0;
};

// 2) Base class for all birds (only common behaviors here)
class Bird {
public:
    virtual ~Bird() = default;
    virtual void walk() {
        std::cout << "Walking\n";
    }
};

class Eagle : public Bird, public Flyable {
public:
    void fly() override {
        std::cout << "Eagle flying\n";
    }
    void walk() override {
        std::cout << "Eagle walking\n";
    }
};

class Penguin : public Bird {
public:
    // No fly(): Penguins simply don't implement Flyable
    // walk() inherited
    void walk() override {
        std::cout << "Penguin walking\n";
    }
};

// Client code for flying birds only
void makeFlyingBirdsFly(const std::vector<Flyable*>& flock) {
    for (auto f : flock) {
        f->fly();
    }
}

int main() {
    Eagle   eagle;
    Penguin penguin;

    // Only Eagle goes in the Flyable collection
    std::vector<Flyable*> flyers = { &eagle };
    makeFlyingBirdsFly(flyers);

    // We can still interact with Penguin via Bird:
    penguin.walk();

    return 0;
}

/*
Output (LSP-Compliant Example):

Eagle flying
Eagle walking
Penguin walking
*/
