#include "raylib.h"

struct CurrentSong //Värdena i denna struct ska ändras medans man spelar 
{
    private:

    public:
    float songPosition; //time
    int notesHit;
    int notesMissed;
    
};
struct Beatmap
{
    public:
    float beatPosition; //relativ till songPosition
};

