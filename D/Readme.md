# Dependency Inversion Principle (DIP)

## Definition
The **Dependency Inversion Principle** prescribes two key rules:
1. **High-level modules** should not depend on **low-level modules**. Both should depend on **abstractions**.  
2. **Abstractions** should not depend on **details**. **Details** (concrete implementations) should depend on **abstractions**.

By inverting traditional dependencies, DIP decouples the overall system and fosters flexible architecture.

---

## Key Terms
- **High-Level Module**  
  Contains business logic or orchestration (e.g. a service layer).  
- **Low-Level Module**  
  Provides concrete functionality (e.g. database access, file I/O).  
- **Abstraction**  
  An interface or abstract class that defines a contract without implementation.  
- **Dependency Injection**  
  A technique for supplying an object’s dependencies from the outside, rather than creating them internally.  
- **Inversion of Control (IoC)**  
  A design principle where control over flow and dependencies is inverted, often implemented via DIP and DI.

---

## Use Cases
- **Data Access Layers**  
  Define a repository interface (`IUserRepository`) and inject concrete implementations (SQL, NoSQL, in-memory) into services.  
- **Logging Frameworks**  
  Depend on an `ILogger` interface and plug in console, file, or remote loggers without changing business code.  
- **Payment Gateways**  
  Business logic works against `IPaymentProcessor`; add Stripe, PayPal, or mock implementations via configuration.  
- **UI & Rendering Engines**  
  High-level UI components depend on abstract rendering back-ends (OpenGL, DirectX, Vulkan).  
- **Plugin Architectures**  
  Load modules dynamically by relying on a well-defined plugin interface.

---

## Benefits
- **Loose Coupling**  
  High-level code is unaware of concrete implementations, reducing interdependencies.  
- **Flexibility & Extensibility**  
  Swap or add implementations without modifying client code.  
- **Testability**  
  Easily inject mocks or stubs for unit testing high-level modules.  
- **Maintainability**  
  Changes to low-level details do not cascade into business logic.

---

## When to Use / When Not to Use

### When to Use
- You have distinct layers (UI, service, data) that should remain independent.  
- Multiple implementations (e.g. databases, external services) may be substituted.  
- You need to unit-test business logic in isolation from external dependencies.  
- The project scope and longevity justify architectural flexibility.

### When Not to Use
- In small throw-away scripts or prototypes where simplicity is paramount.  
- When there is only a single implementation and no foreseeable need for substitution.  
- In performance-critical hotspots where indirection costs are unacceptable.  
- If added abstractions would introduce undue complexity without real benefit.

