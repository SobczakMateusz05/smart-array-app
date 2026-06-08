#include "ftxui/dom/elements.hpp"



int main() {
    using namespace ftxui;
    auto screen = ftxui::Screen::Create(
        ftxui::Dimension::Full(),
        ftxui::Dimension::Full()
        );

    auto p = ftxui::paragraph("Hello world") | color(Color::Blue) | bgcolor(Color::White);

    Render(screen, p);
    screen.Print();


    return 0;
}