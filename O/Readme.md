# Open/Closed Principle (OCP)

## Definition
The **Open/Closed Principle** states that software entities (classes, modules, functions, etc.) should be **open for extension** but **closed for modification**. In other words, you should be able to add new behavior without changing existing code.

---

## Key Terms
- **Extension**: Adding new functionality by introducing new code (e.g., subclasses, decorators, plugins).  
- **Modification**: Changing existing source code.  
- **Abstraction**: Relying on interfaces or abstract base classes to define contracts.  
- **Polymorphism**: Using a common interface to refer to different concrete implementations.

---

## Use Cases
- **Adding New Variants**: Introducing new strategies (e.g., new sorting or compression algorithms) without touching the core engine.  
- **Feature Flags / Plugins**: Loading new features via plugin modules that implement a known interface.  
- **Reporting Engines**: Supporting new report formats (PDF, Excel, JSON) by implementing a `IReportGenerator` interface.  
- **Payment Processing**: Accepting new payment gateways (Stripe, ApplePay) by adding classes that implement `IPaymentMethod`.

---

## Benefits
- **Reduced Risk**: Existing, tested code remains untouched, minimizing regressions.  
- **Easier Maintenance**: New requirements can be satisfied by adding new modules or classes.  
- **Scalability**: System grows organically by plugging in new behaviors.  
- **Clear Separation**: Core logic depends on abstractions, not concrete implementations.

---

## When to Use / When Not to Use

### When to Use
- You expect to add new variants or behaviors over time.  
- The core logic is stable, but the set of supported types or strategies may grow.  
- You want to minimize changes to existing, well-tested code.

### When Not to Use
- For very small or throw-away prototypes where YAGNI applies (You Aren’t Gonna Need It).  
- When the overhead of abstraction (interfaces, indirection) outweighs the benefit.  
- If requirements are unlikely to change, and simplicity is paramount.

