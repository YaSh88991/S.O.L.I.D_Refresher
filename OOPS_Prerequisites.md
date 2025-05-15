
## 1. Classes & Objects

* **Class**: A user-defined data type that encapsulates data members (attributes) and member functions (behaviors). Classes serve as blueprints for creating objects.
* **Object**: A concrete instance of a class created at runtime. Each object has its own state, accessed and modified through the class’s public interface.

### Key Points:

1. **Constructors & Destructors**: Special methods that handle initialization (`Rectangle(double w, double h)`) and cleanup (`~Rectangle()`).
2. **Access Specifiers**: `public`, `protected`, and `private` control visibility and encapsulation.
3. **Member Functions**: Define behaviors; can be marked `const` when they do not modify object state.

```cpp
class Rectangle {
public:
    // Constructor initializes width and height
    Rectangle(double w, double h) : width(w), height(h) {}

    // Compute the area; marked const because it doesn't change state
    double area() const { return width * height; }

    // Optionally expose perimeter calculation
    double perimeter() const { return 2 * (width + height); }

private:
    double width;
    double height;
};

int main() {
    Rectangle rect(3.0, 4.0);
    std::cout << "Area: " << rect.area() << std::endl;
    std::cout << "Perimeter: " << rect.perimeter() << std::endl;
}
```

In this example, `Rectangle` defines two distinct behaviors (`area()` and `perimeter()`), illustrating how one class can offer multiple related operations while hiding internal details.

---

## 2. Encapsulation & Abstraction

### Encapsulation

* **Definition**: The principle of bundling data and methods operating on that data within a single unit (class), and restricting direct access to some of an object’s components.
* **Benefits**:

  * Protects object integrity by preventing external code from placing the object into an invalid state.
  * Enables internal changes without affecting external dependents.

```cpp
class BankAccount {
public:
    explicit BankAccount(double initialBalance) : balance(initialBalance) {}

    // Deposits only positive amounts
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    // Withdraws funds if sufficient balance exists
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    // Read-only access to balance
    double getBalance() const { return balance; }

private:
    double balance;
};
```

Here, direct access to `balance` is forbidden; all operations must go through `deposit()` or `withdraw()`, which enforce business rules.

### Abstraction

* **Definition**: The concept of representing essential features without including background details.
* **Implementation**:

  * Use abstract base classes and pure virtual methods to define **what** operations are available.
  * Hide complex implementation behind a clear public interface.

```cpp
// Abstract interface for various printer types
class Printer {
public:
    virtual ~Printer() = default;

    // Clients care only that they can print a message
    virtual void print(const std::string &message) = 0;
};

// Concrete implementation that prints to console
class ConsolePrinter : public Printer {
public:
    void print(const std::string &message) override {
        std::cout << message << std::endl;
    }
};

// Future-proof: new implementations like FilePrinter can be introduced without changing client code
```

With this abstraction, client code can remain unchanged even if the printing mechanism switches from console to file or network.

---

## 3. Interfaces

* **Interface**: A contract specifying a set of methods without providing implementation. Typically realized using purely abstract base classes in C++.

```cpp
class Shape {
public:
    virtual ~Shape() = default;

    // Must be implemented by derived classes
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};

class Circle : public Shape {
public:
    explicit Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
    double perimeter() const override { return 2 * 3.14159 * radius; }
private:
    double radius;
};

void printMetrics(const Shape &s) {
    std::cout << "Area: " << s.area() << ", Perimeter: " << s.perimeter() << std::endl;
}
```

By programming against the `Shape` interface, `printMetrics` can handle any future shapes (e.g., `Rectangle`, `Triangle`) uniformly.

---

## 4. Inheritance vs. Composition

### Inheritance (Extension)

* **"Is-a" Relationship**: Enables a subclass to inherit attributes and behaviors from a base class.
* **Use Cases**: When the subclass genuinely represents a specialized version of the base.

```cpp
class Vehicle {
public:
    virtual ~Vehicle() = default;
    virtual void start() = 0;
};

class Car : public Vehicle {
public:
    void start() override {
        // Specific implementation for starting a car engine
    }
};
```

### Composition (Aggregation)

* **"Has-a" Relationship**: Embeds one class as a member of another, allowing reuse of functionality without inheritance.
* **Use Cases**: When you need to utilize functionality of another class without forming a subtype.

```cpp
class Engine {
public:
    void ignite() {
        // Complex ignition logic
    }
};

class Car {
public:
    explicit Car() : engine() {}
    void start() { engine.ignite(); }
private:
    Engine engine;  // Delegation: Car delegates ignition to Engine
};
```

**Design Recommendation**: Favor composition over inheritance when you only need to reuse behavior and do not require polymorphic substitution.

---

## 5. Coupling & Cohesion

### Cohesion

* **Definition**: The degree to which the elements of a module belong together.
* **High Cohesion**: Each class or module has a focused, single responsibility.

```cpp
class Logger {
public:
    void logInfo(const std::string &msg) {
        std::cout << "[INFO] " << msg << std::endl;
    }
    void logError(const std::string &msg) {
        std::cerr << "[ERROR] " << msg << std::endl;
    }
};
```

### Coupling

* **Definition**: The degree of interdependence between software modules.
* **Loose Coupling**: Reduces dependencies by programming to interfaces rather than concrete classes.

```cpp
void processFile(IFileReader &reader, ILogger &logger) {
    auto data = reader.readAll();
    // Data processing logic
    logger.logInfo("File processed with " + std::to_string(data.size()) + " records.");
}
```

In this example, `processFile` can work with any `IFileReader` or `ILogger` implementation, facilitating testability and modularity.

---

## 6. Summary of Relationships

| Concept        | Semantic Relation     | C++ Manifestation                                   |
| -------------- | --------------------- | --------------------------------------------------- |
| Inheritance    | "Is-a" Subtype        | `class Car : public Vehicle { ... }`                |
| Composition    | "Has-a" Delegation    | `Engine engine;` embedded in `Car`                  |
| Interface      | Pure abstraction      | `class Shape { virtual ...=0; }`                    |
| Loose Coupling | Depend on interface   | Functions accept references to abstract types       |
| High Cohesion  | Single responsibility | Classes with a single, clear purpose (e.g., Logger) |

---

Armed with these detailed OOP constructs, you are now equipped to delve into the SOLID principles:

1. **Single Responsibility Principle**
2. **Open/Closed Principle**
3. **Liskov Substitution Principle**
4. **Interface Segregation Principle**
5. **Dependency Inversion Principle**


