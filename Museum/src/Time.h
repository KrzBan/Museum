#pragma once

class Time
{
public: 
	static double DeltaTime();
	static double RealTime();

	static float DeltaTimeF();
	static float RealTimeF();

	static int FPS();

	static void UpdateTime();
};

