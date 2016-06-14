#include "Background.h"
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <time.h>

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

float getCoord(float x, float z , float freq1){
	return 1;
	
/*	float h1=mulDelSmoothNoise1D(((float)(x)*freq1));
	h1=	h1+mulDelSmoothNoise1D(((float)(z+309.2)*freq1));
	

	h1=(h1/2)*(z+10.01); 
	return h1/100;
*/}

const int screenWidth=800;

const int screenheight=800;
void Background::layer1(int viewx,float freq1){




	int xstep=100;
	int depthstep=5;
	for(int depth=1;depth<80;depth=depth+depthstep){

			glBegin(GL_TRIANGLE_STRIP);
		for(int x=0;x<screenWidth-1;x=x+xstep){


				glColor3f(1,1,1);


				float h2=getCoord(viewx+x,depth/8.0f,freq1);		
				glVertex3f(viewx+x,depth,h2 );
				 h2=getCoord((viewx+x),-(depth+depthstep)/8.0f,freq1);		
				glVertex3f((viewx+x)/800.0f,h2,-(depth+5)/8.0f);



	}
			glEnd();		
}

}


void drawGrid(){
	
}

void Background::render(float viewx){
	static time_t start = time(nullptr);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(viewx + 400, 300, -500);
	glScalef(400, -1000, 500);
	GLfloat mat_specular[] = {100.0, 100.0, 100.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {0, 0 - 0, -50.0, 0.0};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureRock);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureSnow);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureRockGrass);

	plane.draw();

	glUseProgram(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureSky);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1000, 1000);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, -900);

		glTexCoord2f(1, 0);
		glVertex3f(800, 0, -900);

		glTexCoord2f(1, 1);
		glVertex3f(800, 600, -900);

		glTexCoord2f(0, 1);
		glVertex3f(0, 600, -900);
	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}





Background::~Background()
{
}






