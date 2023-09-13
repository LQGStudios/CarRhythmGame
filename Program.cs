using Raylib_cs;
using System.Numerics;

namespace RythmRally;

class Program
{

    const int screenWidth = 1280;
    const int screenHeight = 720;
    
    private static void drawEverything(Camera3D cam, Player plObj)
    {
        Raylib.BeginDrawing();
        Raylib.ClearBackground(Color.RAYWHITE);
        Raylib.BeginMode3D(cam);
        plObj.drawPlayer();


        Raylib.DrawPlane(new Vector3(0.0f,-0.5f,0.0f), new Vector2(10.0f, 10.0f), Color.GREEN);

        //Rita FPS och avsluta ritande
        Raylib.EndMode3D();

        Raylib.DrawFPS(10, 10);

        Raylib.EndDrawing();
    }

    public static void Main()
    {

        Raylib.InitWindow(screenWidth, screenHeight, "Rythm Rally");
        Raylib.SetTargetFPS(60);

        Camera3D camera = new Camera3D
        {
            position = new Vector3(0.0f, 6.44f, -6.1f),
            target = new Vector3(0.0f, 0.0f, 0.0f),
            up = new Vector3(0.0f, 0.69f, 0.15f),
            fovy = 60.0f,
            projection = CameraProjection.CAMERA_PERSPECTIVE
        };

        Player playerObject = new Player();

        while (!Raylib.WindowShouldClose())
        {
            playerObject.playerInput();
            drawEverything(camera, playerObject);

        }

        Raylib.CloseWindow();
    }
}