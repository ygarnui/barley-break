uniform mat4 ModelViewMatrix;
uniform mat4 ModelViewProjMatrix;

attribute vec4 vPosition;
attribute vec3 vNormal;
attribute vec2 vTex;

varying vec3 Normal;
varying vec3 Pos;
varying vec2 TexCoord;

void main(void)
{
    TexCoord = vTex;
    Normal = normalize((ModelViewMatrix * vec4(vNormal, 0.0)).xyz);
    Pos = (ModelViewMatrix * vPosition).xyz;
    gl_Position = ModelViewProjMatrix * vec4(vPosition.xyz, 1.0);
}
