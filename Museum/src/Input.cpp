#include "Input.h"

#include "GL\glew.h"
#include "GL\freeglut.h"

#include <array>
#include <vector>

struct InputData {
	std::array<KeyState, 256> keyStates;
	std::vector<int> releasedKeys;

	int MousePosX = 0.5;
	int MousePosY = 0.5;
	int MouseDeltaX, MouseDeltaY;
};

static InputData inputData;

void Input::Init() {
	inputData.releasedKeys.reserve(256);

	glutSetCursor(GLUT_CURSOR_NONE);
}


bool Input::GetKey(int keyCode) { return inputData.keyStates[keyCode].isPressed; }
bool Input::GetKeyDown(int keyCode) { return inputData.keyStates[keyCode].isPressedDown; }
bool Input::GetKeyUp(int keyCode) { return inputData.keyStates[keyCode].isReleased; }

double Input::GetMousePosX() { return inputData.MousePosX; }
double Input::GetMousePosY() { return inputData.MousePosY; }

double Input::GetMouseDeltaX() { return  inputData.MouseDeltaX; }
double Input::GetMouseDeltaY() { return  inputData.MouseDeltaY; }

void Input::InputCallback(unsigned char key, int x, int y) {
	if (inputData.keyStates[key].isPressed) return;

	inputData.keyStates[key].isPressedDown = true;
	inputData.keyStates[key].isPressed = true;
	inputData.keyStates[key].isReleased = false;
	inputData.releasedKeys.push_back(key);
	
}

void Input::InputUpCallback(unsigned char key, int x, int y) {

	inputData.keyStates[key].isPressedDown = false;
	inputData.keyStates[key].isPressed = false;
	inputData.keyStates[key].isReleased = true;
	inputData.releasedKeys.push_back(key);

}
void Input::MouseButtonCallback(int button, int action, int x, int y) {
	
	switch (action) {
	case GLUT_DOWN:
		inputData.keyStates[button].isPressed = true;
		inputData.keyStates[button].isPressedDown = true;
		inputData.keyStates[button].isReleased = false;
		inputData.releasedKeys.push_back(button);

		break;
	case GLUT_UP:
		inputData.keyStates[button].isPressed = false;
		inputData.keyStates[button].isPressedDown = false;
		inputData.keyStates[button].isReleased = true;
		inputData.releasedKeys.push_back(button);
		break;
	}
}

void Input::MousePosCallback(int xpos, int ypos) {

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH)/2;
	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT)/2;

	//inputData.MouseDeltaX = xpos - inputData.MousePosX;	//doesnt work when reseting mouse position
	//inputData.MouseDeltaY = ypos - inputData.MousePosY;	
	inputData.MouseDeltaX = xpos - windowWidth;
	inputData.MouseDeltaY = windowHeight - ypos;
	
	inputData.MousePosX = xpos;
	inputData.MousePosY = ypos;

	glutWarpPointer(windowWidth, windowHeight);
}

void Input::ResetKeyState() {
	inputData.MouseDeltaX = 0;
	inputData.MouseDeltaY = 0;	

	for (int key : inputData.releasedKeys) {
		inputData.keyStates[key].isReleased = false;
		inputData.keyStates[key].isPressedDown = false;
	}
	inputData.releasedKeys.clear();
}


