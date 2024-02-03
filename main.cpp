//standard c++ headers
#include <vector>
#include <iostream>
//raylib headers
#include "raylib.h"
#include "libs/raymath.h"
#include "libs/raygui.h"

//våra egna headers 
#include "player.hpp"
#include "scenery.hpp"
#include "note.hpp"
#include "sound.hpp"

//?musik
Music music; //path till låten
Song song;
Beatmap bm;
CurrentSong cs;
Timer t;
Timer songTimer;
double songLength;//assets for the world

//misc variabler
unsigned int cycles = 0;
bool transition = false;
int activeScene = 0;
Texture2D grassTexture;
Texture2D roadTexture;
Texture2D skyTexture;

Model grassPlane;
Model asphaltPlane;

//moving pieces
Texture2D noteTexture;
Model sceneryModels[2];
Model playerModel;
Sound moveSound;

//shaders
Shader worldShader;
Shader objectShader;
Shader noteShader;

void loadAssets()
{
    grassTexture = LoadTexture("assets/grass11.png");
    roadTexture = LoadTexture("assets/asphalt.png");
    skyTexture = LoadTexture("assets/Fading_Sky-Sunset_02-1024x512.png");

    noteTexture = LoadTexture("assets/note.png");
    sceneryModels[0] = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 2.0f)); 
    sceneryModels[1] = LoadModelFromMesh(GenMeshCube(0.5f, 3.0f, 2.0f));
    playerModel = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 2.0f));
    moveSound = LoadSound("assets/104026__rutgermuller__tires-squeaking.wav");
    SetSoundVolume(moveSound, 0.5);// justerar volymen (mellan 0 och 1)

    grassPlane = LoadModelFromMesh(GenMeshPlane(60.0f, 50.0f, 50, 50));
    SetMaterialTexture(&grassPlane.materials[0], MATERIAL_MAP_DIFFUSE, grassTexture);
    asphaltPlane = LoadModelFromMesh(GenMeshPlane(9.5f, 50.0f, 50, 50));
    SetMaterialTexture(&asphaltPlane.materials[0], MATERIAL_MAP_DIFFUSE, roadTexture);
    worldShader = LoadShader("assets/base.vs",0);
    grassPlane.materials[0].shader = worldShader;
    asphaltPlane.materials[0].shader = worldShader;

    objectShader = LoadShader("assets/objects.vs",0);
    sceneryModels[0].materials[0].shader = objectShader;
    sceneryModels[1].materials[0].shader = objectShader;

    noteShader = LoadShader("assets/notes.vs",0);
}

void unloadAssets()
{
    UnloadTexture(grassTexture);
    UnloadTexture(roadTexture);
    UnloadTexture(skyTexture);

    UnloadTexture(noteTexture);
    UnloadModel(sceneryModels[0]);
    UnloadModel(sceneryModels[1]);
    UnloadModel(playerModel);
    UnloadSound(moveSound);

    UnloadModel(grassPlane);
    UnloadModel(asphaltPlane);
    UnloadShader(worldShader);
    UnloadShader(objectShader);
    UnloadShader(noteShader);
}


void drawWorld(Camera3D& cam, Player& plObj, std::vector<Scenery>& scObjs, std::vector<Note>& ntObjs)
{
    //setup
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexturePro(skyTexture, {0,0,1024,512}, {0,0,1280,720}, {0,0}, 0.0f, WHITE); //rita skyboxen
    BeginMode3D(cam);

    //rita världen
    DrawModel(grassPlane, (Vector3){0.0f,-0.6f,-5.0f}, 1.0f, WHITE);
    DrawModel(asphaltPlane, (Vector3){0.0f,-0.59f,-5.0f}, 1.0f, WHITE);

    //rita spelaren
    plObj.drawPlayer(playerModel);

    BeginShaderMode(noteShader); //noter har inte en inbyggd shader och därför behövs shadermode
        for (int i = 0; i < (int)ntObjs.size(); i++)
        {
            //rita noter
            DrawBillboard(cam, noteTexture, (Vector3){ntObjs[i].notePosition.x, 0, ntObjs[i].notePosition.y}, 2.0f, WHITE);
        }
    EndShaderMode();
    
    //rita dekorationer
    sceneryModels[scObjs[0].selectedModel].transform = MatrixTranslate(scObjs[0].sceneryPosition.x, 0.0f, scObjs[0].sceneryPosition.y);
    DrawModel(sceneryModels[scObjs[0].selectedModel], (Vector3){0.0f,0.0f,0.0f}, 1.0f, BLUE);

    //Rita FPS och avsluta ritande
    EndMode3D();
    DrawFPS(10, 10);

    EndDrawing();
}

