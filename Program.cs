using Raylib_cs;

namespace RythmRally;

class Program
{
    public static void Main()
    {
        Raylib.InitWindow(800, 480, "Hello World");

        while (!Raylib.WindowShouldClose())
        {
            Player.HelloWorld();
        }

        Raylib.CloseWindow();
    }
}