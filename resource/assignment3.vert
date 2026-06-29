#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec2 vertexUV;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPosition;
out vec3 fragNormal;
out vec3 fragColor;
out vec2 fragUV;
out vec3 viewDirection;

void main() {
    vec4 worldPosition = modelMatrix * vec4(vertexPosition, 1.0);
    fragPosition = worldPosition.xyz;
    fragNormal = normalize(mat3(transpose(inverse(modelMatrix))) * vertexNormal);
    fragColor = vertexColor;
    fragUV = vertexUV;
    viewDirection = normalize(-vec3(viewMatrix * worldPosition));
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}
