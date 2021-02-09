#include <iostream>
#include <string>

#include "src/Utility.h"
#include "src/ResourceManager.h"

#include "src/Input.h"
#include "src/Time.h"
#include "src/Scene.h"

#include "App.h"

int screenWidth = 1280;
int screenHeight = 720;

std::unique_ptr<App> app;

void Draw()
{
	app->Draw();
}

void Resize(int width, int height)
{
	app->Resize(width, height);
}

void Idle()
{
	app->Idle();
}

void Timer(int value) {
	
	glutTimerFunc(1000/60, Timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Museum");

	glewInit();
	std::cout<<"Vendor: "<< glGetString(GL_VENDOR)<<'\n'; // Returns the vendor
	std::cout << "Renderer: " << glGetString(GL_RENDERER)<<'\n'; // Returns a hint to the model


	//Bind callback functions
	glutDisplayFunc(Draw);			
	glutIdleFunc(Idle);
	glutTimerFunc(1000/60, Timer, 0);
	glutReshapeFunc(Resize);

	glutKeyboardFunc(Input::InputCallback);
	glutKeyboardUpFunc(Input::InputUpCallback);
	glutMouseFunc(Input::MouseButtonCallback);

	//Both events call the same callback function, to always capture mouse position
	glutMotionFunc(Input::MousePosCallback);	//when button is pressed
	glutPassiveMotionFunc(Input::MousePosCallback);	//when no button is pressed

	//Enable features
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);

	Input::Init();
	Scene::Init();

	app = std::make_unique<App>(screenWidth, screenHeight);
	glutMainLoop();					//start
	app.reset();

	return(0);
}

