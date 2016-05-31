#include "Background.h"
#include <iostream>
#include <math.h>

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


float mulDelSmoothNoise1D(float x){
	return (((smoothNoise1D(x)+smoothNoise1D(0.6*(x-2))*0.6+smoothNoise1D(3.1*x-4)/8+smoothNoise1D(16.3*x)/8)+smoothNoise1D(x-14.3)+smoothNoise1D(4*x)*0.15+smoothNoise1D(x/16)*3)/7);

}



const int screenWidth=800;

const int screenheight=800;
void Background::layer1(int viewx,float freq1,float maxL1Height,float red,float green, float blue ,float xoff){

	double h1=mulDelSmoothNoise1D(((float)(-1+viewx+xoff)*freq1));	
	h1=(h1*h1)/h1;
	h1=h1*maxL1Height;
	h1=screenheight-h1-(screenWidth-maxL1Height);
	for(int x=0;x<screenWidth-1;x++){
		double h2=mulDelSmoothNoise1D((((float)(viewx+x+xoff))*freq1));	
		h2=(h2*h2)/h2;
		h2=h2*maxL1Height;
		h2=screenheight-h2-(screenWidth-maxL1Height);
		glBegin(GL_QUADS);

			glColor3f(red, green, blue);
			glVertex2f(x, h2);
			glVertex2f(x, screenheight);
			glVertex2f(x-1, screenheight);
			glVertex2f(x-1, h1);
		glEnd();
		h1=h2;
	}



}
void Background::render(int viewx){
	layer1(viewx,0.0084,200,0.15,0.07,0.03,300);
	layer1(viewx,0.014,300,0.3,0.15,0.07,0.16);
	layer1(viewx,0.01,200,0.6,0.3,0.15,400);


}


Background::Background()
{
}


Background::~Background()
{
}






