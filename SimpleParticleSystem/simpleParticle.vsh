
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inVelocity;
layout (location = 2) in float inStartTime;
layout (location = 3) in float inOpacity;

uniform mat4 uViewMatrix, uProjectionMatrix;

// the fragment shader can use this for it's output colour's alpha component
out float vOpacity;
out vec3 vPosition_eye;
out mat4 vViewMatrix;

void main() {
    vOpacity = inOpacity;
    vPosition_eye = vec3(uViewMatrix * vec4 (inPosition, 1.0)).xyz;
    vViewMatrix = uViewMatrix;
    gl_Position = uProjectionMatrix * uViewMatrix * vec4 (inPosition, 1.0);
    gl_PointSize = 10.0; // size in pixels
}