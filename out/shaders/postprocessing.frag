uniform sampler2D tex;

void main() {
    vec4 originalColor = texture2D(tex, gl_TexCoord[0].xy);

    gl_FragColor = originalColor;
}