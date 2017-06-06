#include "stdafx.h"
#include "PauseState.h"
#include "TextBar.h"
#include "GameProjectApp.h"

const std::string PauseState::pause_message = "Paused";
const std::string PauseState::pause_font_path = "./font/consolas_bold.ttf";
const unsigned short PauseState::pause_font_height = 64;
const float PauseState::text_pos_x = 640;
const float PauseState::text_pos_y = 500;

PauseState::PauseState(GameProjectApp* app) : GameState(app)
{
	FontPtr pauseFont = m_app->getResourceManager()->getFont(pause_font_path, pause_font_height);
	m_pauseText = new TextBar(pauseFont, pause_message, text_pos_x, text_pos_y, TextBar::def_text_colour, 0x00000000);

}


PauseState::~PauseState()
{
	delete m_pauseText;
}

PauseState::PauseState(const PauseState & other) : GameState(other)
{
}

State * PauseState::clone() const
{
	return new PauseState(*this);
}

void PauseState::update(float deltaTime)
{
}

void PauseState::draw(aie::Renderer2D * renderer)
{
	// Grey out screen
	renderer->setRenderColour(0x00000040);
	renderer->drawBox(640, 360, 1280, 720);
	m_pauseText->draw(renderer);
	renderer->setRenderColour(0xffffffff);
}

