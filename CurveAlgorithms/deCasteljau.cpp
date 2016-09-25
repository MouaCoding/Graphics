 #include <GLUT/GLUT.h>
#include <iostream>
#include<cmath>
#include<fstream>
#include <ctime>
using namespace std;

void display();

int ptsCreated = 0;

struct Point
{
    
    int x;
    int y;
};
struct bezPts
{
    float x[1000];
    float y[1000];
};
void subdivide(int x1, int y1, int x2, int y2, int x3, int y3,
               int x4, int y4, int x5, int y5);
int numPoints = 0;
int found = 0;
int tolerance = 0;
bezPts bez;
Point array1[1024];
Point array2[1024];
int calc = 0;
int colormode = 0;
int newmode = 1;
int mode = -1;
Point points[100]; //input points
bool edit = 0; //edit mode on/off
int oldx = -1, oldy = -1, newx = -1, newy = -1;
int SubMenu;  //a submenu id is needed if you choose to implement a submenu
void createMenu();	//a function that creates menu
void processMenu(int value); //----Call back function---// As explained during discussion, this process menu operations
void processMouseClick(int button, int state, int x, int y); //----Call back function---// similar to menu processing, this process mouse click
float t = 1;
float* PixelBuffer;
int MainWindow;

int getPt( int n1 , int n2 , float perc )
{
    int diff = n2 - n1;
    
    return n1 + ( diff * perc );
}




//green
void setPixel(int x, int y)
{
    PixelBuffer[(x + 500 * y) * 3 + 0] = 0.0;
    PixelBuffer[(x + 500 * y) * 3 + 1] = 1.0;
    PixelBuffer[(x + 500 * y) * 3 + 2] = 0.0;
}

//white
void setPixel1(int x, int y)
{
    PixelBuffer[(x + 500 * y) * 3 + 0] = 1.0;
    PixelBuffer[(x + 500 * y) * 3 + 1] = 1.0;
    PixelBuffer[(x + 500 * y) * 3 + 2] = 1.0;
}

//black
void setPixel2(int x, int y)
{
    PixelBuffer[(x + 500 * y) * 3 + 0] = 0.0;
    PixelBuffer[(x + 500 * y) * 3 + 1] = 0.0;
    PixelBuffer[(x + 500 * y) * 3 + 2] = 0.0;
}
void setPixel3(int x, int y)
{
    PixelBuffer[(x + 500 * y) * 3 + 0] = 1.0;
    PixelBuffer[(x + 500 * y) * 3 + 1] = 0.0;
    PixelBuffer[(x + 500 * y) * 3 + 2] = 0.0;
}
void setPixel4(int x, int y)
{
    PixelBuffer[(x + 500 * y) * 3 + 0] = 1.0;
    PixelBuffer[(x + 500 * y) * 3 + 1] = 0.0;
    PixelBuffer[(x + 500 * y) * 3 + 2] = 1.0;
}
void setPixel5(int x, int y)
{
    PixelBuffer[(x + 500 * y) * 3 + 0] = 0.0;
    PixelBuffer[(x + 500 * y) * 3 + 1] = 0.8;
    PixelBuffer[(x + 500 * y) * 3 + 2] = 0.0;
}

//line drawing algorithm used from textbook
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
        if(colormode == 0)
            setPixel1(round(x), round(y));
        else if (colormode == 1)
            setPixel4(round(x), round(y));
        else if (colormode == 2)
            setPixel3(round(x), round(y));
        
    }
    
}

void Bernstein_Bezier(int x1, int y1, int x2, int y2, int x3, int y3,
                      int x4, int y4, int x5, int y5)
{
    //bezPts bez;
    //the formula is below:
    float bezX = (pow(1-t,3))*x1 + 3*t*(pow(1-t, 2))*x2 + 3*(pow(t, 2))*(1-t)*x3 + (pow(t, 3))*x4;
    float bezY = (pow(1-t,3))*y1 + 3*t*(pow(1-t, 2))*y2 + 3*(pow(t, 2))*(1-t)*y3 + (pow(t, 3))*y4;
    unsigned long sum = 0;
    for( float i = 0 ; i < t ; i += 0.001 ) //slider
    {
        unsigned long start = clock(); // start clock
        bezX =(pow(1-i,3))*x1 + 3*t*(pow(1-i, 2))*x2 + 3*(pow(i, 2))*(1-i)*x3 + (pow(i, 3))*x4;
        bezY = (pow(1-i,3))*y1 + 3*t*(pow(1-i, 2))*y2 + 3*(pow(i, 2))*(1-i)*y3 + (pow(i, 3))*y4;
        //calculate each bezier point
        unsigned long end = clock(); // end clock
        sum = sum + end-start; // add to the total time
        
    }
    cout << "It took " << sum << "ticks, or " << ((float)sum)/CLOCKS_PER_SEC << "seconds " <<
    "using Bernstein-B ́ezier form." << endl;
    
    //for (int k = 0; k < 1000; k++)
    //  cout << bez.x[k] << " " << bez.y[k] << endl;
    
}


