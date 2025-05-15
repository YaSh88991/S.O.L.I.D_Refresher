// ===== OCP Violation Example =====

// All shipping‐cost logic lives in one class using if/else.
// Adding a new method (e.g., "sea") requires editing calculateCost.

#include <iostream>
#include <stdexcept>
#include <string>

class ShippingService
{
public:
    double calculateCost(const std::string &method, double weightKg)
    {
        if (method == "ground")
        {
            return 5.0 + 1.2 * weightKg;
        }
        else if (method == "air")
        {
            return 10.0 + 3.5 * weightKg;
        }
        else
        {
            throw std::invalid_argument("Unknown shipping method");
        }
    }
};

int main()
{
    ShippingService svc;
    std::cout << "Ground: $" << svc.calculateCost("ground", 2.5) << "\n";
    std::cout << "Air:    $" << svc.calculateCost("air", 2.5) << "\n";
    // Later, to support "sea", you must:
    //  * Add another else-if branch here.
    return 0;
}



// ===== Refactoring to a OCP-Compliant Example =====
// Define a stable abstraction and extend behavior via new subclasses.

#include <iostream>
#include <memory>

// 1) Abstraction (interface)
class ShippingCostCalculator
{
public:
    virtual ~ShippingCostCalculator() = default;
    virtual double calculate(double weightKg) const = 0;
};

// 2) Initial implementations
class GroundShipping : public ShippingCostCalculator
{
public:
    double calculate(double weightKg) const override
    {
        return 5.0 + 1.2 * weightKg;
    }
};

class AirShipping : public ShippingCostCalculator
{
public:
    double calculate(double weightKg) const override
    {
        return 10.0 + 3.5 * weightKg;
    }
};

// 3) Client depends only on the abstraction
class ShippingServiceOCP
{
    const ShippingCostCalculator &calculator;

public:
    explicit ShippingServiceOCP(const ShippingCostCalculator &calc)
        : calculator(calc) {}
    void ship(double weightKg) const
    {
        std::cout << "Cost: $" << calculator.calculate(weightKg) << "\n";
    }
};

int mainOCP()
{
    GroundShipping ground;
    ShippingServiceOCP svc1(ground);
    svc1.ship(2.5);

    AirShipping air;
    ShippingServiceOCP svc2(air);
    svc2.ship(2.5);

    // --- Later: add SeaShipping without touching any existing code ---
    class SeaShipping : public ShippingCostCalculator
    {
    public:
        double calculate(double weightKg) const override
        {
            return 3.0 + 0.8 * weightKg;
        }
    };

    SeaShipping sea;
    ShippingServiceOCP svc3(sea);
    svc3.ship(2.5);

    return 0;
}
