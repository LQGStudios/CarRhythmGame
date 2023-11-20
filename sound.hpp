#include "raylib.h"
#include "libs/raymath.h"
#include <list>
#include <fstream> //för att läsa csv med beatmaps
 
struct Song 
{   
    Music music;

};
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
        void LoadBeatMap(const char*bPath) //läser in en csv-fil med beatmappen i. Denna beatmap kommer från ett excel-dokument med timing och annan notinformation
        {
            bPath = "assets/beatmaps/Bm140.cs";

            std::ifstream fullBeatmap;
            fullBeatmap.open(bPath);

            if (fullBeatmap.fail())
            {
                std::cerr << "Kan inte öppna filen" << bPath <<std::endl;
            }
            

        }
};

