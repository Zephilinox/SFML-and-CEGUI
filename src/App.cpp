#include "App.hpp"

#include <iostream>

App::App()
    : m_window(sf::VideoMode(1280, 720, 32), "SFML&CEGUI")
    , m_guiManager(&m_window)
{
    m_font.loadFromFile("data/cegui/fonts/DejaVuSans.ttf");
    m_text.setPosition(1280/2, 720/2);
    m_text.setFont(m_font);
    m_text.setColor(sf::Color::Black);
    m_text.setString("Hello World!");

    auto* root = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    auto* fr = root->getChild("Window");
    auto* eb = fr->getChild("Editbox");
    fr->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&App::onDialogClosed, this));
    eb->subscribeEvent(CEGUI::FrameWindow::EventTextChanged, CEGUI::Event::Subscriber(&App::onEditboxTextChanged, this));
}

void App::run()
{
    sf::Event e;

    while (!m_done)
    {
        while (m_window.pollEvent(e))
        {
            if (m_guiManager.handleEvent(e))
            {
                continue;
            }

            switch (e.type)
            {
                case sf::Event::Closed:
                {
                    stop();
                    break;
                }

                case sf::Event::KeyPressed:
                {
                    if (e.key.code == sf::Keyboard::Escape)
                    {
                        stop();
                        break;
                    }
                }

                default:
                {
                    break;
                }
            }
        }

        m_guiManager.update(1.f/60.f);

        m_window.clear(sf::Color::White);

        m_window.pushGLStates();
        m_window.draw(m_text);
        m_window.popGLStates();

        m_guiManager.draw();

        m_window.display();
    }
}

void App::stop()
{
    m_done = true;
}

bool App::onDialogClosed(const CEGUI::EventArgs& e)
{
    stop();
    return true;
}

bool App::onEditboxTextChanged(const CEGUI::EventArgs& e)
{
    auto* root = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    auto* fr = root->getChild("Window");
    auto* eb = fr->getChild("Editbox");
    m_text.setString(eb->getText().c_str());
    return true;
}
