/******************************************************************************************************************************************************************************************
File Name:  Input.cpp
Author(s):  Yohaan Mohan
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/
#include "Advanced2d.h"

namespace GAM200
{
	Input::Input(HWND hwnd)
	{
		//save window handle
		window = hwnd;

		//create DirectInput object
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&di, NULL);

		//initialize keyboard
		di->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
		keyboard->SetDataFormat(&c_dfDIKeyboard);
		keyboard->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		keyboard->Acquire();

		//initialize mouse
		di->CreateDevice(GUID_SysMouse, &mouse, NULL);
		mouse->SetDataFormat(&c_dfDIMouse);
		mouse->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		mouse->Acquire();
	}

	Input::~Input()
	{
		di->Release();
		keyboard->Release();
		mouse->Release();
	}

	void Input::Update()
	{
		//poll state of the keyboard
		keyboard->Poll();
		if (!SUCCEEDED(keyboard->GetDeviceState(256, (LPVOID)&keyState)))
		{
			//keyboard device lost, try to re-acquire
			keyboard->Acquire();
		}

		//poll state of the mouse
		mouse->Poll();
		if (!SUCCEEDED(mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState)))
		{
			//mouse device lose, try to re-acquire
			mouse->Acquire();
		}

		//get mouse position
		GetCursorPos(&position);
		ScreenToClient(window, &position);
	}

	bool Input::GetMouseButton(char button)
	{
		return (mouseState.rgbButtons[button] & 0x80);
	}
}