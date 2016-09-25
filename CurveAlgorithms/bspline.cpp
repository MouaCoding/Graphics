

#include <GLUT/GLUT.h>
#include <iostream>
#include<cmath>
#include<fstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void display();

int ptsCreated = 0;
int apo = 0;
int abc = 0;
int c2 = 0;
int k = 0;
int uniform, chordLength, centripetal;
class Point
{
public:
    float x;
    float y;
    
    
    void setxy(float x2, float y2)
    {
        x = x2; y = y2;
    }
    
    const Point & operator=(const Point &rPoint)
    {
        x = rPoint.x;
        y = rPoint.y;
        return *this;
    }
    
};
struct bezPts
{
    float x[1000];
    float y[1000];
};
void subdivide(int x1, int y1, int x2, int y2, int x3, int y3,
               int x4, int y4, int x5, int y5);
int numPoints = 0;
int counter2 = 0;
int somevalue = 0;
int C1MODE = 0;
int found = 0;
int tolerance = 0;
bezPts bez;
Point array1[1024];
Point array2[1024];
Point array3[1024];
int arrayCount=0;
int called = 0;
int calc = 0;
int colormode = 0;
int newmode = 1;
int mode = -1;
Point points[100]; //input points
bool edit = 0; //edit mode on/off
int oldx = -1, oldy = -1, newx = -1, newy = -1;
int SubMenu, SubMenu2;  //a submenu id is needed if you choose to implement a submenu
void createMenu();	//a function that creates menu
void processMenu(int value); //----Call back function---// As explained during discussion, this process menu operations
void processMouseClick(int button, int state, int x, int y); //----Call back function---// similar to menu processing, this process mouse click
float t = 1;
float* PixelBuffer;
int MainWindow;
int counter = 0;

int clicks = 4;

void initArray()
{
    for(int in = 0; in < 1025; in++)
        array1[in].x = 0;
}


int factorial(int n)
{
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return n;
}

float binomial_coff(float n,float k)
{
    float ans;
    ans = factorial(n) / (factorial(k)*factorial(n-k));
    return ans;
}

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
void setPixel6(int x, int y)
{
    PixelBuffer[(x + 500 * y) * 3 + 0] = 0.0;
    PixelBuffer[(x + 500 * y) * 3 + 1] = 1.0;
    PixelBuffer[(x + 500 * y) * 3 + 2] = 1.0;
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
        if(colormode == 0)
            setPixel1(round(x), round(y));
        else if (colormode == 1)
            setPixel4(round(x), round(y));
        else if (colormode == 2)
            setPixel3(round(x), round(y));
        else if(colormode == 3)
            setPixel(round(x), round(y));
        else if(colormode == 4)
            setPixel6(round(x), round(y));
        
    }
    
}

void drawLine1(Point p1, Point p2) {
    colormode = 3;
    lineDDA(p1.x, p1.y, p2.x, p2.y);
    colormode = 0;
}
void drawLine2(Point p1, Point p2) {
    colormode = 2;
    lineDDA(p1.x, p1.y, p2.x, p2.y);
    colormode = 0;
}
void drawLine(Point p1, Point p2) {
    lineDDA(p1.x, p1.y, p2.x, p2.y);
}

//calc point
Point drawBezier(Point PT[], double t) {
    Point P;
    P.x = pow((1 - t), 3) * PT[0].x + 3 * t * pow((1 -t), 2) * PT[1].x + 3 * (1-t) * pow(t, 2)* PT[2].x + pow (t, 3)* PT[3].x;
    P.y = pow((1 - t), 3) * PT[0].y + 3 * t * pow((1 -t), 2) * PT[1].y + 3 * (1-t) * pow(t, 2)* PT[2].y + pow (t, 3)* PT[3].y;
    
    return P;
}

Point drawBezierGeneralized(Point PT[], double t) {
    Point P;
    P.x = 0; P.y = 0;
    for (int i = 0; i<clicks; i++)
    {
        P.x = P.x + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].x;
        P.y = P.y + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].y;
    }
    //cout<<P.x<<endl<<P.y;
    //cout<<endl<<endl;
    return P;
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
        unsigned long start = clock();
        bezX =(pow(1-i,3))*x1 + 3*t*(pow(1-i, 2))*x2 + 3*(pow(i, 2))*(1-i)*x3 + (pow(i, 3))*x4;
        bezY = (pow(1-i,3))*y1 + 3*t*(pow(1-i, 2))*y2 + 3*(pow(i, 2))*(1-i)*y3 + (pow(i, 3))*y4;
        //calculate each bezier point
        unsigned long end = clock();
        sum = sum + end-start;
        
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
        
        //lineDDA(xa, ya, xb, yb);
        //lineDDA(xb, yb, xc, yc);
        //lineDDA(xc, yc, xd, yd);
        
        setPixel( x , y );
        //Point p2 = drawBezierGeneralized(points,t);
        //drawLine(p1, p2);
        //p1 = p2;
        
        
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
    //  cout << "Intersection Point: " << array1[b].x << "," << array1[b].y << index<<endl;
    
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
        
        //lineDDA(xa, ya, xb, yb);
        //lineDDA(xb, yb, xc, yc);
        //lineDDA(xc, yc, xd, yd);
        
        setPixel5( x , y );
        
        
        unsigned long end = clock();
        sum = sum + end-start;
        
        //if(PixelBuffer[(x + 500 * y) * 3 + 0] == 0.0 &&
        // PixelBuffer[(x + 500 * y) * 3 + 1] == 0.8 &&
        //PixelBuffer[(x + 500 * y) * 3 + 2] == 0.0)
        //{
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
    //      cout << "copyIntersection Point: " << array2[b].x << "," << array2[b].y <<  index<<endl;
    
    
    
    
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
    colormode=1;
    lineDDA(tmp1, tmp2, tmp3, tmp4);
    lineDDA(tmp3, tmp4, tmp5, tmp6);

    lineDDA(xx, yy, xxx, yyy);
        colormode = 0;
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

Point calcPoint(Point p, int numPoints)
{
    p.x = p.x/numPoints;
    
    return p;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glDrawPixels(500, 500, GL_RGB, GL_FLOAT, PixelBuffer);
    
    glFlush();
}



