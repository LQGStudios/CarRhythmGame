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
#include "data.hpp" 
#include "menuHelper.hpp"

//?musik
Music music; //path till låten
Beatmap bm;
CurrentSong cs;
Timer t;
Timer songTimer;
Song song;
const char* titles[] = {"1: 140 kph\n", "2: Song 2\n", "3: Song 3\n", "4: Song 4\n", "5: Song 5\n"};
int scores[] = {0, 0, 0};

//misc variabler
Menu m;
menuHelper mHelp;
int selectedSong = 0;
unsigned int cycles = 0;
bool transition = false;
int activeScene = 0;
float scrollValue = 0;
int scrollLoc = 0;

//Textures
Texture2D grassTexture;
Texture2D roadTexture;
Texture2D skyTexture;
Texture2D grades;
Texture2D frame;
Texture2D failTexture;
Texture2D backgrounds[3];

Model grassPlane;
Model asphaltPlane;

//moving pieces
Texture2D noteTexture;
Model sceneryModels[2][2];
Model playerModel;
Sound moveSound;

//shaders
Shader worldShader;
Shader objectShader;
Shader noteShader;

void loadAssets()
{   
    bm.s.LoadSettings();
    grassTexture = LoadTexture("assets/grass11.png");
    roadTexture = LoadTexture("assets/asphalt.png");
    skyTexture = LoadTexture("assets/Fading_Sky-Sunset_02-1024x512.png");
    grades = LoadTexture("assets/grades.png");
    frame = LoadTexture("assets/frame.png");
    failTexture = LoadTexture("assets/Lbozo.png");

    backgrounds[0] = LoadTexture("assets/TitleScreen.png");
    backgrounds[1] = LoadTexture("assets/TitleScreen2.png");
    backgrounds[2] = LoadTexture("assets/TitleScreen3.png");

    noteTexture = LoadTexture("assets/note.png");
    sceneryModels[0][0] = LoadModel("assets/windmillWalls.glb");
    sceneryModels[0][1] = LoadModel("assets/windmillMain.glb");

    sceneryModels[1][0] = LoadModel("assets/ladaMain.glb");
    sceneryModels[1][1] = LoadModel("assets/ladaWalls.glb");

    playerModel = LoadModel("assets/carfinal.glb");
    moveSound = LoadSound("assets/104026__rutgermuller__tires-squeaking.wav");
    SetSoundVolume(moveSound, 0.005f);

    grassPlane = LoadModelFromMesh(GenMeshPlane(60.0f, 50.0f, 50, 50));
    SetMaterialTexture(&grassPlane.materials[0], MATERIAL_MAP_DIFFUSE, grassTexture);
    asphaltPlane = LoadModelFromMesh(GenMeshPlane(9.5f, 50.0f, 50, 50));
    SetMaterialTexture(&asphaltPlane.materials[0], MATERIAL_MAP_DIFFUSE, roadTexture);
    worldShader = LoadShader("assets/base.vs", "assets/scroll.fs");
    grassPlane.materials[0].shader = worldShader;
    asphaltPlane.materials[0].shader = worldShader;
    scrollLoc = GetShaderLocation(worldShader, "uTime");
    
    noteShader = LoadShader("assets/notes.vs",0);

    objectShader = LoadShader("assets/objects.vs",0);
    sceneryModels[0][0].materials[0].shader = objectShader;
    sceneryModels[0][1].materials[0].shader = objectShader;
    
    sceneryModels[1][0].materials[0].shader = objectShader;
    sceneryModels[1][1].materials[0].shader = objectShader;

}

void unloadAssets()
{
    UnloadTexture(grassTexture);
    UnloadTexture(roadTexture);
    UnloadTexture(skyTexture);
    UnloadTexture(failTexture);
    UnloadTexture(frame);
    UnloadTexture(grades);

    UnloadTexture(backgrounds[0]);
    UnloadTexture(backgrounds[1]);
    UnloadTexture(backgrounds[2]);

    UnloadTexture(noteTexture);
    
    UnloadModel(sceneryModels[0][0]);
    UnloadModel(sceneryModels[0][1]);
    UnloadModel(sceneryModels[1][0]);
    UnloadModel(sceneryModels[1][1]);

    UnloadModel(playerModel);
    UnloadSound(moveSound);

    UnloadModel(grassPlane);
    UnloadModel(asphaltPlane);
    UnloadShader(worldShader);
    UnloadShader(objectShader);
    UnloadShader(noteShader);
}


