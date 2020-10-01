#pragma once

#include <SDL_mixer.h>

class Audio {

public:

	static enum AudioType { SOUND, MUSIC };

private:

	enum class AudioController { PLAY, PAUSE, STOP, RESUME };

private:

	AudioType audioType;

	Mix_Chunk *sound;
	Mix_Music* music;

	int soundChannel;

	bool isLoop;

private:

	Mix_Chunk* loadSound(const char* directory);
	Mix_Music* loadMusic(const char* directory);

	void controller(const AudioController &action);

public:

	Audio(const AudioType& audioType, const char* directory, const bool& isLoop, const int &soundChannel);
	~Audio();

	void play();
	void stop();

	void pause();
	void resume();

	int getChannel();
	void setChannel(const int &channel);

	bool getIsLoop();
	void setIsLoop(const bool &isLoop);

};