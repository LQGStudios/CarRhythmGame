#include "raylib.h"
#include "vector"
#include "libs/raymath.h"
#include <list>
#include <fstream> //för att läsa fil med savedata
#include <iostream>
#include <string>
//?include guard, så att inte sound.hpp och data slåss om vem som var först att definera saker
#pragma once

struct HighScore
{
    int first = 0;
    int second = 0;
    int third = 0;

    HighScore(int first, int second, int third)
    {
        
    }
};

struct Settings
{
    double delay = 2.31674f; //använd i sound.hpp
    std::vector<HighScore> hi = {}; //alla high scores i en vector
    void SetDelay(double timeDiff)
    {
        delay += timeDiff; //slår alla andra lösningar, no diff
    }
    Loadings()
    {
        // sätt saker och ting till saken på rad x i sparfilen
    }
    Savings(double d) //om bråttom, ta bort
    {
        //skriv värdet av delay osv. till fil
    }
    Resettings()
    {
        delay = 2.31674f;
        Savings(delay);
    }
    Rescore()
    {

    }

};