//WORKS! 5 points
void fiveptBezier(int x1, int y1, int x2, int y2, int x3, int y3,
                  int x4, int y4, int x5, int y5)
{
    
    int index = 0;
    int x,y,xa, xb, xc, xd, ya, yb, yc, yd;
    int tmp1, tmp2, tmp3,tmp4,tmp5,tmp6;
    unsigned long sum = 0;
    
    for( float i = 0 ; i < t ; i += 0.001 ) //slider
    {
        unsigned long start = clock();
        //this part has 3 connected lines
        xa = getPt( x1 , x2 , i );
        ya = getPt( y1 , y2 , i );
        xb = getPt( x2 , x3 , i );
        yb = getPt( y2 , y3 , i );
        xc = getPt( x3 , x4 , i );
        yc = getPt( y3 , y4 , i );
        xd = getPt( x4 , x5 , i );
        yd = getPt( y4 , y5 , i );
        
        //this part has 2 connected lines
        tmp1 = getPt(xa,xb,i); //xa
        tmp2 = getPt(ya,yb,i); //ya
        tmp3 = getPt(xb,xc,i); //xb
        tmp4 = getPt(yb,yc,i); //yb
        tmp5 = getPt(xc,xd,i); //xc
        tmp6 = getPt(yc,yd,i); //yc
        
        //this part has 1 connected lines
        //can just reuse xa,ya,xb,yb
        xa = getPt( tmp1 , tmp3 , i );
        ya = getPt( tmp2 , tmp4 , i );
        xb = getPt( tmp3 , tmp5 , i );
        yb = getPt( tmp4 , tmp6 , i );
        
        
        x = getPt( xa , xb , i );
        y = getPt( ya , yb , i );
        

        
        setPixel( x , y );
        

        unsigned long end = clock();
        sum = sum + end-start;
        
        
        array1[index].x = x;
        array1[index].y = y;
        index+=1;
        
        numPoints = index;
        //IF GREEN (The curve is green)
        // if the pixel is already set, then output the point.
        //NOTE: this is after the clock() function, so it doesnt calculate this extra if loop
        
    }
    //for(int b = 0; b <= index; b++)
      //cout << "Intersection Point: " << array1[b].x << "," << array1[b].y << index<<endl;
    
    cout << "it took " << sum << "ticks, or " << ((float)sum)/CLOCKS_PER_SEC << "seconds " <<
    "using de Casteljau's algorithm." << endl;
    Bernstein_Bezier( x1,  y1,  x2,  y2,  x3,  y3,
                     x4,  y4,  x5,  y5);
    
    
    xa = getPt( x1 , x2 , t );
    ya = getPt( y1 , y2 , t );
    xb = getPt( x2 , x3 , t );
    yb = getPt( y2 , y3 , t );
    xc = getPt( x3 , x4 , t );
    yc = getPt( y3 , y4 , t );
    xd = getPt( x4 , x5 , t );
    yd = getPt( y4 , y5 , t );
    
    tmp1 = getPt(xa,xb,t); //xa
    tmp2 = getPt(ya,yb,t); //ya
    tmp3 = getPt(xb,xc,t); //xb
    tmp4 = getPt(yb,yc,t); //yb
    tmp5 = getPt(xc,xd,t); //xc
    tmp6 = getPt(yc,yd,t); //yc
    
    int xx = getPt( tmp1 , tmp3 , t );
    int yy = getPt( tmp2 , tmp4 , t );
    int xxx = getPt( tmp3 , tmp5 , t );
    int yyy = getPt( tmp4 , tmp6 , t );
    
    //colormode = 1;
    lineDDA(xa, ya, xb, yb);
    lineDDA(xb, yb, xc, yc);
    lineDDA(xc, yc, xd, yd);
    
    //colormode=2;
    lineDDA(tmp1, tmp2, tmp3, tmp4);
    lineDDA(tmp3, tmp4, tmp5, tmp6);
    
    //colormode = 1;
    lineDDA(xx, yy, xxx, yyy);
}

//for the second curve, for computing intersections
void fiveptBezierCOPY(int x1, int y1, int x2, int y2, int x3, int y3,
                      int x4, int y4, int x5, int y5)
{
    
    int index = 0;
    int x,y,xa, xb, xc, xd, ya, yb, yc, yd;
    int tmp1, tmp2, tmp3,tmp4,tmp5,tmp6;
    unsigned long sum = 0;
    
    for( float i = 0 ; i < t ; i += 0.001 ) //slider
    {
        unsigned long start = clock();
        //this part has 3 connected lines
        xa = getPt( x1 , x2 , i );
        ya = getPt( y1 , y2 , i );
        xb = getPt( x2 , x3 , i );
        yb = getPt( y2 , y3 , i );
        xc = getPt( x3 , x4 , i );
        yc = getPt( y3 , y4 , i );
        xd = getPt( x4 , x5 , i );
        yd = getPt( y4 , y5 , i );
        
        //this part has 2 connected lines
        tmp1 = getPt(xa,xb,i); //xa
        tmp2 = getPt(ya,yb,i); //ya
        tmp3 = getPt(xb,xc,i); //xb
        tmp4 = getPt(yb,yc,i); //yb
        tmp5 = getPt(xc,xd,i); //xc
        tmp6 = getPt(yc,yd,i); //yc
        
        //this part has 1 connected lines
        //can just reuse xa,ya,xb,yb
        xa = getPt( tmp1 , tmp3 , i );
        ya = getPt( tmp2 , tmp4 , i );
        xb = getPt( tmp3 , tmp5 , i );
        yb = getPt( tmp4 , tmp6 , i );
        
        
        x = getPt( xa , xb , i );
        y = getPt( ya , yb , i );
        
        setPixel5( x , y );
        

        unsigned long end = clock();
        sum = sum + end-start;
        
        array2[index].x = x;
        array2[index].y = y;
        index+=1;
        
        //}
        
        //IF GREEN (The curve is green)
        // if the pixel is already set, then output the point.
        //NOTE: this is after the clock() function, so it doesnt calculate this extra if loop
        
    }
    //for(int b = 0; b <= index-5; b++)
    //  if(array1[b].x == array2[b].x)
      //    cout << "copyIntersection Point: " << array2[b].x << "," << array1[b].x << " "<<  index<<endl;
    
    
    
    
    xa = getPt( x1 , x2 , t );
    ya = getPt( y1 , y2 , t );
    xb = getPt( x2 , x3 , t );
    yb = getPt( y2 , y3 , t );
    xc = getPt( x3 , x4 , t );
    yc = getPt( y3 , y4 , t );
    xd = getPt( x4 , x5 , t );
    yd = getPt( y4 , y5 , t );
    
    tmp1 = getPt(xa,xb,t); //xa
    tmp2 = getPt(ya,yb,t); //ya
    tmp3 = getPt(xb,xc,t); //xb
    tmp4 = getPt(yb,yc,t); //yb
    tmp5 = getPt(xc,xd,t); //xc
    tmp6 = getPt(yc,yd,t); //yc
    
    int xx = getPt( tmp1 , tmp3 , t );
    int yy = getPt( tmp2 , tmp4 , t );
    int xxx = getPt( tmp3 , tmp5 , t );
    int yyy = getPt( tmp4 , tmp6 , t );
    
    //colormode = 1;
    lineDDA(xa, ya, xb, yb);
    lineDDA(xb, yb, xc, yc);
    lineDDA(xc, yc, xd, yd);
    
    //colormode=2;
    lineDDA(tmp1, tmp2, tmp3, tmp4);
    lineDDA(tmp3, tmp4, tmp5, tmp6);
    
    //colormode = 1;
    lineDDA(xx, yy, xxx, yyy);
}


