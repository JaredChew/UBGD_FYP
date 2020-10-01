#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Specification/session.h"

#define DEFAULT_VALUE_CHANGE 1.0f

#define MAX_FISH 200
#define DEFAULT_FISH_TOTAL 200

#define TOTAL_OBSTACLES 5

#define DEFAULT_SEPERATION_DISTANCE 4.0f
#define DEFAULT_ALIGNMENT_DISTANCE 5.0f
#define DEFAULT_COHESION_DISTANCE 5.0f

#define DEFAULT_SEPERATION_WEIGHT 7.0f
#define DEFAULT_ALIGNMENT_WEIGHT 5.0f
#define DEFAULT_COHESION_WEIGHT 3.0f

#define DEFAULT_ATTRACTION_DISTANCE 7.0f
#define DEFAULT_AVOIDANCE_DISTANCE 10.0f

#define DEFAULT_ATTRACTION_WEIGHT 5.0f
#define DEFAULT_AVOIDANCE_WEIGHT 30.0f

#define FISH_VELOCITY_LIMIT 50.0f
#define FISH_ACCELERATION_LIMIT 5.0f
#define FISH_SWIMMABLE_DISTANCE 40.0f

#define BAIT_SPEED 50.0f
#define SHARK_SPEED 30.0f

class Shark;
class Bait;
class Rock;
class Fish_AI;
class FlockingBehaviour;

class Window;
class Keyboard;
class Mouse;
class Camera;

class SteeringBehaviour_Demo : public Session {

private:

	Window *const wnd;
	Keyboard *const kbd;
	Mouse *const mse;
	Camera *const camera;

private:

	Bait *bait;
	Shark *shark;

	Rock **rock;
	Fish_AI **fish;

	FlockingBehaviour *fb;

	GLuint screenTexture;
	GLuint depthBuffer;

	enum class Command { NONE, BOID_CONT, SPRT_DTNC, ALGN_DTNC, CHSN_DTNC, SPRT_WGHT, ALGN_WGHT, CHSN_WGHT, ATTRC_DSNC, AVDN_DTNC } currentCommand;

private:

	void executeCommand(const int &amount);
	void controls();

public:

	SteeringBehaviour_Demo(Window *const wnd, Keyboard *const kbd, Mouse *const mse, Camera *const camera);
	~SteeringBehaviour_Demo();

	void update() override;
	void render();

};