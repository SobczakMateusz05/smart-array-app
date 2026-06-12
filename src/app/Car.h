#ifndef CAR_H
#define CAR_H

#include <string>

/**
 * @brief Pojedynczy samochód przechowywany w aplikacji.
 *
 * Klasa przechowuje dane jednego samochodu: identyfikator, markę, model,
 * rok produkcji, przebieg oraz kolor. Identyfikator jest nadawany
 * automatycznie przez CarManager.
 */
class Car {
public:
    /**
     * @brief Tworzy pusty samochód (wszystkie pola domyślne).
     */
    Car() = default;

    /**
     * @brief Tworzy samochód z podanymi danymi.
     *
     * @param id identyfikator samochodu
     * @param brand marka
     * @param model model
     * @param year rok produkcji
     * @param mileage przebieg w km
     * @param color kolor
     */
    Car(unsigned id, const std::string &brand, const std::string &model,
        int year, int mileage, const std::string &color);

    /** @brief Zwraca identyfikator. */
    [[nodiscard]] unsigned getId() const;

    /** @brief Zwraca markę. */
    [[nodiscard]] const std::string &getBrand() const;

    /** @brief Zwraca model. */
    [[nodiscard]] const std::string &getModel() const;

    /** @brief Zwraca rok produkcji. */
    [[nodiscard]] int getYear() const;

    /** @brief Zwraca przebieg w km. */
    [[nodiscard]] int getMileage() const;

    /** @brief Zwraca kolor. */
    [[nodiscard]] const std::string &getColor() const;

    /** @brief Ustawia identyfikator. */
    void setId(unsigned id);

    /** @brief Ustawia markę. */
    void setBrand(const std::string &brand);

    /** @brief Ustawia model. */
    void setModel(const std::string &model);

    /** @brief Ustawia rok produkcji. */
    void setYear(int year);

    /** @brief Ustawia przebieg w km. */
    void setMileage(int mileage);

    /** @brief Ustawia kolor. */
    void setColor(const std::string &color);

private:
    unsigned _id = 0;
    std::string _brand;
    std::string _model;
    int _year = 0;
    int _mileage = 0;
    std::string _color;
};

#endif
