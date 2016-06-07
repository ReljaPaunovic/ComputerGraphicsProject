#version 120

uniform sampler2D tex;

uniform vec2 playerPosition;
uniform float time;

float viewDistance = 300.0;

void main() {
    gl_FragColor = texture2D(tex, gl_TexCoord[0].xy);
}


