uniform sampler2D tex2D;

uniform vec4 LightPos;
uniform vec4 LightColor;
uniform vec4 DiffuseMaterial;

//x: ambientFactor;
//y: shinessExponent;
//z: shinessFactor;
//w: gammaCorrection;
uniform vec4 ShadingParameters1;

varying vec3 Normal;
varying vec3 Pos;
varying vec2 TexCoord;

const float kOpaque = 0.0;
const float kFade = 1.0;
const float kTransparent = 2.0;
const float kCutout = 3.0;

void main(void)
{
    float ambientFactor = ShadingParameters1.x;
    float shinessExponent = ShadingParameters1.y;
    float shinessFactor = ShadingParameters1.z;
    float gammaCorrection = ShadingParameters1.w;

    vec3 normal = normalize(Normal);
    vec3 sight = normalize(Pos);

    vec4 texColor = texture2D(tex2D, TexCoord);
    vec4 diffuse = texColor * DiffuseMaterial;

    vec3 dirToLight;
    if (LightPos.w == 0.0)
    {
        dirToLight = LightPos.xyz;
    }
    else
    {
        dirToLight = normalize(LightPos.xyz - Pos);
    }

    float diffuseIntensity = clamp(dot(normal, dirToLight), 0.0, 1.0);
    float spec = 0.0;
    if (dot(sight, normal) < 0.0)
    {
        vec3 reflectView = reflect(sight, normal);
        spec = pow(max(dot(reflectView, dirToLight), 1e-6), shinessExponent) * shinessFactor;
    }

    vec3 albedo = LightColor.rgb * diffuse.rgb;

    vec3 diffusePart = vec3(diffuseIntensity * albedo);
    vec3 ambientPart = vec3((1.0 - diffuseIntensity) * ambientFactor * albedo);
    vec4 color = vec4(diffusePart + ambientPart, DiffuseMaterial.a);

    color.r = clamp(color.r, 0.0, 1.0);
    color.g = clamp(color.g, 0.0, 1.0);
    color.b = clamp(color.b, 0.0, 1.0);
    color.a = 1;

    gl_FragColor = pow(color, vec4(gammaCorrection, gammaCorrection, gammaCorrection, 1));

}
