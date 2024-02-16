#include "raylib.h"
#include <vector>
#include "libs/raymath.h"
#include <list>
#include <fstream> //för att läsa fil med savedata
#include <iostream>
#include <string>
#include <algorithm>
//?include guard, så att inte sound.hpp och data slåss om vem som var först att definera saker
#pragma once

struct Menu
{
    int selected;
};
struct Settings
{

    //standardvärden
    float delay = 2.317f; //använd i sound.hpp
    float musicVolume = 1.0f;
    float carVolume = 0.005f;
    float sfxVolume = 1.0f;
    std::vector<int> allHighScores = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


    void ChangeSetting(int change, Menu m) //om vänster/högerpil nedtryckt
    {
        switch (m.selected)
        {
        case 0:
            SetSetting(delay, change * 0.001f); //ändra med 1 ms varje gång
            break;
        case 1:
            SetSetting(musicVolume, change * 0.005f); //ändra med 1% varje gång
            break;
        case 2:
            SetSetting(carVolume, change * 0.00005f); //ändra lite lite varje gång
            break;
        case 3:
            SetSetting(sfxVolume, change * 0.005f); //ändra med 1% varje gång
            break;
        default:
            break;
        }
    }
    void SetSetting(float& setting, float diff)
    {
        setting += diff; //slår alla andra lösningar, no diff
        if (setting <= 0)
        {
            setting = 0;
        }
        if(musicVolume >= 1.0f)
            musicVolume = 1.0f;
        if(carVolume >= 1.0f)
            carVolume = 1.0f;
        if(sfxVolume >= 1.0f)
            sfxVolume = 1.0f;
        std::cout << setting << std::endl;
    }
    void SetAndSortHighScores(int newScore, int offset)
    {
        int tempscores[4] = {0,0,0,0};

        tempscores[0] = allHighScores[3 * offset];
        tempscores[1] = allHighScores[3 * offset + 1];
        tempscores[2] = allHighScores[3 * offset + 2];

        tempscores[3] = newScore;
        std::sort(tempscores, tempscores + (sizeof(tempscores)/sizeof(tempscores[0])), std::greater<int>());

        allHighScores[3 * offset] = tempscores[0];
        allHighScores[3 * offset + 1] = tempscores[1];
        allHighScores[3 * offset + 2] = tempscores[2];

    }

    void LoadSettings()
    {
        std::ifstream save;
        save.open("save.data"); //den är öppen att läsa till
        if(save.is_open())
        {
            std::string line;
            for(int i = 0; i < 15; i++)
            {
                std::getline(save, line);
                allHighScores[i] = std::stoi(line);
            }
            std::getline(save, line);
            delay = std::stof(line); //string to float
            std::getline(save, line);
            musicVolume = std::stof(line);
            std::getline(save, line);
            carVolume = std::stof(line);
            std::getline(save, line);
            sfxVolume = std::stof(line);
        }
        // sätt saker och ting till saken på rad x i sparfilen
    }
    void SaveSettings() //skriv värdet av delay osv. till fil
    {
        //sakerna som ska sparas är 19 stycken (första 15 är scores), de tar alla upp varsin rad i sparfilen
        std::string values[19] = {
            std::to_string(allHighScores[0]),
            std::to_string(allHighScores[1]),
            std::to_string(allHighScores[2]),
            std::to_string(allHighScores[3]),
            std::to_string(allHighScores[4]),
            std::to_string(allHighScores[5]),
            std::to_string(allHighScores[6]),
            std::to_string(allHighScores[7]),
            std::to_string(allHighScores[8]),
            std::to_string(allHighScores[9]),
            std::to_string(allHighScores[10]),
            std::to_string(allHighScores[11]),
            std::to_string(allHighScores[12]),
            std::to_string(allHighScores[13]),
            std::to_string(allHighScores[14]),
            std::to_string(delay),
            std::to_string(musicVolume),
            std::to_string(carVolume),
            std::to_string(sfxVolume)
        };

        std::ofstream save;
        save.open("save.data", std::ofstream::out); //den är öppen att skriva till
        if(save.is_open())
        {
            for(int i = 0; i < 19; i++)
            {
                
                save<<values[i]<< std::endl;
            }
            std::cout << "sparade till fil" << std::endl;
            save.close();
        }
        else std::cerr<<"Unable to open file";

    }
    void Resettings()
    {
        delay = 2.31674f;
        musicVolume = 1.0f;
        carVolume = 0.004f;
        sfxVolume = 0.8f;
        SaveSettings();
    }

};