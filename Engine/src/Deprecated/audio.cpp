#include "audio.h"

Audio::Audio(const AudioType& audioType, const char* directory, const bool& isLoop, const int& soundChannel) {

	this->audioType = audioType;

	this->isLoop = isLoop;
	this->soundChannel = soundChannel;

	switch (audioType) {

	case AudioType::SOUND:
		sound = loadSound(directory);
		break;

	case AudioType::MUSIC:
		music = loadMusic(directory);
		break;

	}

}

Audio::~Audio() {

	Mix_FreeChunk(sound);
	Mix_FreeMusic(music);

	delete music;
	music = nullptr;

	delete sound;
	sound = nullptr;

}

Mix_Chunk* Audio::loadSound(const char* directory) {

	Mix_Chunk* soundToPass = Mix_LoadWAV(directory);

	if (soundToPass == nullptr) {

		//std::cerr << "\nSDL failed to load sound at: " << soundFileDir << std::endl;

	}

	return soundToPass;

}

Mix_Music* Audio::loadMusic(const char* directory) {

	Mix_Music* musicToPass = Mix_LoadMUS(directory);

	if (musicToPass == nullptr) {

		//std::cerr << "\nSDL failed to load music at: " << MusicFileDir << std::endl;

	}

	return musicToPass;

}

void Audio::controller(const AudioController& action) {

	switch (action) {

		case AudioController::PLAY:

			if (audioType) { Mix_PlayChannel(soundChannel, sound, isLoop); }
			else { Mix_PlayMusic(music, isLoop); }

			break;

		case AudioController::PAUSE:

			if (audioType) { Mix_Pause(soundChannel); }
			else { Mix_PauseMusic(); }

			break;

		case AudioController::STOP:

			if (audioType) { Mix_HaltChannel(soundChannel); }
			else { Mix_HaltMusic(); }

			break;

		case AudioController::RESUME:

			if (audioType) { Mix_Resume(soundChannel); }
			else { Mix_ResumeMusic(); }

			break;

	}

}

void Audio::play() {
	controller(AudioController::PLAY);
}

void Audio::stop() {
	controller(AudioController::STOP);
}

void Audio::pause() {
	controller(AudioController::PAUSE);
}

void Audio::resume() {
	controller(AudioController::RESUME);
}

int Audio::getChannel() {
	return soundChannel;
}

void Audio::setChannel(const int& channel) {
	this->soundChannel = soundChannel;
}

bool Audio::getIsLoop() {
	return isLoop;
}

void Audio::setIsLoop(const bool& isLoop) {
	this->isLoop = isLoop;
}