
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inVelocity;
layout (location = 2) in float inStartTime;
layout (location = 3) in float inOpacity;

uniform vec3 uEmitterPosition; // emitter position in world coordinates
uniform float uElapsedTime; // system time in seconds

// the fragment shader can use this for it's output colour's alpha component
out vec3 outPosition;
out vec3 outVelocity;
out float outStartTime;
out float outOpacity;

void main() {
    // work out the elapsed time for _this particle_ after its start time
    float t = uElapsedTime - inStartTime;
    // allow time to loop around so particle emitter keeps going
    t = mod (t, 3.0);
    vec3 p;
//    if (inOpacity < 0.1){
//        p = uEmitterPosition;
//        outOpacity = 1.0;
//    } else {
        p = inPosition;
//    }

    // gravity
    vec3 a = vec3 (0.0, -1.0, 0.0);
    vec3 v = inVelocity;
    // this is a standard kinematics equation of motion with velocity and
    // acceleration (gravity)
    p += v * a;
    outPosition = p;
    outVelocity = v;
    outStartTime = inStartTime;
    // gradually make particle fade to invisible over 3 seconds
    outOpacity = inOpacity - 0.2;// 1.0 - ((t) / 3.0);
}
