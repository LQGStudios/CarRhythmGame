#include "raylib.h"
#include "vector"
#include "libs/raymath.h"
#include <list>
#include <fstream> //för att läsa fil med savedata
#include <iostream>
#include <string>


struct Settings
{
    double delay;  
    void SetDelay(double delay, double time)
    {
        delay += time; //
        //s
    }
    LoadSettings()
    {
        // sätt saker och ting till saken på rad x i sparfilen
    }
    SaveSettings()
    {
        //skriv värdet av delay osv. till fil
    }
};
struct HighScore
{
    int first = 0;
    int second = 0;
    int third = 0;

    HighScore(int first, int second, int third)
    {
        
    }
};