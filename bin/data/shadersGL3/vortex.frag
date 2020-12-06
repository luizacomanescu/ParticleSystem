#version 150

uniform float radius;
uniform float u_time;
uniform vec2 u_resolution;
out vec4 fragColor;

void main(){
//  vec2 coord = (gl_FragCoord.xy - u_resolution) / radius;
//  vec3 color = vec3(0.0);
//  vec2 translate = vec2(-0.5, -0.5);
//  coord += translate;
//
//  for(int i = 0; i < 40; i++){
//    float radi = 0.4;
//    float rad = radians(360.0 / 40.0) * float(i);
//
//    color += 0.003 / length(coord + vec2(radi * cos(rad), radi * sin(rad)));
//  }
//
//    fragColor = vec4(color, 1.0);
    
    vec2 coord = (gl_FragCoord.xy - u_resolution) / radius;
    float color = 0.0;

    color +=abs(sin(u_time)) / length(coord);

    fragColor = vec4(vec3(color), 1.0);
}
