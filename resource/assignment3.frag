#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec3 fragColor;
in vec2 fragUV;
in vec3 viewDirection;

uniform sampler2D textureSampler;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 objectColor;
uniform float shininess;
uniform bool useAmbient;
uniform bool useDiffuse;
uniform bool useSpecular;
uniform bool useHalfVector;
uniform bool useToon;
uniform bool useProceduralWood;
uniform bool useTexture;

out vec4 finalColor;

vec3 proceduralWoodColor(vec3 position) {
    float radius = length(position.xz);
    float bands = fract(radius * 5.0);
    vec3 wood1 = vec3(0.45, 0.24, 0.09);
    vec3 wood2 = vec3(0.66, 0.42, 0.19);
    return (bands < 0.5) ? wood1 : wood2;
}

void main() {
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightPosition - fragPosition);
    vec3 V = normalize(cameraPosition - fragPosition);
    vec3 baseColor = objectColor * fragColor;

    if (useTexture && !useToon && !useProceduralWood) {
        baseColor *= texture(textureSampler, fragUV).rgb;
    }
    if (useProceduralWood) {
        baseColor = proceduralWoodColor(fragPosition);
    }

    float ambientStrength = useAmbient ? 0.22 : 0.0;
    float diffuseStrength = useDiffuse ? max(dot(N, L), 0.0) : 0.0;

    float specularStrength = 0.0;
    if (useSpecular && diffuseStrength > 0.0) {
        if (useHalfVector) {
            vec3 H = normalize(L + V);
            specularStrength = pow(max(dot(N, H), 0.0), shininess);
        } else {
            vec3 R = reflect(-L, N);
            specularStrength = pow(max(dot(V, R), 0.0), shininess);
        }
    }

    if (useToon) {
        float intensity = max(dot(N, L), 0.0);
        float bands = 0.15;
        if (intensity > 0.80) bands = 1.0;
        else if (intensity > 0.55) bands = 0.75;
        else if (intensity > 0.30) bands = 0.45;
        float outline = dot(normalize(N), normalize(V));
        if (outline < 0.22) {
            finalColor = vec4(0.08, 0.08, 0.08, 1.0);
        } else {
            finalColor = vec4(baseColor * bands, 1.0);
        }
        return;
    }

    vec3 result = baseColor * ambientStrength + baseColor * diffuseStrength + vec3(1.0) * specularStrength;
    finalColor = vec4(result, 1.0);
}