int here = 0;
void processMouseClick(int button, int state, int x, int y)
{
    int index, n;
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
            n = ptsCreated+1;
            
            
            if(ptsCreated == 2)
            {
                lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
            }
            if(ptsCreated == 3 && C1MODE !=2)
            {
                for(int j = 0; j < 500*500*3; j++)
                    PixelBuffer[j] = 0; // clear buff
                lineDDA(points[0].x, points[0].y, points[1].x, points[1].y);
                lineDDA(points[1].x, points[1].y, points[2].x, points[2].y);
                
                
                quadraticBezier(points[0].x, points[0].y, points[1].x, points[1].y,points[2].x, points[2].y);
                
                if(abc == 2)
                {
                    Point a,b,c,d,half1,half2;
                    a.x= getPt(points[0].x, points[1].x, 1.5);
                    a.y = getPt(points[0].y, points[1].y, 1.5); // 1 up
                    
                    b.x = getPt(points[2].x, points[1].x, 1.5);
                    b.y = getPt(points[2].y, points[1].y, 1.5); // 1 left
                    
                    //lineDDA(points[0].x, points[0].y, a.x, a.y);
                    //lineDDA(points[2].x, points[2].y, b.x, b.y);
                    
                    c.x = getPt(b.x, points[0].x, 1.5);
                    c.y = getPt(b.y, points[0].y, 1.5);
                    
                    d.x = getPt(a.x, points[2].x, 1.5);
                    d.y = getPt(a.y, points[2].y, 1.5);
                    colormode = 1;
                    //lineDDA(b.x,b.y,c.x,c.y);
                    //lineDDA(a.x, a.y, d.x, d.y);
                    
                    half1.x = getPt(b.x, points[0].x, 0.27);
                    half1.y =getPt(b.y, points[0].y, 0.27);
                    
                    half2.x = getPt(a.x, d.x, 0.27);
                    half2.y =getPt(a.y, d.y, 0.27);
                    
                    lineDDA(half1.x, half1.y, points[0].x, points[0].y);
                    lineDDA(half2.x, half2.y, points[2].x, points[2].y);
                    lineDDA(half1.x, half1.y, half2.x, half2.y);
                    colormode = 0;
                    quadraticBezier(points[0].x, points[0].y, half1.x, half1.y, points[1].x, points[1].y);
                    quadraticBezier(points[1].x, points[1].y, half2.x, half2.y, points[2].x, points[2].y);
                    
      
                    
                    a.x= getPt(points[0].x, points[1].x, 1.3);
                    a.y = getPt(points[0].y, points[1].y, 1.3); // 1 up
                    
                    b.x = getPt(points[2].x, points[1].x, 1.9);
                    b.y = getPt(points[2].y, points[1].y, 1.9); // 1 left
                    
                    //lineDDA(points[0].x, points[0].y, a.x, a.y);
                    //lineDDA(points[2].x, points[2].y, b.x, b.y);
                    
                    c.x = getPt(b.x, points[0].x, 1.3);
                    c.y = getPt(b.y, points[0].y, 1.3);
                    
                    d.x = getPt(a.x, points[2].x, 1.3);
                    d.y = getPt(a.y, points[2].y, 1.3);
                    colormode = 4;
                    
                    
                    half1.x = getPt(b.x, points[0].x, 0.27);
                    half1.y =getPt(b.y, points[0].y, 0.27);
                    
                    half2.x = getPt(a.x, d.x, 0.27);
                    half2.y =getPt(a.y, d.y, 0.27);
                    
                    lineDDA(half1.x, half1.y, points[0].x, points[0].y);
                    lineDDA(half2.x, half2.y, points[2].x, points[2].y);
                    lineDDA(half1.x, half1.y, half2.x, half2.y);
                    colormode = 0;

                    
                    
                    a.x= getPt(points[0].x, points[1].x, 1.9);
                    a.y = getPt(points[0].y, points[1].y, 1.9); // 1 up
                    
                    b.x = getPt(points[2].x, points[1].x, 1.3);
                    b.y = getPt(points[2].y, points[1].y, 1.3); // 1 left
                    
                    //lineDDA(points[0].x, points[0].y, a.x, a.y);
                    //lineDDA(points[2].x, points[2].y, b.x, b.y);
                    
                    c.x = getPt(b.x, points[0].x, 1.3);
                    c.y = getPt(b.y, points[0].y, 1.3);
                    
                    d.x = getPt(a.x, points[2].x, 1.3);
                    d.y = getPt(a.y, points[2].y, 1.3);
                    colormode = 2;
                    
                    
                    half1.x = getPt(b.x, points[0].x, 0.27);
                    half1.y =getPt(b.y, points[0].y, 0.27);
                    
                    half2.x = getPt(a.x, d.x, 0.27);
                    half2.y =getPt(a.y, d.y, 0.27);
                    lineDDA(half1.x, half1.y, points[0].x, points[0].y);
                    lineDDA(half2.x, half2.y, points[2].x, points[2].y);
                    lineDDA(half1.x, half1.y, half2.x, half2.y);
                    colormode = 0;

                    
                    
                }
                
            }
            if(ptsCreated >= clicks )
            {
                
                for(int j = 0; j < 500*500*3; j++)
                    PixelBuffer[j] = 0; // clear buff
                if(C1MODE !=2)
                {
                    for(int k=0;k<clicks-1;k++)
                        drawLine(points[k], points[k+1]);
                }
                else if (C1MODE ==2)
                {
                    //for(int k=0;k<clicks-1;k+=2)
                    //  drawLine(points[k], points[k+1]);
                    drawLine(points[0],points[1]);
                    drawLine(points[clicks-2],points[clicks-1]);
                }
                Point p1 = points[0];
                

                
                for(double t = 0.0;t <= 1.0; t += 0.01)
                {
                    Point p2 = drawBezierGeneralized(points,t);
                    drawLine1(p1, p2);
                    p1 = p2;
                    
                }

                if(C1MODE == 1)
                {
                    
                    called++;
                    
                    if(abc == 1){
                    //code from internet
                    printf("\nCalculating Interpolating Form...\n");
                    
                    float bu[clicks];
                    
                    Point pp = points[counter];
                    
                    for (int uInt = 0; uInt <= 100; uInt++) //100 points
                    {
                        float u = uInt/(float)100;
                        bu[counter+0] = (-9.0/2.0)*(u-(1.0/3.0))*(u-(2.0/3.0))*(u-1.0);
                        bu[counter+1] = (27.0/2.0)*u*(u-(2.0/3.0))*(u-1.0);
                        bu[counter+2] = (-27.0/2.0)*u*(u-(1.0/3.0))*(u-1.0);
                        bu[counter+3] = (9.0/2.0)*u*(u-(1.0/3.0))*(u-(2.0/3.0));
                        
                        float x = 0.0;
                        float y = 0.0;
                        Point ppp;
                        
                        for (int i = counter; i < counter+4; i++)
                        {
                            x += bu[i]*points[i].x;//ctrlPoints[i][0];
                            y += bu[i]*points[i].y;//ctrlPoints[i][1];
                            
                            
                        }
                        if(//array1[arrayCount].x == 0)
                           (arrayCount >=166 && called == 2) || called ==1 || (arrayCount >=268 && called == 3) || (arrayCount >=370 && called == 4) || (arrayCount >=470 && called == 5)
                           || (arrayCount >=571 && called == 6) || (arrayCount >=673 && called == 7)
                           || (arrayCount >=774 && called == 8) || (arrayCount >=874 && called == 9)
                           || (arrayCount >=975 && called == 10))
                        {
                            array1[arrayCount].x = x;
                            array1[arrayCount].y = y; //store x and y value
                            
                        }
                        ppp.x = x;
                        ppp.y = y;
                        
                        printf("x=%g  y=%g\n", x, y);
                        
                        
                        
                        pp = ppp;
                        
                        
                        arrayCount++;
                    }
                        
                        counter++;
                    }
                    
                    
                    else if(abc == 2)
                    {
                     
                        for(int j = 0; j < 500*500*3; j++)
                            PixelBuffer[j] = 0; // clear buff
                        
                            for(int k=0;k<clicks-1;k++)
                                drawLine(points[k], points[k+1]);
                        int set = 0;
                        for( int i = 0; i < clicks-3 ; i++)
                        {
                         
                        Point a,b,c,d,e,f;
                        Point half1,half2,half3;
                        
                        a.x = getPt(points[i+0].x, points[i+1].x, 1.5);
                        a.y = getPt(points[i+0].y, points[i+1].y, 1.5); // 1 up
                        
                        b.x = getPt(points[i+2].x, points[i+1].x, 1.5);
                        b.y = getPt(points[i+2].y, points[i+1].y, 1.5); // 1 left
                        
                        c.x = getPt(points[i+1].x, points[i+2].x, 1.5);
                        c.y = getPt(points[i+1].y, points[i+2].y, 1.5); //2 right
                        
                        d.x = getPt(points[i+3].x, points[i+2].x, 1.5);
                        d.y = getPt(points[i+3].y, points[i+2].y, 1.5); // 2 up
                        
                        e.x = getPt(b.x, points[i+0].x, 1.5);
                        e.y = getPt(b.y, points[i+0].y, 1.5);
                        
                        f.x = getPt(c.x, points[i+3].x, 1.5);
                        f.y = getPt(c.y, points[i+3].y, 1.5);
                        
                        half1.x = getPt(b.x, points[i+0].x, 0.33);
                        half1.y =getPt(b.y, points[i+0].y, 0.33);
                        
                        half2.x = getPt(a.x, d.x, 0.5);
                        half2.y =getPt(a.y, d.y, 0.5);
                        
                        half3.x = getPt(c.x, points[i+3].x, 0.33);
                        half3.y =getPt(c.y, points[i+3].y, 0.33);
                            colormode = 1;
                            if(set == 0)
                            {
                        lineDDA(half1.x, half1.y, half2.x, half2.y);
                        lineDDA(half2.x, half2.y, half3.x, half3.y);
                            
                        lineDDA(half1.x, half1.y, e.x, e.y);
                            }
                            
                        lineDDA(half3.x, half3.y, f.x, f.y);
                            colormode = 0;
                            if(set == 0)
                            {
                        quadraticBezier(points[i+0].x, points[i+0].y, half1.x, half1.y, points[i+1].x, points[i+1].y);
                        quadraticBezier(points[i+1].x, points[i+1].y, half2.x, half2.y, points[i+2].x, points[i+2].y);
                            }
                        quadraticBezier(points[i+2].x, points[i+2].y, half3.x, half3.y, points[i+3].x, points[i+3].y);

                            
                            
                            
                            
                            
                            
                            a.x = getPt(points[i+0].x, points[i+1].x, 1.3);
                            a.y = getPt(points[i+0].y, points[i+1].y, 1.3); // 1 up
                            
                            b.x = getPt(points[i+2].x, points[i+1].x, 1.9);
                            b.y = getPt(points[i+2].y, points[i+1].y, 1.9); // 1 left
                            
                            c.x = getPt(points[i+1].x, points[i+2].x, 1.9);
                            c.y = getPt(points[i+1].y, points[i+2].y, 1.9); //2 right
                            
                            d.x = getPt(points[i+3].x, points[i+2].x, 1.3);
                            d.y = getPt(points[i+3].y, points[i+2].y, 1.3); // 2 up
                            
                            e.x = getPt(b.x, points[i+0].x, 1.9);
                            e.y = getPt(b.y, points[i+0].y, 1.9);
                            
                            f.x = getPt(c.x, points[i+3].x, 1.9);
                            f.y = getPt(c.y, points[i+3].y, 1.9);
                            
                            half1.x = getPt(b.x, points[i+0].x, 0.33);
                            half1.y =getPt(b.y, points[i+0].y, 0.33);
                            
                            half2.x = getPt(a.x, d.x, 0.5);
                            half2.y =getPt(a.y, d.y, 0.5);
                            
                            half3.x = getPt(c.x, points[i+3].x, 0.33);
                            half3.y =getPt(c.y, points[i+3].y, 0.33);
                            colormode = 4;
                            if(set == 0)
                            {
                                lineDDA(half1.x, half1.y, half2.x, half2.y);
                                lineDDA(half2.x, half2.y, half3.x, half3.y);
                                
                                lineDDA(half1.x, half1.y, e.x, e.y);
                            }
                            
                            lineDDA(half3.x, half3.y, f.x, f.y);
                            colormode = 0;

                            
                            
                            
                            
                            a.x = getPt(points[i+0].x, points[i+1].x, 1.9);
                            a.y = getPt(points[i+0].y, points[i+1].y, 1.9); // 1 up
                            
                            b.x = getPt(points[i+2].x, points[i+1].x, 1.3);
                            b.y = getPt(points[i+2].y, points[i+1].y, 1.3); // 1 left
                            
                            c.x = getPt(points[i+1].x, points[i+2].x, 1.3);
                            c.y = getPt(points[i+1].y, points[i+2].y, 1.3); //2 right
                            
                            d.x = getPt(points[i+3].x, points[i+2].x, 1.9);
                            d.y = getPt(points[i+3].y, points[i+2].y, 1.9); // 2 up
                            
                            e.x = getPt(b.x, points[i+0].x, 1.3);
                            e.y = getPt(b.y, points[i+0].y, 1.3);
                            
                            f.x = getPt(c.x, points[i+3].x, 1.3);
                            f.y = getPt(c.y, points[i+3].y, 1.3);
                            
                            half1.x = getPt(b.x, points[i+0].x, 0.33);
                            half1.y =getPt(b.y, points[i+0].y, 0.33);
                            
                            half2.x = getPt(a.x, d.x, 0.5);
                            half2.y =getPt(a.y, d.y, 0.5);
                            
                            half3.x = getPt(c.x, points[i+3].x, 0.33);
                            half3.y =getPt(c.y, points[i+3].y, 0.33);
                            colormode = 2;
                            if(set == 0)
                            {
                                lineDDA(half1.x, half1.y, half2.x, half2.y);
                                lineDDA(half2.x, half2.y, half3.x, half3.y);
                                
                                lineDDA(half1.x, half1.y, e.x, e.y);
                            }
                            
                            lineDDA(half3.x, half3.y, f.x, f.y);
                            colormode = 0;
                            
                            
                            
                                                        set++;
                            
                        }
                        /*
                        lineDDA(points[0].x, points[0].y, a.x, a.y);
                        lineDDA(points[2].x, points[2].y, b.x, b.y);
                        lineDDA(points[1].x, points[1].y, c.x, c.y);
                        lineDDA(points[3].x, points[3].y, d.x, d.y);
                        lineDDA(a.x, a.y, b.x, b.y);
                        lineDDA(c.x, c.y, d.x, d.y);
                        
                        lineDDA(b.x, b.y, e.x, e.y); //vector through first point
                         */
                    }//abc=2
                    
                    
                    if(c2 == 1)
                    {
                        float Tvalue, Tvalue2;
                        float total;
                        if(uniform == 1) //t = 1/3 * 2/3 = 1/2 = 0.5
                        {
                        Point temp, temp1, temp2, temp3;
                        temp.x = getPt(points[clicks-2].x, points[clicks-1].x, 1.5);
                        temp.y = getPt(points[clicks-2].y, points[clicks-1].y, 1.5);
                        temp1.x = getPt(points[clicks-3].x, points[clicks-2].x, 1.5);
                        temp1.y = getPt(points[clicks-3].y, points[clicks-2].y, 1.5);
                        temp2.x = getPt(temp1.x, temp.x, 1.5);
                        temp2.y = getPt(temp1.y, temp.y, 1.5);
                        temp3.x = temp2.x-20;
                        temp3.y = temp2.y;
                        
                        colormode = 1;
                        lineDDA(points[clicks-1].x, points[clicks-1].y, temp.x, temp.y);
                        lineDDA(points[clicks-2].x, points[clicks-2].y, temp1.x, temp1.y);
                        lineDDA(temp1.x, temp1.y, temp2.x, temp2.y);
                        colormode = 0;
                        
                        cubicBezier(points[clicks-1].x, points[clicks-1].y, temp.x, temp.y, temp2.x, temp2.y, temp3.x, temp3.y);
                        }
                        else if (chordLength == 1)
                        {
                            Point temp, temp1, temp2, temp3;
                            float T;
                            total =sqrt((points[1].x-points[0].x)*(points[1].x-points[0].x)+
                                        (points[1].y-points[0].y)*(points[1].y-points[0].y))
                            + (sqrt((points[2].x-points[1].x)*(points[2].x-points[1].x)+
                                        (points[2].y-points[1].y)*(points[2].y-points[1].y)))
                            + (sqrt((points[3].x-points[2].x)*(points[3].x-points[2].x)+
                                        (points[3].y-points[2].y)*(points[3].y-points[2].y)));
                            Tvalue = sqrt((points[1].x-points[0].x)*(points[1].x-points[0].x)+
                                          (points[1].y-points[0].y)*(points[1].y-points[0].y))/total;
                            Tvalue2= sqrt((points[2].x-points[1].x)*(points[2].x-points[1].x)+
                                          (points[2].y-points[1].y)*(points[1].y-points[1].y))/total;
                            T = Tvalue/Tvalue2;
                            temp.x = getPt(points[clicks-2].x, points[clicks-1].x, 1+T);
                            temp.y = getPt(points[clicks-2].y, points[clicks-1].y, 1+T);
                            temp1.x = getPt(points[clicks-3].x, points[clicks-2].x, 1+T);
                            temp1.y = getPt(points[clicks-3].y, points[clicks-2].y, 1+T);
                            temp2.x = getPt(temp1.x, temp.x, 1+T);
                            temp2.y = getPt(temp1.y, temp.y, 1+T);
                            temp3.x = temp2.x-20;
                            temp3.y = temp2.y;
                            
                            colormode = 1;
                            lineDDA(points[clicks-1].x, points[clicks-1].y, temp.x, temp.y);
                            lineDDA(points[clicks-2].x, points[clicks-2].y, temp1.x, temp1.y);
                            lineDDA(temp1.x, temp1.y, temp2.x, temp2.y);
                            colormode = 0;
                            
                            cubicBezier(points[clicks-1].x, points[clicks-1].y, temp.x, temp.y, temp2.x, temp2.y, temp3.x, temp3.y);
                        }
                        else if (centripetal == 1)
                        {
                            Point temp, temp1, temp2, temp3;
                            //found t1's centr t value
                            float T;
                            total = sqrt(sqrt((points[1].x-points[0].x)*(points[1].x-points[0].x)+
                                         (points[1].y-points[0].y)*(points[1].y-points[0].y)))
                                + sqrt(sqrt((points[2].x-points[1].x)*(points[2].x-points[1].x)+
                                   (points[2].y-points[1].y)*(points[2].y-points[1].y)))
                                + sqrt(sqrt((points[3].x-points[2].x)*(points[3].x-points[2].x)+
                                   (points[3].y-points[2].y)*(points[3].y-points[2].y)));
                            
                            Tvalue = sqrt(sqrt((points[1].x-points[0].x)*(points[1].x-points[0].x)+
                                          (points[1].y-points[0].y)*(points[1].y-points[0].y)))/total;
                            Tvalue2= sqrt(sqrt((points[2].x-points[1].x)*(points[2].x-points[1].x)+
                                          (points[2].y-points[1].y)*(points[1].y-points[1].y)))/total;
                            T = Tvalue/Tvalue2;
                            
                            temp.x = getPt(points[clicks-2].x, points[clicks-1].x, 1+T);
                            temp.y = getPt(points[clicks-2].y, points[clicks-1].y, 1+T);
                            temp1.x = getPt(points[clicks-3].x, points[clicks-2].x, 1+T);
                            temp1.y = getPt(points[clicks-3].y, points[clicks-2].y, 1+T);
                            temp2.x = getPt(temp1.x, temp.x, 1+T);
                            temp2.y = getPt(temp1.y, temp.y, 1+T);
                            temp3.x = temp2.x-20;
                            temp3.y = temp2.y;
                            
                            colormode = 1;
                            lineDDA(points[clicks-1].x, points[clicks-1].y, temp.x, temp.y);
                            lineDDA(points[clicks-2].x, points[clicks-2].y, temp1.x, temp1.y);
                            lineDDA(temp1.x, temp1.y, temp2.x, temp2.y);
                            colormode = 0;
                            
                            cubicBezier(points[clicks-1].x, points[clicks-1].y, temp.x, temp.y, temp2.x, temp2.y, temp3.x, temp3.y);
                        }

                    }//c2=1

                    clicks++; //for continuous
                    
                    
                }
                
                else if(C1MODE == 2)
                {
                    
                    called++;
                    
                    //code from internet
                    printf("\nCalculating Interpolating Form...\n");
                    
                    float bu[clicks];
                    
                    Point pp = points[counter];
                    
                    for (int uInt = 0; uInt <= 100; uInt++) //100 points
                    {
                        float u = uInt/(float)100;
                        bu[counter+0] = (-9.0/2.0)*(u-(1.0/3.0))*(u-(2.0/3.0))*(u-1.0);
                        bu[counter+1] = (27.0/2.0)*u*(u-(2.0/3.0))*(u-1.0);
                        bu[counter+2] = (-27.0/2.0)*u*(u-(1.0/3.0))*(u-1.0);
                        bu[counter+3] = (9.0/2.0)*u*(u-(1.0/3.0))*(u-(2.0/3.0));
                        
                        float x = 0.0;
                        float y = 0.0;
                        Point ppp;
                        
                        for (int i = counter; i < counter+4; i++)
                        {
                            x += bu[i]*points[i].x;//ctrlPoints[i][0];
                            y += bu[i]*points[i].y;//ctrlPoints[i][1];
                            
                            
                        }
                        if(//array1[arrayCount].x == 0)
                           (arrayCount >=166 && called == 2) || called ==1 || (arrayCount >=268 && called == 3) || (arrayCount >=370 && called == 4) || (arrayCount >=470 && called == 5)
                           || (arrayCount >=571 && called == 6) || (arrayCount >=673 && called == 7)
                           || (arrayCount >=774 && called == 8) || (arrayCount >=874 && called == 9)
                           || (arrayCount >=975 && called == 10))
                        {
                            array1[arrayCount].x = x;
                            array1[arrayCount].y = y; //store x and y value
                            
                        }
                        ppp.x = x;
                        ppp.y = y;
                        
                        printf("x=%g  y=%g\n", x, y);
                        
                        
                        
                        pp = ppp;
                        
                        
                        arrayCount++;
                    }
                    
                    clicks++; //for continuous
                    counter++; //for creating interpolations
                    
                    
                }
                else
                    ptsCreated = 0;
                if(C1MODE == 1)
                {
                    for(int i = 0; i < arrayCount-1; i++)
                    { //return to this
                        
                        if(array1[i+1].x == 0||array1[i].x == 0){
                            
                            //array1[i].x = array1[i+1].x;
                            //array1[i].y = array1[i+1].y;
                            setPixel5(array1[i].x , array1[i].y);
                        }
                        else
                            drawLine2(array1[i], array1[i+1]);//array1[i] = array1[i+1];
                        
                    }
                }
                
                
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
            for(index = 0; index < clicks-1; index++)
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
                //for(int i = 0; i < ptsCreated; i++)
                  //  std::cout<< "New Point: " <<points[i].x << " " << points[i].y<<std::endl;
                
                
                for(int j = 0; j < 500*500*3; j++)
                    PixelBuffer[j] = 0; // clear buff
                
                if (c2 == 2) //de boors
                {
                    if(k < 2)
                    {
                        for(int j = 0; j < 500*500*3; j++)
                            PixelBuffer[j] = 0; // clear buff
                        drawLine(points[0], points[clicks-2]);
                        
                        cout << "k is less than 2.\nPlease increase k value!" << endl;
                        
                    }
                    if(k >= 2)
                    {
                        for(int j = 0; j < 500*500*3; j++)
                            PixelBuffer[j] = 0; // clear buff
                    for(int k=0;k<clicks-2;k++)
                    {
                        drawLine(points[k], points[k+1]);
                    }
                        if(k == 3 || k >= 5) //quadratic
                        {
                        Point temp,temp1;
                        Point tmp,tmp1;
                        for( int i = 0; i < clicks-3 ; i++)
                        {
                        temp.x = getPt(points[i].x, points[i+1].x, 0.5);
                        temp.y = getPt(points[i].y, points[i+1].y, 0.5);
                        temp1.x = getPt(points[i+1].x, points[i+2].x, 0.5);
                        temp1.y = getPt(points[i+1].y, points[i+2].y, 0.5);
                            tmp.x = getPt(temp.x, points[i+1].x, 0.5);
                            tmp.y = getPt(temp.y, points[i+1].y, 0.5);
                            tmp1.x = getPt(points[i+1].x, temp1.x, 0.5);
                            tmp1.y = getPt(points[i+1].y, temp1.y, 0.5);
                        quadraticBezier(temp.x, temp.y, points[i+1].x, points[i+1].y, temp1.x, temp1.y);
                            colormode =2;
                            lineDDA(tmp.x, tmp.y, tmp1.x, tmp1.y);
                            colormode =0;
                        }
                        }//k = 3
                        
                        if(k == 4)
                        {
                            for( int i = 0; i < clicks-4 ; i++)
                            {
                            Point temp,temp1, temp2;
                            Point tmp,tmp1,tmp2;
                            Point tempp,tempp1;
                                Point tt,tt1;
                                tt.x = getPt(points[i+0].x, points[i+1].x, 0.45);
                                tt.y = getPt(points[i+0].y, points[i+1].y, 0.45);//.5
                                tt1.x = getPt(points[i+2].x, points[i+3].x, 0.47);
                                tt1.y = getPt(points[i+2].y, points[i+3].y, 0.47);

                            temp.x = getPt(points[i+0].x, points[i+1].x, 0.75);
                            temp.y = getPt(points[i+0].y, points[i+1].y, 0.75);
                            temp1.x = getPt(points[i+1].x, points[i+2].x, 0.5);
                            temp1.y = getPt(points[i+1].y, points[i+2].y, 0.5);
                            colormode = 2;
                            lineDDA(temp.x, temp.y, temp1.x, temp1.y);
                            temp2.x= getPt(points[i+2].x, points[i+3].x, 0.25);
                            temp2.y = getPt(points[i+2].y, points[i+3].y, 0.25);
                            lineDDA(temp1.x, temp1.y, temp2.x, temp2.y);
                            
                            tmp.x = getPt(temp.x, temp1.x, 0.66);
                            tmp.y = getPt(temp.y, temp1.y, 0.66);
                            tmp1.x = getPt(temp1.x, temp2.x, 0.33);
                            tmp1.y = getPt(temp1.y, temp2.y, 0.33);
                            tmp2.x = getPt(tmp.x, tmp1.x, 0.5);
                            tmp2.y = getPt(tmp.y, tmp1.y, 0.5);
                            colormode = 1;
                            lineDDA(tmp.x, tmp.y, tmp1.x, tmp1.y);
                            colormode = 0;
                            
                            tempp.x = getPt(tt.x,//points[i+0].x,
                                            tmp.x, 0.75);
                            tempp.y = getPt(tt.y,//points[i+0].y,
                                            tmp.y, 0.75);
                            //lineDDA(points[0].x, points[0].y, tempp.x, tempp.y);
                            tempp1.x = getPt(tmp1.x, tt1.x,//points[i+3].x,
                                             0.45);
                            tempp1.y = getPt(tmp1.y, tt1.y,//points[i+3].y,
                                             0.45);
                            //lineDDA(tmp1.x, tmp1.y, tempp1.x, tempp1.y);
                            
                            quadraticBezier(tempp.x, tempp.y, tmp.x, tmp.y, tmp2.x, tmp2.y);
                            quadraticBezier(tmp2.x, tmp2.y, tmp1.x, tmp1.y, tempp1.x, tempp1.y);
                            }
                        }
                    }
                    
                } //c2 = 2
                else{
                
                if(calc==3)
                {
                    points[index].x = points[index+1].x;
                    points[index].y = points[index+1].y;
                    //clicks--;
                }
                for(int k=0;k<clicks-1;k++)
                {
                    
                    drawLine(points[k], points[k+1]);
                }
                Point p1 = points[0];
                
                for(double t = 0.0;t <= 1.0; t += 0.02)
                {
                    
                    Point p2 = drawBezierGeneralized(points,t);
                    drawLine1(p1, p2);
                    p1 = p2;
                }
            }
            
            
            
            if (calc == 1) // aitkens
            {
                for(int j = 0; j < 500*500*3; j++)
                    PixelBuffer[j] = 0; // clear buff
                
                for (float j = 50; j < 65; j+=1) //slider indicator
                    setPixel1(x,j);
                
                
                float percentSlider = x/300.0;
                
                t=1;
                t = t*percentSlider;
                //cout << t << endl;
                //cout << (points[2].x+points[1].x)*t << endl;
                //cout << (points[2].y+points[1].y)*t << endl;
                lineDDA(0, 50, 300, 50);
                lineDDA(0, 50, 0, 65);
                lineDDA(0, 65, 300, 65);
                lineDDA(300, 50, 300, 65);
                
                
                float bu[4];
                
                Point pp = points[0];
                
                for (int uInt = 0; uInt <= 100; uInt++) //100 points
                {
                    float u = uInt/(float)100;
                    bu[counter2+0] = (-9.0/2.0)*(u-(1.0/3.0))*(u-(2.0/3.0))*(u-1.0);
                    bu[counter2+1] = (27.0/2.0)*u*(u-(2.0/3.0))*(u-1.0);
                    bu[counter2+2] = (-27.0/2.0)*u*(u-(1.0/3.0))*(u-1.0);
                    bu[counter2+3] = (9.0/2.0)*u*(u-(1.0/3.0))*(u-(2.0/3.0));
                    
                    float x = 0.0;
                    float y = 0.0;
                    Point ppp;
                    for (int i = 0; i < 4; i++)
                    {
                        x += bu[i]*points[i].x;//ctrlPoints[i][0];
                        y += bu[i]*points[i].y;//ctrlPoints[i][1];
                    }
                    ppp.x = x;
                    ppp.y = y;
                    
                    //printf("x=%g  y=%g\n", x, y);
                    drawLine1(pp,ppp);//setPixel5(x, y);
                    pp = ppp;
                    
                    
                    
                }
                // clicks++; //for continuous
                //counter2++; //for creating interpolations
                Point a,b,c,d,e;
                cout << t << endl;
                //float slope = (points[1].y-points[0].y)/(points[1].x-points[0].x);
                if(t >= 0 && t <= 1)
                {
                    a.x = getPt(points[0].x, points[1].x, 1+t) ;
                    a.y = getPt(points[0].y, points[1].y, 1+t) ;
                    drawLine2(points[0], a);
                    b.x = getPt(points[1].x, points[2].x, t) ;
                    b.y = getPt(points[1].y, points[2].y, t) ;
                    drawLine2(a,b);
                    c.x = getPt(points[2].x, points[3].x, t-1) ;
                    c.y = getPt(points[2].y, points[3].y, t-1) ;
                    drawLine2(points[3], c);
                    drawLine2(c,b);
                    d.x = getPt(a.x, b.x, 0.75) ;
                    d.y = getPt(a.y, b.y, 0.75) ;
                    e.x = getPt(c.x, b.x, 0.75) ;
                    e.y = getPt(c.y, b.y, 0.75) ;
                    drawLine2(d, e);
                }
                if(t > 1 && t <= 2)
                {
                    a.x = getPt(points[0].x, points[1].x, 1+t) ;
                    a.y = getPt(points[0].y, points[1].y, 1+t) ;
                    drawLine2(points[0], a);
                    b.x = getPt(points[1].x, points[2].x, t) ;
                    b.y = getPt(points[1].y, points[2].y, t) ;
                    drawLine2(a,b);
                    c.x = getPt(points[2].x, points[3].x, t-1) ;
                    c.y = getPt(points[2].y, points[3].y, t-1) ;
                    drawLine2(points[3], c);
                    drawLine2(c,b);
                    d.x = getPt(a.x, b.x, 0.75) ;
                    d.y = getPt(a.y, b.y, 0.75) ;
                    e.x = getPt(c.x, b.x, 0.25) ;
                    e.y = getPt(c.y, b.y, 0.25) ;
                    drawLine2(d, e);
                }
                if(t < 0 && t >=-1)
                {
                    a.x = getPt(points[0].x, points[1].x, 1+t) ;
                    a.y = getPt(points[0].y, points[1].y, 1+t) ;
                    drawLine2(points[0], a);
                    b.x = getPt(points[1].x, points[2].x, t) ;
                    b.y = getPt(points[1].y, points[2].y, t) ;
                    drawLine2(a,b);
                    c.x = getPt(points[2].x, points[3].x, t-1) ;
                    c.y = getPt(points[2].y, points[3].y, t-1) ;
                    drawLine2(points[3], c);
                    drawLine2(c,b);
                    d.x = getPt(a.x, b.x, 0.15) ;
                    d.y = getPt(a.y, b.y, 0.15) ;
                    e.x = getPt(c.x, b.x, 0.75) ;
                    e.y = getPt(c.y, b.y, 0.75) ;
                    drawLine2(d, e);
                }
                //f.x = getPt(points[1].x, points[2].x, t) ;
                //f.y = getPt(points[1].y, points[2].y, t) ;
                
                colormode=0;
                
                
                for(int k=0;k<clicks-1;k++)
                    drawLine(points[k], points[k+1]);
                Point p1 = points[0];
                
                for(double t = 0.0;t <= 1.0; t += 0.02)
                {
                    
                    Point p2 = drawBezierGeneralized(points,t);
                    //drawLine1(p1, p2);
                    p1 = p2;
                }
                //ptsCreated=0;
                
            }
            //part c, subivide into two
            if(calc == 2)
            {
                
                
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
                
                
                fiveptBezier(dx,dy,cx,cy,cx1,cy1,ax3, ay3,//bx2, by2,
                             points[4].x, points[4].y);
                
            }//calc
        }//else if
        
    } //else if mode = 2
    else if(mode == 3)
    {
        cout << "HI";
        
    }//mode = 3
    }//else
    glutPostRedisplay();
    glFlush();
}

