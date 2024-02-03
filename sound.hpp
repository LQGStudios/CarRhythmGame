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
    CSVNote(int _lane,float _time)
    {
        lane = _lane;
        time = _time;
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
        //?kodstandard för csv är att ha 5värdesiffror på tiden när noten ska sättas ut på första taktslaget, annars 4 värdesiffrorshare  
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
                std::string line; //något av de 2 värdena i csv-filen(l står för värdet i kolumn 0, vilken fil på vägen (0-4), t står för tiden i sekunder då noten ska dyka upp)
                //läser en rad av beatmappen
                getline(fullBeatmap, line, ',');
                //std::cout << line <<std::endl;

                if (i < 1)
                {
                    //talet är i första kolumnen, ska då behandlas som lane
                    //l= lane
                    l = std::stoi(line);
                    //std::cout << "reading lane!" << l;
                }
                else
                {
                    //t = time
                    t = std::stod(line);
                    i= -1;//så att i ska bli 0 igen när loopen börjar om
                    //std::cout << "reading time, " << t;
                    
                } 
                lt.push_back(CSVNote(l,t));
                i++;
                
            }
            std::cout << lt[1].time;
            
            fullBeatmap.close();
            std::cout << "beatmappen e slut";
        }
            /* //todo: fix this garbage
            while (fullBeatmap.peek() != EOF) //medans vi läser filen, innan den har tagit slut alltså, kollar vi på tabellen rad för rad
            {
                std::string lts; //något av de 2 värdena i csv-filen(l står för värdet i kolumn 0, vilken fil på vägen (0-4), t står för tiden i sekunder då noten ska dyka upp, s:et är för att det är en string)
                getline(fullBeatmap, lts, ','); //läser en rad av beatmappen
                //std::cout << lts <<std::endl;

                if (i < 1)
                {
                    //talet är i första kolumnen, ska då behandlas som lane
                    //l= lane
                    l = std::stoi(lts);
                    //std::cout << "reading lane!" << l;
                }
                else
                {
                    //t = time
                    t = std::stod(lts);
                    i= -1;//så att i ska bli 0 igen när loopen börjar om
                    //std::cout << "reading time, " << t;
                    
                } 
                i++;
                CSVNote ltcsv = {l, t};
                std::cout << ltcsv.lane << std::endl;
                //lt.push_back(lts)
                
            }
            
            fullBeatmap.close();
            std::cout << "beatmappen är slut\n";
        }
        */

        bool ShouldPlaceNote(double elapsed) // kalla på i main, vid update music stream
        {
            //todo: ingen for loop här. Börja med att bara kolla om [0] av lt
            //todo: matchar tiden. När den har returnat true en gång, gå vidare till [1] av lt och så vidare
            //todo: laborera med margin. Den ska vara ca 1/60 av en sekund iom 60 fps target
            float margin = 0.0167f;
            int i = 0;
            /*
            if(lt[i].time - margin < elapsed && elapsed < lt[i].time + margin)
            {
                return true;
            }
            */
            /*
            for(std::size_t i = 1; i < lt.size(); i++) //man kan inte jämföra en int med  lt.size så därför är "i" en "size_t"
            {
                //std::cout << lt[i].time << std::endl;
                return false;
            }
            */
            return false;
        }

};