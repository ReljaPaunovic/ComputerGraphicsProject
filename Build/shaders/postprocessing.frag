#version 120

uniform sampler2D tex;

uniform vec2 playerPosition;
uniform float time;

uniform float cameraX;
uniform float cameraY;

uniform float screenWidth;
uniform float screenHeight;

void main() {
    float absWaterHeight = 650.0;
    float waterHeight = screenHeight - (absWaterHeight - cameraY);

    if (gl_FragCoord.y > waterHeight) {
        gl_FragColor = texture2D(tex, gl_TexCoord[0].xy);
    } else {
        vec2 reflectCoords = gl_TexCoord[0].xy;
        reflectCoords.y = (waterHeight + (waterHeight - reflectCoords.y * screenHeight)) / screenHeight;

        reflectCoords.x += sin(time * 12.0 + gl_FragCoord.y / 3.0) / 100.0;

        vec3 color = texture2D(tex, reflectCoords).xyz;
        color.b *= 1.15;

        gl_FragColor = vec4(0.8 * color, 1.0);
    }
}