
in vec3 incoordinates;
#extension GL_EXT_gpu_shader4 : enable
out vec3 coordinates;
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
return ( 1.0f - ( (x * (x * (x * 11532.0) + 582241.0) + 1126513539.0) /1073741824.0f));
}
asd

float smoothNoise1D( float x )
{
float xs ;
int xi ; 
float l0, l1 ; 
float xf; 

	xi = int(x);
	xf = x - float(xi);
	xs = sCurve(xf);
	l0 = simpleNoise1D( xi );
	l1 = simpleNoise1D( xi+1 );
return lerp1( xf, l0, xs ); 
}


float f2Dnoise(float x,float y){
	return smoothNoise1D(x/400)+smoothNoise1D((y-213.2)/400);
}

void main() {
	vec3 pos = gl_Vertex.xyz;
	pos.z=f2Dnoise(pos.x,pos.y);
    coordinates = pos;
    gl_Position = ftransform()
}
