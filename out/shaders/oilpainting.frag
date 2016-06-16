#version 120

uniform sampler2D tex;

uniform vec2 playerPosition;
uniform float time;


float viewDistance = 300.0;
void main() {

	float averageR[5] =  float[5](0.0,0.0,0.0,0.0,0.0);
	float averageG[5] =  float[5](0.0,0.0,0.0,0.0,0.0);
	float averageB[5] =  float[5](0.0,0.0,0.0,0.0,0.0);
	int countss[5] =  int[5](0,0,0,0,0);
	int ind;
	vec4 c;
    vec4 originalColor = vec4(0,0,0,0);
	for(float x = 0.0; x <= 6/800.0; x=x+1.0/800.0) {
		for(float y = 0.0; y <= 6/800.0; y=y+1.0/800.0) {
			c = texture2D(tex,gl_TexCoord[0].xy+vec2(x,y));
			ind=int(((c.r+c.g+c.b)*1.66667));
			averageR[ind]=averageR[ind]+c.r;
			averageG[ind]=averageG[ind]+c.g;
			averageB[ind]=averageB[ind]+c.b;
			countss[ind]=countss[ind]+1;
		}	
	}	


	int max=0;
	int t=0;
	for(int i=0;i<5;i++){
		if(max<countss[i]){
			max=countss[i];
			t=i;
		}
	}

	float rr=averageR[t]/float(max);
	float rg=averageG[t]/float(max);
	float rb=averageB[t]/float(max);
    gl_FragColor = vec4(rr,rg,rb,1);

}
