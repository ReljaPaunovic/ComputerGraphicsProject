out vec3 coordinates;

void main() {
    coordinates = gl_Vertex.xyz;
    gl_Position = ftransform();
}