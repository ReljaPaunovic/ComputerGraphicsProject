varying vec3 normal;

uniform sampler2D tex;

void main() {
    vec3 lightDir = normalize(vec3(1, 1, 1));
    float diffuse = dot(normal, lightDir) * (1.0 - gl_FragCoord.z + 0.5);

    gl_FragColor = vec4(diffuse * texture2D(tex, gl_TexCoord[0].xy).xyz, 1.0);
}