//4 points
void cubicBezier(int x1, int y1, int x2, int y2, int x3, int y3,
                 int x4, int y4)
{
    int x,y,xa, xb, xc, ya, yb, yc;
    int tmp1, tmp2, tmp3,tmp4;
    for( float i = 0 ; i < 1 ; i += 0.0001 ) //slider
    {
        xa = getPt( x1 , x2 , i );
        ya = getPt( y1 , y2 , i );
        xb = getPt( x2 , x3 , i );
        yb = getPt( y2 , y3 , i );
        xc = getPt( x3 , x4 , i );
        yc = getPt( y3 , y4 , i );
        
        tmp1 = getPt(xa,xb,i); //xa
        tmp2 = getPt(ya,yb,i); //ya
        tmp3 = getPt(xb,xc,i); //xb
        tmp4 = getPt(yb,yc,i); //yb
        
        x = getPt( tmp1 , tmp3 , i );
        y = getPt( tmp2 , tmp4 , i );
        
        setPixel( x , y );
    }
    tmp1 = getPt(x1,x2,t); //xa
    tmp2 = getPt(y1,y2,t); //ya
    tmp3 = getPt(x2,x3,t); //xb
    tmp4 = getPt(y2,y3,t); //yb
    int tmp5 = getPt(x3,x4,t); //xc
    int tmp6 = getPt(y3,y4,t); //yc
    
    int xx = getPt( tmp1 , tmp3 , t );
    int yy = getPt( tmp2 , tmp4 , t );
    int xxx = getPt( tmp3 , tmp5 , t );
    int yyy = getPt( tmp4 , tmp6 , t );
    //colormode=2;
    lineDDA(tmp1, tmp2, tmp3, tmp4);
    lineDDA(tmp3, tmp4, tmp5, tmp6);
    
    //colormode = 1;
    lineDDA(xx, yy, xxx, yyy);
}
//3 points
void quadraticBezier(int x1, int y1, int x2, int y2, int x3, int y3)
{
    int x,y,xa, xb, ya, yb;
    for( float i = 0 ; i < 1 ; i += 0.0001 ) //slider
    {
        xa = getPt( x1 , x2 , i );
        ya = getPt( y1 , y2 , i );
        xb = getPt( x2 , x3 , i );
        yb = getPt( y2 , y3 , i );
        
        x = getPt( xa , xb , i );
        y = getPt( ya , yb , i );
        
        setPixel(x,y);
    }
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glDrawPixels(500, 500, GL_RGB, GL_FLOAT, PixelBuffer);
    
    glFlush();
}

