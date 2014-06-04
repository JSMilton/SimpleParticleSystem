
in float opacity;
uniform sampler2D tex; // optional. enable point-sprite coords to use
out vec4 outFragColor;

const vec4 particleColor = vec4 (0.5, 0.5, 0.8, 0.8);

void main () {
    // using point texture coordinates which are pre-defined over the point
    vec2 texcoord = vec2 (gl_PointCoord.s, 1.0 - gl_PointCoord.t);
    vec4 texel = texture (tex, texcoord);
    outFragColor.a = opacity * texel.a;
    outFragColor.rgb = particleColor.rgb * texel.rgb;
}