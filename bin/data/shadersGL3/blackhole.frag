#version 150

uniform float u_time;
uniform float radius;
uniform vec2 u_resolution;

out vec4 fragColor;

void main(){
    vec2 coord = (gl_FragCoord.xy - u_resolution) / radius;
    float color = 0.0;

    color += 0.1 * (abs(sin(u_time)) + 0.1) / length(coord);

    fragColor = vec4(vec3(color), 1.0);
}
