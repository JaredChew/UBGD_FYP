#pragma once

#include <thread>
#include <cstdlib> 
#include <chrono>
#include <string>
#include <iostream>

#include <GLFW/glfw3.h>

#define MINIMUM_SLEEP_TIME 10000000.0

#define DYNAMIC_WINDOW_TITLE_SIZE 80

class Window {

private:

	GLFWwindow *window;
	GLFWwindow *share;

	GLFWmonitor *monitor;

	static int width;
	static int height;

	static float windowRatio;

	std::string title;
	char dynamicTitle[DYNAMIC_WINDOW_TITLE_SIZE];

	bool vsync;
	bool displayFps;
	//bool usingDynamicTitle;

	double fpsLimit;

	long double currentTime;
	long double totalFrames;
	long double targetDeltaTime;

	std::chrono::steady_clock::time_point tick;
	std::chrono::steady_clock::time_point tock;

	static std::chrono::duration<long double, std::nano> deltaTime;
	static std::chrono::duration<long double, std::nano> timeElapsed;

private:

	void recordTime();
	void limitFps();
	void fpsCounter();

	static void onWindowResized(GLFWwindow *window, int width, int height);

public:

	Window(const int &width, const int &height, const std::string &title, GLFWmonitor *const monitor, GLFWwindow *const share);
	~Window();

	bool successfulCreation();

	void update();

	//void recordTick();
	//void recordTock();

	void setVsync(const bool &onOff);
	void setFpsLimit(const double &fpsLimit);
	void setDisplayFps(const bool &displayFps);
	//void setDynamicTitle(const bool& dynamicTitle);

	int getWidth();
	int getHeight();

	float getWindowRatio();

	static long double getDeltaTime();
	static long double getDeltaTime_Seconds();

	static long double getTimeElapsed();
	static long double getTimeElapsed_Seconds();

	GLFWwindow *getWindow() const;

};