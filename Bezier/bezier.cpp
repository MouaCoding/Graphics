#include <GLUT/GLUT.h>
#include <iostream>
#include<cmath>
#include<fstream>
#include <unistd.h>
using namespace std;

void display();

int ptsCreated = 0;

struct Point
{
    int x;
    int y;
};
int newmode = 1;
int mode = -1;
Point points[100]; //input points
bool edit = 0; //edit mode on/off
int oldx = -1, oldy = -1, newx = -1, newy = -1;
int SubMenu;  //a submenu id is needed if you choose to implement a submenu
void createMenu();	//a function that creates menu
void processMenu(int value); //----Call back function---// As explained during discussion, this process menu operations
void processMouseClick(int button, int state, int x, int y); //----Call back function---// similar to menu processing, this process mouse click

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

//WORKS! 5 points
void fiveptBezier(int x1, int y1, int x2, int y2, int x3, int y3,
                  int x4, int y4, int x5, int y5)
{
    int x,y,xa, xb, xc, xd, ya, yb, yc, yd;
    int tmp1, tmp2, tmp3,tmp4,tmp5,tmp6;
    for( float i = 0 ; i < 1 ; i += 0.0001 )
    {
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
        
        //THIS IS A TEST, IT CONNECTS P0 TO P4 USING QUADRATIC BEZIER
        /*
         xa = getPt( x1 , x2 , i );
         ya = getPt( y1 , y2 , i );
         x = getPt( xa , xd , i );
         y = getPt( ya , yd , i );
         
         setPixel( x , y );
         */
    }
}

