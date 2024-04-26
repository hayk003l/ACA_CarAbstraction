#include <iostream>

class Car {
    private:
    std::string _make = "Mercedes-Benz";
    int _year = 2024;
    std::string _color = "White";
    int _hp = 350;

    public:

    Car() {}

    Car(const std::string& make, const int& year, const std::string& color, const int& hp) : _make(make), _year(year), _color(color), _hp(hp)  {
        std::cout << "Call ctor" << std::endl;
    }

    ~Car() {
        std::cout << "Call dtor" << std::endl;
    }

    void printCar() {
        std::cout << "Make = " << _make << std::endl;
        std::cout << "Year = " << _year << std::endl;
        std::cout << "Color = " << _color << std::endl;
        std::cout << "Horse Power = " << _hp << std::endl;
    
        std::cout << std::endl;
    }

};


class Parking {
    private:
    Car** _arr = nullptr;
    int _size = 0;
    int _count = 0;

    public:
    Parking(const int& size) : _size(size) {
        _arr = new Car*[_size];
        for (int i = 0; i < _size; ++i) {
            _arr[i] = new Car;
        }
    }

    Parking (const Parking& obj) {  
        std::cout << "Copy ctor" << std::endl;
        this->_size = obj._size;
        this->_count = obj._count;
        _arr = new Car*[_size];
        for (int i = 0; i < _size; ++i) {
            _arr[i] = new Car;
        }

        for (int i = 0; i < _count; ++i) {
            _arr[i] = obj._arr[i];
        }
    }

    Parking& operator=(const Parking& obj) {
        if(this != &obj) {
            for (int i = 0; i < _count; ++i) {
                delete[] _arr[i];
            }
            delete[] _arr;
            
            this->_size = obj._size;
            this->_count = obj._count;
            _arr = new Car*[_size];
            
            for (int i = 0; i < _size; ++i) {
            _arr[i] = new Car;
            }

            for (int i = 0; i < _count; ++i) {
                _arr[i] = obj._arr[i];
            }
        }
        return *this;
    }

    ~Parking() {
        std::cout << "Call Parking dtor" << std::endl;
        for (int i = 0; i < _size; ++i) {
            delete _arr[i];
        }
        delete[] _arr; 
    }
    bool registerCar(Car* newCar) {
        bool result = false;
        if(_size >= _count) {
            _arr[_count] = newCar;
            _count++;
            result = true;
        }  
        return result;
    }

    void removeCar(const int& index) {
        for (int i = index; i < _count - 1; ++i) {
            _arr[i] = _arr[i + 1];
        }
        _count--;
    }

    void  printArr() const {
        for(int i = 0; i < _count; ++i) {
            _arr[i]->printCar();
        }
    }
};


int main() {

    Car obj1("Toyota Supra", 1994, "Red", 1000);
    Car obj2("Toyota Mark II", 1995, "White", 900);
    Car obj3;
    Car obj4;

   Parking carParking(5);

    carParking.registerCar(&obj1);
    carParking.registerCar(&obj2);
    carParking.registerCar(&obj3);
    carParking.registerCar(&obj3);

    std::cout << "First parking" << std::endl;

    carParking.printArr();

    carParking.removeCar(1);
    carParking.printArr();

    std::cout << "First parking after removing car" << std::endl;

    Parking carParkingTwo = carParking;

    std::cout << "Second parking" << std::endl;

    carParkingTwo.printArr();

    return 0;
}