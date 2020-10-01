#include "SteeringBehaviour.h"

#include <iostream>

#include "Manipulators/openGL.h"

#include "Modules BackEnd/window.h"
#include "Modules BackEnd/mouse.h"
#include "Modules BackEnd/camera.h"
#include "Modules BackEnd/keyboard.h"
#include "Modules FrontEnd/flockingBehaviour.h"

#include "Utilities/random.h"

#include "../Entities/bait.h"
#include "../Entities/fish.h"
#include "../Entities/rock.h"
#include "../Entities/shark.h"

SteeringBehaviour_Demo::SteeringBehaviour_Demo(Window *const wnd, Keyboard *const kbd, Mouse *const mse, Camera *const camera) : wnd(wnd), kbd(kbd), mse(mse), camera(camera) {

	Utilities::Random::seedRandom();

	OpenGL::initTexture(screenTexture, 1, wnd->getWidth(), wnd->getHeight());
	OpenGL::initDepthBufferTexture(depthBuffer, wnd->getWidth(), wnd->getHeight());

	currentCommand = Command::NONE;

	bait = new Bait(wnd, kbd, camera, &screenTexture, BAIT_SPEED);
	shark = new Shark(wnd, kbd, camera, &screenTexture, SHARK_SPEED);

	rock = new Rock * [TOTAL_OBSTACLES];

	for (int i = 0; i < TOTAL_OBSTACLES; ++i) { rock[i] = new Rock(wnd, camera, &screenTexture); }

	fish = new Fish_AI * [MAX_FISH];

	for (int i = 0; i < MAX_FISH; ++i) {
		
		fish[i] = new Fish_AI(wnd, camera, &screenTexture, FISH_VELOCITY_LIMIT, FISH_ACCELERATION_LIMIT);

		fish[i]->addAttractor(bait->transform);
		fish[i]->addRepeller(shark->transform);

		for (int j = 0; j < TOTAL_OBSTACLES; ++j) { fish[i]->addRepeller(rock[j]->transform); }
	
		fish[i]->setCenterPosition(glm::vec3(0.0f));

		fish[i]->setAttractorDistance(DEFAULT_ATTRACTION_DISTANCE);
		fish[i]->setRepellerDistance(DEFAULT_AVOIDANCE_DISTANCE);
		fish[i]->setBoundaryRadius(FISH_SWIMMABLE_DISTANCE);

		fish[i]->setAttractorWeight(DEFAULT_ATTRACTION_WEIGHT);
		fish[i]->setRepellerWeight(DEFAULT_AVOIDANCE_WEIGHT);

	}

	fb = new FlockingBehaviour(DEFAULT_FISH_TOTAL);

	for (int i = 0; i < DEFAULT_FISH_TOTAL; ++i) { fb->addBoid(fish[i]); }

	fb->setSeperationDistance(DEFAULT_SEPERATION_DISTANCE);
	fb->setAlignmentDistance(DEFAULT_ALIGNMENT_DISTANCE);
	fb->setCohesionDistance(DEFAULT_COHESION_DISTANCE);

	fb->setSeperationWeight(DEFAULT_SEPERATION_WEIGHT);
	fb->setAlignmentWeight(DEFAULT_ALIGNMENT_WEIGHT);
	fb->setCohesionWeight(DEFAULT_COHESION_WEIGHT);

	camera->setPosition(glm::vec3(0.0f, 0.0f, 50.0f));

	std::cout << "\nControls:\nPress WASD to move the BAIT." << "\n";
	std::cout << "Press IJKL to move the SHARK." << "\n";
	std::cout << "Hold Z and use the mouse to control the camera. RIGHT BUTTON to rotate, MIDDLE BUTTON to pan, and SCROLL to zoom" << "\n";
	std::cout << "Press 0-9 to switch between different control commands" << "\n";
	std::cout << "Press Q to reduce value of selected command\nPress E to increment the value of selected command" << "\n";
	std::cout << "\nNote: increment/reduce value is " << DEFAULT_VALUE_CHANGE << "\n";
	std::cout << "Note: Current control command is set to NULL" << "\n";

}

SteeringBehaviour_Demo::~SteeringBehaviour_Demo() {

	delete fb;
	fb = nullptr;

	for (int i = 0; i < MAX_FISH; ++i) {

		delete fish[i];
		fish[i] = nullptr;

	}

	delete[] fish;
	fish = nullptr;

	delete shark;
	shark = nullptr;

	delete bait;
	bait = nullptr;

	glUseProgram(0);

}

