in vec3 coordinates;
in vec3 normal;

float simpleNoise1D(float x){
    return fract(sin(dot(vec2(float( x), float(x)) ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    // gl_FragColor = vec4(height, 0.0, 0.0, 1.0);
    // vec3 lightDir = normalize(vec3(1, 1, 1));
    // float lightness = dot(normal, lightDir);
    // gl_FragColor = vec4(lightness, 0.0, 0.0, 1.0);
    gl_FragColor = vec4(gl_FragCoord.z, 0.0, 0.0, 1.0);
}
