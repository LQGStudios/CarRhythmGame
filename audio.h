#pragma once
#include <string>

class Audio
{
public:
    Audio();
    void Update();
    void PlaySong(int songIndex);
    void PlayOGG(const char *filename);
    void PlayMIDI(std::string midiTitle);


private:
    std::string trackTitle;
    std::string midiTitle;
    int speedX;
    int speedY;
    int radius;
};