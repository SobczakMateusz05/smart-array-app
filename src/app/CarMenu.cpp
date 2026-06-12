#include "CarMenu.h"

#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

static const std::string DATA_FILE = "cars.dat";

static std::string field(const std::string &s, int width) {
    if (s.size() >= width) {
        return s.substr(0, width);
    }

    return s + std::string(width - s.size(), ' ');
}

static std::string formatEntry(const Car &c) {
    return field(std::to_string(c.getId()), 5)
           + field(c.getBrand(), 14)
           + field(c.getModel(), 14)
           + field(std::to_string(c.getYear()), 7)
           + field(std::to_string(c.getMileage()) + " km", 12)
           + c.getColor();
}

static std::string formatShort(int index, const Car &c) {
    return field(std::to_string(index), 5)
           + field(c.getBrand(), 14)
           + c.getModel();
}

static bool matches(const Car &c, const std::string &brand,
                    const std::string &model, const std::string &year) {
    if (!brand.empty() && c.getBrand() != brand) {
        return false;
    }

    if (!model.empty() && c.getModel() != model) {
        return false;
    }

    if (!year.empty() && std::to_string(c.getYear()) != year) {
        return false;
    }

    return true;
}

CarMenu::CarMenu() {
    _manager.loadFromFile(DATA_FILE);
    _refreshEntries();
}

void CarMenu::_refreshEntries() {
    _entries.clear();
    _indexMap.clear();
    for (unsigned i = 0; i < _manager.count(); i++) {
        if (_viewFrom >= 0 && ((int) i < _viewFrom || (int) i > _viewTo)) {
            continue;
        }

        if (!matches(_manager.get(i), _searchBrand, _searchModel, _searchYear)) {
            continue;
        }

        if (_shortMode) {
            _entries.push_back(formatShort(i, _manager.get(i)));
        } else {
            _entries.push_back(formatEntry(_manager.get(i)));
        }

        _indexMap.push_back(i);
    }
    if (_entries.empty()) {
        _entries.push_back("(brak samochodów)");
    }
    if (_selected >= (int) _entries.size()) {
        _selected = _entries.size() - 1;
    }
}

int CarMenu::_currentIndex() const {
    if (_selected < 0 || _selected >= (int) _indexMap.size()) {
        return -1;
    }

    return _indexMap[_selected];
}

