using Raylib_cs;

namespace RythmRally;

public partial class Player
{
    public static void HelloWorld()
    {
        
        Raylib.BeginDrawing();
        Raylib.ClearBackground(Color.WHITE);

        Raylib.DrawText("Hello, world!", 12, 12, 20, Color.BLACK);

        Raylib.EndDrawing();
    }
}