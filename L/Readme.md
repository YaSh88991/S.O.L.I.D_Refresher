# Liskov Substitution Principle (LSP)

## Definition
Subtypes must be substitutable for their base types without altering the desirable properties of a program (correctness, task performed, etc.). In other words, if `S` is a subtype of `T`, then objects of type `T` in a program may be replaced with objects of type `S` without changing the program’s behavior.

---

## Key Terms
- **Subtype / Supertype**  
  - **Supertype (Base Type):** The abstract or concrete parent class/interface.  
  - **Subtype (Derived Type):** A class that inherits from or implements the supertype.  
- **Behavioral Subtyping**  
  Ensuring that a subtype preserves the behavior (contracts) defined by its supertype.  
- **Preconditions & Postconditions**  
  - **Precondition:** What must be true before a method is called.  
  - **Postcondition:** What must be true after the method finishes.  
  A subtype must not strengthen preconditions or weaken postconditions.  
- **Invariant**  
  A condition that must always hold true for all instances of a type, both before and after any method.

---

## Use Cases
- **Collection Hierarchies**  
  - A `SortedList` should behave like a `List` (no unexpected exceptions, ordering guarantees only add).  
  - A `ReadOnlyCollection` should support all `Collection` operations except mutation.  
- **GUI Frameworks**  
  - A `Button` subclass can be used wherever a `Widget` is expected, honoring event-handling contracts.  
- **Numeric Types**  
  - A `PositiveInteger` subtype of `Integer` should accept all operations on `Integer` without introducing invalid states (e.g., negative results).  
- **Shape Polymorphism (Area Calculation)**  
  - A `Square` subtype of `Rectangle` must not break code that assumes width and height can vary independently.

---

## Benefits
- **Reliability**: Clients relying on a base type won’t break when new subtypes arrive.  
- **Maintainability**: Reasoning about code is easier when inheritance hierarchies respect contracts.  
- **Extensibility**: New subtypes can be introduced safely, reducing regression risk.  
- **Testability**: Base-type tests automatically apply to all conforming subtypes.

---

## When to Use / When Not to Use

### When to Use
- Designing class hierarchies where subclasses truly represent specializations of a base.  
- You need polymorphic behavior and want to ensure substitutability.  
- You want to define formal contracts (pre/postconditions, invariants) and have them enforced in all derived classes.

### When Not to Use
- If a “subclass” cannot satisfy the base class contract without weakening guarantees (e.g., a `Square` that cannot behave like an unconstrained `Rectangle`).  
- When composition (`has-a`) would model relationships more naturally than inheritance (`is-a`).  
- For simple utility/helper classes where polymorphic substitution isn’t required.




## Bonus Tip

Think of LSP like swapping in a “universal remote” for your TV:

1. **Base Remote (Supertype)**
   - Has buttons: **Power**, **Volume Up/Down**, **Channel Up/Down**.  
   - TV code expects to call exactly those buttons.

2. **Universal Remote (Subtype)**
   - It can have extra buttons (e.g. **Netflix**, **Guide**), but it **must** still support Power, Volume, and Channel exactly as the original remote did—otherwise the TV won’t understand some commands.

---

> **Any place** you use the original remote, you should be able to replace it with the universal remote and **nothing breaks**.

- If the universal remote **removes** or **changes** how Volume works (say Volume Down makes it louder instead of softer), you’ll confuse the TV code.  
- If it **refuses** to respond to Channel commands in certain situations, you violate the contract.

---

### How This Maps to Code
```cpp
class Remote {
public:
    virtual void power();
    virtual void volumeUp();
    // ...
};

class UniversalRemote : public Remote {
    // ...
};
```

The UniversalRemote must honor all Remote behaviors exactly (same button effects, no extra preconditions).



## Why It Matters
- **Predictability**: Client code written for `Remote` keeps working if you pass in any `Remote`-derived object.  
- **Safety**: You won’t get surprises (exceptions, wrong behavior) just because you swapped in a new subclass.  
- **Extensibility**: You can add extra buttons or features in `UniversalRemote` without touching the TV code.

---

In short, **LSP = “Subtype won’t behave worse than the base type.”**  

If the TV code expects “channel up always goes up by one,” your subtype must do exactly that, no exceptions.
