
in float vOpacity;
in vec3 vPosition_eye;
in mat4 vViewMatrix;
uniform sampler2D tex; // optional. enable point-sprite coords to use
out vec4 outFragColor;

uniform vec3 uLightPositionWorld;

// fixed point light properties
vec3 light_position_world = vec3 (0.0, 10.0, 10.0); // use this if you can't be arsed with the uniform
vec3 Ls = vec3 (1.0, 1.0, 1.0); // white specular colour
vec3 Ld = vec3 (0.0, 0.5, 1.0); // dull white diffuse light colour
vec3 La = vec3 (0.1, 0.1, 0.1); // grey ambient colour

// surface reflectance
vec3 Ks = vec3 (0.5, 0.5, 0.5); // fully reflect specular light
vec3 Kd = vec3 (0.5, 0.5, 0.5); // orange diffuse surface reflectance
vec3 Ka = vec3 (1.0, 1.0, 1.0); // fully reflect ambient light
float specular_exponent = 0.01f; // specular 'power'

float light_power = 250;

void main () {
    // using point texture coordinates which are pre-defined over the point
    vec2 texcoord = vec2 (gl_PointCoord.s, 1.0 - gl_PointCoord.t);
    vec2 normalcoord = vec2(gl_PointCoord.s, gl_PointCoord.y) * 2.0 - 1.0;
    
    vec3 normal_eye = vec3(vViewMatrix * vec4(normalcoord, 1, 0)).xyz;
    
    vec3 EyeDirection_eye = vec3(0,0,0) - vPosition_eye;
    vec3 light_position_eye = vec3(vViewMatrix * vec4(light_position_world, 1.0)).xyz;
    vec3 light_direction_eye = light_position_eye + EyeDirection_eye;
    vec3 light_distance_eye = light_position_eye.xyz - vPosition_eye.xyz;
    float LD = dot(light_distance_eye, light_distance_eye);
    vec3 n = normalize(normal_eye);
    vec3 l = normalize(light_direction_eye);
    float dot_prod = dot (n, l);
    dot_prod = max (dot_prod, 0.0);
    vec3 Id = Ld * Kd * dot_prod * light_power / LD; // final diffuse intensity
    
    // ambient intensity
    vec3 Ia = La * Kd * Ka * light_power * dot_prod / LD;
    
    vec3 E = normalize(EyeDirection_eye);
    vec3 R = reflect(-l, n);
    float cosAlpha = max(dot(E,R), 0);
    vec3 Is = Ls * Ks * light_power * pow(cosAlpha, 5) / LD; // final specular intensity
    
    // final colour
    outFragColor = texture(tex, texcoord) * vec4(Is + Id + Ia, 1);
    outFragColor.a = vOpacity;
}