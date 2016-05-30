#include "Background.h"
#include <iostream>


float sCurve( float x )
{
	return x*x*(3-2*x);
}

float lerp1( float x, float a, float b )
{
return a + x*( b - a );
} 

float simpleNoise1D( int x )
{
x = (x<<13) ^ x;
return ( 1.0 - ( (x * (x * x * 11432 + 582251) + 1126513539) &0x8fffffff) /1073741824.0);
}

float smoothNoise1D( float x )
{
float xs ;
int xi ; 
float l0, l1 ; 
float xf ; 

xi = (int)x;
xf = x - (float)xi;
xs = sCurve(xf);
l0 = simpleNoise1D( xi );
l1 = simpleNoise1D( xi+1 );
return lerp1( xf, l0, xs ); 
}




const int screenWidth=800;
const int maxL1Height=500;
const int screenheight=800;
const double freq1=0.01;
void Background::layer1(int viewx){
	
	double h1=smoothNoise1D(((float)(-1+viewx)*freq1));	
	h1=(h1*h1)/h1;
	h1=h1*maxL1Height;
	h1=screenheight-h1;
	for(int x=0;x<screenWidth-1;x++){
		double h2=smoothNoise1D((((float)(viewx+x))*freq1));	
		h2=(h2*h2)/h2;
		h2=h2*maxL1Height;
		
		glBegin(GL_QUADS);

			glColor3f(0.2f, 0.3f, 0.2f);
			glVertex2f(x, h2);
			glVertex2f(x, screenheight);
			glVertex2f(x-1, screenheight);
			glVertex2f(x-1, h1);
		glEnd();
		h1=h2;
	}



}
void Background::render(int viewx){
	layer1(viewx);

}


Background::Background()
{
}


Background::~Background()
{
}