void drawWorld(Camera3D& cam, Player& plObj, Scenery& scObj, std::vector<Note>& ntObjs, std::vector<HitText>& htObjs)
{
    //setup
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexturePro(skyTexture, {0,0,1024,512}, {0,0,1280,720}, {0,0}, 0.0f, WHITE); //rita skyboxen
    BeginMode3D(cam);

    //rita världen
    scrollValue += 0.2f * GetFrameTime();
    SetShaderValue(worldShader, scrollLoc, &scrollValue, SHADER_UNIFORM_FLOAT);
    DrawModel(grassPlane, (Vector3){0.0f,-0.6f,-5.0f}, 1.0f, WHITE);
    DrawModel(asphaltPlane, (Vector3){0.0f,-0.59f,-5.0f}, 1.0f, WHITE);

    //rita spelaren
    plObj.drawPlayer(playerModel);

    //rita dekorationer
        sceneryModels[scObj.selectedModel][0].transform = MatrixTranslate(scObj.sceneryPosition.x, -1.0f, scObj.sceneryPosition.y);
        sceneryModels[scObj.selectedModel][1].transform = MatrixTranslate(scObj.sceneryPosition.x, -1.0f, scObj.sceneryPosition.y);
        if(scObj.selectedModel == 1)
        {
            DrawModel(sceneryModels[scObj.selectedModel][0], (Vector3){0.0f,0.0f,0.0f}, 1.0f, WHITE);
            DrawModel(sceneryModels[scObj.selectedModel][1], (Vector3){0.0f,0.0f,0.0f}, 1.0f, RED);
        }
        else
        {
            DrawModel(sceneryModels[scObj.selectedModel][0], (Vector3){0.0f,0.0f,0.0f}, 1.0f, BROWN);
            DrawModel(sceneryModels[scObj.selectedModel][1], (Vector3){0.0f,0.0f,0.0f}, 1.0f, GRAY);
        }
    BeginShaderMode(noteShader); //noter har inte en inbyggd shader och därför behövs shadermode
        for (int i = (int)ntObjs.size() - 1; i >= 0; i--)
        {
            //rita noter
            DrawBillboard(cam, noteTexture, (Vector3){ntObjs[i].notePosition.x, 0, ntObjs[i].notePosition.y}, 2.0f, WHITE);
        }
    EndShaderMode();
    
    //Rita FPS och avsluta ritande
    EndMode3D();
    DrawFPS(10, 10);
    mHelp.drawSlider(10, 60, 144, 32, (float)(cs.earlyHit + cs.perfectHit + cs.lateHit + cs.notesMissed)/(float)bm.lt.size(), GREEN, GetColor(0x00000066));
    DrawText(TextFormat("%d%%", (int)floor((float)(cs.earlyHit + cs.perfectHit + cs.lateHit + cs.notesMissed)/(float)bm.lt.size() * 100)), 10, 20, 32, RAYWHITE);

    for (int i = (int)htObjs.size() - 1; i >= 0; i--)
    {
        htObjs[i].lifeSpan -= GetFrameTime() * 8.0f;
        if(htObjs[i].lifeSpan < 0)
        {
            htObjs.erase(htObjs.begin() + i);
        }

        switch (htObjs[i].type)
        {
        case 0:
            DrawText("EARLY", 10, 480 + htObjs[i].lifeSpan * 20.0f, 32, ColorAlpha(YELLOW, htObjs[i].lifeSpan/3.0f));
            break;
        case 1:
            DrawText("PERFECT", 10, 480 + htObjs[i].lifeSpan * 20.0f, 32, ColorAlpha(MAGENTA, htObjs[i].lifeSpan/3.0f));
            break;
        case 2:
            DrawText("LATE", 10, 480 + htObjs[i].lifeSpan * 20.0f, 32, ColorAlpha(ORANGE, htObjs[i].lifeSpan/3.0f));
            break;
        case 3:
            DrawText("MISS", 10, 480 + htObjs[i].lifeSpan * 20.0f, 32, ColorAlpha(RED, htObjs[i].lifeSpan/3.0f));
            break;
        default:
            break;
        }

        
    }
    
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
    std::cout << "\n\n\nHej, beatmappen är laddad\n Delay är: " << bm.s.delay << std::endl;

}

