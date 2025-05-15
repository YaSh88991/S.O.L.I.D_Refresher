# Single Responsibility Principle (SRP)

## Definition
A class (or module) should have **only one reason to change**. SRP mandates that each unit of code encapsulates a single responsibility or concern, so modifications to one aspect of the system affect only one place.

---

## Key Terms
- **Responsibility**: A coherent set of related behaviors or functions.  
- **Concern**: A specific area of interest or functionality in the application.  
- **Cohesion**: The degree to which the elements of a module belong together. High cohesion means one focused purpose.

---

## Use Cases
- **Report Generation**: Separating formatting (HTMLFormatter) from file output (FileWriter) and data (Report).  
- **Logging Systems**: Splitting log message creation, log level filtering, and log persistence into distinct classes.  
- **Configuration Management**: One class parses configuration files, another provides access to values, another watches for changes.

---

## Benefits
- **Maintainability**: Changes to one concern (e.g. formatting) don’t ripple into unrelated code (e.g. file I/O).  
- **Testability**: You can write focused unit tests for each class without stubbing out unrelated logic.  
- **Reusability**: Small, purpose-driven classes can be reused across different contexts.  
- **Readability**: Developers immediately see a class’s sole purpose, reducing cognitive load.

---

## When to Use / When Not to Use

### When to Use
- You identify a class doing more than one task (e.g. computing + persisting).  
- You want to make a piece of code easier to test in isolation.  
- You foresee multiple implementations of a responsibility (e.g. different file formats).

### When Not to Use
- For very small helper classes whose single method is unlikely to change separately.  
- When the overhead of extra classes outweighs the benefit (e.g. trivial, stable code).  
- If splitting responsibilities would lead to an explosion of classes with negligible logic.

