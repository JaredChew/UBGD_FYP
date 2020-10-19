#include "window.h"

#include "../Utilities/timer.h"

#include <thread>

int Window::width;
int Window::height;

float Window::windowRatio;

Window::Window(const int &width, const int &height, const std::string &title, GLFWmonitor *const monitor, GLFWwindow *const share) {

	window = glfwCreateWindow(width, height, title.c_str(), monitor, share);

	this->width = width;
	this->height = height;

	this->windowRatio = static_cast<float>(width) / static_cast<float>(height);

	this->title = title;

	this->monitor = monitor;
	this->share = share;

	vsync = false;
	displayFps = false;

	fpsLimit = 0.0;
	totalFrames = 0.0;

	targetDeltaTime = 0;
	currentTime = 0;

	// Hook window resize.
	glfwSetWindowSizeCallback(window, onWindowResized);

	timer = new Timer();

}

Window::~Window() {

	glfwDestroyWindow(window);

}

void Window::limitFps() {

	std::chrono::steady_clock::time_point tock2;

	while (currentTime < targetDeltaTime) {

		if (targetDeltaTime - currentTime > MINIMUM_SLEEP_TIME) { //1000000.0

			std::chrono::duration<double, std::nano> deltaTargetCurrent(0.7 * (targetDeltaTime - currentTime));
			//std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTargetCurrent));

		}

		tock2 = std::chrono::high_resolution_clock::now();

		currentTime = std::chrono::duration<long double, std::nano>(tock2 - this->timer->getTock()).count();

	}

	//printf("currentTime: %f | targetDeltaTime: %f", currentTime, targetDeltaTime);

}

void Window::fpsCounter() {

	currentTime = timer->getDeltaTime();

	if (fpsLimit > 0.0) { limitFps(); }

	totalFrames = 1000000000.0 / currentTime;

	if (displayFps) {
		sprintf(dynamicTitle, "%s | FPS: %f", title.c_str(), totalFrames);
		glfwSetWindowTitle(window, dynamicTitle);
		//printf("\nFrames: %f\n\n", totalFrames);
	}

}

void Window::onWindowResized(GLFWwindow *window, int widthResize, int heightResize) {

	if (heightResize == 0) heightResize = 1;						// Prevent A Divide By Zero By making Height Equal One

	width = widthResize;
	height = heightResize;

	windowRatio = static_cast<float>(width) / static_cast<float>(height);

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

}

bool Window::successfulCreation() {
	return !window ? false : true;
}

void Window::update() {

	timer->recordTock();

	fpsCounter();

	timer->recordTick();

}
/*
void Window::recordTick() {
	tick = std::chrono::high_resolution_clock::now(); //tock;
}

void Window::recordTock() {
	tock = std::chrono::high_resolution_clock::now(); //tock;
}
*/
void Window::setVsync(const bool &vsync) {

	this->vsync = vsync;

	glfwSwapInterval(vsync);

}

void Window::setFpsLimit(const double &fpsLimit) {

	this->fpsLimit = fpsLimit;

	targetDeltaTime = 1000000000.0 / fpsLimit;

}

void Window::setDisplayFps(const bool &displayFps) {
	this->displayFps = displayFps;
}

int& const Window::getWidth() {
	return width;
}

int& const Window::getHeight() {
	return height;
}

float& const Window::getWindowRatio() {
	return windowRatio;
}

long double Window::getDeltaTime() {
	return timer->getDeltaTime();
}

long double Window::getDeltaTime_Seconds() {
	return timer->getDeltaTimeSeconds();
}

long double Window::getTimeElapsed() {
	return timer->getTimeElapsed();
}

long double Window::getTimeElapsed_Seconds() {
	return timer->getTimeElapsedSeconds();
}

GLFWwindow *Window::getWindow() const {
	return window;
}