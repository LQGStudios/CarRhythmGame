using Raylib_cs;
using System.Numerics;

namespace RythmRally;

public partial class Player
{

    public float playerXPosition = 0.0f;
    private float animationProgress = 0.0f;
    private int animationDirection = 1;

    private Model playerModel = Raylib.LoadModel("assets/cube.obj");
    public void drawPlayer()
    {   
        
        float angle = 0;

        //multiplicera vinkeln med pi/180 för att omvandla till radianer, 0.0174532925 == pi/180
        playerModel.transform = Raymath.MatrixRotateXYZ(new Vector3(0f, 0.0174532925f * angle, 0f)); 
        Raylib.DrawModel(playerModel, new Vector3(playerXPosition, 0.0f, -1.0f), 1.0f, Color.WHITE);
        Raylib.DrawCubeWires(new Vector3(playerXPosition, 0.0f, -1.0f), 1.0f, 1.0f, 2.0f, Color.BLACK);
    }

    public void playerInput()
    {
        if(Raylib.IsKeyPressed(KeyboardKey.KEY_RIGHT) && playerXPosition > -3.0f)
        {
            playerXPosition -= 1.5f;
        }
        else if(Raylib.IsKeyPressed(KeyboardKey.KEY_LEFT) && playerXPosition < 3.0f)
        {
            playerXPosition += 1.5f;
        }
    }
}