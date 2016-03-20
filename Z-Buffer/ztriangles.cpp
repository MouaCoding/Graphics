#include <cstdlib>
#include <cmath>
#include <algorithm>
//#include <GLUT/GLUT.h>
#include <GL/glut.h>
using namespace std;

float *PixelBuffer;

//float zbuff[500][500];// z buff same dimensions 
float* zbuffer = new float[500*300];


void display();

void zBuffInit()
{
  for(int i = 0; i < (500*300); i++)
	zbuffer[i] = 20.0; //set to infinity
}

/*
void drawZPixel(int x, int y, int z)
{
	if(z <= zbuff[x][y])
		zbuff[x][y] = z;
	//return x;
}
*/


inline int round(const float a) {return int (a+0.5);}

//BLUE
void setPixel(int x, int y)
{
    PixelBuffer[(x + 200 * y) * 3 + 0] = 0.0;
    PixelBuffer[(x + 200 * y) * 3 + 1] = 0.0;
  PixelBuffer[(x + 200 * y) * 3 + 2] = 1.0;
}

//GREEN
void setPixel1(int x, int y)
{
    PixelBuffer[(x + 200 * y) * 3 + 0] = 0.0;
    PixelBuffer[(x + 200 * y) * 3 + 1] = 1.0;
  PixelBuffer[(x + 200 * y) * 3 + 2] = 0.0;
}

//CYAN
void setPixel2(int x, int y)
{
    PixelBuffer[(x + 200 * y) * 3 + 0] = 0.0;
    PixelBuffer[(x + 200 * y) * 3 + 1] = 1.0;
  PixelBuffer[(x + 200 * y) * 3 + 2] = 1.0;
}

//RED
void setPixel3(int x, int y)
{
    PixelBuffer[(x + 200 * y) * 3 + 0] = 1.0;
    PixelBuffer[(x + 200 * y) * 3 + 1] = 0.0;
  PixelBuffer[(x + 200 * y) * 3 + 2] = 0.0;
}


float ComputeZVal(int x,int y,float normal[6])
{
	float d = -(normal[3]*normal[0] + normal[4]*normal[1] + normal[5]*normal[3]);

	return (-normal[0]*x - normal[1]*y - d) / normal[2];
}


void edge(float x1,float y1,float x2,float y2,int *le,int *re)
{
	float slope,x,temp;
            int i;

    if(y2<y1) //if first point is above the second point, then swap
    {
        temp=x1;
	x1=x2;
	x2=temp;
        temp=y1;
	y1=y2;
	y2=temp;
    }

    if(y1==y2)//if both points are not same height or line is not horizontal
         slope=x2-x1;
    else
        slope=(x2-x1)/(y2-y1);

    x=x1;

    for(i=y1;i<=y2;i++)
    {
        if(x<le[i]) 
	  le[i]=x;
        if(x>re[i]) 
	  re[i]=x;
        x+=slope;
    }
}

//BLUE
void bluefill(float x1,float y1,float x2,float y2,float x3,float y3, float* zbuff, float *norm)
{

//note that le and re are the end of the window of the left and right
    int le[500],re[500],i,j;

    int ymin = floor(min(y1,y2)+0.5);
    int temp = floor(min(y2,y3)+0.5);
    ymin = floor(min(ymin,temp)+0.5);

    int ymax = floor(max(y1,y2)+0.5);
    temp = floor(max(y2,y3)+0.5);
    ymax = floor(max(ymin,temp)+0.5);

    le[0] = ymin;
    re[0] = ymax;

    for(i=0;i<500;i++)
    {    
	le[i]=500;
	re[i]=0;
    }

	norm = new float[6];;
	for(int i=0;i<6;i++) {norm[i] = 2.0;}
	//norm[2]=0,norm[3]=0;
    edge(x1,y1,x2,y2,le,re);
    edge(x2,y2,x3,y3,le,re);
    edge(x3,y3,x1,y1,le,re);

	int z;

    for(j=0;j<500;j++)
    {
        if(le[j]<=re[j])
            for(i=le[j];i<re[j];i++)
             	{  
		z = ComputeZVal(x1,y1,norm);
	        if(z <= zbuff[500*j+i])
	        {
	        zbuff[500*j+i] = z;
		setPixel(i,j);
		
    		}
	}
}
}


void redfill(float x1,float y1,float x2,float y2,float x3,float y3,float* zbuff, float *norm)
{
    int le[500],re[500],i,j;

    int ymin = floor(min(y1,y2)+0.5);
    int temp = floor(min(y2,y3)+0.5);
    ymin = floor(min(ymin,temp)+0.5);

    int ymax = floor(max(y1,y2)+0.5);
    temp = floor(max(y2,y3)+0.5);
    ymax = floor(max(ymin,temp)+0.5);

    le[0] = ymin;
    re[0] = ymax;

    for(i=0;i<500;i++)
    {
        le[i]=500;
        re[i]=0;
    }

    edge(x1,y1,x2,y2,le,re);
    edge(x2,y2,x3,y3,le,re);
    edge(x3,y3,x1,y1,le,re);
	norm= new float[6];
    	for(int i=0;i<6;i++) {norm[i] = 0;}
	int z;
    for(j=0;j<500;j++)
    {
        if(le[j]<=re[j])
                for(i=le[j];i<re[j];i++)
                {
                z = ComputeZVal(x1,y1,norm);
                if(z <= zbuff[500*j+i])
                {
	           zbuff[500*j+i] = z;
                   setPixel3(i,j);
		}	
		}
	}
}
void cyanfill(float x1,float y1,float x2,float y2,float x3,float y3,float* zbuff, float *norm)
{
    int le[500],re[500],i,j;

    int ymin = floor(min(y1,y2)+0.5);
    int temp = floor(min(y2,y3)+0.5);
    ymin = floor(min(ymin,temp)+0.5);

    int ymax = floor(max(y1,y2)+0.5);
    temp = floor(max(y2,y3)+0.5);
    ymax = floor(max(ymin,temp)+0.5);

    le[0] = ymin;
    re[0] = ymax;

    for(i=0;i<500;i++)
    {
        le[i]=500;
        re[i]=0;
    }

    edge(x1,y1,x2,y2,le,re);
    edge(x2,y2,x3,y3,le,re);
    edge(x3,y3,x1,y1,le,re);

	norm= new float[6];;
    	for(int i=0;i<6;i++) {norm[i] = 1.0;}

	int z;

    for(j=0;j<500;j++)
    {
        if(le[j]<=re[j])
                for(i=le[j];i<re[j];i++)
                {
                z = ComputeZVal(x1,y1,norm);
                if(z <= zbuff[500*j+i])
                {
                   zbuff[500*j+i] = z;
                   setPixel2(i,j);
                }
                }
        }
}



