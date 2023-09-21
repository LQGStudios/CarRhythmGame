#include "audio.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <list>

//arrayen med låtar defineras 
//*ska fixa ett bättre sätt att lösa det här sen
const char *trackList[2] = {"assets/music/math_jungle.ogg", "assets/music/King-Gizzard_Horology.ogg"};
//indexen är desamma
const char *midiList[2] = {"assets/midi/math_jungle.midi", "assets/midi/King-Gizzard_Horology.midi"};


const char *filename; //för att detta ska vara lätt tillgängligt i alla funktioner

Music music;
Audio::Audio()
{
    //sätter värdena av variablerna i audio.hpp
}

void Audio::Update()
{
    //!---------------------------------------------
    UpdateMusicStream(music);   // för att musiken ska ladda
    std::cout << GetMusicTimePlayed(music) << "\n";
    //!---------------------------------------------

}

void Audio::PlayOGG(const char *filename){
    InitAudioDevice();
    music = LoadMusicStream(filename);
    //start playing ogg file
    PlayMusicStream(music);
    GetMusicTimePlayed(music);
    //bool pause = false;    
}


void Audio::PlaySong(int songIndex)
{
    
    const char *filename = trackList[songIndex];
    PlayOGG(filename);
    //initialize beatmap

    //const char *midiName = "assets/music/math_jungle.ogg";
    //PlayMIDI(midiName);

}