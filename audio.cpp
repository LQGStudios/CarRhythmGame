#include <raylib.h>
#include "audio.hpp"
#include <chrono>
#include <iostream>
#include <list>
#include <raymath.h>
using namespace std; //för att slippa skriva std::string

//arrayen med låtar defineras 
//*ska fixa ett bättre sätt att lösa det här sen
//indexen är desamma
Music music;
Song trackList[2]; //skapar en lista över låt-klasser

const char *filename; //för att detta ska vara lätt tillgängligt i alla funktioner
/*
const char *midiList[2] = {"assets/midi/math_jungle.mid", "assets/midi/King-Gizzard_Horology.mid"};
*/

void Audio::Update()
{
    UpdateMusicStream(music);   // för att musiken ska ladda
    Timing(); //kollar hur långt in i låten man är
}
void Song::CreateTrackList()
{
    //tanken är att stoppa in all data om en låt här
    Song mj("Math Jungle - Max Wasserman", "assets/music/math_jungle.ogg", "assets/music/math_jungle.mid", 120, 0.0f);
    Song h("Horology - King Gizzard and the Lizard Wizard", "assets/music/King-Gizzard_Horology.ogg", "assets/music/King-Gizzard_Horology.mid", 165, 0.0f);
    
    trackList[0] = mj;
    trackList[1] = h;

}

void Audio::PlaySong(int i)
{
    Song song = trackList[i]; 
    //spelar enbart ljudet
    PlayOGG(song.path);
    //laddar in midi-filen, vilket är det man ska trycka på knappar i takt med
    PlayBeatmap(song.bPath);
   // PlayMIDI(midiname);
    //const char *midiName = "assets/music/math_jungle.ogg";
    //PlayMIDI(midiName);

}


void Audio::Timing()
{
    std::cout << GetMusicTimePlayed(music) << "\n";
    float songPosition = GetMusicTimePlayed(music);
    //hur länge man väntar innan noterna kommer fram
}

void Audio::PlayOGG(const char *path){
    InitAudioDevice();
    //laddar musik
    music = LoadMusicStream(path);
    //spelar ogg-filen
    PlayMusicStream(music);
    GetMusicTimePlayed(music);
    //bool pause = false;    
}

void Audio::PlayBeatmap(const char*midiname)
{
    //läs in filen
    //midifile.read("test.mid");
}

void Audio::NoteMovement()
{

}