//4 points
void cubicBezier(int x1, int y1, int x2, int y2, int x3, int y3,
                 int x4, int y4)
{
    int x,y,xa, xb, xc, ya, yb, yc;
    int tmp1, tmp2, tmp3,tmp4;
    for( float i = 0 ; i < 1 ; i += 0.0001 )
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
        
        x = getPt( tmp1 , tmp2 , i );
        y = getPt( tmp3 , tmp4 , i );
        
        setPixel( x , y );
    }
}
//3 points
void quadraticBezier(int x1, int y1, int x2, int y2, int x3, int y3)
{
    int x,y,xa, xb, ya, yb;
    for( float i = 0 ; i < 1 ; i += 0.0001 )
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
    /*	glColor3f(1.0,0.0,0.0);
     glPointSize(3.0);
     for (int i = 0; i < ptsCreated; i++)
     {
     glBegin(GL_POINTS);
     glVertex2i(points[i].x,points[i].y);
     glEnd();
     }
     
     if(ptsCreated >= 5)
     {		fiveptBezier(points[0].x, points[0].y, points[1].x, points[1].y,
     points[2].x, points[2].y, points[3].x, points[3].y,
     points[4].x, points[4].y);
     }
     */	sleep(1);
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
            
            
            if(ptsCreated >= 5 && ptsCreated <10)
            {
                for(int i = 0; i < ptsCreated; i++)
                    std::cout<<"Points Created: " <<points[i].x << " "
                    << points[i].y<<std::endl;
                
                fiveptBezier(points[0].x, points[0].y, points[1].x, points[1].y,
                             points[2].x, points[2].y, points[3].x, points[3].y,
                             points[4].x, points[4].y);
               
            }
            if(ptsCreated >= 10 && ptsCreated < 15)
            {
                fiveptBezier(points[5].x, points[5].y,
                             points[6].x, points[6].y,
                             points[7].x, points[7].y,
                             points[8].x, points[8].y,
                             points[9].x, points[9].y);

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
                std::cout << "Clicked Point: " << index << std::endl;
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
                
                
                for(int i = 0; i < 25; i++)
                    setPixel1(points[i].x,points[i].y); //plot new point
                if(index == 0 )
                {
                    fiveptBezier(newx,newy,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                    
                }
                else if(index == 1)
                {
                    fiveptBezier(points[0].x,points[0].y,
                                 newx,newy,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 2)
                {
                    fiveptBezier(points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 newx,newy,points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 3)
                {
                    fiveptBezier(points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 newx,newy,points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 4)
                {
                    fiveptBezier(points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 newx,newy);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 5 )
                {
                    fiveptBezier(newx,newy,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 6)
                {
                    fiveptBezier(points[5].x,points[5].y,
                                 newx,newy,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 7)
                {
                    fiveptBezier(points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 newx,newy,points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 8)
                {
                    fiveptBezier(points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 newx,newy,points[9].x,points[9].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 9)
                {
                    fiveptBezier(points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 newx,newy);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                
                else if(index == 10 )
                {
                    fiveptBezier(newx,newy,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 11)
                {
                    fiveptBezier(points[10].x,points[10].y,
                                 newx,newy,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 12)
                {
                    fiveptBezier(points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 newx,newy,points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 13)
                {
                    fiveptBezier(points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 newx,newy,points[14].x,points[14].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 14)
                {
                    fiveptBezier(points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 newx,newy);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                
                else if(index == 15 )
                {
                    fiveptBezier(newx,newy,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 16)
                {
                    fiveptBezier(points[15].x,points[15].y,
                                 newx,newy,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 17)
                {
                    fiveptBezier(points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 newx,newy,points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 18)
                {
                    fiveptBezier(points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 newx,newy,points[19].x,points[19].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                }
                else if(index == 19)
                {
                    fiveptBezier(points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 newx,newy);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[20].x,points[20].y,
                                 points[21].x,points[20].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);                
                }
                
                else if(index == 20 )
                {
                    fiveptBezier(newx,newy,
                                 points[21].x,points[21].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);                
                }
                else if(index == 21)
                {
                    fiveptBezier(points[20].x,points[20].y,
                                 newx,newy,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                }
                else if(index == 22)
                {
                    fiveptBezier(points[20].x,points[20].y,
                                 points[21].x,points[21].y,
                                 newx,newy,points[23].x,points[23].y,
                                 points[24].x,points[24].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                }
                else if(index == 23)
                {
                    fiveptBezier(points[20].x,points[20].y,
                                 points[21].x,points[21].y,
                                 points[22].x,points[22].y,
                                 newx,newy,points[24].x,points[24].y);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                }
                else if(index == 24)
                {
                    fiveptBezier(points[20].x,points[20].y,
                                 points[21].x,points[21].y,
                                 points[22].x,points[22].y,
                                 points[23].x,points[23].y,
                                 newx,newy);
                    fiveptBezier(
                                 points[0].x,points[0].y,
                                 points[1].x,points[1].y,
                                 points[2].x,points[2].y,
                                 points[3].x,points[3].y,
                                 points[4].x,points[4].y);
                    fiveptBezier(
                                 points[5].x,points[5].y,
                                 points[6].x,points[6].y,
                                 points[7].x,points[7].y,
                                 points[8].x,points[8].y,
                                 points[9].x,points[9].y);
                    fiveptBezier(
                                 points[10].x,points[10].y,
                                 points[11].x,points[11].y,
                                 points[12].x,points[12].y,
                                 points[13].x,points[13].y,
                                 points[14].x,points[14].y);
                    fiveptBezier(
                                 points[15].x,points[15].y,
                                 points[16].x,points[16].y,
                                 points[17].x,points[17].y,
                                 points[18].x,points[18].y,
                                 points[19].x,points[19].y);
                }
                
            }
            
            
        }}
    //}
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
    for(int j = 0; j < 25; j++){
        cout <<"Loaded Points: " << points[j].x << " " << points[j].y << endl;
        setPixel1(points[j].x,points[j].y);
    }
    fiveptBezier(points[0].x,points[0].y,
                 points[1].x,points[1].y,
                 points[2].x,points[2].y,
                 points[3].x,points[3].y,
                 points[4].x,points[4].y);	
    fiveptBezier(points[5].x,points[5].y,
                 points[6].x,points[6].y,
                 points[7].x,points[7].y,
                 points[8].x,points[8].y,
                 points[9].x,points[9].y);
    fiveptBezier(points[10].x,points[10].y,
                 points[11].x,points[11].y,
                 points[12].x,points[12].y,
                 points[13].x,points[13].y,
                 points[14].x,points[14].y);
    fiveptBezier(points[15].x,points[15].y,
                 points[16].x,points[16].y,
                 points[17].x,points[17].y,
                 points[18].x,points[18].y,
                 points[19].x,points[19].y);
    fiveptBezier(points[20].x,points[20].y,
                 points[21].x,points[21].y,
                 points[22].x,points[22].y,
                 points[23].x,points[23].y,
                 points[24].x,points[24].y);
    
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
    //SubMenu = glutCreateMenu(processMenu);
    
    glutCreateMenu(processMenu);
    glutAddMenuEntry("Input Mode", 1);
    glutAddMenuEntry("Edit Mode", 2);
    glutAddMenuEntry("Load", 3);
    glutAddMenuEntry("Save", 4);
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
int  main(int argc, char *argv[])
{
    
    PixelBuffer = new float[500 * 500 * 3];
    *PixelBuffer = 0;
    /*        for (int i = 0; i < 500 * 500 * 3; i++)
     {
     PixelBuffer[i] = 0;
     }
     */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    
    MainWindow = glutCreateWindow("Program 4");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glutDisplayFunc(display);
    
    //        createMenu();
    glutMouseFunc(processMouseClick);
    glutMotionFunc(motion);
    createMenu();
    
    glutMainLoop();
    return 0;
}

