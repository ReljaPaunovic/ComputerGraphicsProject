uniform sampler2D tex;

uniform vec2 playerPosition;
uniform float time;

float viewDistance = 300.0;

void main() {

	float averageR[5] =  float[5](0,0,0,0,0);
	float averageG[5] =  float[5](0,0,0,0,0);
	float averageB[5] =  float[5](0,0,0,0,0);
	int counts[5] =  int[5](0,0,0,0,0);
    /*vec4 originalColor = vec4(0,0,0,0);
	for(float x = 0.0; x <= 10.0/800.0; x=x+1.0/800.0) {
		for(float y = 0.0; y <= 10.0/800.0; y=y+1.0/800.0) {
			float r=(tex,gl_TexCoord[0].xy+vec2(x,y).r);
			float g=(tex,gl_TexCoord[0].xy+vec2(x,y).g);
			float b=(tex,gl_TexCoord[0].xy+vec2(x,y).b);
			int ind=(int)((r+g+b)*1.66667);
			averageR[ind]+=r;
			averageB[ind]+=g;
			averageG[ind]+=b;
			counts[ind]++;
		}	
	}	
	int max=0;
	for(int i=0;i<5;i++){
		if(max<counts[i]){
			max=counts[i];
		}
	}
	
    gl_FragColor = vec4(averageR,averageG,averageB,1);
}


