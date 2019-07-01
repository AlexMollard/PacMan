#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Node.h"


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	_2dRenderer = new aie::Renderer2D();

	_Font = new aie::Font("./font/consolas.ttf", 32);

	_Level = new Level();
	
	setVSync(false);

	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
	delete _Level;
	delete _Font;
	delete _2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;
	_Level->Update(deltaTime);
	_Level->UpDateGlobalTransform();

	// input example
	aie::Input* input = aie::Input::getInstance();

	//Vector2 MousePos;
	//MousePos.x = input->getMouseX();
	//MousePos.y = input->getMouseY();

	//if (input->wasKeyPressed(aie::INPUT_KEY_Z))
	//{
	//	_StartPos = MousePos;
	//}

	//if (input->wasKeyPressed(aie::INPUT_KEY_X))
	//{
	//	_EndPos = MousePos; 
	//}
	
	//_Grid->FindPath(_StartPos, _EndPos, _Path);
	

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	_2dRenderer->begin();
	
	//Draw level
	_2dRenderer->setRenderColour(1, 1, 1);
	_Level->Draw(_2dRenderer);


	_2dRenderer->setRenderColour(0, 1, 0);
	//_2dRenderer->drawBox(getWindowWidth() / 2 + (tan(m_timer) * 100), getWindowHeight() / 2, 100, 100);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	_2dRenderer->drawText(_Font, fps, getWindowWidth() * 0.005, getWindowHeight() * 0.95);

	// done drawing sprites
	_2dRenderer->end();
}