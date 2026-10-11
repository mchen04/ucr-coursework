#ifndef SOUND_H
#define SOUND_H
#include <SFML/Audio.hpp>

using namespace std;

class Sound {
    public:
        Sound(const std::string& filename) {
            if (!buffer.loadFromFile(filename)) {
                // Handle error if the file failed to load
            }
            sound.setBuffer(buffer);
        };

        void play() {
            sound.play();
        };

        void pause() {
            sound.pause();
        };

        void stop() {
            sound.stop();
        };

        void setVolume(float volume) {
            sound.setVolume(volume);
        };

        void setPitch(float pitch) {
            sound.setPitch(pitch);
        };

        void setPosition(float x, float y, float z) {
            sound.setPosition(x, y, z);
        };

    private:
        sf::SoundBuffer buffer;
        sf::Sound sound;

};

#endif