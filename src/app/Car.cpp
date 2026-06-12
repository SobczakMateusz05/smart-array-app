#include "Car.h"

Car::Car(unsigned id, const std::string &brand, const std::string &model,
         int year, int mileage, const std::string &color)
    : _id(id), _brand(brand), _model(model),
      _year(year), _mileage(mileage), _color(color) {
}

unsigned Car::getId() const {
    return _id;
}

const std::string &Car::getBrand() const {
    return _brand;
}

const std::string &Car::getModel() const {
    return _model;
}

int Car::getYear() const {
    return _year;
}

int Car::getMileage() const {
    return _mileage;
}

const std::string &Car::getColor() const {
    return _color;
}

void Car::setId(unsigned id) {
    _id = id;
}

void Car::setBrand(const std::string &brand) {
    _brand = brand;
}

void Car::setModel(const std::string &model) {
    _model = model;
}

void Car::setYear(int year) {
    _year = year;
}

void Car::setMileage(int mileage) {
    _mileage = mileage;
}

void Car::setColor(const std::string &color) {
    _color = color;
}
