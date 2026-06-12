#ifndef CARMANAGER_H
#define CARMANAGER_H

#include <string>
#include "../smartArray/SmartArray.h"
#include "Car.h"

/**
 * @brief Zarządza kolekcją samochodów.
 *
 * Przechowuje samochody w kontenerze SmartArray, nadaje im kolejne
 * identyfikatory oraz udostępnia operacje dodawania, usuwania, edycji
 * i odczytu. Potrafi też zapisać i wczytać dane z pliku binarnego.
 */
class CarManager {
public:
    /**
     * @brief Tworzy pustego menedżera (brak samochodów).
     */
    CarManager() = default;

    /**
     * @brief Dodaje nowy samochód na koniec listy.
     *
     * Identyfikator jest nadawany automatycznie.
     *
     * @param brand marka
     * @param model model
     * @param year rok produkcji
     * @param mileage przebieg w km
     * @param color kolor
     */
    void add(const std::string &brand, const std::string &model,
             int year, int mileage, const std::string &color);

    /**
     * @brief Usuwa samochód spod podanego indeksu.
     *
     * @param index pozycja samochodu na liście (od 0)
     */
    void remove(unsigned index);

    /**
     * @brief Aktualizuje dane samochodu spod podanego indeksu.
     *
     * Identyfikator pozostaje bez zmian.
     *
     * @param index pozycja samochodu na liście (od 0)
     */
    void update(unsigned index, const std::string &brand, const std::string &model,
                int year, int mileage, const std::string &color);

    /**
     * @brief Zwraca samochód spod podanego indeksu.
     *
     * @param index pozycja samochodu na liście (od 0)
     * @return stała referencja do samochodu
     */
    [[nodiscard]] const Car &get(unsigned index) const;

    /**
     * @brief Zwraca liczbę samochodów na liście.
     */
    [[nodiscard]] unsigned count() const;

    /**
     * @brief Sprawdza czy lista jest pusta.
     */
    [[nodiscard]] bool isEmpty() const;

    /**
     * @brief Zwraca średni rocznik wszystkich samochodów.
     *
     * @return średni rok produkcji lub 0, gdy lista jest pusta
     */
    [[nodiscard]] int averageYear() const;

    /**
     * @brief Zwraca sumę przebiegu samochodów danej marki.
     *
     * @param brand szukana marka
     * @return suma przebiegów (w km)
     */
    [[nodiscard]] long totalMileageForBrand(const std::string &brand) const;

    /**
     * @brief Wczytuje samochody z pliku binarnego.
     *
     * Jeśli plik nie istnieje, lista pozostaje bez zmian.
     *
     * @param filename nazwa pliku
     */
    void loadFromFile(const std::string &filename);

    /**
     * @brief Zapisuje samochody do pliku binarnego.
     *
     * @param filename nazwa pliku
     */
    void saveToFile(const std::string &filename) const;

private:
    SmartArray<Car> _cars;
    unsigned _nextId = 1;
};

#endif
