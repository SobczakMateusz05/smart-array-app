#ifndef CARMENU_H
#define CARMENU_H

#include <string>
#include <vector>

#include "ftxui/component/component.hpp"

#include "CarManager.h"

/**
 * @brief Interfejs tekstowy (TUI) aplikacji do zarządzania samochodami.
 *
 * Klasa buduje i obsługuje całe menu oparte o bibliotekę ftxui. Pozwala
 * dodawać, edytować, usuwać oraz wyświetlać samochody (pełną listę,
 * skróconą listę, wybrany zakres lub pojedynczy element). Dane są
 * przechowywane w obiekcie CarManager.
 */
class CarMenu {
public:
    /**
     * @brief Tworzy menu i wczytuje dane z pliku.
     */
    CarMenu();

    /**
     * @brief Uruchamia główną pętlę interfejsu.
     */
    void run();

private:
    /**
     * @brief Przebudowuje listę napisów wyświetlaną w menu.
     *
     * Uwzględnia aktualny tryb (skrócony/pełny) oraz wybrany zakres.
     */
    void _refreshEntries();

    /**
     * @brief Zwraca rzeczywisty indeks samochodu dla zaznaczonej pozycji.
     *
     * @return indeks w CarManager lub -1, gdy nic nie jest zaznaczone
     */
    [[nodiscard]] int _currentIndex() const;

    CarManager _manager;

    int _selected = 0;
    bool _showForm = false;
    bool _isEditing = false;
    std::string _statusMsg;

    std::string _fBrand, _fModel, _fYear, _fMileage, _fColor;

    std::string _fFrom, _fTo, _fIndex;

    std::string _fSearchBrand, _fSearchModel, _fSearchYear;
    std::string _fSumBrand;

    std::string _searchBrand, _searchModel, _searchYear;

    bool _shortMode = false;
    int _viewFrom = -1;
    int _viewTo = -1;

    std::vector<std::string> _entries;
    std::vector<int> _indexMap;
};

#endif
