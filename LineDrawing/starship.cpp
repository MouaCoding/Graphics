#include <stdlib.h>
#include <math.h>
//#include <GLUT/GLUT.h>
#include <GL/glut.h>
using namespace std;

float *PixelBuffer;

    void display();

inline int round(const float a) {return int (a+0.5);}

void setPixel(int x, int y)
{
    PixelBuffer[(x + 200 * y) * 3 + 0] = 1.0;
    PixelBuffer[(x + 200 * y) * 3 + 1] = 1.0;
    PixelBuffer[(x + 200 * y) * 3 + 2] = 1.0;
}

void lineDDA(int x0, int y0, int xEnd, int yEnd)
{
    int dx = xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;
    

    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);

    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);


    setPixel(round(x), round(y));

    for (k = 0; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x), round(y));
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

void starship()
{
    //8 cases of lines
    bres(20, 100, 100, 100); //horizontal
    bres(20, 0, 100, 100); //slope = 1
    bres(20, 50, 200, 100);// slope < 1
    bres(20, 200, 100, 100); // slope = -1
    bres(20, 150, 200, 100); //slope > -1
    
    
    //this was the farthest i could go without making it a vertical line
    bres(40, 60, 50, 100);  // slope > 1

    
    //this was the farthest i could go without making it a vertical line
    bres(59, 140, 60, 100); //slope < -1 For example: -2,
    
    //lineDDA(220, 0, 220, 200); //test
    bres(220, 0, 220, 200); // VERTICAL
    
    //muffler top
    bres(20, 130, 10, 130);
    bres(20, 120, 10, 120);
    bres(10, 120, 10, 130);

    
    //muffler bottom
    bres(20, 80, 10, 80);
    bres(20, 70, 10, 70);
    bres(10, 70, 10, 80);

    //laser gun top
    bres(80, 165, 48, 165);
    bres(80, 155, 53, 155);
    bres(80, 155, 80, 165);
    
    //laser gun bottom
    bres(80, 35, 53, 35);
    bres(80, 25, 46, 25);
    bres(80, 25, 80, 35);
    
    //lasers
    bres(90, 160, 110, 160);
    bres(120, 160, 140, 160);
    bres(90, 30, 110, 30);
    bres(120, 30, 140, 30);
    
    

}
int main(int argc, char *argv[])
{

    PixelBuffer = new float[200*200 * 3];
   
    
/*
    //call bresenham algorithm
    bres(0, 100, 100, 100); //horizontal
    bres(0, 0, 100, 100); //slope = 1
    bres(0, 50, 200, 100);// slope < 1

    bres(40, 60, 50, 100);  // slope > 1

    bres(0, 200, 100, 100); // slope = -1
    bres(0, 150, 200, 100); //slope > -1
    
    bres(55, 140, 60, 100); //slope < -1 For example: -2

    //lineDDA(210, 0, 210, 200);
    bres(210, 0, 210, 200); // VERTICAL
 */
    
    

    //Drawing a starship!
      bres(10,10,100,100);
  bres(100,100,20,20);
  bres(20,20,10,10);//starship();
    
    
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        
        glutInitWindowSize(400, 400);
        

    
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Program 1");
    glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
    
    glutDisplayFunc(display);
    
    glutMainLoop();//main display loop, will display until terminate
    return 0;
}

void display()
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