void createMenu()
{
    //submenu
    SubMenu = glutCreateMenu(processMenu);
    glutAddMenuEntry("Raise by 1", 7);
    glutAddMenuEntry("Raise by n", 10);
    glutAddMenuEntry("Reduce by 1", 8);
    
    SubMenu2 = glutCreateMenu(processMenu);
    glutAddMenuEntry("Uniform", 15);
    glutAddMenuEntry("Chord Length", 16);
    glutAddMenuEntry("Centripetal", 17);
    
    
    
    glutCreateMenu(processMenu);
    glutAddMenuEntry("Input Mode", 1);
    glutAddMenuEntry("Edit Mode", 2);
    glutAddMenuEntry("Delete Mode", 5);
    //glutAddMenuEntry("Part C", 6);
    //glutAddMenuEntry("Degree Raise", 7);
    glutAddMenuEntry("Clear", 9);
    
    glutAddSubMenu("Degree Change", SubMenu);
    glutAddSubMenu("Parametrization Type", SubMenu2);
    glutAddMenuEntry("Aitken's Interpolation", 11);
    glutAddMenuEntry("C1 Piecewise Interpolation", 12);
    glutAddMenuEntry("C1 Manual Piecewise Interpolation", 13);
    glutAddMenuEntry("C2 Piecewise Interpolation", 14);
    glutAddMenuEntry("De Boor's Algorithm", 18);
    glutAddMenuEntry("C1 Piecewise Quadratic B-Spline", 19);
    glutAddMenuEntry("Exit", 0);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}



