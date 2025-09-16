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
    shapes.emplace_back(std::make_unique<Circle>(5.0));       // Circle radius 5
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