void DrawHighScores(int X, int Y, int title)
{
    if(title == 5){return;}
    scores[0] = bm.s.allHighScores[title * 3];
    scores[1] = bm.s.allHighScores[(title * 3) + 1];
    scores[2] = bm.s.allHighScores[(title * 3) + 2];
    DrawText("High Scores:\n",1.5*X, Y, 40, GOLD);
    for (int i = 0; i < 3; i++)
    {
        DrawText(TextFormat("%d points", scores[i]),1.5*X, Y + 40*(i+1), 40, WHITE);
    }
    
}

void DrawSettings(int keyPress)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    int sX = GetScreenWidth()/3;
    int sY = 150;
    DrawText(TextFormat("Audio delay:\n <- %f -> milliseconds", s.delay), sX, sY, 30, BLACK);
    DrawText(TextFormat("Music volume:\n <- %f ->", s.musicVolume * 100.0f), sX, sY + 80, 30, BLACK);
    DrawText(TextFormat("Car volume:\n <- %f ->", s.carVolume * 100.0f), sX, sY + 160, 30, BLACK);
    DrawText(TextFormat("SFX volume:\n <- %f ->", s.sfxVolume * 100.0f), sX, sY + 240, 30, BLACK);

    
    DrawText("Reset", sX, sY + 360, 30, BLACK);
    DrawText("Save Settings", sX, sY + 400, 30, BLACK);
    DrawText("Exit Without Saving", sX, sY + 440, 30, BLACK);

    switch (keyPress)
    {
    case 0:
        DrawText(TextFormat("Audio delay:\n <- %f -> milliseconds", bm.s.delay * 1000), sX, sY, 30, GOLD);
        break;
    case 1:
        DrawText(TextFormat("Music volume:\n <- %f ->", s.musicVolume * 100), sX, sY + 80, 30, GOLD);
        break;
    case 2:
        DrawText(TextFormat("Car volume:\n <- %f ->", s.carVolume * 100), sX, sY + 160, 30, GOLD);
        break;
    case 3:
        DrawText(TextFormat("SFX volume:\n <- %f ->", s.sfxVolume * 100), sX, sY + 240, 30, GOLD);

        break;
    case 4:
        DrawText("Reset", sX, sY + 360, 30, GOLD);
        break;
    case 5:
        DrawText("Save Settings", sX, sY + 400, 30, GOLD);
        break;
    case 6:
        DrawText("Exit Without Saving", sX, sY + 440, 30, GOLD);
        break;
    default:
        std::cout << "error in drawsettings" << std::endl;
        break;
    }
    
    DrawFPS(10, 10);
    EndDrawing();
}

void drawMenu(int keyPress)
{
    //setup
    BeginDrawing();
    ClearBackground(RAYWHITE);
    mHelp.drawFadeBg(backgrounds);


    int menuX = GetScreenWidth()/3;
    int menuY = 350;
    //text, x, y, fontsize, color
    mHelp.drawRoundedSquare(menuX - 50, menuY - 25, 550, 300, Color{0,0,0,120});
    DrawText("RYTHM\nRALLY", 500, 50 + 10 * sin(cycles * PI/180), 80, DARKGRAY);
    for (int i = 0; i < 6; i++)
    {
        if (i >=5) //om inställningar är valt
        {
            DrawText("Settings", menuX, menuY + 40*i, 40, LIGHTGRAY);
            if (i == keyPress)
            {
                DrawText("Settings", menuX, menuY + 40*i, 40, GOLD);
            }
        }
        else
        {
            DrawText(titles[i], menuX, menuY + 40*i, 40, LIGHTGRAY);
            if (i == keyPress)
            {
                DrawText(titles[i], menuX, menuY + 40*i, 40, GOLD);
            }

        }
    }

    DrawHighScores(menuX, menuY, keyPress);

    if(transition == true)
    {
        DrawCircle(640, 360, cycles * 15, BLACK);
        if(15 * cycles >= 800 && activeScene == 0)
        {
            
            activeScene = 1;
            transition = false;
            //?musik
            switch (m.selected)
            {
            case 0:
                PlaySong("assets/music/140kph.ogg", bm, "assets/beatmaps/bm140.csv");                
                break;
            case 1:
                song.SongError();
                
                break;
            case 2:
                song.SongError();
                
                break;
            case 3:
                song.SongError();
                
                break;
            case 4:
                song.SongError();
                break;
            case 5:
                DrawSettings(m.selected);
                break;

            default:
                song.SongError();
                
            }
            
        }
    }

    //Rita FPS och avsluta ritande

    DrawFPS(10, 10);

    EndDrawing();
}


