#include "raylib.h"
#include "libs/raymath.h"
#include <list>

struct HitText
{
    public:
        float lifeSpan = 6.0f;
        int type;

        HitText(int _type)
        {
            type = _type;
        }
};

struct Note
{

    public: 
        Vector2 notePosition =  (Vector2){1.5f, 27.0f};
        bool outOfBounds = false;
        
        bool moveNote()
        {
            //Z positionen
            notePosition.y -= 0.2f;
            //kamerans z-position är ungefär -7, och om objektet är bakom kameran behövs det inte längre
            if(notePosition.y < -7)
            {
                outOfBounds = true;
            }
            return outOfBounds;
        }
        
        Note(int lane) //ny dekoration
        {
            notePosition.x = -3.0f + (1.5f * lane);
        }

        

        
};