Point Aitkens(float t0, float t1, float t, int numPt)
{
    Point retP;
    retP.x = (t1-t)/(t1-t0)*points[numPt].x + (t-t0)/(t1-t0)*points[numPt+1].x;
    retP.y = (t1-t)/(t1-t0)*points[numPt].y + (t-t0)/(t1-t0)*points[numPt+1].y;
    //setPixel3(retP.x, retP.y);
    drawLine2(points[0], retP);
    return retP;
}

Point Aitkens2(float t0, float t1,Point p0,Point p1, float t)
{
    Point retP;
    retP.x = (t1-t)/(t1-t0)*p0.x + (t-t0)/(t1-t0)*p1.x;
    retP.y = (t1-t)/(t1-t0)*p0.y + (t-t0)/(t1-t0)*p1.y;
    //drawLine1(t0, t1);
    //setPixel3(retP.x, retP.y);
    return retP;
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
        C1MODE = 1;
        //		ptsCreated = 0;
        glFlush();
        glutMouseFunc(processMouseClick);
    }
    else if(value == 2)
    {
        mode = 2;
        glutMouseFunc(processMouseClick);
    }
    else if (value == 5)
    {
        mode = 2;
        calc = 3;
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
        Point copy[100];
        clicks = clicks+1; // first time = 5
        ptsCreated += 1;
        int var = clicks; // 5
        for(int j = 0; j < clicks-1; j++)
        {
            copy[j].x = points[j].x;
            copy[j].y = points[j].y;
        }
        points[clicks-1].x = points[clicks-2].x;
        points[clicks-1].y = points[clicks-2].y;
        for(int i = 1; i < clicks-1; i++)
        {
            var-=1;
            points[i].x = getPt(copy[i-1].x, copy[i].x,((float)var/(float)clicks));
            points[i].y = getPt(copy[i-1].y, copy[i].y,((float)var/(float)clicks));
            
        }
        
        for(int k=0;k<clicks-1;k++)
            drawLine(points[k], points[k+1]);
        Point p1 = points[0];
        for(double t = 0.0;t <= 1.0; t += 0.02)
        {
            
            Point p2 = drawBezierGeneralized(points,t);
            drawLine1(p1, p2);
            p1 = p2;
        }
        cout << "Current Degree: " << clicks-1 << endl;
        ptsCreated=0;
        
        glutMouseFunc(processMouseClick);
    }
    
    else if(value == 10) // raise by n
    {
        mode = 1;
        int n;
        cin >> n;
        Point copy[100];
        for(int p = 0; p < n; p++)
        {
            clicks = clicks+1; // first time = 5
            ptsCreated += 1;
            int var = clicks; // 5
            for(int j = 0; j < clicks-1; j++)
            {
                copy[j].x = points[j].x;
                copy[j].y = points[j].y;
            }
            points[clicks-1].x = points[clicks-2].x;
            points[clicks-1].y = points[clicks-2].y;
            for(int i = 1; i < clicks-1; i++)
            {
                var-=1;
                points[i].x = (float)getPt(copy[i-1].x, copy[i].x,((float)var/(float)clicks));
                points[i].y = (float)getPt(copy[i-1].y, copy[i].y,((float)var/(float)clicks));
                cout <<points[i].x << "," << points[i].y << endl;
            }
            
            for(int k=0;k<clicks-1;k++)
                drawLine(points[k], points[k+1]);
            Point p1 = points[0];

            for(double t = 0.0;t <= 1.0; t += 0.02)
            {
                
                Point p2 = drawBezierGeneralized(points,t);
                drawLine1(p1, p2);
                p1 = p2;
            }
            
            cout << "Current Degree: " << clicks-1 << endl;
            //ptsCreated=0;
        }
        glutMouseFunc(processMouseClick);
        
    }
    else if(value == 8)
    {
        mode = 1;
        Point copy[100],copy2[100],copy3[100];
        for(int j = 0; j < clicks; j++)
        {
            copy[j].x = points[j].x;
            copy[j].y = points[j].y;
            copy2[j].x = points[j].x;
            copy2[j].y = points[j].y;
            copy3[j].x = points[j].x;
            copy3[j].y = points[j].y;
        }
        
        clicks = clicks-1; // first time = 3
        ptsCreated -= 1;
        int var = clicks;//clicks; // 3
        int var2 = 0;
        
        
        
        for(int i = 0; i < clicks-1; i++)
        {
            
            copy2[i].x = ((float)(clicks)/(float)(var))*copy[i].x - (float)(var2)/(float)(var)*copy[i-1].x;
            copy2[i].y = ((float)(clicks)/(float)(var))*copy[i].y - (float)(var2)/(float)(var)*copy[i-1].y;
            
            var-=1;
            var2+=1;
        }
        
        copy2[clicks-1].x = ((float)(clicks)/(float)(var))*copy[clicks-1].x - (float)(var2)/(float)(var)*points[clicks-2].x;//endpoint is now 2nd to end
        copy2[clicks-1].y = ((float)(clicks)/(float)(var))*copy[clicks-1].y - (float)(var2)/(float)(var)*points[clicks-2].y;
        
        var = clicks;
        var2 = 0;
        copy3[clicks-1].x = copy[clicks].x;
        copy3[clicks-1].y = copy[clicks].y;
        for(int i = 0; i < clicks-1; i++)
        {
            var-=1; //2,1
            var2+=1; //1,2
            copy3[i].x = ((float)(clicks)/(float)(var2))*copy[i+1].x - (float)(var)/(float)(var2)*copy3[i+1].x;
            copy3[i].y = ((float)(clicks)/(float)(var2))*copy[i+1].y - (float)(var)/(float)(var2)*copy3[i+1].y;
            
        }
        
        
        copy3[0].x = clicks*copy[1].x - (clicks-1)*copy3[1].x;
        copy3[0].y = clicks*copy[1] .y - (clicks-1)*copy3[1].y;
        
        //take the average
        for(int i = 1; i < clicks-1; i++)
        {
            points[i].x = (copy2[i].x + copy3[i].x)/2;
            points[i].y = (copy2[i].y + copy3[i].y)/2;
        }
        points[clicks-1].x = copy[clicks].x;
        points[clicks-1].y = copy[clicks].y;
        points[0].x = copy[0].x;
        points[0].y = copy[0].y;
        
        
        if(clicks == 2)
            cout << "Cannot draw Degree 2 Bezier Curve!" << endl;
        else if(clicks >2)
        {
            for(int k=0;k<clicks-1;k++)
                drawLine(points[k], points[k+1]);
            Point p1 = points[0];

            for(double t = 0.0;t <= 1.0; t += 0.02)
            {
                
                Point p2 = drawBezierGeneralized(points,t);
                drawLine1(p1, p2);
                p1 = p2;
            }
            cout << "Current Degree: " << clicks-1 << endl;
            ptsCreated=0;
        }
        
        glutMouseFunc(processMouseClick);
    }
    else if(value == 9)
    {
        for(int j = 0; j < 500*500*3; j++)
            PixelBuffer[j] = 0; // clear buff
        ptsCreated = 0;
        calc = 0;
        C1MODE = 0;
        clicks = 4;
        called = 0;
        
    }
    
    else if(value == 11) // Aitken's
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
    
    else if(value == 12)
    {
        mode = 1;
        C1MODE = 1;
        abc = 1;
        initArray();
        glutMouseFunc(processMouseClick);
    }
    else if(value == 13)
    {
        mode = 1;
        C1MODE = 2;
        initArray();
        glutMouseFunc(processMouseClick);
    }
    else if(value == 14)
    {
        mode = 1;
        C1MODE = 1;
        c2 = 1;
        initArray();
        glutMouseFunc(processMouseClick);
    }
    else if(value == 15) //uniform
    {
        uniform = 1;
        chordLength = 0;
        centripetal = 0;
        mode = 1;
        C1MODE = 1;
        c2 = 1;
        initArray();
        glutMouseFunc(processMouseClick);
    }
    else if(value == 16) // chord length
    {
        chordLength = 1;
        centripetal = 0;
        uniform = 0;
        mode = 1;
        C1MODE = 1;
        c2 = 1;
        initArray();
        glutMouseFunc(processMouseClick);
    }
    else if(value == 17) //centripetal
    {
        centripetal = 1;
        uniform = 0;
        chordLength = 0;
        mode = 1;
        C1MODE = 1;
        c2 = 1;
        initArray();
        glutMouseFunc(processMouseClick);
    }
    else if(value == 18) //de boors
    {
        k = 2;
        mode = 2;
        C1MODE = 1;
        c2 = 2;
        initArray();
        glutMouseFunc(processMouseClick);
    }
    else if(value == 19) //bspline
    {
        mode = 1;
        C1MODE = 1;
        abc = 2;
        initArray();
        glutMouseFunc(processMouseClick);
    }
    
    
    glutPostRedisplay();
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

static void SpecialKeyFunc( int Key, int x, int y )
{
    switch ( Key ) {

        case GLUT_KEY_UP:
            k++;
            cout << "k = " << k << endl;
            mode = 2;
            glutMouseFunc(processMouseClick);
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            k--;
            cout << "k = " <<k << endl;
            mode = 2;
            glutMouseFunc(processMouseClick);
            glutPostRedisplay();
            break;
            
    }
}
int main(int argc, char *argv[])
{
    
    PixelBuffer = new float[500 * 500 * 3];
    *PixelBuffer = 0;
    
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    
    MainWindow = glutCreateWindow("Program 2");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glutDisplayFunc(display);

    //        createMenu();
    glutMouseFunc(processMouseClick);
    glutSpecialFunc( SpecialKeyFunc );
    glutMotionFunc(motion);
    //glutMotionFunc(processMouseClick);
    createMenu();
    
    glutMainLoop();
    
    return 0;
}