void processMouseClick(int button, int state, int x, int y)
{
    int index;
    if(mode ==1&& newmode == 1)
    {
        //implementation: user clicks at pos x,y
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            
            PixelBuffer[((500 - y) * 500 + x) * 3] = 1;
            PixelBuffer[((500 - y) * 500 + x) * 3 + 1] = 1;
            PixelBuffer[((500 - y) * 500 + x) * 3 + 2] = 1;
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
            int x1 = x;
            points[ptsCreated].x = x1;
            int y1 = 500-y;
            points[ptsCreated].y = y1;
            ptsCreated++; // need 5 pts, so inc until reaches 5 pts
            
            if(ptsCreated == 2)
            {
                lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
            }
            if(ptsCreated == 3)
            {
                for(int j = 0; j < 500*500*3; j++)
                    PixelBuffer[j] = 0; // clear buff
                lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
                lineDDA(points[1].x, points[1].y, points[2].x, points[2].y);
                
                //intermediate line segments
                colormode = 1;
                lineDDA((points[1].x+points[0].x)/2, (points[1].y+points[0].y)/2,
                        (points[2].x+points[1].x)/2, (points[2].y+points[1].y)/2);
                colormode = 0;
                
                quadraticBezier(points[0].x, points[0].y, points[1].x, points[1].y,points[2].x, points[2].y);
            }
            if(ptsCreated == 4)
            {
                for(int j = 0; j < 500*500*3; j++)
                    PixelBuffer[j] = 0; // clear buff
                lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
                lineDDA(points[1].x, points[1].y, points[2].x, points[2].y);
                lineDDA(points[2].x, points[2].y, points[3].x, points[3].y);
                
                //intermediate line segments
                colormode = 1;
                lineDDA((points[1].x+points[0].x)/2, (points[1].y+points[0].y)/2,
                        (points[2].x+points[1].x)/2, (points[2].y+points[1].y)/2);
                lineDDA((points[2].x+points[1].x)/2, (points[2].y+points[1].y)/2,
                        (points[3].x+points[2].x)/2, (points[3].y+points[2].y)/2);
                
                colormode = 2;
                lineDDA((((points[1].x+points[0].x)/2) +((points[2].x+points[1].x)/2))/2,
                        (((points[1].y+points[0].y)/2) +((points[2].y+points[1].y)/2))/2,
                        (((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2,
                        (((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2);
                
                colormode = 0;
                cubicBezier(points[0].x, points[0].y, points[1].x, points[1].y,points[2].x, points[2].y,
                            points[3].x, points[3].y);
                
                
            }
            
            if(ptsCreated == 5)// && ptsCreated <10)
            {
                //for(int i = 0; i < ptsCreated; i++)
                //std::cout<<"Points Created: " <<points[i].x << " "
                //<< points[i].y<<std::endl;
                for(int j = 0; j < 500*500*3; j++)
                    PixelBuffer[j] = 0; // clear buff
                
                //original polygon
                lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
                lineDDA(points[1].x, points[1].y, points[2].x, points[2].y);
                lineDDA(points[2].x, points[2].y, points[3].x, points[3].y);
                lineDDA(points[3].x, points[3].y, points[4].x, points[4].y);
                
                //intermediate line segments
                colormode = 1;
                lineDDA((points[1].x+points[0].x)/2, (points[1].y+points[0].y)/2,
                        (points[2].x+points[1].x)/2, (points[2].y+points[1].y)/2);
                lineDDA((points[2].x+points[1].x)/2, (points[2].y+points[1].y)/2,
                        (points[3].x+points[2].x)/2, (points[3].y+points[2].y)/2);
                lineDDA((points[3].x+points[2].x)/2, (points[3].y+points[2].y)/2,
                        (points[4].x+points[3].x)/2, (points[4].y+points[3].y)/2);
                
                colormode = 2;
                lineDDA((((points[1].x+points[0].x)/2) +((points[2].x+points[1].x)/2))/2,
                        (((points[1].y+points[0].y)/2) +((points[2].y+points[1].y)/2))/2,
                        (((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2,
                        (((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2);
                lineDDA((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2,
                        (((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2,
                        (((points[3].x+points[2].x)/2) +((points[4].x+points[3].x)/2))/2,
                        (((points[3].y+points[2].y)/2) +((points[4].y+points[3].y)/2))/2);
                
                colormode = 1;
                lineDDA(
                        (((((points[1].x+points[0].x)/2) +((points[2].x+points[1].x)/2))/2) +
                         ((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2))/2,
                        
                        (((((points[1].y+points[0].y)/2) +((points[2].y+points[1].y)/2))/2) +
                         ((((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2))/2,
                        
                        (((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2) +
                         ((((points[3].x+points[2].x)/2) +((points[4].x+points[3].x)/2))/2))/2,
                        
                        (((((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2) +
                         ((((points[3].y+points[2].y)/2) +((points[4].y+points[3].y)/2))/2))/2);
                
                
                colormode = 0;
                
                fiveptBezier(points[0].x, points[0].y, points[1].x, points[1].y,
                             points[2].x, points[2].y, points[3].x, points[3].y,
                             points[4].x, points[4].y);
                
            }
            
            if(ptsCreated == 10) //&& ptsCreated < 15)
            {
                
                
                lineDDA(points[5].x, points[5].y, points[6].x, points[6].y);
                lineDDA(points[6].x, points[6].y, points[7].x, points[7].y);
                lineDDA(points[7].x, points[7].y, points[8].x, points[8].y);
                lineDDA(points[8].x, points[8].y, points[9].x, points[9].y);
                
                
                //intermediate line segments
                colormode = 1;
                lineDDA((points[6].x+points[5].x)/2, (points[6].y+points[5].y)/2,
                        (points[7].x+points[6].x)/2, (points[7].y+points[6].y)/2);
                lineDDA((points[7].x+points[6].x)/2, (points[7].y+points[6].y)/2,
                        (points[8].x+points[7].x)/2, (points[8].y+points[7].y)/2);
                lineDDA((points[8].x+points[7].x)/2, (points[8].y+points[7].y)/2,
                        (points[9].x+points[8].x)/2, (points[9].y+points[8].y)/2);
                
                colormode = 2;
                lineDDA((((points[6].x+points[5].x)/2) +((points[7].x+points[6].x)/2))/2,
                        (((points[6].y+points[5].y)/2) +((points[7].y+points[6].y)/2))/2,
                        (((points[7].x+points[6].x)/2) +((points[8].x+points[7].x)/2))/2,
                        (((points[7].y+points[6].y)/2) +((points[8].y+points[7].y)/2))/2);
                lineDDA((((points[7].x+points[6].x)/2) +((points[8].x+points[7].x)/2))/2,
                        (((points[7].y+points[6].y)/2) +((points[8].y+points[7].y)/2))/2,
                        (((points[8].x+points[7].x)/2) +((points[9].x+points[8].x)/2))/2,
                        (((points[8].y+points[7].y)/2) +((points[9].y+points[8].y)/2))/2);
                
                colormode = 1;
                lineDDA(
                        (((((points[6].x+points[5].x)/2) +((points[7].x+points[6].x)/2))/2) +
                         ((((points[7].x+points[6].x)/2) +((points[8].x+points[7].x)/2))/2))/2,
                        
                        (((((points[6].y+points[5].y)/2) +((points[7].y+points[6].y)/2))/2) +
                         ((((points[7].y+points[6].y)/2) +((points[8].y+points[7].y)/2))/2))/2,
                        
                        (((((points[7].x+points[6].x)/2) +((points[8].x+points[7].x)/2))/2) +
                         ((((points[8].x+points[7].x)/2) +((points[9].x+points[8].x)/2))/2))/2,
                        
                        (((((points[7].y+points[6].y)/2) +((points[8].y+points[7].y)/2))/2) +
                         ((((points[8].y+points[7].y)/2) +((points[9].y+points[8].y)/2))/2))/2);
                
                
                colormode = 0;
                
                fiveptBezierCOPY(points[5].x, points[5].y,
                                 points[6].x, points[6].y,
                                 points[7].x, points[7].y,
                                 points[8].x, points[8].y,
                                 points[9].x, points[9].y);
                
                
                for(int q = 0; q <= numPoints-1; q++)
                {
                    for(int r = 0; r <= numPoints-1; r++)
                        if((array1[q].x == array2[r].x) && (array1[q].y == array2[r].y))
                            cout << "Approximate Point of Intersections: " << array2[q].x << "," <<array2[q].y << endl;
                }
                
                

            }
            
            if(ptsCreated >= 15&& ptsCreated <20)
            {
                fiveptBezier(points[10].x, points[10].y,
                             points[11].x, points[11].y,
                             points[12].x, points[12].y,
                             points[13].x, points[13].y,
                             points[14].x, points[14].y);
                
            }
            if(ptsCreated >= 20&& ptsCreated <25)
            {
                fiveptBezier(points[15].x, points[15].y,
                             points[16].x, points[16].y,
                             points[17].x, points[17].y,
                             points[18].x, points[18].y,
                             points[19].x, points[19].y);
                
            }
            if(ptsCreated >= 25)
            {
                fiveptBezier(points[20].x, points[20].y,
                             points[21].x, points[21].y,
                             points[22].x, points[22].y,
                             points[23].x, points[23].y,
                             points[24].x, points[24].y);
                
            }
            
            
        }
    }
    else if(mode == 2) // edit mode
    {
        
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            edit = 1;
            oldx = x;
            oldy = 500-y;
        }
        else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            bool selector = 0;
            edit = 0;
            for(index = 0; index < ptsCreated; index++)
            {
                if(oldx>points[index].x-10 && oldy>points[index].y-10 &&
                   oldx<points[index].x+10 && oldy<points[index].y+10)
                { selector = 1; break;}
            }
            if(selector == 1){
                //std::cout << "Clicked Point: " << index << std::endl;
                setPixel1(points[index].x,points[index].y); //clear old point
                mode = 1;
                newmode = 1;
                glutMouseFunc(processMouseClick);
                
                newx = x;
                newy = 500-y;
                oldx = points[index].x;
                oldy = points[index].y;
                points[index].x = newx;
                points[index].y = newy;
                for(int i = 0; i < ptsCreated; i++)
                    std::cout<< "New Point: " <<points[i].x << " " << points[i].y<<std::endl;
                
                
                for(int j = 0; j < 500*500*3; j++)
                    PixelBuffer[j] = 0; // clear buff
                
                
                for(int i = 0; i < 5; i++){
                    lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
                    lineDDA(points[1].x, points[1].y, points[2].x, points[2].y);
                    lineDDA(points[2].x, points[2].y, points[3].x, points[3].y);
                    lineDDA(points[3].x, points[3].y, points[4].x, points[4].y);
                    setPixel1(points[i].x,points[i].y); //plot new point
                }
                //intermediate line segments
                colormode = 1;
                lineDDA((points[1].x+points[0].x)/2, (points[1].y+points[0].y)/2,
                        (points[2].x+points[1].x)/2, (points[2].y+points[1].y)/2);
                lineDDA((points[2].x+points[1].x)/2, (points[2].y+points[1].y)/2,
                        (points[3].x+points[2].x)/2, (points[3].y+points[2].y)/2);
                lineDDA((points[3].x+points[2].x)/2, (points[3].y+points[2].y)/2,
                        (points[4].x+points[3].x)/2, (points[4].y+points[3].y)/2);
                
                colormode = 2;
                lineDDA((((points[1].x+points[0].x)/2) +((points[2].x+points[1].x)/2))/2,
                        (((points[1].y+points[0].y)/2) +((points[2].y+points[1].y)/2))/2,
                        (((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2,
                        (((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2);
                lineDDA((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2,
                        (((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2,
                        (((points[3].x+points[2].x)/2) +((points[4].x+points[3].x)/2))/2,
                        (((points[3].y+points[2].y)/2) +((points[4].y+points[3].y)/2))/2);
                
                colormode = 1;
                lineDDA(
                        (((((points[1].x+points[0].x)/2) +((points[2].x+points[1].x)/2))/2) +
                         ((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2))/2,
                        
                        (((((points[1].y+points[0].y)/2) +((points[2].y+points[1].y)/2))/2) +
                         ((((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2))/2,
                        
                        (((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2) +
                         ((((points[3].x+points[2].x)/2) +((points[4].x+points[3].x)/2))/2))/2,
                        
                        (((((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2) +
                         ((((points[3].y+points[2].y)/2) +((points[4].y+points[3].y)/2))/2))/2);
                
                
                colormode = 0;
                
                if(index == 0 )
                {
                    fiveptBezier(newx,newy,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    

                }
                else if(index == 1)
                {
                    fiveptBezier(points[0].x,points[0].y,
                                 newx,newy,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                }
                else if(index == 2)
                {
                    fiveptBezier(points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 newx,newy,points[3].x,points[3].y,
                                 points[4].x,points[4].y);

                }
                else if(index == 3)
                {
                    fiveptBezier(points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 newx,newy,points[4].x,points[4].y);

                }
                else if(index == 4)
                {
                    fiveptBezier(points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 newx,newy);
                }
            }
            
            if (calc == 1)
            {
                for(int j = 0; j < 500*500*3; j++)
                    PixelBuffer[j] = 0; // clear buff
                
                for (float j = 50; j < 65; j+=1) //slider indicator
                    setPixel1(x,j);
                
                cout << x << endl;
                float percentSlider = x/300.0;
                cout << percentSlider << endl;
                t=1;
                t = t*percentSlider;
                cout << t << endl;
                cout << (points[2].x+points[1].x)*t << endl;
                cout << (points[2].y+points[1].y)*t << endl;
                lineDDA(0, 50, 300, 50);
                lineDDA(0, 50, 0, 65);
                lineDDA(0, 65, 300, 65);
                lineDDA(300, 50, 300, 65);
                
                
                lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
                lineDDA(points[1].x, points[1].y, points[2].x, points[2].y);
                lineDDA(points[2].x, points[2].y, points[3].x, points[3].y);
                lineDDA(points[3].x, points[3].y, points[4].x, points[4].y);

                colormode=0;
                fiveptBezier(points[0].x, points[0].y, points[1].x, points[1].y,
                             points[2].x, points[2].y, points[3].x, points[3].y,
                             points[4].x, points[4].y);
                
            }
            
            //part c, subivide into two
            if(calc == 2)
            {
 
                //need first pt,
                //for(int j = 0; j < 500*500*3; j++)
                //  PixelBuffer[j] = 0; // clear buff
                
                
                cout << x << endl;
                float percentSlider = x/300.0;
                cout << percentSlider << endl;
                t=1;
                t = t*percentSlider;
                cout << t << endl;
                cout << (points[2].x+points[1].x)*t << endl;
                cout << (points[2].y+points[1].y)*t << endl;
                
                //CALCULATIONS OF SUBDIVISION
                float ax = (points[1].x+points[0].x)/2;
                float ax1 = (points[2].x+points[1].x)/2;
                float ax2 =(points[3].x+points[2].x)/2;
                float ax3 =(points[4].x+points[3].x)/2;
                float ay = (points[1].y+points[0].y)/2;
                float ay1 = (points[2].y+points[1].y)/2;
                float ay2 = (points[3].y+points[2].y)/2;
                float ay3 = (points[4].y+points[3].y)/2;
                float bx = (ax+ax1)/2;
                float bx1 = (ax1+ax2)/2;
                float bx2 = (ax3+ax2)/2;
                float by = (ay+ay1)/2;
                float by1 = (ay2+ay1)/2;
                float by2 = (ay2+ay3)/2;
                float cx = (bx+bx1)/2;
                float cx1 = (bx2+bx1)/2;
                float cy = (by+by1)/2;
                float cy1 = (by2+by1)/2;
                float dx = (cx+cx1)/2;
                float dy = (cy+cy1)/2;
                for(int j = 0; j < 500*500*3; j++)
                    PixelBuffer[j] = 0; // clear buff
                //original polygon
                for (float j = 50; j < 65; j+=1) //slider indicator
                    setPixel1(x,j);
                
                lineDDA(0, 50, 300, 50);
                lineDDA(0, 50, 0, 65);
                lineDDA(0, 65, 300, 65);
                lineDDA(300, 50, 300, 65);
                
                lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
                lineDDA(points[1].x, points[1].y, points[2].x, points[2].y);
                lineDDA(points[2].x, points[2].y, points[3].x, points[3].y);
                lineDDA(points[3].x, points[3].y, points[4].x, points[4].y);
                
                //intermediate line segments
                colormode = 1;
                lineDDA((points[1].x+points[0].x)/2, (points[1].y+points[0].y)/2,
                        (points[2].x+points[1].x)/2, (points[2].y+points[1].y)/2);
                lineDDA((points[2].x+points[1].x)/2, (points[2].y+points[1].y)/2,
                        (points[3].x+points[2].x)/2, (points[3].y+points[2].y)/2);
                lineDDA((points[3].x+points[2].x)/2, (points[3].y+points[2].y)/2,
                        (points[4].x+points[3].x)/2, (points[4].y+points[3].y)/2);
                
                colormode = 2;
                lineDDA((((points[1].x+points[0].x)/2) +((points[2].x+points[1].x)/2))/2,
                        (((points[1].y+points[0].y)/2) +((points[2].y+points[1].y)/2))/2,
                        (((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2,
                        (((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2);
                lineDDA((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2,
                        (((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2,
                        (((points[3].x+points[2].x)/2) +((points[4].x+points[3].x)/2))/2,
                        (((points[3].y+points[2].y)/2) +((points[4].y+points[3].y)/2))/2);
                
                colormode = 1;
                lineDDA(
                        (((((points[1].x+points[0].x)/2) +((points[2].x+points[1].x)/2))/2) +
                         ((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2))/2,
                        
                        (((((points[1].y+points[0].y)/2) +((points[2].y+points[1].y)/2))/2) +
                         ((((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2))/2,
                        
                        (((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2) +
                         ((((points[3].x+points[2].x)/2) +((points[4].x+points[3].x)/2))/2))/2,
                        
                        (((((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2) +
                         ((((points[3].y+points[2].y)/2) +((points[4].y+points[3].y)/2))/2))/2);
                
                
                colormode = 0;
                fiveptBezier(points[0].x, points[0].y,ax,ay,bx,by,cx, cy,
                             dx, dy);

                
                
                fiveptBezier(dx,dy,cx,cy,cx1,cy1,ax3, ay3,
                             points[4].x, points[4].y);

            }
        }}
    
    glutPostRedisplay();
    glFlush();
}

void load(const char *filename)
{
    ifstream file(filename);
    file.clear();
    int i = 0;
    while(!file.eof())
    {
        int x,y;
        file >> x;
        file >> y;
        points[i].x = x;
        points[i].y = y;
        i++;
    }
    ptsCreated = i;
    for(int j = 0; j < 5; j++){
        cout <<"Loaded Points: " << points[j].x << " " << points[j].y << endl;
        setPixel1(points[j].x,points[j].y);
    }
    if(ptsCreated == 2)
    {
        lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
    }
    if(ptsCreated == 3)
    {
        for(int j = 0; j < 500*500*3; j++)
            PixelBuffer[j] = 0; // clear buff
        lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
        lineDDA(points[1].x, points[1].y, points[2].x, points[2].y);
        quadraticBezier(points[0].x, points[0].y, points[1].x, points[1].y,points[2].x, points[2].y);
    }
    if(ptsCreated == 4)
    {
        for(int j = 0; j < 500*500*3; j++)
            PixelBuffer[j] = 0; // clear buff
        lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
        lineDDA(points[1].x, points[1].y, points[2].x, points[2].y);
        lineDDA(points[2].x, points[2].y, points[3].x, points[3].y);
        cubicBezier(points[0].x, points[0].y, points[1].x, points[1].y,points[2].x, points[2].y,
                    points[3].x, points[3].y);
        
    }
    
    if(ptsCreated >= 5 && ptsCreated <10)
    {
        for(int i = 0; i < ptsCreated; i++)
            std::cout<<"Points Created: " <<points[i].x << " "
            << points[i].y<<std::endl;
        for(int j = 0; j < 500*500*3; j++)
            PixelBuffer[j] = 0; // clear buff
        lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
        lineDDA(points[1].x, points[1].y, points[2].x, points[2].y);
        lineDDA(points[2].x, points[2].y, points[3].x, points[3].y);
        lineDDA(points[3].x, points[3].y, points[4].x, points[4].y);
        
        //intermediate line segments
        colormode = 1;
        lineDDA((points[1].x+points[0].x)/2, (points[1].y+points[0].y)/2,
                (points[2].x+points[1].x)/2, (points[2].y+points[1].y)/2);
        lineDDA((points[2].x+points[1].x)/2, (points[2].y+points[1].y)/2,
                (points[3].x+points[2].x)/2, (points[3].y+points[2].y)/2);
        lineDDA((points[3].x+points[2].x)/2, (points[3].y+points[2].y)/2,
                (points[4].x+points[3].x)/2, (points[4].y+points[3].y)/2);
        
        colormode = 2;
        lineDDA((((points[1].x+points[0].x)/2) +((points[2].x+points[1].x)/2))/2,
                (((points[1].y+points[0].y)/2) +((points[2].y+points[1].y)/2))/2,
                (((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2,
                (((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2);
        lineDDA((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2,
                (((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2,
                (((points[3].x+points[2].x)/2) +((points[4].x+points[3].x)/2))/2,
                (((points[3].y+points[2].y)/2) +((points[4].y+points[3].y)/2))/2);
        
        colormode = 1;
        lineDDA(
                (((((points[1].x+points[0].x)/2) +((points[2].x+points[1].x)/2))/2) +
                 ((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2))/2,
                
                (((((points[1].y+points[0].y)/2) +((points[2].y+points[1].y)/2))/2) +
                 ((((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2))/2,
                
                (((((points[2].x+points[1].x)/2) +((points[3].x+points[2].x)/2))/2) +
                 ((((points[3].x+points[2].x)/2) +((points[4].x+points[3].x)/2))/2))/2,
                
                (((((points[2].y+points[1].y)/2) +((points[3].y+points[2].y)/2))/2) +
                 ((((points[3].y+points[2].y)/2) +((points[4].y+points[3].y)/2))/2))/2);
        
        
        colormode = 0;
        
        fiveptBezier(points[0].x, points[0].y, points[1].x, points[1].y,
                     points[2].x, points[2].y, points[3].x, points[3].y,
                     points[4].x, points[4].y);
        
    }
    
    

    
}

void save(const char *filename)
{
    ofstream file(filename);
    for(int i = 0; i < ptsCreated; i++)
        file << points[i].x << " " << points[i].y << endl;
    file.close();
}

void createMenu()
{
    //submenu
    SubMenu = glutCreateMenu(processMenu);
        glutAddMenuEntry("Tolerance = 1", 7);
        glutAddMenuEntry("Tolerance = 2", 8);
        glutAddMenuEntry("Tolerance = 3", 10);
    
    glutCreateMenu(processMenu);
    glutAddMenuEntry("Input Mode", 1);
    glutAddMenuEntry("Edit Mode", 2);
    glutAddMenuEntry("Load", 3);
    glutAddMenuEntry("Save", 4);
    glutAddMenuEntry("Slider", 5);
    glutAddMenuEntry("Part C", 6);
    glutAddSubMenu("Part D", SubMenu);
    glutAddMenuEntry("Clear", 9);
    
    //glutAddSubMenu("SubMenu", SubMenu);
    
    glutAddMenuEntry("Exit", 0);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMenu(int value)
{
    if (value == 0)
    {
        glutDestroyWindow(MainWindow);
        exit(0);
    }
    else if (value == 1)
    {
        mode = 1;
        //		ptsCreated = 0;
        glFlush();
        glutMouseFunc(processMouseClick);
    }
    else if(value == 2)
    {
        mode = 2;
        glutMouseFunc(processMouseClick);
    }
    
    else if (value == 3)
    {
        load("outfile");
        mode = 2;
        glutMouseFunc(processMouseClick);
    }
    else if (value == 4)
    {
        save("outfile");
    }
    else if (value == 5)
    {
        mode = 2;
        calc = 1;
        colormode = 0;
        lineDDA(0, 50, 300, 50);
        lineDDA(0, 50, 0, 65);
        lineDDA(0, 65, 300, 65);
        lineDDA(300, 50, 300, 65);
        glutMouseFunc(processMouseClick);
    }
    else if (value == 6)
    {
        mode = 2;
        calc = 2;
        lineDDA(0, 50, 300, 50);
        lineDDA(0, 50, 0, 65);
        lineDDA(0, 65, 300, 65);
        lineDDA(300, 50, 300, 65);
        glutMouseFunc(processMouseClick);
    }
    
    else if(value == 7)
    {
        mode = 1;
        tolerance = 1;
        glutMouseFunc(processMouseClick);
    }
    else if(value == 8)
    {
        mode = 1;
        tolerance = 2;
        glutMouseFunc(processMouseClick);
    }
    else if(value == 9)
    {
        for(int j = 0; j < 500*500*3; j++)
            PixelBuffer[j] = 0; // clear buff
        ptsCreated = 0;
        calc = 0;
        
    }
    else if(value == 10)
    {
        mode = 1;
        tolerance = 3;
        glutMouseFunc(processMouseClick);
    }
    
    
    glutPostRedisplay();
}

void deletePt()
{
    
}
void motion(int xmouse, int ymouse)
{
    if(edit == 1){
        newx = xmouse;
        newy = 500 - ymouse;}
    else{
        return;
    }
    glutPostRedisplay();    //std::cout << newx << std::endl;
}
int main(int argc, char *argv[])
{
    
    PixelBuffer = new float[500 * 500 * 3];
    *PixelBuffer = 0;//initialize pixel buffer
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    
    MainWindow = glutCreateWindow("Program 1");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glutDisplayFunc(display);
    
    //        createMenu();
    glutMouseFunc(processMouseClick);
    glutMotionFunc(motion);
    createMenu();
    
    glutMainLoop();
    
    return 0;
}

void subdivide(int x1, int y1, int x2, int y2, int x3, int y3,
               int x4, int y4, int x5, int y5)
{
    
    //subdivide a bezier curve in two:
    float ax = (x2+x1)/2;
    float ax1 = (x3+x2)/2;
    float ax2 =(x4+x3)/2;
    float ax3 =(x5+x4)/2;
    float ay = (y2+y1)/2;
    float ay1 = (y3+y2)/2;
    float ay2 = (y4+y3)/2;
    float ay3 = (y5+y4)/2;
    float bx = (ax+ax1)/2;
    float bx1 = (ax1+ax2)/2;
    float bx2 = (ax3+ax2)/2;
    float by = (ay+ay1)/2;
    float by1 = (ay2+ay1)/2;
    float by2 = (ay2+ay3)/2;
    float cx = (bx+bx1)/2;
    float cx1 = (bx2+bx1)/2;
    float cy = (by+by1)/2;
    float cy1 = (by2+by1)/2;
    float dx = (cx+cx1)/2;
    float dy = (cy+cy1)/2;
    //for(int j = 0; j < 500*500*3; j++)
    //  PixelBuffer[j] = 0; // clear buff
    
    //cout << "Points of Intersection: " << bx << "," << by << endl;
    
    {
        
    }
    if(tolerance == 1)
    {
        fiveptBezier(x1,y1,ax,ay,bx,by,cx, cy,
                     dx, dy);
        fiveptBezier(dx,dy,cx,cy,cx1,cy1,ax3, ay3,//bx2, by2,
                     x5,y5);
    }
    else if(tolerance == 2) // subdivide again!
    {
        tolerance = 1;
        subdivide(x1,y1,ax,ay,bx,by,cx, cy,
                  dx, dy);
        subdivide(dx,dy,cx,cy,cx1,cy1,ax3, ay3,//bx2, by2,
                       x5,y5);
    }
    else if( tolerance == 3)
    {
        tolerance = 2;
        subdivide(x1,y1,ax,ay,bx,by,cx, cy,
                  dx, dy);
        subdivide(dx,dy,cx,cy,cx1,cy1,ax3, ay3,//bx2, by2,
                  x5,y5);
    }
    
}
