#include "Background.h"
#include <iostream>
#include <math.h>
#include <GL/glew.h>

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
return ( 1.0f - ( (x * (x * x * 11432 + 582251) + 1126513539) &0x8fffffff) /1073741824.0f);
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
	return (((smoothNoise1D(x)+smoothNoise1D(0.6f*(x-2))*0.6f+smoothNoise1D(3.1f*x-4)/8+smoothNoise1D(16.3f*x)/8)+smoothNoise1D(x-14.3f)+smoothNoise1D(4*x)*0.15f+smoothNoise1D(x/16)*3)/7);

}



const int screenWidth=800;

const int screenheight=800;
void Background::layer1(int viewx,float freq1,float maxL1Height,float red,float green, float blue ,float xoff){

	float h1=mulDelSmoothNoise1D(((float)(-1+viewx+xoff)*freq1));	
	h1=(h1*h1)/h1;
	h1=h1*maxL1Height;
	h1=screenheight-h1-(screenWidth-maxL1Height);
	for(int x=0;x<screenWidth-1;x++){
		float h2=mulDelSmoothNoise1D((((float)(viewx+x+xoff))*freq1));	
		h2=(h2*h2)/h2;
		h2=h2*maxL1Height;
		h2=screenheight-h2-(screenWidth-maxL1Height);
		glBegin(GL_QUADS);

			glColor3f(red, green, blue);
			glVertex2i(viewx+x, (int) h2);
			glVertex2i(viewx+x, screenheight);
			glVertex2i(viewx+x-1, screenheight);
			glVertex2i(viewx+x-1, (int) h1);
		glEnd();
		h1=h2;

	}



}
void Background::render(float viewx){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLint shader;
	glGetIntegerv(GL_CURRENT_PROGRAM, &shader);
	GLint uniLayer = glGetUniformLocation(shader, "layer");
	 
	glUniform1i(uniLayer, 0);
	layer1((int) viewx,0.0084f,200,0.15f,0.07f,0.03f,300);
	glUniform1i(uniLayer, 1);
	layer1((int) viewx,0.014f,300,0.3f,0.15f,0.07f,0.16f);
	glUniform1i(uniLayer, 2);
	layer1((int) viewx,0.01f,200,0.6f,0.3f,0.15f,400);


}


Background::Background()
{
}


Background::~Background()
{
}