int main(int argc, char *argv[])
{
    	PixelBuffer = new float[200*200 * 3];
	zBuffInit();
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(300, 300);
   	glutInitWindowPosition(0, 0);
	glutCreateWindow("Program 3");

	glutDisplayFunc(display);
    	glutMainLoop();//main display loop, will display until terminate
    	return 0;
}

void tri()
{
        float* normal = new float[6];
int j;
	GLfloat x1 =0,y1=60,x2=30,y2=60,x3=15,y3=80;
	        cyanfill(x1,y1,x2,y2,x3,y3,zbuffer,normal);

	for(int i = 0; i < 200; i+=15)
		if(i == 15 || i == 60 || i == 105 || i == 150)
		redfill(x1+i,y1+i,x2+i,y2+i,x3+i,y3+i,zbuffer,normal);
		else if(i == 30 || i == 75 || i == 120 || i == 175) 
		bluefill(x1+i,y1+i,x2+i,y2+i,x3+i,y3+i,zbuffer,normal);
		else
		cyanfill(x1+i,y1+i,x2+i,y2+i,x3+i,y3+i,zbuffer,normal);
x1 =0,y1=80,x2=30,y2=80,x3=15,y3=100;
	for( j = 0; j<200; j+= 10)
                if(j == 10 || j == 40 || j == 70 || j == 100 || j == 130)
                redfill(x1+j,y1+j,x2+j,y2+j,x3+j,y3+j,zbuffer,normal);
                else if(j == 20 || j == 50 || j == 80 || j == 110 || j == 140)
                bluefill(x1+j,y1+j,x2+j,y2+j,x3+j,y3+j,zbuffer,normal);
                else
                cyanfill(x1+j,y1+j,x2+j,y2+j,x3+j,y3+j,zbuffer,normal); 

x1 =0,y1=100,x2=30,y2=100,x3=15,y3=120;
        for(j = 0; j<200; j+= 10)
                if(j == 10 || j == 40 || j == 70 || j == 100 || j == 130)
                redfill(x1+j,y1+j,x2+j,y2+j,x3+j,y3+j,zbuffer,normal);
                else if(j == 20 || j == 50 || j == 80 || j == 110 || j == 140)
                bluefill(x1+j,y1+j,x2+j,y2+j,x3+j,y3+j,zbuffer,normal);
                else
                cyanfill(x1+j,y1+j,x2+j,y2+j,x3+j,y3+j,zbuffer,normal);

x1 =0,y1=120,x2=30,y2=120,x3=15,y3=140;
        for(j = 0; j<140; j+= 10)
                if(j == 10 || j == 40 || j == 70 || j == 100 || j == 130)
                redfill(x1+j,y1+j,x2+j,y2+j,x3+j,y3+j,zbuffer,normal);
                else if(j == 20 || j == 50 || j == 80 || j == 110 || j == 140)
                bluefill(x1+j,y1+j,x2+j,y2+j,x3+j,y3+j,zbuffer,normal);
                else
                cyanfill(x1+j,y1+j,x2+j,y2+j,x3+j,y3+j,zbuffer,normal);


x1 =0,y1=0,x2=30,y2=0,x3=15,y3=20;
        for(j = 0; j<140; j+= 10)
                if(j == 10 || j == 40 || j == 70 || j == 100 || j == 130)
                redfill(x1+j,y1,x2+j,y2,x3+j,y3,zbuffer,normal);
                else if(j == 20 || j == 50 || j == 80 || j == 110 || j == 140)
                bluefill(x1+j,y1,x2+j,y2,x3+j,y3,zbuffer,normal);
                else
                cyanfill(x1+j,y1,x2+j,y2,x3+j,y3,zbuffer,normal);
}
void drawTriangle()
{

	float* normal = new float[6];


        GLfloat x1=20,y1=20,x2=110,y2=110,x3=150,y3=50;
        redfill(x1,y1,x2,y2,x3,y3,zbuffer,normal);


	x1=40,y1=60,x2=120,y2=120,x3=170,y3=70;
        bluefill(x1,y1,x2,y2,x3,y3,zbuffer,normal);


        x1=60,y1=100,x2=140,y2=140,x3=190,y3=90;
        cyanfill(x1,y1,x2,y2,x3,y3,zbuffer,normal);
}

void display()
{
    
    	glClear(GL_COLOR_BUFFER_BIT);
	tri();
	drawTriangle();

	//glRasterPos2i(0,0);
	glLoadIdentity();
    	glDrawPixels(200, 200, GL_RGB, GL_FLOAT, PixelBuffer);
    
    	glFlush();
}
