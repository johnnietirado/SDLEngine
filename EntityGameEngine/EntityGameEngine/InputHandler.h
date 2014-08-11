#pragma once

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_
#include <SDL.h>
#include "Vector2D.h"
#include <iostream>
#include <vector>
#include <map>

class InputHandler
{
public:

	static InputHandler* Instance()
	{
		if(mInstance == 0)
			mInstance = new InputHandler();
		return mInstance;
	}

	void Initialize();
	void InitializeJoysticks();
	void Update();
	void Shutdown();

	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	bool JoysticksInitialized() { return mJoysticksInitialized;}
	bool getButtonState(int joy, int buttonNumber) { return mButtonStates[joy][buttonNumber]; }

	bool isKeyDown(SDL_Scancode key);
	bool isKeyUp(SDL_Scancode key);

	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	Vector2D* getMousePosition() { return mMousePosition; }

	bool getMouseButtonState(int Button);
	bool Clicked();

private:
	InputHandler(void) {};
	~InputHandler(void) {};

	static InputHandler* mInstance;

	Vector2D* mMousePosition;

	std::vector<SDL_Joystick*> mJoysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> mJoystickValues;
	std::vector<std::vector<bool>> mButtonStates;
	std::map<int, bool> mMouseButtonStates;

	const Uint8* mKeyState;

	bool mJoysticksInitialized, released, clicked;

	enum MOUSE_BUTTONS
	{
		LEFT = 0,
		RIGHT = 1,
		MIDDLE = 2
	};
};

#endif