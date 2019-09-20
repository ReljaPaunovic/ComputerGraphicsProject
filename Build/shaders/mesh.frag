varying vec3 normal;

uniform sampler2D tex;
uniform sampler2D texNormal;

uniform bool enableNormalMapping;

mat4 calculateNormalRotation() {
    // rotation from (0, 0, 1) to normal
    vec3 a = vec3(0, 0, 1);
    vec3 b = normal;

    vec3 v = cross(a, b);
    float s = length(v);
    float c = dot(a, b);

    mat3 vskew = mat3(vec3(0, v.z, -v.y), vec3(-v.z, 0, v.x), vec3(v.y, -v.x, 0));

    mat3 R = mat3(1.0) + vskew + vskew * vskew * (1 - c) / (s * s);

    return mat4(R);
}

void main() {
    vec3 actualNormal = normal;
    if (enableNormalMapping) {
        vec3 bumpNormal = 2 * texture(texNormal, gl_TexCoord[0].xy).xyz - vec3(1.0, 1.0, 1.0);
        actualNormal = (calculateNormalRotation() * vec4(bumpNormal, 1)).xyz;
    }

    vec3 lightDir = normalize(vec3(1, 1, 1));
    float diffuse = dot(actualNormal, lightDir);
	
    gl_FragColor = vec4(diffuse * texture(tex, gl_TexCoord[0].xy).xyz, 1.0);
}
