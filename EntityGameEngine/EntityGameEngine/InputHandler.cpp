#include "InputHandler.h"
#include "Misc.h"
#include "Engine.h"

InputHandler* InputHandler::mInstance = NULL;
const int mJoystickDeadZone = 1000;

void InputHandler::Initialize()
{
	mMousePosition = new Vector2D();
	clicked = false;
}

void InputHandler::InitializeJoysticks()
{
	int i, j;
	if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if(SDL_NumJoysticks() > 0)
	{
		for(i = 0; i < SDL_NumJoysticks(); ++i)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);
			
			if(joy != NULL)
			{
				mJoysticks.push_back(joy);
				mJoystickValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0))); // adds the pair
				std::vector<bool> tempButtons;

				//Add Buttons
				for(j = 0; j < SDL_JoystickNumButtons(joy); ++j)
				{
					tempButtons.push_back(false);
				}

				mButtonStates.push_back(tempButtons);
			}
			else
			{
				printf("Joystick generation error: %s\n", SDL_GetError());
			}
		}

		SDL_JoystickEventState(SDL_ENABLE);
		mJoysticksInitialized = true;

		printf("Initialized %d Joystick(s)\n", mJoysticks.size());
		printf("Number of Axis: %d\n", SDL_JoystickNumAxes(mJoysticks[0]));
	}
	else
	{
		mJoysticksInitialized = false;
	}
}

void InputHandler::Update()
{
	SDL_Event event;
	mKeyState = SDL_GetKeyboardState(0);
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			Engine::Instance()->Shutdown();
		}

#pragma region Joystick
		if(event.type == SDL_JOYAXISMOTION)
		{
			int whichOne = event.jaxis.which;

			//Left Stick move Left or right
			if(event.jaxis.axis == 0)
			{
				if(event.jaxis.value > mJoystickDeadZone)
					mJoystickValues[whichOne].first->setX(1);
				
				else if(event.jaxis.value < -mJoystickDeadZone)
					mJoystickValues[whichOne].first->setX(-1);
				
				else
					mJoystickValues[whichOne].first->setX(0);
			}

			//Right Stick moves Right or Left
			if(event.jaxis.axis == 1)
			{
				if(event.jaxis.value > mJoystickDeadZone)
					mJoystickValues[whichOne].first->setY(1);
				
				else if(event.jaxis.value < -mJoystickDeadZone)
					mJoystickValues[whichOne].first->setY(-1);
				
				else
					mJoystickValues[whichOne].first->setY(0);
			}

			if(event.jaxis.axis == 3)
			{
				if(event.jaxis.value > mJoystickDeadZone)
					mJoystickValues[whichOne].second->setX(1);
				
				else if(event.jaxis.value < -mJoystickDeadZone)
					mJoystickValues[whichOne].second->setX(-1);
				
				else
					mJoystickValues[whichOne].second->setX(0);
			}

			if(event.jaxis.axis == 4)
			{
				if(event.jaxis.value > mJoystickDeadZone)
					mJoystickValues[whichOne].second->setY(1);
				
				else if(event.jaxis.value < -mJoystickDeadZone)
					mJoystickValues[whichOne].second->setY(-1);
				
				else
					mJoystickValues[whichOne].second->setY(0);
			}
		}
#pragma endregion

#pragma region Mouse

		if(event.type == SDL_MOUSEMOTION)
		{
			mMousePosition->setX(event.motion.x);
			mMousePosition->setY(event.motion.y);
		}

		switch(event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				onMouseButtonDown(event);
				break;

			case SDL_MOUSEBUTTONUP:
				onMouseButtonUp(event);
				break;

			default:
				break;
		}
#pragma endregion
	}
}

void InputHandler::Shutdown()
{
	if(mJoysticksInitialized)
		for(unsigned int i = 0; i < SDL_NumJoysticks(); ++i)
			SDL_JoystickClose(mJoysticks[i]);
}

int InputHandler::xvalue(int joy, int stick)
{
	if(mJoystickValues.size() > 0)
	{
		switch(stick)
		{
		case 1:
			return mJoystickValues[joy].first->getX();
			break;
		case 2:
			return mJoystickValues[joy].second->getX();
			break;
		default:
			return 0;
			break;
		}
	}
	return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
	if(mJoystickValues.size() > 0)
	{
		switch(stick)
		{
		case 1:
			return mJoystickValues[joy].first->getY();
			break;
		case 2:
			return mJoystickValues[joy].second->getY();
			break;
		default:
			return 0;
			break;
		}
	}
	return 0;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if(mKeyState != 0)
	{
		if(mKeyState[key] == 1)
			return true;
		else
			return false;
	}
	return false;
}

bool InputHandler::isKeyUp(SDL_Scancode key)
{
	if(mKeyState != 0)
	{
		if(mKeyState[key] == 1)
			return false;
		else
			return true;
	}
	return false;
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if(event.button.button == SDL_BUTTON_LEFT)
		mMouseButtonStates[LEFT] = true;

	if(event.button.button == SDL_BUTTON_MIDDLE)
		mMouseButtonStates[MIDDLE] = true;

	if(event.button.button == SDL_BUTTON_RIGHT)
		mMouseButtonStates[RIGHT] = true;
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if(event.button.button == SDL_BUTTON_LEFT)
		mMouseButtonStates[LEFT] = false;

	if(event.button.button == SDL_BUTTON_MIDDLE)
		mMouseButtonStates[MIDDLE] = false;

	if(event.button.button == SDL_BUTTON_RIGHT)
		mMouseButtonStates[RIGHT] = false;
}

bool InputHandler::getMouseButtonState(int Button)
{
	if(mMouseButtonStates.size() > 0)
	{
		return mMouseButtonStates[Button];
	}
	return false;
}

bool InputHandler::Clicked()
{
	if(getMouseButtonState(Mouse::LEFT) && released)
	{
		released = false;
	}
	if (!getMouseButtonState(Mouse::LEFT) && !released)
	{
		clicked = true;
		released = true;
	}
	else if (!getMouseButtonState(Mouse::LEFT))
	{
		released = true;
		clicked = false;
	}
	return clicked;
}
