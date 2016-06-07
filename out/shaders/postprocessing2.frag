uniform sampler2D tex;

uniform vec2 playerPosition;
uniform float time;

void main() {
    vec4 color = texture2D(tex, gl_TexCoord[0].xy);
    float avg = (color.r + color.g + color.b) / 3;
    gl_FragColor = vec4(avg, avg, avg, 1.0);
}