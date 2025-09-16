
# Shape Hierarchy Demo (C++)

A small example that demonstrates **interfaces via abstract base classes**, **inheritance**, and **runtime polymorphism** in C++ using a `Shape` hierarchy.

---

## What this program shows

- **Abstract base class:** `Shape` declares pure virtual methods `area()` and `describe()`.
- **Inheritance:** `Circle`, `Rectangle`, and `Triangle` derive from `Shape`.
- **Polymorphism:** Base-class pointers (`Shape*`) refer to derived objects; calling virtual functions dispatches to the correct override.
- **Resource cleanup:** Virtual destructor in `Shape` ensures proper destruction through base pointers.

---

## File Contents

```cpp
#include <iostream>
#include <cmath>
```

- `<iostream>` for console I/O.
- `<cmath>` for `M_PI` and math.

> On MSVC, you may need to `#define _USE_MATH_DEFINES` **before** including `<cmath>` to use `M_PI`.

---

## Class Overview

### `class Shape`
- **Role:** Abstract interface for all shapes.
- **Key members:**
  - `virtual ~Shape() {}` — virtual destructor for safe polymorphic deletion.
  - `virtual double area() const = 0;` — pure virtual, must be implemented by derived classes.
  - `virtual void describe() const = 0;` — pure virtual, prints human-readable details.

### `class Circle : public Shape`
- **State:** `double radius;`
- **Ctor:** `Circle(double r)`
- **Overrides:**
  - `double area() const` → `πr²`
  - `void describe() const` → prints radius

### `class Rectangle : public Shape`
- **State:** `double width, height;`
- **Ctor:** `Rectangle(double w, double h)`
- **Overrides:**
  - `double area() const` → `width * height`
  - `void describe() const` → prints width/height

### `class Triangle : public Shape`
- **State:** `double base, height;`
- **Ctor:** `Triangle(double b, double h)`
- **Overrides:**
  - `double area() const` → `0.5 * base * height`
  - `void describe() const` → prints base/height

---

## How `main()` Works

1. **Create shapes via base pointers:**
   ```cpp
   Shape* shape1 = new Circle(5.0);
   Shape* shape2 = new Rectangle(4.0, 6.0);
   Shape* shape3 = new Triangle(3.0, 7.0);
   ```
2. **Store them together (heterogeneous collection):**
   ```cpp
   Shape* shapes[] = { shape1, shape2, shape3 };
   ```
3. **Polymorphic calls in a loop:**
   ```cpp
   for (int i = 0; i < 3; ++i) {
       shapes[i]->describe();               // calls derived describe()
       std::cout << "Area: " << shapes[i]->area() << '\n'; // calls derived area()
       std::cout << "--------------------------" << std::endl;
   }
   ```
4. **Clean up:**
   ```cpp
   delete shape1;
   delete shape2;
   delete shape3;
   ```
   Thanks to `virtual ~Shape()`, the correct derived destructors (if any) would run.

---

## Example Output

```
Circle with radius: 5
Area: 78.5398
--------------------------
Rectangle with width: 4 and height: 6
Area: 24
--------------------------
Triangle with base: 3 and height: 7
Area: 10.5
--------------------------
```

(Exact formatting/precision of `Area` may vary by environment.)

---

## Build & Run

### Linux / macOS (clang++ or g++)
```bash
g++ -std=c++17 -O2 shapes.cpp -o shapes
./shapes
```

### Windows (MSVC)
If you need `M_PI`:
```cpp
#define _USE_MATH_DEFINES
#include <cmath>
```
Then build with Developer Command Prompt:
```bat
cl /EHsc /std:c++17 shapes.cpp
shapes.exe
```

---

## Design Notes & Best Practices

- **Why a virtual destructor?** Deleting through a base-class pointer without a virtual destructor is undefined behavior if the derived class owns resources.
- **Const-correctness:** `area()` and `describe()` are `const` because they don’t modify object state.
- **Avoiding raw `new`/`delete`:** Prefer RAII with smart pointers:
  ```cpp
  #include <memory>
  std::unique_ptr<Shape> s1 = std::make_unique<Circle>(5.0);
  ```
  and store `std::unique_ptr<Shape>` in a `std::vector` to eliminate manual `delete`.

---

## Extending the Hierarchy

To add a new shape:

1. Derive from `Shape`.
2. Add necessary member variables.
3. Implement:
   ```cpp
   double area() const override { /* formula */ }
   void describe() const override { /* print details */ }
   ```
4. Use it via `Shape*`/`std::unique_ptr<Shape>` to benefit from polymorphism.

---

## Simple UML (ASCII)

```
     +------------------+
     |     Shape        |<<abstract>>
     |------------------|
     | + area()=0       |
     | + describe()=0   |
     | + ~Shape()       |
     +---------^--------+
               |
   +-----------+-----------+--------------+
   |                       |              |
+--------+            +-----------+   +-----------+
| Circle |            | Rectangle |   | Triangle  |
|radius  |            |w, h       |   |b, h       |
+--------+            +-----------+   +-----------+
| area() |            | area()    |   | area()    |
| desc() |            | desc()    |   | desc()    |
+--------+            +-----------+   +-----------+
```

---

## Common Pitfalls

- **`M_PI` not defined:** Define `_USE_MATH_DEFINES` before `<cmath>` on MSVC, or use `constexpr double PI = 3.141592653589793;`.
- **Forgetting `virtual` destructor:** Leads to undefined behavior when deleting via `Shape*`.
- **Object slicing:** Storing derived objects **by value** in a container of base type slices them. Use pointers or references (ideally smart pointers).

---

## Variations to Try

- Add `perimeter()` as another pure virtual method.
- Use `std::vector<std::unique_ptr<Shape>>` instead of raw arrays/pointers.
- Add input validation and formatted output with `std::fixed << std::setprecision(2)` for areas.
````


