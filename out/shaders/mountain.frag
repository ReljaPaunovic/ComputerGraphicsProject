uniform int layer;
#extension GL_EXT_gpu_shader4 : enable
in vec3 coordinates;
/*
float sCurve( float x )
{
	return x*x*(3.0-2.0*x);
}
float lerp1( float x, float a, float b )
{
	return a + x*( b - a );
} 

float simpleNoise1D( int x )
{
x = (x<<13) ^ x;
return ( 1.0f - ( (x * (x * x * 11432.0 + 582251.0) + 1126513539.0) &0x8fffffff) /1073741824.0f);
}


float smoothNoise1D( float x )
{
float xs ;
int xi ; 
float l0, l1 ; 
float xf; 

	xi = (int)x;
	xf = x - (float)xi;
	xs = sCurve(xf);
	l0 = simpleNoise1D( xi );
	l1 = simpleNoise1D( xi+1 );
return lerp1( xf, l0, xs ); 
}
*/
void main() {
/*	vec3 color = vec3(0.4,0,2,0.1)
	float offset=0.0;
	if (layer == 1) {
		color=color/3;
		offset=124.2;
    } else {
		offset=932.4;
		color=color/3;
    }
	smoothNoise1D(offset+coordinates.x+coordinates.y);
*/
	

	
}
