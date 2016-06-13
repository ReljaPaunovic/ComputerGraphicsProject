uniform int layer;

in vec3 coordinates;

void main() {
    if (layer == 0) {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    } else if (layer == 1) {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    } else {
        gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
    }
}