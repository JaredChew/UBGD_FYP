#pragma once

class Window;
class Keyboard;
class Mouse;
class Camera;
class Session;

class Game {

private:

	Window *const wnd;

private:

	Keyboard *kbd;
	Mouse *mse;

	Camera *camera;

	Session *session;

public:
	Game(Window *const wnd);
	~Game();

	void initSessionState();

	void gameLoop();

};