void SteeringBehaviour_Demo::executeCommand(const int &amount) {

	switch (currentCommand) {

		case Command::ALGN_DTNC: //alignment distance
			fb->setAlignmentDistance(fb->getAlignmentDistance() + amount);
			std::cout << "\nAlignment distance value is now at " << fb->getAlignmentDistance() << "\n";
			break;

		case Command::ALGN_WGHT: //alignment weight
			fb->setAlignmentWeight(fb->getAlignmentWeight() + amount);
			std::cout << "\nAlignment weight value is now at " << fb->getAlignmentWeight() << "\n";
			break;

		case Command::ATTRC_DSNC: //attraction distance
			for (int i = 0; i < MAX_FISH; ++i) { fish[i]->setAttractorDistance(fish[i]->getAttractorDistance() + amount); }
			std::cout << "\nAttraction distance value is now at " << fish[0]->getAttractorDistance() << "\n";
			break;

		case Command::AVDN_DTNC: //avoidance distance
			for (int i = 0; i < MAX_FISH; ++i) { fish[i]->setRepellerDistance(fish[i]->getRepellerDistance() + amount); }
			std::cout << "\nAvoidance weight value is now at " << fish[0]->getRepellerDistance() << "\n";
			break;

		case Command::BOID_CONT: //boid count

			if (amount > 0 && fb->getCurrentTotalBoids() < MAX_FISH) {

				for (int i = 0; i < DEFAULT_VALUE_CHANGE && i; ++i) {
					fb->addBoid(fish[fb->getCurrentTotalBoids() + i]);
				}

			}
			else if(fb->getCurrentTotalBoids() >= 0) {
				fb->removeBoid(DEFAULT_VALUE_CHANGE);
			}

			std::cout << "\nFishes " << (amount > 0 ? "incremented" : "reduced") << " by " << DEFAULT_VALUE_CHANGE << "\n";

			break;

		case Command::CHSN_DTNC: //cohesion distance
			fb->setCohesionDistance(fb->getCohesionDistance() + amount);
			std::cout << "\nCohesion distance value is now at " << fb->getCohesionDistance() << "\n";
			break;

		case Command::CHSN_WGHT: //cohesion weight
			fb->setCohesionWeight(fb->getCohesionWeight() + amount);
			std::cout << "\nCohesion weight value is now at " << fb->getCohesionWeight() << "\n";
			break;

		case Command::SPRT_DTNC: //seperation distance
			fb->setSeperationDistance(fb->getSeperationDistance() + amount);
			std::cout << "\nSeperation distance value is now at " << fb->getSeperationDistance() << "\n";
			break;

		case Command::SPRT_WGHT: //seperation weight
			fb->setSeperationWeight(fb->getSeperationWeight() + amount);
			std::cout << "\nSeperation weight value is now at " << fb->getSeperationWeight() << "\n";
			break;

	}

}

void SteeringBehaviour_Demo::controls() {

	for (int i = 0; i < 9; ++i) {

		if (kbd->isPressedOnce(GLFW_KEY_0 + i)) {
			
			currentCommand = (Command)i;

			std::cout << "\nControl command set to " << (int)currentCommand << "\n";
		
		}

	}

	if (kbd->isPressedOnce(GLFW_KEY_0)) { currentCommand = Command::NONE; }

	if (kbd->isPressedOnce('Q')) { executeCommand(-DEFAULT_VALUE_CHANGE); }

	if (kbd->isPressedOnce('E')) { executeCommand(DEFAULT_VALUE_CHANGE); }

}

void SteeringBehaviour_Demo::update() {

	controls();

	fb->update(wnd->getDeltaTime_Seconds());

	bait->update(wnd->getDeltaTime_Seconds());
	shark->update(wnd->getDeltaTime_Seconds());

}

void SteeringBehaviour_Demo::render() {
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);

	for (int i = 0; i < fb->getCurrentTotalBoids(); ++i) { fish[i]->render(); }
	for (int i = 0; i < TOTAL_OBSTACLES; ++i) { rock[i]->render(); }

	shark->render();
	bait->render();
	
	renderToScreen(screenTexture, wnd->getWidth(), wnd->getHeight());

}