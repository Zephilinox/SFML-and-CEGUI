#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>

#include "GUIManager.hpp"

class App
{
public:
    App();

    void run();
    void stop();

    bool onDialogClosed(const CEGUI::EventArgs& e);
    bool onEditboxTextChanged(const CEGUI::EventArgs& e);

private:
    sf::RenderWindow m_window;
    GUIManager m_guiManager;
    bool m_done;
    sf::Text m_text;
    sf::Font m_font;
};

#endif //APP_HPP
