#include "raylib.h"
#include "vector"
#include "libs/raymath.h"
#include <list>
#include <fstream> //för att läsa csv med beatmaps
#include <iostream>
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
        int notesInARow; //nollställ när en not har nått skärmens nedkant
        
    
};
struct CSVNote
{
    int lane;
    double time; 
    CSVNote(int _lane,double _time)
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
        int currentNoteInSong = 0;
        
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
            
            while (fullBeatmap.peek() != EOF) //medans vi läser filen, innan den har tagit slut alltså, kollar vi på tabellen rad för rad
            {
                std::string line; //något av de 2 värdena i csv-filen(l står för värdet i kolumn 0, vilken fil på vägen (0-4), t står för tiden i sekunder då noten ska dyka upp)
                std::string s; //
                //läser en rad av beatmappen
                getline(fullBeatmap, line, '\n'); //tolkar en line som texten mellan newlineo och nästa newline
                s = line.substr(2,line.length()); //s är den delen av raden efter kommatecknet. 2 för att lane och komma är 2 karaktärer

                
                
                //l = lane
                l = std::stoi(line.substr(0,1));
                //std::cout << "reading " << s << " time!" << t;
                // t = time
                t = std::stod(s);               
                
                lt.push_back(CSVNote(l,t));
                std::cout << "lane to place in: "<< lt[lt.size() - 1].lane << std::endl; //outputar den senast tillagda i lane

                
            }
            
            std::cout << "beatmappen e slut";
            fullBeatmap.close();
        }

        int ShouldPlaceNote(double elapsed) // kalla på i main, vid update music stream
        {
            //todo: ingen for loop här. Börja med att bara kolla om [0] av lt
            //todo: matchar tiden. När den har returnat true en gång, gå vidare till [1] av lt och så vidare
            //todo: laborera med margin. Den ska vara ca 1/60 av en sekund iom 60 fps target
            float margin = 0.0167f;

            if(lt[currentNoteInSong].time - margin < elapsed && elapsed < lt[currentNoteInSong].time + margin)
            {
                return lt[currentNoteInSong++].lane; //säger till vilken lane
            }

            /*
            for(std::size_t i = 1; i < lt.size(); i++) //man kan inte jämföra en int med  lt.size så därför är "i" en "size_t"
            {
                //std::cout << lt[i].time << std::endl;
                return false;
            }
            */
            return -1; //-1 motsvarar false
        }

};