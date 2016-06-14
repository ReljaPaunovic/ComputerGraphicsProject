
in vec3 incoordinates;
out vec3 coordinates;
out vec3 normal;
uniform float cameraX;
float sCurve( float x )
{
	return x*x*(3.0-2.0*x);
}
float lerp1( float x, float a, float b )
{
	return a + x*( b - a );
} 

float simpleNoise1D(int x){
    return fract(sin(dot(vec2(float( x), float(x)) ,vec2(12.9898,78.233))) * 43758.5453);
}

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
	return (smoothNoise1D(x*5)+smoothNoise1D(y*5-213.2))*10;
}

vec3 transformPos(vec3 pos) {
	return vec3(
		pos.x,
		// sin((pos.x*pos.x*pos.x+pos.z*pos.z*pos.z) * 50.0) / 2 + 0.5,
		f2Dnoise((pos.x + cameraX / 800.0 / (1.0 - pos.z)) / 4.0, pos.z / 4.0) / 30.0,
		pos.z
	);
}

vec3 calculateNormal(vec3 p1) {
	vec3 p2 = transformPos(p1 + vec3(0.01, 0.0, 0.0));
	vec3 p3 = transformPos(p1 + vec3(0.0, 0.0, 0.01));

	return normalize(cross(p2 - p1, p3 - p1));
}

void main() {
	// vec3 pos = transformPos(gl_Vertex.xyz);
 //    coordinates = pos;

 //    normal = calculateNormal(gl_Vertex.xyz);

 //    gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);
 gl_Position = ftransform();
}
