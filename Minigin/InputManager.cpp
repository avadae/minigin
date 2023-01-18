// https://stackoverflow.com/questions/11040133/what-does-defining-win32-lean-and-mean-exclude-exactly
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl.h>

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_currentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_currentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

