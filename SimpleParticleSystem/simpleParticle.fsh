
in float opacity;
uniform sampler2D tex; // optional. enable point-sprite coords to use
out vec4 outFragColor;

const vec3 particleColor = vec3(1, 0, 0);

void main () {
    // using point texture coordinates which are pre-defined over the point
    vec2 texcoord = vec2 (gl_PointCoord.s, 1.0 - gl_PointCoord.t);
    vec4 texel = texture (tex, texcoord);
    outFragColor = vec4(particleColor, opacity);
}