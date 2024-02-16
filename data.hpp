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


    HighScore(int one, int two, int three)
    {
        first = one;
        second = two;
        third = three;
    }
};
struct Menu
{
    int selected;
};
struct Settings
{
    float delay = 2.31674f; //använd i sound.hpp

    float musicVolume = 1.0f;
    float carVolume = 1.0f;
    float sfxVolume = 1.0f;


    std::vector<HighScore> hi = {}; //alla high scores i en vector
    void SetDelay(float timeDiff)
    {
        delay += timeDiff; //slår alla andra lösningar, no diff
    }
    void Loadings()
    {
        // sätt saker och ting till saken på rad x i sparfilen
    }
    void SaveSettings(double d) //om bråttom, ta bort
    {
        delay = d;
        //skriv värdet av delay osv. till fil
    }
    void Resettings()
    {
        delay = 2.31674f;
        SaveSettings(delay);
    }
    void ResetScore()
    {

    }

};