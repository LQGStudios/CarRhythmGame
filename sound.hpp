#include "raylib.h"
#include "libs/raymath.h"
#include <list>
#include <fstream> //för att läsa csv med beatmaps
 
typedef struct Timer {
    double startTime;   // Start time (seconds)
    double lifeTime;    // Lifetime (seconds)
} Timer;

void StartTimer(Timer* timer, double lifetime)
{
    std::cout << "startade timer";
    timer->startTime = GetTime(); //double
    timer->lifeTime = lifetime;
}

bool TimerDone(Timer timer)
{
    return GetTime() - timer.startTime >= timer.lifeTime;
}

double GetElapsed(Timer timer)
{
    return GetTime() - timer.startTime;
}
struct Song 
{   
    Music music;

};
struct CurrentSong //Värdena i denna struct ska ändras medans man spelar 
{
    private:

    public:
        double songPosition; //time
        int notesHit;
        int notesMissed;
        
    
};
struct Beatmap
{
    public:
        int lane;
        double t;
        Timer timer1;
        double currTime;
        float beatPosition; //relativ till songPosition
        void LoadBeatMap(const char*bPath) //läser in en csv-fil med beatmappen i. Denna beatmap kommer från ett excel-dokument med timing och annan notinformation
        {
            std::ifstream fullBeatmap;
            fullBeatmap.open(bPath);

            if (fullBeatmap.fail())
            {
                std::cerr << "Kan inte öppna filen" << bPath <<std::endl; //skickar ett smidigt errormeddelande
            }
            
            int i = 0; //för denna while-loop
            StartTimer(&timer1, 10); //& för att peka på timern som definerades några rader upp i denna struct
            while (fullBeatmap.peek() != EOF) //medans vi läser filen, innan den har tagit slut alltså, kollar vi på tabellen rad för rad
            {
                currTime = GetElapsed(timer1);
            //läser en rad av beatmappen
                std::string lt; //något av de 2 värdena i csv-filen(l står för värdet i kolumn 0, vilken fil på vägen (0-4), t står för tiden i sekunder då noten ska dyka upp)
                getline(fullBeatmap, lt, ',');
                std::cout << lt <<std::endl;
                std::cout << currTime;

                
                if (i < 1)
                {
                    //l
                    //talet är i första kolumnen, ska då behandlas som lane
                    std::cout << "reading lane!";
                    lane = std::stoi(lt);
                }
                else
                {
                    //t
                    std::cout << "reading time";
                    t = std::stod(lt);
                    i= -1;//så att i ska bli 0 igen när loopen börjar om
                    //kalla funktionen som sätter ut en not utifrån dessa parametrar, vänta sen till tiden för nästa not
                } 
                i++;
            }
            fullBeatmap.close();

        }
};
