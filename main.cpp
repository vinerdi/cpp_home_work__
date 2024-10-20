#include <iostream>
#include <string>
using namespace std;

// Logger class for logging messages
class Logger {
public:
    static bool is_print_logs;
    static void log(const string& message, const string& color) {
        if (is_print_logs) {
            cout << "[" << color << "] " << message << endl;
        }
    }
};

bool Logger::is_print_logs = true;

// Abstract base class for shapes
class Shape {
public:
    virtual void draw() const = 0;  // pure virtual function for drawing shapes
    virtual ~Shape() {}
};

// Interface for providing information about shapes
class Informable {
public:
    virtual void info() const = 0;  // pure virtual function for providing information
    virtual ~Informable() {}
};

// Circle class inheriting from Shape and Informable
class Circle : public Shape, public Informable {
protected:
    string name;
    string color;
public:
    Circle(string n = "Circle", string c = "Red") : name(n), color(c) {
        Logger::log("Circle created", "Green");
    }

    void draw() const override {
        cout << "Drawing a " << color << " " << name << endl;
    }

    void info() const override {
        cout << "Name: " << name << ", Color: " << color << endl;
    }

    ~Circle() override {
        Logger::log("Circle destroyed", "Red");
    }
};

// Square class inheriting from Shape and Informable
class Square : public Shape, public Informable {
protected:
    string name;
    string color;
public:
    Square(string n = "Square", string c = "Blue") : name(n), color(c) {
        Logger::log("Square created", "Green");
    }

    void draw() const override {
        cout << "Drawing a " << color << " " << name << endl;
    }

    void info() const override {
        cout << "Name: " << name << ", Color: " << color << endl;
    }

    ~Square() override {
        Logger::log("Square destroyed", "Red");
    }
};

// CircleInSquare class inheriting from both Circle and Square (Multiple Inheritance)
class CircleInSquare : public Circle, public Square {
public:
    CircleInSquare() : Circle("CircleInSquare", "Pink"), Square("CircleInSquare", "Pink") {
        Logger::log("CircleInSquare created", "Green");
    }

    // Override draw method to specify behavior for CircleInSquare
    void draw() const override {
        cout << "Drawing a Circle in a Square with color " << Circle::color << endl;
    }

    // Override info method to provide specific info for CircleInSquare
    void info() const override {
        cout << "Name: CircleInSquare, Color: " << Circle::color << endl;
    }

    ~CircleInSquare() {
        Logger::log("CircleInSquare destroyed", "Red");
    }
};

// Function to render any shape (Dependency Inversion Principle)
void renderShape(const Shape& shape) {
    shape.draw();
}

#define skipln cout << endl;

int main() {
    Logger::is_print_logs = true;

    // Demonstrating multiple inheritance with CircleInSquare class
    CircleInSquare* figure = new CircleInSquare();
    figure->info();
    figure->draw();
    skipln;

    // Using dependency inversion principle
    renderShape(static_cast<const Circle&>(*figure));
    skipln;

    // Clean up
    delete figure;

    return 0;
}