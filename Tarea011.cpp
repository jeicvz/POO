#include <iostream>
#include <cmath>      // Para M_PI
#include <vector>     // Para RepoVector
using namespace std;

class RepoArrFloat {
private:
    float data[100];
    int count = 0;
public:
    void Save(float valor) {
        if (count < 100) {
            data[count++] = valor;
            cout << "Área guardada en arreglo [" << count - 1 << "]: " << valor << endl;
        } else {
            cout << "Repositorio arreglo lleno\n";
        }
    }

    float GetArea(int index) const {
        if (index >= 0 && index < count) {
            return data[index];
        } else {
            cout << "Índice inválido en arreglo\n";
            return -1;
        }
    }

    int getCount() const {
        return count;
    }
};

class RepoVector {
private:
    vector<float> data;
public:
    void Save(float valor) {
        data.push_back(valor);
        cout << "Área guardada en vector [" << data.size() - 1 << "]: " << valor << endl;
    }

    float GetArea(int index) const {
        if (index >= 0 && index < data.size()) {
            return data[index];
        } else {
            cout << "Índice inválido en vector\n";
            return -1;
        }
    }

    int getCount() const {
        return data.size();
    }
};

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

class FigFactory {
public:
    virtual IFig* createFig() = 0;
    virtual ~FigFactory() {}
};

class TriangleFactory : public FigFactory {
    double base, altura;
public:
    TriangleFactory(double b, double h) : base(b), altura(h) {}
    IFig* createFig() override {
        return new Triangle(base, altura);
    }
};

class CircleFactory : public FigFactory {
    double radio;
public:
    CircleFactory(double r) : radio(r) {}
    IFig* createFig() override {
        return new Circle(radio);
    }
};

class SquareFactory : public FigFactory {
    double lado;
public:
    SquareFactory(double l) : lado(l) {}
    IFig* createFig() override {
        return new Square(lado);
    }
};

int main() {
    FigFactory* factories[3];
    factories[0] = new TriangleFactory(3.0, 4.0);
    factories[1] = new CircleFactory(2.5);
    factories[2] = new SquareFactory(5.0);

    IFig* figuras[3];
    FigGeoPrinter* impresoras[3];

    RepoArrFloat repoArr;
    RepoVector repoVec;

    for (int i = 0; i < 3; ++i) {
        figuras[i] = factories[i]->createFig();
        impresoras[i] = dynamic_cast<FigGeoPrinter*>(figuras[i]);
    }

    for (int i = 0; i < 3; ++i) {
        float area = figuras[i]->area();    
        figuras[i]->mostrar(); 
        impresoras[i]->PrintDetails(); 
        repoArr.Save(area);
        repoVec.Save(area);

        delete figuras[i];
        delete factories[i];
    }

    cout << "\n--- Áreas almacenadas en el REPO ARREGLO ---\n";
    for (int i = 0; i < repoArr.getCount(); ++i) {
        cout << "Área[" << i << "]: " << repoArr.GetArea(i) << "\n";
    }

    cout << "\n--- Áreas almacenadas en el REPO VECTOR ---\n";
    for (int i = 0; i < repoVec.getCount(); ++i) {
        cout << "Área[" << i << "]: " << repoVec.GetArea(i) << "\n";
    }

    return 0;
}
