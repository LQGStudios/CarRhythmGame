#pragma once
#include <string>
using namespace std;

class Audio
{
public:
    Audio();
    void Update();
    void PlaySong(int i);
    void PlayOGG(const char *filename);
    void PlayBeatmap(const char *filename);
    void NoteMovement();
    void Timing();
private:
    string trackTitle;
    string midiTitle;
    int speedX;
    int speedY;
    int radius;
};

class Song //eftersom att alla variabler är 
{
public:
    void CreateTrackList();
    string ingameTitle;
    const char *path;
    const char* bPath; //beatmap path
    int bpm;
    float beatLength = 60/bpm; //hur lång tid går det mellan varje taktslag
    float songPosition = 0.0f; //hur långt in i låten man är, det ska alltid vara 0 från början
    float startOffset; //hur lång tid till beatmappen ska starta
    Song(string ingameTitle, const char* path, const char* bPath, int bpm, float startOffset) //constructor, en funktion man kan kalla för att lätt skapa ett objekt
    {
        ingameTitle = ingameTitle;
        path = path;
        bPath = bPath;
        bpm = bpm;
        startOffset = startOffset;
    }
};