void DrawResults()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(frame, 0, 0, WHITE);
    DrawText("Results:", 32, 100, 64, BLACK);

    DrawText(TextFormat("Highest combo: %d notes", cs.highestCombo), 32, 210, 32, BLACK);
    DrawText(TextFormat("Early: %d%%", (int)floor((float)cs.earlyHit/(float)bm.lt.size() * 100)), 32, 250, 32, BLACK);
    DrawText(TextFormat("Perfect: %d%%", (int)floor((float)cs.perfectHit/(float)bm.lt.size() * 100)), 32, 290, 32, BLACK);
    DrawText(TextFormat("Late: %d%%", (int)floor((float)cs.lateHit/(float)bm.lt.size() * 100)), 32, 330, 32, BLACK);
    DrawText(TextFormat("Missed: %d%%", (int)floor((float)cs.notesMissed/(float)bm.lt.size() * 100)), 32, 370, 32, BLACK);
    DrawText(TextFormat("Score: %d", cs.currentScore), 32, 480, 32, BLACK);

    DrawTexturePro(grades,{0, cs.finalGrade * 256.0f, 256, 256},{500,104,512,512},{0,0},0.0f,WHITE);

    EndDrawing();
}

void DrawFail()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexturePro(failTexture, {0,0,1920,1080}, {0,0,1280,720}, {0,0}, 0.0f, WHITE);
    DrawText("Game Over...", 650, 600, 96, WHITE);

    EndDrawing();
}


