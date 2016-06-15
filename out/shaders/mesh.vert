varying vec3 normal;

uniform bool enableSimplification;
uniform float simplifyGridSpacing;

float roundCoord(float c) {
    return round(c / simplifyGridSpacing) * simplifyGridSpacing;
}

void main() {
    gl_TexCoord[0] = gl_MultiTexCoord0;
    normal = normalize(gl_NormalMatrix * gl_Normal);

    vec4 pos = gl_Vertex;
    if (enableSimplification) {
        pos = vec4(roundCoord(pos.x), roundCoord(pos.y), roundCoord(pos.z), pos.w);
    }

    gl_Position = gl_ModelViewProjectionMatrix * pos;
}