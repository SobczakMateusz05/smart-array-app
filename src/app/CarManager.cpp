#include "CarManager.h"
#include <fstream>

void CarManager::add(const std::string &brand, const std::string &model,
                     int year, int mileage, const std::string &color) {
    _cars.pushBack(Car(_nextId++, brand, model, year, mileage, color));
}

void CarManager::remove(unsigned index) {
    _cars.erase(index);
}

void CarManager::update(unsigned index, const std::string &brand, const std::string &model,
                        int year, int mileage, const std::string &color) {
    Car &c = _cars[index];
    c.setBrand(brand);
    c.setModel(model);
    c.setYear(year);
    c.setMileage(mileage);
    c.setColor(color);
}

const Car &CarManager::get(unsigned index) const {
    return _cars.at(index);
}

unsigned CarManager::count() const {
    return _cars.size();
}

bool CarManager::isEmpty() const {
    return _cars.isEmpty();
}

int CarManager::averageYear() const {
    if (_cars.isEmpty()) return 0;

    long suma = 0;
    for (unsigned i = 0; i < _cars.size(); i++)
        suma += _cars[i].getYear();

    return (int) (suma / _cars.size());
}

long CarManager::totalMileageForBrand(const std::string &brand) const {
    long suma = 0;
    for (unsigned i = 0; i < _cars.size(); i++)
        if (_cars[i].getBrand() == brand)
            suma += _cars[i].getMileage();

    return suma;
}

void CarManager::loadFromFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return;
    }

    _cars.clear();
    _nextId = 1;

    unsigned howMany = 0;
    file.read((char *) &howMany, sizeof(howMany));

    for (unsigned i = 0; i < howMany; i++) {
        int id = 0, year = 0, mileage = 0;
        std::string brand, model, color;

        file.read((char *) &id, sizeof(id));

        unsigned len = 0;
        file.read((char *) &len, sizeof(len));
        brand.resize(len);
        file.read(&brand[0], len);

        file.read((char *) &year, sizeof(year));
        file.read((char *) &mileage, sizeof(mileage));

        file.read((char *) &len, sizeof(len));
        model.resize(len);
        file.read(&model[0], len);

        file.read((char *) &len, sizeof(len));
        color.resize(len);
        file.read(&color[0], len);

        if (id >= _nextId) {
            _nextId = id + 1;
        }
        _cars.pushBack(Car(id, brand, model, year, mileage, color));
    }
}

void CarManager::saveToFile(const std::string &filename) const {
    std::ofstream file(filename, std::ios::binary);

    unsigned howMany = _cars.size();
    file.write((char *) &howMany, sizeof(howMany));

    for (unsigned i = 0; i < _cars.size(); i++) {
        const Car &car = _cars[i];

        unsigned id = car.getId();
        int year = car.getYear();
        int mileage = car.getMileage();
        std::string brand = car.getBrand();
        std::string model = car.getModel();
        std::string color = car.getColor();

        file.write((char *) &id, sizeof(id));

        unsigned len = brand.size();
        file.write((char *) &len, sizeof(len));
        file.write(brand.c_str(), len);

        file.write((char *) &year, sizeof(year));
        file.write((char *) &mileage, sizeof(mileage));

        len = model.size();
        file.write((char *) &len, sizeof(len));
        file.write(model.c_str(), len);

        len = color.size();
        file.write((char *) &len, sizeof(len));
        file.write(color.c_str(), len);
    }
}
