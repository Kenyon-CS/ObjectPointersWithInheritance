#include <iostream>
#include <cmath>

// Base class Shape
class Shape {
public:
    // Virtual destructor to ensure proper cleanup of derived objects
    virtual ~Shape() {}
    
    // Pure virtual function to calculate the area
    virtual double area() const = 0;

    // Pure virtual function to describe the shape
    virtual void describe() const = 0;
};

// Derived class Circle
class Circle : public Shape {
private:
    double radius;

public:
    // Constructor
    Circle(double r) : radius(r) {}

    // Overriding the area function
    double area() const override {
        return M_PI * radius * radius;
    }

    // Overriding the describe function
    void describe() const override {
        std::cout << "Circle with radius: " << radius << std::endl;
    }
};

// Derived class Rectangle
class Rectangle : public Shape {
private:
    double width, height;

public:
    // Constructor
    Rectangle(double w, double h) : width(w), height(h) {}

    // Overriding the area function
    double area() const override {
        return width * height;
    }

    // Overriding the describe function
    void describe() const override {
        std::cout << "Rectangle with width: " << width << " and height: " << height << std::endl;
    }
};

// Derived class Triangle
class Triangle : public Shape {
private:
    double base, height;

public:
    // Constructor
    Triangle(double b, double h) : base(b), height(h) {}

    // Overriding the area function
    double area() const override {
        return 0.5 * base * height;
    }

    // Overriding the describe function
    void describe() const override {
        std::cout << "Triangle with base: " << base << " and height: " << height << std::endl;
    }
};

int main() {
    // Using dynamic allocation for base class pointers pointing to derived class objects
    Shape* shape1 = new Circle(5.0);      // Circle with radius 5
    Shape* shape2 = new Rectangle(4.0, 6.0);  // Rectangle with width 4 and height 6
    Shape* shape3 = new Triangle(3.0, 7.0);   // Triangle with base 3 and height 7

    // Array of shape pointers to demonstrate polymorphism
    Shape* shapes[] = { shape1, shape2, shape3 };

    // Loop through each shape, call describe() and area() polymorphically
    for (int i = 0; i < 3; ++i) {
        shapes[i]->describe();
        std::cout << "Area: " << shapes[i]->area() << std::endl;
        std::cout << "--------------------------" << std::endl;
    }

    // Deallocate memory
    delete shape1;
    delete shape2;
    delete shape3;

    return 0;
}
