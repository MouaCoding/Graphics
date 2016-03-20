#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <GLUT/GLUT.h>
//#include <GL/glut.h>
using namespace std;

float *PixelBuffer;

void display();

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
void bluefill(float x1,float y1,float x2,float y2,float x3,float y3)
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
    
    //3 edges for a triangle,
    edge(x1,y1,x2,y2,le,re);
    edge(x2,y2,x3,y3,le,re);
    edge(x3,y3,x1,y1,le,re);
    
    for(j=0;j<500;j++)
    {
        if(le[j]<=re[j])
            for(i=le[j];i<re[j];i++)
                setPixel(i,j);
    }
}

//GREEN
void greenfill(float x1,float y1,float x2,float y2,float x3,float y3)
{
    int le[500],re[500],i,j;
    //min is the lowest vertex
    int ymin = floor(min(y1,y2)+0.5);
    int temp = floor(min(y2,y3)+0.5);
    ymin = floor(min(ymin,temp)+0.5);
    
    //max is the highest vertex
    int ymax = floor(max(y1,y2)+0.5);
    temp = floor(max(y2,y3)+0.5);
    ymax = floor(max(ymin,temp)+0.5);
    
    le[0] = ymin;
    re[0] = ymax;
    
    //we found two of the vertices
    
    for(i=0;i<500;i++)
    {
        le[i]=500;
        re[i]=0;
    }
    
    edge(x1,y1,x2,y2,le,re);
    edge(x2,y2,x3,y3,le,re);
    edge(x3,y3,x1,y1,le,re);
    
    for(j=0;j<500;j++)
    {
        if(le[j]<=re[j])
            for(i=le[j];i<re[j];i++)
                setPixel1(i,j);
    }
}
//CYAN
void cyanfill(float x1,float y1,float x2,float y2,float x3,float y3)
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
    
    for(j=0;j<500;j++)
    {
        if(le[j]<=re[j])
            for(i=le[j];i<re[j];i++)
                setPixel2(i,j);
    }
}

void redfill(float x1,float y1,float x2,float y2,float x3,float y3)
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
    
    for(j=0;j<500;j++)
    {
        if(le[j]<=re[j])
            for(i=le[j];i<re[j];i++)
                setPixel3(i,j);
    }
}

//given
void bres(int x0, int y0, int xEnd, int yEnd)
{
    int dx = fabs(xEnd-x0), dy = fabs(yEnd-y0);
    int p = 2*dy-dx;
    int py = 2*dx-dy;
    int twoDy = 2*dy, twoDyMinusDx = 2*(dy-dx);
    int x,y;
    
    //Determine which endpoint to use as start
    if(dy <= dx)
    {
        if(x0>xEnd)
        {
            x = xEnd;
            y = yEnd;
            xEnd = x0;
        }
        else
        {
            x = x0;
            y = y0;
        }
        setPixel(x,y);
        
        while(x < xEnd)
        {
            x++;
            if(p<0)
                p+= twoDy;
            else{
                if(((xEnd-x0)>0 && (yEnd-y0)>0) || ((xEnd-x0)<0 && (yEnd-y0)<0) )
                    y++;
                else
                    y--;
                p+=twoDyMinusDx;
            }
            setPixel(x,y);
        }
    }
    else{
        if(y0 > yEnd)
        {
            x=xEnd;
            y=yEnd;
            yEnd=y0;
        }
        else{
            x=x0;
            y=y0;
        }
        setPixel(x, y);
        
        while(y < yEnd)
        {
            y++;
            if(py<0)
                py+= twoDy;
            else{
                if(((xEnd-x0)>0 && (yEnd-y0)>0) || ((xEnd-x0)<0 && (yEnd-y0)<0) )
                    x++;
                else if ((xEnd-x0) == 0)
                    x = x;
                else
                    x--;
                py+=2*(dx-dy);
            }
            setPixel(x,y);
        }
    }
}


int main(int argc, char *argv[])
{
    PixelBuffer = new float[200*200 * 3];
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Program 1");
    glutDisplayFunc(display);
    glutMainLoop();//main display loop, will display until terminate
    return 0;
}

void draw(float x1, float y1, float x2, float y2)
{
    bres(x1,y1,x2,y2);
    bres(x1+80,y1+80,x2+50,y2-50);
    bres(x1,y1,x2+50,y2-50);
}

void drawTriangle()
{
    bres(20, 20, 100, 100);
    bres(100, 100, 150, 50);
    bres(20, 20, 150, 50);
    GLfloat x1=20,y1=20,x2=100,y2=100,x3=150,y3=50;
    bluefill(x1,y1,x2,y2,x3,y3);
    
    bres(40, 60, 120, 120);
    bres(120, 120, 170, 70);
    bres(40, 60, 170, 70);
    x1=40,y1=60,x2=120,y2=120,x3=170,y3=70;
    greenfill(x1,y1,x2,y2,x3,y3);
    
    bres(60, 100, 140, 140);
    bres(140, 140, 190, 90);
    bres(60, 100, 190, 90);
    x1=60,y1=100,x2=140,y2=140,x3=190,y3=90;
    cyanfill(x1,y1,x2,y2,x3,y3);
    
    bres(80, 140, 160, 160);
    bres(160, 160, 200, 110);
    bres(80, 140, 200, 110);
    x1=80,y1=140,x2=160,y2=160,x3=200,y3=110;
    redfill(x1,y1,x2,y2,x3,y3);
}

void display()
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    drawTriangle();
    glLoadIdentity();
    glDrawPixels(200, 200, GL_RGB, GL_FLOAT, PixelBuffer);
    
    glFlush();
}




