#include "raylib.h"
#include "libs/raymath.h"
#include "assets.hpp"
#include <list>

struct Note
{
    private:
        Model noteModel = noteAssets::Models;
        Vector2 notePosition =  (Vector2){1.5f, 27.0f};
    
    public: 
        bool outOfBounds = false;
        void drawNoteModel()
        {   
            DrawModel(noteModel, (Vector3){notePosition.x, 0.0f, notePosition.y}, 1.0f, YELLOW);//rita modellen
        }
        void moveNote()
        {
            //Z positionen
            notePosition.y -= 0.2f;
            //kamerans z-position är ungefär -7, och om objektet är bakom kameran behövs det inte längre
            if(notePosition.y < -7)
            {
                outOfBounds = true;
            }
        }

        void deleteNote()
        {
            //ta bort modellen från ram och frigör minnet
            UnloadModel(noteModel);
            
        }
        
        Note(int lane) //ny dekoration
        {
            notePosition.x = -3.0f + (1.5f * lane);
        }

        

        
};
