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

	_Grid = new Grid(20 ,20 ,getWindowWidth() ,getWindowHeight());

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

	_Grid->update(deltaTime, input);

	Vector2 MousePos;
	MousePos.x = input->getMouseX();
	MousePos.y = input->getMouseY();

	if (input->isMouseButtonDown(0))
	{
		Node* MouseNode = _Grid->GetNodeByPos(MousePos);
		if (MouseNode)
			MouseNode->_Blocked = true;
	}

	if (input->isMouseButtonDown(1))
	{
		Node* MouseNode = _Grid->GetNodeByPos(MousePos);
		if (MouseNode)
			MouseNode->_Blocked = false;
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_I))
	{
		_StartPos = MousePos;
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_O))
	{
		_EndPos = MousePos; 
	}

	
	_Grid->FindPath(_StartPos, _EndPos, _Path);
	

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	_2dRenderer->begin();

	//_Grid->Draw(_2dRenderer);
	//
	////Draw Path
	//_2dRenderer->setRenderColour(1.0f, 1.0f, 0.0f);
	//for (int i = 1; i < _Path.size(); i++)
	//{
	//	_2dRenderer->drawLine(_Path[i-1].x, _Path[i-1].y, _Path[i].x, _Path[i].y, 3);
	//}
	//
	////Start point
	//_2dRenderer->setRenderColour(0.2f, 0.7f, 0.0f);
	//_2dRenderer->drawCircle(_StartPos.x, _StartPos.y, 10);
	//
	////End point
	//_2dRenderer->setRenderColour(0.7f, 0.0f, 0.2f);
	//_2dRenderer->drawCircle(_EndPos.x, _EndPos.y, 10);
	//
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