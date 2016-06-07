uniform sampler2D tex;

uniform vec2 playerPosition;
uniform float time;

float viewDistance = 300.0;

void main() {
    /*vec4 originalColor = vec4(0,0,0,0);
	for(float x = 0.0; x <= 10.0/800.0; x=x+1.0/800.0) {
		for(float y = 0.0; y <= 10.0/800.0; y=y+1.0/800.0) {
			originalColor=originalColor+texture2D(tex,gl_TexCoord[0].xy+vec2(x,y));
		}	
	}	
    gl_FragColor = originalColor/100;*/

    // Show light around player
    float d = distance(gl_FragCoord.xy, playerPosition);
    d /= max(1.0, viewDistance - time * 10.0);
    d = 1.0 - d;

    vec4 multiplier = vec4(d, d, d, 1.0);
    gl_FragColor = multiplier * texture2D(tex, gl_TexCoord[0].xy);
}


