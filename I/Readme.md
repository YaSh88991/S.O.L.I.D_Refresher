# Interface Segregation Principle (ISP)

## Definition
The **Interface Segregation Principle** states that **clients should not be forced to depend on interfaces they do not use**. Rather than one large “fat” interface, you should define many small, role-specific interfaces so that implementing classes only need to provide the methods relevant to them.

---

## Key Terms
- **Interface**: A contract (in C++, an abstract class with pure-virtual methods) that declares a set of operations.  
- **Client**: Any class or module that uses an interface’s methods.  
- **Fat Interface**: An interface that contains methods not needed by all clients, leading to unnecessary obligations.  
- **Segregation**: The process of splitting a fat interface into multiple smaller, cohesive interfaces.

---

## Use Cases
- **Printer/Scanner/Multifunction Devices**  
  - Separate `IPrinter`, `IScanner`, and `IFax` rather than one `IMachine` with all methods.  
- **User Notifications**  
  - Define `IEmailNotifier`, `ISmsNotifier`, and `IPushNotifier` so classes only implement the channels they support.  
- **Vehicle Controls**  
  - Split `IVehicle` into `IDrivable`, `ITestable`, `IMaintainable` so a `Bicycle` need not implement `startEngine()`.

---

## Benefits
- **Reduced Coupling**: Clients only depend on the methods they actually use, minimizing ripple effects when interfaces change.  
- **Improved Maintainability**: Smaller interfaces are easier to understand, document, and evolve.  
- **Enhanced Testability**: You can mock or stub only the specific interface needed in a test, without unneeded method stubs.  
- **Greater Flexibility**: New implementers can pick and choose which fine-grained interfaces to support.

---

## When to Use / When Not to Use

### When to Use
- You observe interfaces with many methods, where clients only ever call a subset.  
- Adding new operations to a shared interface would force unrelated classes to implement stubs.  
- You want clear separation of roles and responsibilities across implementing classes.

### When Not to Use
- Interfaces are already small and cohesive—splitting further adds no value.  
- You’re defining temporary prototypes or throw-away code where simplicity matters more than strict segregation.  
- The overhead of multiple tiny interfaces outweighs the benefits in a very simple domain.