void CarMenu::run() {
    // FORM
    auto inpBrand = Input(&_fBrand, "marka");
    auto inpModel = Input(&_fModel, "model");
    auto inpYear = Input(&_fYear, "rok");
    auto inpMileage = Input(&_fMileage, "przebieg");
    auto inpColor = Input(&_fColor, "kolor");

    auto btnSave = Button("  Zapisz  ", [&]() {
        try {
            int year = _fYear.empty() ? 0 : std::stoi(_fYear);
            int mileage = _fMileage.empty() ? 0 : std::stoi(_fMileage);
            if (_isEditing) {
                _manager.update(_currentIndex(), _fBrand, _fModel, year, mileage, _fColor);
                _statusMsg = "Samochód zaktualizowany.";
            } else {
                _viewFrom = _viewTo = -1;
                _shortMode = false;
                _searchBrand = _fSearchBrand = "";
                _searchModel = _fSearchModel = "";
                _searchYear = _fSearchYear = "";
                _manager.add(_fBrand, _fModel, year, mileage, _fColor);
                _selected = _manager.count() - 1;
                _statusMsg = "Samochód dodany.";
            }
            _manager.saveToFile(DATA_FILE);
            _refreshEntries();
            _showForm = false;
        } catch (...) {
            _statusMsg = "Błąd: rok i przebieg muszą być liczbami.";
        }
    });

    auto btnCancel = Button("  Anuluj  ", [&]() {
        _showForm = false;
    });

    auto formContainer = Container::Vertical({
        inpBrand, inpModel, inpYear, inpMileage, inpColor,
        Container::Horizontal({btnSave, btnCancel})
    });

    auto formRenderer = Renderer(formContainer, [&]() {
        return vbox({
                   text(_isEditing ? " Edytuj samochód " : " Dodaj samochód ") | bold | hcenter,
                   separator(),
                   hbox({text(" Marka:    "), inpBrand->Render() | size(WIDTH, EQUAL, 26)}),
                   hbox({text(" Model:    "), inpModel->Render() | size(WIDTH, EQUAL, 26)}),
                   hbox({text(" Rok:      "), inpYear->Render() | size(WIDTH, EQUAL, 26)}),
                   hbox({text(" Przebieg: "), inpMileage->Render() | size(WIDTH, EQUAL, 26)}),
                   hbox({text(" Kolor:    "), inpColor->Render() | size(WIDTH, EQUAL, 26)}),
                   separator(),
                   hbox({btnSave->Render(), btnCancel->Render()}) | hcenter,
               }) | border | size(WIDTH, EQUAL, 46);
    });

    // LIST
    auto menu = Menu(&_entries, &_selected);

    auto btnAdd = Button("  Dodaj  ", [&]() {
        _fBrand = _fModel = _fYear = _fMileage = _fColor = "";
        _isEditing = false;
        _showForm = true;
        _statusMsg = "";
    });

    auto btnEdit = Button("  Edytuj  ", [&]() {
        if (_manager.isEmpty() || _currentIndex() < 0) {
            _statusMsg = "Brak samochodów do edycji.";
            return;
        }
        const Car &c = _manager.get(_currentIndex());
        _fBrand = c.getBrand();
        _fModel = c.getModel();
        _fYear = std::to_string(c.getYear());
        _fMileage = std::to_string(c.getMileage());
        _fColor = c.getColor();
        _isEditing = true;
        _showForm = true;
        _statusMsg = "";
    });

    auto btnDelete = Button("  Usuń  ", [&]() {
        if (_manager.isEmpty() || _currentIndex() < 0) {
            _statusMsg = "Brak samochodów do usunięcia.";
            return;
        }
        _manager.remove(_currentIndex());
        _manager.saveToFile(DATA_FILE);

        if (_selected > 0) {
            _selected--;
        }

        _refreshEntries();
        _statusMsg = "Samochód usunięty.";
    });

    auto btnCount = Button("  Ile?  ", [&]() {
        _statusMsg = "Liczba samochodów: " + std::to_string(_manager.count());
    });

    // RANGE AND INDEX
    auto inpFrom = Input(&_fFrom, "od");
    auto inpTo = Input(&_fTo, "do");
    auto inpIndex = Input(&_fIndex, "indeks");

    auto btnRange = Button("  Zakres  ", [&]() {
        try {
            int from = std::stoi(_fFrom);
            int to = std::stoi(_fTo);
            if (from < 0 || to >= (int) _manager.count() || from > to) {
                _statusMsg = "Błędny zakres.";
                return;
            }
            _viewFrom = from;
            _viewTo = to;
            _selected = 0;
            _refreshEntries();
            _statusMsg = "Pokazano zakres " + _fFrom + "-" + _fTo + ".";
        } catch (...) {
            _statusMsg = "Błąd: podaj liczby (od, do).";
        }
    });

    auto btnIndex = Button("  Indeks  ", [&]() {
        try {
            int index = std::stoi(_fIndex);
            if (index < 0 || index >= (int) _manager.count()) {
                _statusMsg = "Błędny indeks.";
                return;
            }
            _viewFrom = _viewTo = index;
            _selected = 0;
            _refreshEntries();
            _statusMsg = "Pokazano element o indeksie " + _fIndex + ".";
        } catch (...) {
            _statusMsg = "Błąd: podaj liczbę (indeks).";
        }
    });

    auto btnShort = Button("  Skrót  ", [&]() {
        _shortMode = !_shortMode;
        _refreshEntries();
        _statusMsg = _shortMode ? "Lista skrócona." : "Lista pełna.";
    });

    auto btnAll = Button("  Wszystkie  ", [&]() {
        _viewFrom = _viewTo = -1;
        _shortMode = false;
        _selected = 0;
        _refreshEntries();
        _statusMsg = "Pokazano wszystkie.";
    });

    // SEARCH AND AGGREGATION
    auto inpSearchBrand = Input(&_fSearchBrand, "marka");
    auto inpSearchModel = Input(&_fSearchModel, "model");
    auto inpSearchYear = Input(&_fSearchYear, "rok");
    auto inpAggBrand = Input(&_fSumBrand, "marka");

    auto btnSearch = Button("  Szukaj  ", [&]() {
        _searchBrand = _fSearchBrand;
        _searchModel = _fSearchModel;
        _searchYear = _fSearchYear;
        _viewFrom = _viewTo = -1;
        _selected = 0;
        _refreshEntries();
        if (_searchBrand.empty() && _searchModel.empty() && _searchYear.empty()) {
            _statusMsg = "Pokazano wszystkie.";
        } else {
            _statusMsg = "Znaleziono: " + std::to_string(_indexMap.size());
        }
    });

    auto btnAvgYear = Button("  Śr. rocznik  ", [&]() {
        if (_manager.isEmpty()) {
            _statusMsg = "Brak samochodów.";
            return;
        }
        _statusMsg = "Średni rocznik: " + std::to_string(_manager.averageYear());
    });

    auto btnSumMileage = Button("  Suma przeb. marki  ", [&]() {
        long suma = _manager.totalMileageForBrand(_fSumBrand);
        _statusMsg = "Suma przebiegu marki " + _fSumBrand + ": "
                     + std::to_string(suma) + " km";
    });

    auto btnLeave = Button("  Wyjdź  ", [&]() {
        std::exit(0);
    });

    auto mainContainer = Container::Vertical({
        menu,
        Container::Horizontal({inpFrom, inpTo, inpIndex}),
        Container::Horizontal({btnRange, btnIndex, btnShort, btnAll}),
        Container::Horizontal({
            inpSearchBrand, inpSearchModel, inpSearchYear, btnSearch,
            inpAggBrand, btnAvgYear, btnSumMileage
        }),
        Container::Horizontal({btnAdd, btnEdit, btnDelete, btnCount, btnLeave})
    });

    static const std::string HEADER =
            field("ID", 5) +
            field("Marka", 14) +
            field("Model", 14) +
            field("Rok", 7) +
            field("Przebieg", 12) +
            "Kolor";

    // MAIN LAYOUT RENDER
    auto mainRenderer = Renderer(mainContainer, [&]() {
        return vbox({
            text(" Zarządzanie samochodami ") | bold | hcenter,
            separator(),
            text(" " + HEADER) | bold,
            separator(),
            menu->Render() | frame | flex,
            separator(),
            hbox({
                text(" Od: "), inpFrom->Render() | size(WIDTH, EQUAL, 8),
                text(" Do: "), inpTo->Render() | size(WIDTH, EQUAL, 8),
                text(" Indeks: "), inpIndex->Render() | size(WIDTH, EQUAL, 8),
            }) | hcenter,
            hbox({
                btnRange->Render(),
                btnIndex->Render(),
                btnShort->Render(),
                btnAll->Render(),
            }) | hcenter,
            separator(),
            hbox({
                text(" Szukaj  marka: "), inpSearchBrand->Render() | size(WIDTH, EQUAL, 12),
                text(" model: "), inpSearchModel->Render() | size(WIDTH, EQUAL, 12),
                text(" rok: "), inpSearchYear->Render() | size(WIDTH, EQUAL, 8),
                btnSearch->Render(),
            }) | hcenter,
            hbox({
                text(" Marka: "), inpAggBrand->Render() | size(WIDTH, EQUAL, 14),
                btnAvgYear->Render(),
                btnSumMileage->Render(),
            }) | hcenter,
            separator(),
            hbox({
                btnAdd->Render(),
                btnEdit->Render(),
                btnDelete->Render(),
                btnCount->Render(),
                btnLeave->Render(),
            }) | hcenter,
            separator(),
            text(" " + _statusMsg) | color(Color::Yellow),
        });
    });

    auto app = mainRenderer | Modal(formRenderer, &_showForm);

    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(app);
}
