uniform sampler2D tex;

uniform vec2 playerPosition;
uniform float time;

uniform float explosionRange;
uniform vec2 explosionPos;

uniform float shockwaveRange;
uniform float shockwaveDistance;

uniform float cameraX;
uniform float cameraY;

vec2 getShockwaveCoords(vec2 finalPos, float dist) {
    dist = abs(dist - shockwaveDistance);

    if (dist < shockwaveRange) {
        float t = time * gl_TexCoord[0].x * 5.0 + dist;
        vec2 maxOffset = vec2(sin(t) * 10.0 / 800.0, sin(t) * 10.0 / 600.0);
        vec2 actualOffet = mix(maxOffset, vec2(0.0, 0.0), dist / shockwaveRange);

        return gl_TexCoord[0].xy + actualOffet;
    } else {
        return gl_TexCoord[0].xy;
    }
}

void main() {
    vec2 finalPos = explosionPos - vec2(cameraX, cameraY);
    finalPos.y = 600.0 - finalPos.y;

    float dist = distance(gl_FragCoord.xy, finalPos);

    // First process shockwave to get sampling coordinates
    vec2 coords = getShockwaveCoords(finalPos, dist);
    vec3 baseColor = texture2D(tex, coords).xyz;

    // Secondly process brightness from explosion
    vec3 explodeColor = baseColor * 5.0;
    explodeColor.r *= 1.1;
    explodeColor.g *= 1.1;

    vec3 finalColor = mix(explodeColor, baseColor, min(1.0, dist / explosionRange));

    gl_FragColor = vec4(finalColor, 1.0);
}