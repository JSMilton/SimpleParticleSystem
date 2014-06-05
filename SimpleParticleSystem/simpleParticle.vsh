
layout (location = 0) in vec3 vI; // initial velocity
layout (location = 1) in float startTime;

uniform mat4 uViewMatrix, uProjectionMatrix;
uniform vec3 uEmitterPosition; // emitter position in world coordinates
uniform float uElapsedTime; // system time in seconds

// the fragment shader can use this for it's output colour's alpha component
out float opacity;

void main() {
    // work out the elapsed time for _this particle_ after its start time
    float t = uElapsedTime - startTime;
    // allow time to loop around so particle emitter keeps going
    t = mod (t, 3.0);
    opacity = 0.0;
    
    vec3 p = uEmitterPosition;
    // gravity
    vec3 a = vec3 (0.0, -1.0, 0.0);
    // this is a standard kinematics equation of motion with velocity and
    // acceleration (gravity)
    p += vI * t + 0.5 * a * t * t;
    // gradually make particle fade to invisible over 3 seconds
    opacity = 1.0 - ((t*0.65) / 3.0);
    
    gl_Position = uProjectionMatrix * uViewMatrix * vec4 (p, 1.0);
    gl_PointSize = 5.0; // size in pixels
}