#include <iostream>
#include <cmath>  // Para M_PI
using namespace std;
class FigGeoPrinter {
public:
    virtual void PrintDetails() = 0;
};
class IFig {
public:
    virtual double area() = 0;
    virtual double perimetro() const = 0;
    virtual void mostrar() const = 0;
    virtual ~IFig() {}
};
class FigGeo {
protected:
    double _area = 0;
public:
    virtual double calcArea() = 0;

    void saveArea() {
        if (_area == 0) {
            cout << "Calculando área...\n";
            _area = calcArea();
        }
    }

    double getArea() const {
        return _area;
    }
};
class Triangle : public IFig, public FigGeo, public FigGeoPrinter {
private:
    double base, altura;
public:
    Triangle(double b, double h) : base(b), altura(h) {}

    double calcArea() override {
        return (base * altura) / 2.0;
    }

    double area() override {
        saveArea();
        return getArea();
    }

    double perimetro() const override {
        return 3 * base; 
    }

    void mostrar() const override {
        cout << "Triangle:\n";
        cout << "Base: " << base << ", Altura: " << altura << endl;
        cout << "Área: " << _area << endl;
        cout << "Perímetro: " << perimetro() << "\n\n";
    }

    void PrintDetails() override {
        cout << "[PrintDetails] Triángulo - base = " << base << ", altura = " << altura << ", área = " << _area << "\n";
    }
};

class Circle : public IFig, public FigGeo, public FigGeoPrinter {
private:
    double radio;
public:
    Circle(double r) : radio(r) {}

    double calcArea() override {
        return M_PI * radio * radio;
    }

    double area() override {
        saveArea();
        return getArea();
    }

    double perimetro() const override {
        return 2 * M_PI * radio;
    }

    void mostrar() const override {
        cout << "Circle:\n";
        cout << "Radio: " << radio << endl;
        cout << "Área: " << _area << endl;
        cout << "Perímetro: " << perimetro() << "\n\n";
    }

    void PrintDetails() override {
        cout << "[PrintDetails] Círculo - radio = " << radio << ", área = " << _area << "\n";
    }
};

class Square : public IFig, public FigGeo, public FigGeoPrinter {
private:
    double lado;
public:
    Square(double l) : lado(l) {}

    double calcArea() override {
        return lado * lado;
    }

    double area() override {
        saveArea();
        return getArea();
    }

    double perimetro() const override {
        return 4 * lado;
    }

    void mostrar() const override {
        cout << "Square:\n";
        cout << "Lado: " << lado << endl;
        cout << "Área: " << _area << endl;
        cout << "Perímetro: " << perimetro() << "\n\n";
    }

    void PrintDetails() override {
        cout << "[PrintDetails] Cuadrado - lado = " << lado << ", área = " << _area << "\n";
    }
};

int main() {
    IFig* figuras[3];
    FigGeoPrinter* impresoras[3];

    figuras[0] = new Triangle(3.0, 4.0);
    figuras[1] = new Circle(2.5);
    figuras[2] = new Square(5.0);

    impresoras[0] = dynamic_cast<FigGeoPrinter*>(figuras[0]);
    impresoras[1] = dynamic_cast<FigGeoPrinter*>(figuras[1]);
    impresoras[2] = dynamic_cast<FigGeoPrinter*>(figuras[2]);

    for (int i = 0; i < 3; ++i) {
        figuras[i]->area();    
        figuras[i]->mostrar(); 
        impresoras[i]->PrintDetails(); 
        delete figuras[i];
    }

    return 0;
}
