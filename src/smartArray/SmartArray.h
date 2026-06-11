#ifndef SMARTARRAY_H
#define SMARTARRAY_H

#include <ostream>

/**
 * @brief Inteligentna tablica dynamiczna (kontener podobny do std::vector).
 *
 * @tparam T typ przechowywanych elementów
 *
 * Tablica przechowuje elementy w ciągłym obszarze pamięci i automatycznie
 * zarządza swoją pojemnością. Może dynamicznie zwiększać rozmiar w razie potrzeby.
 */
template<typename T>
class SmartArray {
public:
    /**
     * @brief Tworzy pustą tablicę.
     */
    SmartArray();

    /**
     * @brief Tworzy tablicę z zarezerwowaną pamięcią.
     *
     * Nie tworzy elementów logicznych (size = 0).
     *
     * @param size liczba elementów do rezerwacji
     */
    explicit SmartArray(unsigned size);

    /**
     * @brief Tworzy tablicę wypełnioną wartościami.
     *
     * @param size liczba elementów
     * @param elem wartość początkowa dla wszystkich elementów
     */
    SmartArray(unsigned size, const T &elem);

    /**
     * @brief Konstruktor kopiujący.
     */
    SmartArray(const SmartArray &array);

    /**
     * @brief Destruktor.
     */
    ~SmartArray();

    /**
     * @brief Zwraca element z kontrolą zakresu.
     *
     * @return referencja do elementu (umożliwia modyfikację)
     * @throws std::out_of_range jeśli index >= size()
     */
    T &at(unsigned index);

    /**
     * @brief Zwraca element z kontrolą zakresu (wersja const).
     *
     * @return stała referencja do elementu
     * @throws std::out_of_range jeśli index >= size()
     */
    const T &at(unsigned index) const;

    /**
     * @brief Dostęp do elementu bez sprawdzania zakresu.
     *
     * Uwaga: brak kontroli poprawności indeksu.
     *
     * @return referencja do elementu
     */
    T &operator[](unsigned index);

    /**
     * @brief Dostęp do elementu bez sprawdzania zakresu (const).
     */
    const T &operator[](unsigned index) const;

    /**
     * @brief Sprawdza czy tablica jest pusta.
     */
    [[nodiscard]] bool isEmpty() const;

    /**
     * @brief Zwraca liczbę elementów.
     */
    [[nodiscard]] unsigned size() const;

    /**
     * @brief Zwraca aktualną pojemność tablicy.
     */
    [[nodiscard]] unsigned capacity() const;

    /**
     * @brief Rezerwuje pamięć.
     *
     * Jeśli nowa pojemność jest mniejsza lub równa obecnej,
     * operacja może nie zmienić stanu tablicy.
     */
    void reserve(unsigned size);

    /**
     * @brief Zmienia liczbę elementów.
     *
     * Jeśli zwiększany, nowe elementy są domyślnie inicjalizowane.
     */
    void resize(unsigned size);

    /**
     * @brief Zmienia rozmiar i wypełnia nową wartością.
     *
     * @param elem wartość dla nowych elementów
     */
    void resize(unsigned size, T elem);

    /**
     * @brief Usuwa wszystkie elementy.
     *
     * size = 0, capacity pozostaje bez zmian.
     */
    void clear();

    /**
     * @brief Wstawia element w wybranym miejscu.
     *
     * @throws std::out_of_range jeśli index > size()
     */
    void insert(unsigned index, T elem);

    /**
     * @brief Usuwa element spod indeksu.
     *
     * @throws std::out_of_range jeśli index >= size()
     */
    void erase(unsigned index);

    /**
     * @brief Usuwa kilka elementów od indeksu.
     *
     * @throws std::out_of_range jeśli zakres wykracza poza tablicę
     */
    void erase(unsigned index, unsigned amount);

    /**
     * @brief Dodaje element na koniec.
     */
    void pushBack(T elem);

    /**
     * @brief Usuwa ostatni element.
     */
    void popBack();

    /**
     * @brief Porównuje dwie tablice.
     *
     * @return true jeśli mają ten sam rozmiar i identyczne elementy
     */
    bool operator==(const SmartArray &array) const;

    /**
     * @brief Zmniejsza pojemność do aktualnego rozmiaru.
     */
    void shrinkToFit();

    /**
     * @brief Dodaje element na początek tablicy.
     */
    void pushFront(T elem);

    /**
     * @brief Usuwa pierwszy element.
     */
    void popFront();

    /**
     * @brief Operator przypisania.
     */
    SmartArray &operator=(const SmartArray &array);

private:
    T *_data;
    unsigned _size;
    unsigned _capacity;

    void _checkCapacityAndReserve(unsigned size);
    void _checkCapacityAndReserve();
};

/**
 * @brief Wypisuje zawartość tablicy w formacie:
 * [a, b, c]
 */
template<typename T>
std::ostream &operator<<(std::ostream &os, const SmartArray<T> &array);

#include "SmartArray.cpp"

#endif