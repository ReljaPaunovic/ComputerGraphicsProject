varying vec3 coordinates;
varying vec3 normal;

uniform sampler2D texRock;
uniform sampler2D texSnow;
uniform sampler2D texRockGrass;

float simpleNoise1D(float x){
    return fract(sin(dot(vec2(float( x), float(x)) ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    // gl_FragColor = vec4(height, 0.0, 0.0, 1.0);
    vec3 lightDir = normalize(vec3(1, 1, 1));
    float diffuse = dot(normal, lightDir);

    float relHeight = (coordinates.y + 0.4) / 0.7 * 1.2;
    relHeight = pow(relHeight, 6.0);
    relHeight = min(relHeight, 1);

    vec3 grassColor = 0.5 * texture2D(texRockGrass, gl_TexCoord[0].xy * 4.0).xyz;
    vec3 rockColor = 0.5 * texture2D(texRock, gl_TexCoord[0].xy * 4.0).xyz;
    vec3 snowColor = 1.2 * texture2D(texSnow, gl_TexCoord[0].xy * 8.0).xyz;

    if (relHeight > 0.5) {
        gl_FragColor = vec4(diffuse * mix(rockColor, snowColor, (relHeight - 0.5) * 2.0), 1.0);
    } else {
        gl_FragColor = vec4(diffuse * mix(grassColor, rockColor, relHeight * 2.0), 1.0);
    }
}