void drawMenu()
{
    //setup
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("RYTHM\nRALLY", 500, 50 + 10 * sin(cycles * PI/180), 80, DARKGRAY);
    DrawText("1: Song 1\n2: Song 2\n3: Song 3\n4: Song 4\n5: Song 5\n", 10, 400, 40, DARKGRAY);

    

    if(transition == true)
    {
        DrawCircle(640, 360, cycles * 15, BLACK);
        if(15 * cycles >= 800)
        {
            activeScene = 1;
            transition = false;
        }
    }

    //Rita FPS och avsluta ritande

    DrawFPS(10, 10);

    EndDrawing();
}
//?musik
void PlaySong(const char* path, Beatmap& bm,const char* bPath) //den här skulle kunna flyttas till sound.hpp
{
    music = LoadMusicStream(path);
    bm.LoadBeatMap(bPath); //ska ske async från main eller sitta i en vector. Varje gång ny rad läses ur csv, knuffa in i vector
    PlayMusicStream(music);
    StartTimer(&songTimer, GetMusicTimeLength(music)); //& hämtar adressen till en vanlig variabel. I sound.hpp tar ten här funtionen en poiunter som argument så därför behövs & här
    std::cout << GetMusicTimeLength(music);
    std::cout << "\n\n\nHej, beatmappen är laddad\n";

}



int main()
{
    //bredden och höjden på skärmen
    const int screenWidth = 1280;
    const int screenHeight = 720;
    
    //öppna ett nytt fönster
    InitWindow(screenWidth, screenHeight, "Rythm Rally");
    InitAudioDevice();
    SetTargetFPS(60);

    //?musik
    //todo: switch för att välja låt
    PlaySong("assets/music/140kph.ogg", bm, "assets/beatmaps/bm140.csv");

    //skapa en ny kamera
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 6.44f, -6.1f};
    camera.target = (Vector3){0.0f, 2.0f, 1.0f};
    camera.up = (Vector3){0.0f, 0.69f, 0.15f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    

    Player playerObject; //skapa spelaren
    std::vector<Scenery> sceneryObjects = {};
    std::vector<Note> noteObjects = {}; //lista över alla dekorationsobjekt
    sceneryObjects.push_back(Scenery(0)); //lägg till ett nytt dekorationsobjekt i listan

    loadAssets();

    //huvudloop
    while (!WindowShouldClose())
    {
        cycles += 1;

        if(activeScene == 0)
        {
            if(IsKeyPressed(KEY_ENTER) && transition == false)
            {
                transition = true;
                cycles = 0;
            }
            drawMenu();
        }
        else if(activeScene == 1)
        {
            //har spelaren tryckt på en knapp? Flytta och animera om spelaren gjorde det
            bool playerPressedHit = playerObject.playerInput(moveSound); 
            
            //flytta varje dekoration och kontrollera om den fortfarande behövs
            for (int i = 0; i < (int)sceneryObjects.size(); i++)
            {
                Scenery& sc = sceneryObjects[i];
                sc.moveScenery();
                if(sc.outOfBounds == true)
                {
                    sc = Scenery(1);
                }
            }
            
            for (int i = (int)noteObjects.size() - 1; i >= 0; i--)
            {
                Note& nt = noteObjects[i];
                nt.moveNote();
                if(playerPressedHit == true)
                {

                    /*

                    y>0 miss
                    0 > y > -0.5 tidig
                    -0.5 > y > -1.5 perfekt 
                    -1.5 > y > -2.0 sen
                    -2.0 > y miss

                    */
                    if(playerObject.playerXPosition == nt.notePosition.x)
                    {
                        
                        if(nt.notePosition.y > -0.5f && nt.notePosition.y < 0.0f)//tidig träff
                        {
                            std::cout << "EARLY" << std::endl;
                            nt.outOfBounds = true;
                        }
                        else if(nt.notePosition.y > -1.5f && nt.notePosition.y < -0.5f)//perfekt träf
                        {
                            std::cout << "PERFEKT" << std::endl;
                            nt.outOfBounds = true;
                        }
                        else if(nt.notePosition.y > -2.0f && nt.notePosition.y < -1.5f) //sen träff
                        {
                            std::cout << "LATE" << std::endl;
                            nt.outOfBounds = true;
                        }
                        else
                        {
                            std::cout << "MISS" << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "MISS" << std::endl;
                    }
                }
                if(nt.outOfBounds == true)
                {
                    noteObjects.erase(noteObjects.begin() + i); //radera notobjekt från listan
                }
            }
            
            
            drawWorld(camera, playerObject, sceneryObjects, noteObjects); //rita världen
        }
        
        //?Musik
        UpdateMusicStream(music);   // Ser till att musiken fortsätter spela
        //std::cout << GetElapsed(songTimer) << std::endl;
        
        if(bm.ShouldPlaceNote(songTimer)) //om tiden är inom en viss  marginal, sätt ut not

        {
            //?how it's done:
            //noteObjects.push_back(Note(lane)); 
            std::cout << "placed note lmao" << std::endl;
        }
        else
        {
            //iterate through lt vector perchance
            std::cout << "not the time to place a note" << std::endl;
        }
    }

    unloadAssets();
    CloseWindow();
    
}

