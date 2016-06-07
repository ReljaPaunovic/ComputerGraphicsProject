uniform sampler2D tex;

uniform vec2 playerPosition;
uniform float time;

float viewDistance = 300.0;

void main() {
	int[] counts = new int[];
	double[] averageR = new double[10];
	double[] averageG = new double[10];
	double[] averageB = new double[10];
    /*vec4 originalColor = vec4(0,0,0,0);
	for(float x = 0.0; x <= 10.0/800.0; x=x+1.0/800.0) {
		for(float y = 0.0; y <= 10.0/800.0; y=y+1.0/800.0) {
			float r=texture2D(tex,tex,gl_TexCoord[0].xy+vec2(x,y)).r;
			float g=texture2D(tex,tex,gl_TexCoord[0].xy+vec2(x,y)).g;
			float b=texture2D(tex,tex,gl_TexCoord[0].xy+vec2(x,y)).b;
			int ind=(int)(r+g+b*3.33);
			averageR[ind]=averageR[ind]+r;
			averageB[ind]=averageB[ind]+g;
			averageG[ind]=averageG[ind]+b;
			counts[ind]++;
		}	
	}	
	int max=0;
	for(int i=0;i<10;i++){
		if(max<counts[i])
			max=counts[i];
	}

    gl_FragColor = originalColor/100;*/

    // Show light around player
    float d = distance(gl_FragCoord.xy, playerPosition);
    d /= max(1.0, viewDistance - time * 10.0);
    d = 1.0 - d;

    vec4 multiplier = vec4(d, d, d, 1.0);
    gl_FragColor = multiplier * texture2D(tex, gl_TexCoord[0].xy);
}