int main()
{
    //bredden och höjden på skärmen
    const int screenWidth = 1280;
    const int screenHeight = 720;
    
    //öppna ett nytt fönster
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Rythm Rally");
    InitAudioDevice();
    SetTargetFPS(60);

    //skapa en ny kamera
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 6.44f, -6.1f};
    camera.target = (Vector3){0.0f, 2.0f, 1.0f};
    camera.up = (Vector3){0.0f, 0.69f, 0.15f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    

    Player playerObject; //skapa spelaren
    Scenery sceneryObject = Scenery(1);
    std::vector<Note> noteObjects = {};
    std::vector<HitText> hitObjects = {}; //lista över alla dekorationsobjekt

    loadAssets();

    //huvudloop
    while (!WindowShouldClose())
    {
        cycles += 1;
        
        if(activeScene == 0 || activeScene == 4)
        {

            switch (GetKeyPressed()) //för att man ska kunna välja i menyn
            {
            case 49: //betyder tangent 1, går att se med mus-hover
                m.selected = 0; //låtnr eller delay
                break;
            case 50: 
                m.selected = 1; //låtnr eller musikvolym
                break;
            case 51: 
                m.selected = 2; //låtnr eller tire screech-volym
                break;
            case 52: 
                m.selected = 3; //låtnr eller QEsound-volym
                break;
            case 53: 
                m.selected = 4; //låtnr eller återställ
                break;
            case 54: 
                m.selected = 5; //låtnr eller spara och gå tillbaka
                break;
            case 55: 
                m.selected = 6; //låtnr eller spara inte men gå tillbaka
                break;
            case 265: //keycode up
                m.selected--;
                if (m.selected < 0 && activeScene == 0)
                {
                    m.selected = 5;
                }
                else if(m.selected < 0 && activeScene == 4)
                {
                    m.selected = 6;
                }
                break;
            case 264: //keycode down
                m.selected++;
                if (m.selected > 6 && activeScene == 4)
                {
                    m.selected = 0;
                    break;
                }
                else if(m.selected > 5 && activeScene == 0)
                {
                    m.selected = 0;
                }
                break;
            default:
                if(activeScene == 4)
                {
                    DrawSettings(m.selected);
                    break;
                }
                drawMenu(m.selected);
                break;
            }

            if(IsKeyDown(KEY_LEFT))
            {
                bm.s.ChangeSetting(-1, m);
            }
            else if(IsKeyDown(KEY_RIGHT))
            {
                bm.s.ChangeSetting(1, m);
            }

            if(IsKeyPressed(KEY_ENTER))
            {
                
                if(activeScene == 0)
                {    
                    if (m.selected == 5)
                    {
                        activeScene = 4; //om settings valt och enter tryckt
                    }
                    else if (transition == false)
                    {
                        transition = true;
                        cycles = 0;
                    }                
                }
                else if(activeScene == 4)
                {
                    switch (m.selected)
                    {
                    case 4: //reset and exit
                        m.selected = 5;
                        activeScene = 0;
                        cycles = 0;
                        bm.s.Resettings();
                        
                        break;
                    case 5: //exit save
                        m.selected = 5;
                        activeScene = 0;
                        cycles = 0;
                        bm.s.SaveSettings();                    

                        break;
                    case 6:
                        m.selected = 5;
                        activeScene = 0; //yes exit no save
                        cycles = 0;
                        break;         
                    default:
                        m.selected = 5;
                        activeScene = 4;
                        break;
                    }                
                    //std::cout << m.selected << std::endl;
                }

                
            }
        }
        else if(activeScene == 1)
        {
            //har spelaren tryckt på en knapp? Flytta och animera om spelaren gjorde det
            bool playerPressedHit = playerObject.playerInput(moveSound); 
            
            //flytta varje dekoration och kontrollera om den fortfarande behövs
            sceneryObject.moveScenery();
            if(sceneryObject.outOfBounds == true && GetRandomValue(0,3) == 2)
            {
                sceneryObject = Scenery(GetRandomValue(0,1));
            }
            
            for (int i = (int)noteObjects.size() - 1; i >= 0; i--)
            {
                Note& nt = noteObjects[i];
                if(nt.moveNote() == true)
                {
                    hitObjects.push_back(HitText(3));
                    std::cout << "Miss" << std::endl;
                    cs.notesInARow = 0;
                    cs.notesMissed += 1;
                    if(cs.scoreAndFailrate(0, 2) == true)
                    {
                        activeScene = 3;
                    }
                }
                else if(playerPressedHit == true)
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
                            hitObjects.push_back(HitText(0));
                            std::cout << "EARLY" << std::endl;
                            nt.outOfBounds = true;
                            cs.earlyHit += 1;
                            cs.notesInARow += 1;
                            cs.setCombo();
                            cs.scoreAndFailrate(25, -1);
                        }
                        else if(nt.notePosition.y > -1.5f && nt.notePosition.y < -0.5f)//perfekt träf
                        {
                            hitObjects.push_back(HitText(1));
                            std::cout << "PERFEKT" << std::endl;
                            nt.outOfBounds = true;
                            cs.perfectHit += 1;
                            cs.notesInARow += 1;
                            cs.setCombo();
                            cs.scoreAndFailrate(50, -1);
                        }
                        else if(nt.notePosition.y > -2.0f && nt.notePosition.y < -1.5f) //sen träff
                        {
                            hitObjects.push_back(HitText(2));
                            std::cout << "LATE" << std::endl;
                            nt.outOfBounds = true;
                            cs.lateHit += 1;
                            cs.notesInARow += 1;
                            cs.setCombo();
                            cs.scoreAndFailrate(25, -1);
                        }
                    }
                }
                if(nt.outOfBounds == true)
                {
                    noteObjects.erase(noteObjects.begin() + i); //radera notobjekt från listan
                }
            }
            
            drawWorld(camera, playerObject, sceneryObject, noteObjects, hitObjects); //rita världen

            //?Musik
            UpdateMusicStream(music);   // Ser till att musiken fortsätter spela
            int laneToPlace = bm.ShouldPlaceNote(GetElapsed(songTimer));
            if((int)bm.lt.size() == cs.notesMissed + cs.earlyHit + cs.perfectHit + cs.lateHit)
            {

                float maxScore = bm.lt.size() * 50.0f;
                bm.s.SetAndSortHighScores(cs.currentScore, m.selected); //tar emot låt och score
                bm.s.SaveSettings();

                if(cs.currentScore/maxScore > 0.8f)
                {
                    cs.finalGrade = 5;
                }
                else if(cs.currentScore/maxScore > 0.67f)
                {
                    cs.finalGrade = 4;
                }
                else if(cs.currentScore/maxScore > 0.5f)
                {
                    cs.finalGrade = 3;
                }
                else if(cs.currentScore/maxScore > 0.33f)
                {
                    cs.finalGrade = 2;
                }
                else if(cs.currentScore/maxScore > 0.17f)
                {
                    cs.finalGrade = 1;
                }
                else
                {
                    cs.finalGrade = 0;
                }

                activeScene = 2;
            }
            if(laneToPlace != -1) //om tiden är inom en viss  marginal, sätt ut not
            {
                //?how it's done:
                
                noteObjects.push_back(Note(laneToPlace)); 
                std::cout << "actually placed note lmao imagine that" << std::endl;
            }
        }
        else if(activeScene == 2)
        {
            DrawResults();
        }
        else if(activeScene == 3)
        {
            DrawFail();
        }
        
        

    }

    unloadAssets();
    CloseWindow();
    
}

