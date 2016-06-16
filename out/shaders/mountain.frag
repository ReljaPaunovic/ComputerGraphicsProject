varying vec3 coordinates;
varying vec3 normal;
varying mat4 modelView;

uniform sampler2D texRock;
uniform sampler2D texSnow;
uniform sampler2D texRockGrass;

uniform mat4 shadowMapProjection;
uniform sampler2DShadow texShadowMap;

float shadowBias = 0.01;
float ambientLight = 0.5;

void main() {
    // Get coordinates in light view in texture space
    vec4 shadowCoords = shadowMapProjection * modelView * vec4(coordinates, 1.0);
    shadowCoords.x = shadowCoords.x / 2.0 + 0.5;
    shadowCoords.y = shadowCoords.y / 2.0 + 0.5;
    shadowCoords.z = shadowCoords.z / shadowCoords.w;

    // No shadow if the fragment is not in view of the light
    float shadowFactor;
    if (shadowCoords.x < 0 || shadowCoords.x > 1 || shadowCoords.y < 0 || shadowCoords.y > 1) {
        shadowFactor = 1.0;
    } else {
        shadowFactor = texture(texShadowMap, vec3(shadowCoords.xy, shadowCoords.z / 2.0 + 0.5 - shadowBias)).r;
    }

    // Determine texture and diffuse lighting
    vec3 lightDir = normalize(vec3(1, 1, 1));
    float diffuse = dot(normal, lightDir) * (1.0 - gl_FragCoord.z + 0.5);

    float relHeight = (coordinates.y + 1.1) / 1.2;
    relHeight = pow(relHeight, 6.0);
    relHeight = min(relHeight, 1);

    vec3 grassColor = 0.5 * texture2D(texRockGrass, gl_TexCoord[0].xy * 4.0).xyz;
    vec3 rockColor = 0.5 * texture2D(texRock, gl_TexCoord[0].xy * 4.0).xyz;
    vec3 snowColor = 1.2 * texture2D(texSnow, gl_TexCoord[0].xy * 8.0).xyz;

    if (relHeight > 0.5) {
        gl_FragColor = vec4(shadowFactor * diffuse * mix(rockColor, snowColor, (relHeight - 0.5) * 2.0), 1.0);
    } else {
        gl_FragColor = vec4(shadowFactor * diffuse * mix(grassColor, rockColor, relHeight * 2.0), 1.0);
    }
}
