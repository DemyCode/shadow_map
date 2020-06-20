#version 450

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 OutColor;
in vec4 FragPosLightSpace;

uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalc(float dotlightnormal)
{
    vec3 pos = FragPosLightSpace.xyz * 0.5 + 0.5;
    if (pos.z > 1.0)
    {
        pos.z = 1.0;
    }
    float bias = max(0.5 * (1.0 - dotlightnormal), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float depth = texture(shadowMap, pos.xy + vec2(x, y) * texelSize).r;
            shadow += (depth + bias) < pos.z ? 0.0 : 1.0;
        }
    }
    return shadow / 9.0;
}

void main()
{
    vec3 color = OutColor;
    vec3 normal = normalize(Normal);
    vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = 0.3 * color;
    // diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    float dotlightnormal = dot(lightDir, normal);
    float diff = max(dotlightnormal, 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;
    // calculate shadow
    float shadow = ShadowCalc(dotlightnormal);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

    FragColor = vec4(lighting, 1.0);
}