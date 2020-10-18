#pragma once

class Keyboard;
class Mouse;
class Camera;
class Session;

class Game {

private:

	Keyboard *keyboard;
	Mouse *mouse;
	Camera *camera;
	Session *session;

private:
	void freeCameraControl();

public:
	Game();
	~Game();

	void initSessionState();

	void gameLoop();

};