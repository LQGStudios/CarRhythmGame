#version 330
in vec2 fragTexCoord;

uniform sampler2D Texture0;

/// Updated in external code
uniform float uTime;

out vec4 out_FragColor;

void main()
{
   out_FragColor = texture( Texture0, vec2(fragTexCoord.x, fragTexCoord.y + uTime) );
}