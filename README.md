# Shape Hierarchy Demo (C++)

A small example that demonstrates **interfaces via abstract base classes**, **inheritance**, and **runtime polymorphism** in C++ using a `Shape` hierarchy.

---

## What this program shows

- **Abstract base class:** `Shape` declares pure virtual methods `area()` and `describe()`.
- **Inheritance:** `Circle`, `Rectangle`, and `Triangle` derive from `Shape`.
- **Polymorphism:** A `std::vector<std::unique_ptr<Shape>>` stores different shapes; calling virtual functions dispatches to the correct override.
- **Resource cleanup:** Virtual destructor in `Shape` ensures proper destruction of derived objects when `unique_ptr` goes out of scope.

---

## File Contents

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

// Prefer a portable PI constant instead of relying on M_PI on all compilers.
constexpr double PI = 3.141592653589793;

// Base class Shape
class Shape {
public:
    virtual ~Shape() = default;                  // Virtual destructor for polymorphic cleanup
    virtual double area() const = 0;             // Pure virtual: compute area
    virtual void describe() const = 0;           // Pure virtual: print a description
};

// Derived class Circle
class Circle : public Shape {
private:
    double radius;

public:
    explicit Circle(double r) : radius(r) {}

    double area() const override {
        return PI * radius * radius;
    }

    void describe() const override {
        std::cout << "Circle with radius: " << radius << std::endl;
    }
};

// Derived class Rectangle
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    void describe() const override {
        std::cout << "Rectangle with width: " << width
                  << " and height: " << height << std::endl;
    }
};

// Derived class Triangle
class Triangle : public Shape {
private:
    double base, height;

public:
    Triangle(double b, double h) : base(b), height(h) {}

    double area() const override {
        return 0.5 * base * height;
    }

    void describe() const override {
        std::cout << "Triangle with base: " << base
                  << " and height: " << height << std::endl;
    }
};

int main() {
    // Use RAII with std::unique_ptr inside std::vector (no manual delete needed)
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_unique<Circle>(5.0));         // Circle radius 5
    shapes.emplace_back(std::make_unique<Rectangle>(4.0, 6.0)); // Rectangle 4x6
    shapes.emplace_back(std::make_unique<Triangle>(3.0, 7.0));  // Triangle b=3, h=7

    // Polymorphic calls via base-class interface
    for (const auto& shape : shapes) {
        shape->describe();
        std::cout << "Area: " << shape->area() << std::endl;
        std::cout << "--------------------------" << std::endl;
    }

    // No need to delete; unique_ptr cleans up automatically.
    return 0;
}
```

---

## How `main()` Works

1. **Create shapes with smart pointers:**  
   `std::make_unique` constructs each derived object and wraps it in a `std::unique_ptr<Shape>`.

2. **Store them in a `std::vector`:**  
   All shapes live in a single container, allowing iteration and polymorphic calls.

3. **Polymorphic calls in a loop:**
   ```cpp
   for (const auto& shape : shapes) {
       shape->describe();
       std::cout << "Area: " << shape->area() << std::endl;
   }
   ```

4. **Automatic cleanup:**  
   When `shapes` goes out of scope, the `unique_ptr` objects automatically delete their owned shapes.  
   No explicit `delete` statements are required.

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
g++ -std=c++17 -O2 shapes_vector.cpp -o shapes_vector
./shapes_vector
```

### Windows (MSVC)
```bat
cl /EHsc /std:c++17 shapes_vector.cpp
shapes_vector.exe
```

---

## Design Notes & Best Practices

- **Why `unique_ptr`?**  
  Eliminates manual `delete` and guarantees destruction even if exceptions are thrown.
- **Virtual destructor:**  
  Required for safe polymorphic deletion—`unique_ptr<Shape>` will correctly call derived destructors.
- **Const-correctness:**  
  `area()` and `describe()` are `const` because they don’t modify the object.

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
4. Add it to the vector with:
   ```cpp
   shapes.emplace_back(std::make_unique<NewShape>(/*args*/));
   ```

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

- **Object slicing:**  
  Storing derived objects **by value** in a container of base type slices them. Using `std::unique_ptr<Shape>` avoids this.
- **Missing virtual destructor:**  
  Would cause undefined behavior when `unique_ptr` deletes a derived object.
- **Copying `unique_ptr`:**  
  `unique_ptr` cannot be copied—use `emplace_back` or `std::move` to transfer ownership.

---

## Variations to Try

- Add `perimeter()` as another pure virtual method.
- Format areas with `std::fixed << std::setprecision(2)`.
- Use `std::shared_ptr` if multiple owners of a shape are required.
