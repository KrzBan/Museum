#pragma once

#include <memory>


struct KeyState {
	bool isPressedDown; //one frame down
	bool isPressed;		//just down
	bool isReleased;	//isReleased
};

class Input {
public:
	static void Init();

	static bool GetKey(int keyCode);
	static bool GetKeyDown(int keyCode);
	static bool GetKeyUp(int keyCode);	//Repeat cleans Down state, Release cleans Repeat state, nothing resets Release state, TODO: add clean-up method

	static double GetMousePosX();
	static double GetMousePosY();

	static double GetMouseDeltaX();
	static double GetMouseDeltaY();

	static void InputCallback(unsigned char key, int x, int y);
	static void InputUpCallback(unsigned char key, int x, int y);

	static void ResetKeyState();	//resets one frame states such as pressedDown or released!
	static void MouseButtonCallback(int button, int action, int x, int y);
	static void MousePosCallback(int xpos, int ypos);

};

