#include "Time.h"

#include "GL\glew.h"
#include "GL\freeglut.h"


struct TimeData {
	double lastTime = 0;
	double currentTime = 0;
	double deltaTime = 0;
};

static TimeData timeData;

double Time::DeltaTime(){
	return timeData.deltaTime;
}

double Time::RealTime(){
	return timeData.currentTime;
}

float Time::DeltaTimeF() {
	return static_cast<float>(timeData.deltaTime);
}

float Time::RealTimeF() {
	return static_cast<float>(timeData.currentTime);
}

void Time::UpdateTime() {
	timeData.currentTime = glutGet(GLUT_ELAPSED_TIME);

	timeData.deltaTime = (timeData.currentTime - timeData.lastTime)/1000.0;

	timeData.lastTime = timeData.currentTime;
}

int Time::FPS() {
	return static_cast<int>(1 / timeData.deltaTime);
}
