#include "raylib.h"
#include "vector"
#include "libs/raymath.h"
#include <list>
#include <fstream> //för att läsa csv med beatmaps
#include <string>
 
typedef struct Timer {
    double startTime;   // Start time (seconds)
    double lifeTime;    // Lifetime (seconds)
} Timer;

void StartTimer(Timer* timer, double lifetime)
{
    std::cout << "startade timer med namn: " << timer;
    timer->startTime = GetTime(); //double
    timer->lifeTime = lifetime;
}

bool TimerDone(Timer timer)
{
    return GetTime() - timer.startTime >= timer.lifeTime;
}

double GetElapsed(Timer timer)
{
    //vi använder &timer för att peka på timers som defineras tidigare i vår kod
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
struct CSVNote
{
    int lane;
    double time; 
    CSVNote(float _time, int _lane)
    {
        time = _time;
        lane = _lane;
    }
};

struct Beatmap
{
    public:
        int l;
        double t;
        Timer timer1;
        double currTime;
        float beatPosition; //relativ till songPosition
        
        std::vector<CSVNote> lt = {}; //lane, time, datan byts ut mot det som står i csv

        //läser in en csv-fil med beatmappen i. Denna beatmap kommer från ett excel-dokument med timing och annan notinformation
        //csv to vector converter
        void LoadBeatMap(const char*bPath) 
        {
            std::ifstream fullBeatmap;
            fullBeatmap.open(bPath);

            if (fullBeatmap.fail())
            {
                std::cerr << "Kan inte öppna filen" << bPath <<std::endl; //skickar ett smidigt errormeddelande
            }
            
            int i = 0; //för denna while-loop
            while (fullBeatmap.peek() != EOF) //medans vi läser filen, innan den har tagit slut alltså, kollar vi på tabellen rad för rad
            {
                std::string lt; //något av de 2 värdena i csv-filen(l står för värdet i kolumn 0, vilken fil på vägen (0-4), t står för tiden i sekunder då noten ska dyka upp)
                //läser en rad av beatmappen
                getline(fullBeatmap, lt, ',');
                std::cout << lt <<std::endl;

                if (i < 1)
                {
                    //talet är i första kolumnen, ska då behandlas som lane
                    //l= lane
                    l = std::stoi(lt);
                    //std::cout << "reading lane!" << l;
                }
                else
                {
                    //t = time
                    t = std::stod(lt);
                    i= -1;//så att i ska bli 0 igen när loopen börjar om
                    //std::cout << "reading time, " << t;
                    
                } 
                i++;
                lt.push_back(l);
                lt.push_back(t);   
                
            }
            
            fullBeatmap.close();
            std::cout << "beatmappen är slut\n";
        }

        bool ShouldPlaceNote(Timer timer) // kalla på i main, vid update music stream
        {
            float margin = 0.05f;
            for(std::size_t i = 1; i < lt.size(); i++) //man kan inte jämföra en int med  lt.size så därför är "i" en "size_t"
            {
                std::cout << lt[i].time << std::endl;

                if(GetElapsed(timer) < lt[i].time + margin && GetElapsed(timer) < lt[i].time - margin)
                {
                    return true;
                }
                return false;
            }
            return false;
        }

};