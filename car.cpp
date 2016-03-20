#include <GLUT/GLUT.h>
//#include <GL/glut.h>
#include <iostream>
#include <math.h>

void display();
void f(int a);
int MainWindow;
float r,g,b;
GLuint Cube;
GLuint bigcube;
GLuint wheelerss;
GLuint tires;
GLfloat angle;
GLfloat tran;
GLfloat view = 0.5;
GLfloat view1 = 0.5;
GLfloat view2 = 0.2;
GLfloat vieww = 0.1;
GLfloat vieww1 = 0.5;
GLfloat vieww2 = 0.1;

 
using namespace std;
void keyboard(unsigned char key,int x, int y);
static void SpecialKeyFunc( int Key, int x, int y );


void drawcurve(float x1, float y1, float z1, float x2, float y2,float z2, float x3, float y3, float z3)
{
    //float curve[] = {1,1,1,1};
    //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,curve);
    glBegin(GL_LINE_STRIP);
    for(float t=0; t <= 2; t += 0.1) {
        float x = (1-t)*(1-t)*x1 + 2*(1-t)*t*x2 + t*t*x3;
        float y = (1-t)*(1-t)*y1 + 2*(1-t)*t*y2 + t*t*y3;
        float z = (1-t)*(1-t)*z1 + 2*(1-t)*t*z2 + t*t*z3;
        
        glVertex3f(x, y, z);
        
    }
    glEnd();
    
}



void land()
{


    
    float yellowroadline[] = {1,1,0,1.0};
    //road
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,yellowroadline);
    glTranslatef(0, -0.08, 0);
    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-2000.0,0.01,0.05);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-2000.0,0.01,0.1);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(2000.0,0.01,0.1);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(2000.0,0.01,0.05);
    glEnd();
    
    float GroundAmbDifff[] = {0,-2,0,1.0};
    //road
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,GroundAmbDifff);
    glTranslatef(0, -0.08, 0);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-2000.0,0.01,-1.0);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-2000.0,0.01,1.0);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(2000.0,0.01,1.0);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(2000.0,0.01,-1.0);
    glEnd();
    
    
    
    float GroundAmbDiff[] = {0.25, 0.5, 0.2,1.0};
    float GroundShiny = 20;
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,GroundAmbDiff);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,GroundAmbDiff);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,GroundShiny);
    //green landscape
    glTranslatef(0, -0.1, 0);
    glColor3f(0.25, 0.5, 0.2);
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-2000.0,0,-2000.0);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-2000.0,0,2000.0);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(2000.0,0,2000.0);
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(2000.0,0,-2000.0);
    glEnd();
    

    
    
    
    
    
}



void car(float i)
{
    
    //    float i = 0.03;
    r=0.95,g=0.09,b =0.09;
    bigcube = glGenLists(1);
    glNewList(bigcube, GL_COMPILE);
    glShadeModel(GL_SMOOTH);
    
    
    float CarAmbDiff[] = {5.67,0.047,0.047,1.0}; //red
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CarAmbDiff);
    
    //BOTTOM
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex3f(i+0.15, -i, -i);
    glVertex3f(i+0.15, -i, i);
    glVertex3f(-i+0.15, -i, i);
    glVertex3f(-i+0.15, -i, -i);
    glVertex3f(i-0.4, -i, -i+0.1);
    glVertex3f(i-0.4, -i, i-0.1);
    glVertex3f(-i-0.4, -i, i-0.1);
    glVertex3f(-i-0.4, -i, -i+0.1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex3f(i-0.7, -i, -i);
    glVertex3f(i-0.7, -i, i);
    glVertex3f(-0.6, -i, i);
    glVertex3f(-0.6, -i, -i);
    glEnd();
    
    float CarAmbDiff1[] = {1.67,0.047,0.047,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CarAmbDiff1);
    //Front, front of car
    glBegin(GL_POLYGON);
    glColor3f(0.7, g, b);
    glVertex3f(i-0.4, -i, i);
    glVertex3f(i-0.4, i-0.3, i);
    glVertex3f(-i-0.4, i-0.33, i);
    glVertex3f(-i-0.4, -i, i);
    glEnd();

    float CarAmbDiff2[] = {1.67,0.047,0.047,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CarAmbDiff2);
    //Front, back of car
    glBegin(GL_POLYGON);
    glColor3f(0.7, g, b);
    glVertex3f(i-0.4, -i, -i);
    glVertex3f(i-0.4, i-0.3, -i);
    glVertex3f(-i-0.4, i-0.33, -i);
    glVertex3f(-i-0.4, -i, -i);
    glEnd();
    
    

    float CarAmbDiff3[] = {1.67,0.047,0.047,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CarAmbDiff3);
    //  LEFT
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex3f(-i-0.4, -i, i);
    glVertex3f(-i-0.4, i-0.33, i);
    glVertex3f(-i-0.4, i-0.33, -i);
    glVertex3f(-i-0.4, -i, -i);
    glEnd();
    
    
    
    float CarAmbDiff4[] = {5.67,0.47,0.047,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CarAmbDiff4);
    // TOP
    
    glBegin(GL_POLYGON);
    glEnable(GL_BLEND);
    glColor4f(0, g, b, 1);
    glVertex3f(i-0.1, i-0.3, i);
    glVertex3f(i-0.1, i-0.3, -i);
    glVertex3f(-i-0.4, i-0.33, -i);
    glVertex3f(-i-0.4, i-0.33, i);
    glEnd();
    
    glBegin(GL_POLYGON);
    glEnable(GL_BLEND);
    glColor4f(0, g, b, 1);
    glVertex3f(i-0.2, i-0.15, i);
    glVertex3f(i-0.2, i-0.15, -i);
    glVertex3f(-i+0.1, i-0.15, -i);
    glVertex3f(-i+0.1, i-0.15, i);
    glEnd();
     
    
    //right, driver
    glBegin(GL_POLYGON);
    glEnable(GL_BLEND);
    glColor4f(0, g, b, 1);
    glVertex3f(i-0.2, i-0.15, i);
    glVertex3f(i-0.2, i-0.15, -i);
    glVertex3f(-i+0.55, i-0.4, -i);
    glVertex3f(-i+0.55, i-0.4, i);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.7, g, b);
    glVertex3f(i+0.15, i-0.3, i);
    glVertex3f(i+0.15, i-0.3, -i);
    glVertex3f(-i, i-0.3, -i);
    glVertex3f(-i, -i, i);
    glEnd();

    float CarAmbDiff5[] = {1.67,0.47,0.047,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CarAmbDiff5);
    // Blue side - TOP
    
    //bumper
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex3f(i+0.15, -i, -i);
    glVertex3f(i+0.15, i-0.3, -i);
    glVertex3f(i+0.15, i-0.3, i);
    glVertex3f(i+0.15, -i, i);
    glEnd();
    
    //front right, driver
    glBegin(GL_POLYGON);
    glColor3f(0.7, g, b);
    glVertex3f(i-0.2, -i, i);
    glVertex3f(i-0.2, i-0.15, i);
    glVertex3f(-i+0.55, i-0.4, i);
    glVertex3f(-i+0.55, -i, i);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.7, g, b);
    glVertex3f(i-0.2, -i, -i);
    glVertex3f(i-0.2, i-0.15, -i);
    glVertex3f(-i+0.55, i-0.4, -i);
    glVertex3f(-i+0.55, -i, -i);
    glEnd();
    
    //front body
    glBegin(GL_POLYGON);
    glColor3f(0.7, g, b);
    glVertex3f(i+0.15, -i, i);
    glVertex3f(i+0.15, i-0.3, i);
    glVertex3f(-i, i-0.3, i);
    glVertex3f(-i, -i, i);
    glEnd();
    



    
    //back body
    glBegin(GL_POLYGON);
    glColor3f(0.7, g, b);
    glVertex3f(i+0.15, -i, -i);
    glVertex3f(i+0.15, i-0.3, -i);
    glVertex3f(-i, i-0.3, -i);
    glVertex3f(-i, -i, -i);
    glEnd();
    


    
    glPushMatrix();
    float person[] = {0.07,0.47,0.747,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,person);
    GLdouble radius = 0.07;
    GLint slices = 10;
    GLint stacks = 10;
    glTranslatef(-0.05, -0.05, 0);
    glutSolidSphere(radius,slices, stacks);
    glPopMatrix();
    
    
    
    //left, driver
    glBegin(GL_POLYGON);
    glColor4f(0, g, b, 1);
    glVertex3f(i-0.4, i-0.3, i);
    glVertex3f(i-0.4, i-0.3, -i);
    glVertex3f(-i+0.1, i-0.15, -i);
    glVertex3f(-i+0.1, i-0.15, i);
    glEnd();
    
    
    //Accessories of car: muffler and spoiler
    //muffler
    glPushMatrix();
    float muffler[] = {0.8,0.8,0.8,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,muffler);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glColor3f(0,1,0);
    glTranslatef(0.27, -0.22, -0.1);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadratic,0.02f,0.02f,0.1f,32,32);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.27, -0.22, 0.1);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadratic,0.02f,0.02f,0.1f,32,32);
    glPopMatrix();
    
    //lights
    glPushMatrix();
    float lights[] = {6.0,3,0.0,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,lights);
    glTranslatef(0, 0.06, 0);
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex3f(i+0.151, -i, -i+0.3);
    glVertex3f(i+0.151, i-0.37, -i+0.3);
    glVertex3f(i+0.151, i-0.37, i);
    glVertex3f(i+0.151, -i, i);

    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.06, -0.3);
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex3f(i+0.151, -i, -i+0.3);
    glVertex3f(i+0.151, i-0.37, -i+0.3);
    glVertex3f(i+0.151, i-0.37, i);
    glVertex3f(i+0.151, -i, i);
    
    glEnd();
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(0, -0.1, -0.1);
     radius = 0.02;
     slices = 10;
     stacks = 10;
    glTranslatef(-0.6, -0.05, 0);
    glutSolidSphere(radius,slices, stacks);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -0.1, 0.1);
    radius = 0.02;
    slices = 10;
    stacks = 10;
    glTranslatef(-0.6, -0.05, 0);
    glutSolidSphere(radius,slices, stacks);
    glPopMatrix();
    
    


    //wheels
    
    
    float WheelAmbDiff[4][4] = {{0.2,0.2,0.2,1.0},
     {0.0,0.0,1.0,1.0},
     {0.0,1.0,1.0,1.0},
     {1.0,1.0,0.0,0.0}};
     float WheelSpec[] = {0.0,0.0,0.0,1.0};
     float WheelShiny = 2;
     glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,WheelAmbDiff[0]);
     glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,WheelSpec);
     glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,WheelShiny);
    
    
    glTranslatef(-0.6, -0.25, 0.2);
    wheelerss = glGenLists(1);
    glNewList(wheelerss, GL_COMPILE);
    
    glTranslatef(0.2,0,0);
    glColor3f(0,0,0);
    glutSolidTorus(0.025,0.07,10,25);
    
    glTranslatef(0,0,-0.4);
    glutSolidTorus(0.025,0.07,10,25);
    
    glTranslatef(0.5,0,0);
    glutSolidTorus(0.025,0.07,10,25);
    
    glTranslatef(0,0,0.4);
    glutSolidTorus(0.025,0.07,10,25);
    
    glEnd();



        land();


    
    glEndList();
    glLoadIdentity();
    //gluPerspective(120.0, 1.0, 0.0, 10.0);
    //gluLookAt(0, 0.0, 1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    
}
void cube(float i)
{
    //    float i = 0.03;
    Cube = glGenLists(1);
    glNewList(Cube, GL_COMPILE);
    
    float house[] = {1.7,1.0,0.17,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,house);
    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(0.55, 0.45, 0.1);
    glVertex3f(i, -i, -i);
    glVertex3f(i, -i, i);
    glVertex3f(-i, -i, i);
    glVertex3f(-i, -i, -i);
    glEnd();
    
    // White side - BACK
    glBegin(GL_POLYGON);
    
    glVertex3f(i, -i, i);
    glVertex3f(i, i, i);
    glVertex3f(-i, i, i);
    glVertex3f(-i, -i, i);
    glEnd();
    
    // RED side - FRONT
    glBegin(GL_POLYGON);
    
    glVertex3f(i, -i, -i);
    glVertex3f(i, i, -i);
    glVertex3f(-i, i, -i);
    glVertex3f(-i, -i, -i);
    glEnd();
    
    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    
    glVertex3f(i, -i, -i);
    glVertex3f(i, i, -i);
    glVertex3f(i, i, i);
    glVertex3f(i, -i, i);
    glEnd();
    
    // Green side - LEFT
    glBegin(GL_POLYGON);
    
    glVertex3f(-i, -i, i);
    glVertex3f(-i, i, i);
    glVertex3f(-i, i, -i);
    glVertex3f(-i, -i, -i);
    glEnd();
    
    //TOP
    glBegin(GL_POLYGON);
    
    glVertex3f(i, i, i);
    glVertex3f(i, i, -i);
    glVertex3f(-i, i, -i);
    glVertex3f(-i, i, i);
    glEnd();
    
    
    float roof[] = {0.0,0.0,0.17,1.0};
    //float roofShine = 20;
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,roof);
   //     glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,roofShine);
    //right top
    glBegin(GL_POLYGON);
    glColor4f(1, 1, 1, 1);
    glVertex3f(i, i, i);
    glVertex3f(i, i, -i);
    glVertex3f(-i+3, i+3.33, -i);
    glVertex3f(-i+3, i+3.33, i);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor4f(0, g, b, 1);
    glVertex3f(i-3, i+3.3, i);
    glVertex3f(i-3, i+3.3, -i);
    glVertex3f(-i, i, -i);
    glVertex3f(-i, i, i);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor4f(0, g, b, 1);
    glVertex3f(i, i, i);
    glVertex3f(i-3, i+3.3, -i);
    glVertex3f(-i, i, -i);
    glVertex3f(-i, i-0.33, i);
    glEnd();
    
    
    float windows[] = {5,5,5,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,windows);

    //left window
    glBegin(GL_POLYGON);
    glVertex3f(i-4, -i+5.5, i+0.1);
    glVertex3f(i-4, i-1, i+0.1);
    glVertex3f(-i+1, i-1, i+0.1);
    glVertex3f(-i+1, -i+5.5, i+0.1);
    glEnd();
    
    //right window
    glBegin(GL_POLYGON);
    glVertex3f(i-1, -i+5.5, i+0.1);
    glVertex3f(i-1, i-1, i+0.1);
    glVertex3f(-i+4, i-1, i+0.1);
    glVertex3f(-i+4, -i+5.5, i+0.1);
    glEnd();
    
    float door[] = {1.6,1.4,0.12,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,door);
    //door
    glBegin(GL_POLYGON);
    glVertex3f(i-2.5, -i+4, i+0.1);
    glVertex3f(i-2.5, i-4, i+0.1);
    glVertex3f(-i+2.5, i-4, i+0.1);
    glVertex3f(-i+2.5, -i+4, i+0.1);
    glEnd();
    

    glEndList();
    glLoadIdentity();
    //gluPerspective(120.0, 1.0, 0.0, 10.0);
    //gluLookAt(0, 0.0, 1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    
}


//TREES
void cylinder()
{
    glShadeModel(GL_SMOOTH);
    float trunk[] = {0.9f, 0.55f, 0.55f,1.0};
    float trunkSpec[] = {0.0,0.0,0.0,1.0};
    float trunkShiny = 20.0;
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,trunk);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,trunkSpec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,trunkShiny);
    
    GLdouble radius = 0.5;
    GLint slices = 10;
    GLint stacks = 10;
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glColor3f(0.5f, 0.35f, 0.05f);
    glTranslatef(0, -0.1, -2);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic,0.1f,0.1f,2.0f,32,32);
    
    float tree[] = {0.5f, 1.35f, 0.05f,1.0};
    float treeSpec[] = {0,0,0.0,1.0};
    float treeShiny = 20.0;
    //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,tree);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,tree);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,treeSpec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,treeShiny);
    glColor3f(0, 1, 0);
    glTranslatef(0, 0, 2);
    glutSolidSphere(radius,slices, stacks);
    
}

void house()
{
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(0, 0, -12);
    glTranslatef(tran, 0, 0);
    glCallList(Cube);
    glPopMatrix();
}

void car()
{

    //view2 = 0.0;
    glPushMatrix();
    //glTranslatef(0, 0, 0.1);
    //glTranslatef(-0.25, -0.25, 0); //translate right, then rotate
    //glRotatef(angle	, 0.0, 0.0, 1.0);
    gluPerspective(120.0, 1.0, 0.1, 500.0);
    gluLookAt(vieww,//sin(vieww),
              vieww2,
              vieww1+0.5, 0, 0, 0, 0.0, 1.0, 0.0);
    glCallList(bigcube);
    
    for(int i=-100;i<100;i+=5)
    {
        glPushMatrix();
        glTranslatef(i,0,0);
        glTranslatef(tran, 0, 0);
        cylinder();
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(i,0,4);
        glTranslatef(tran, 0, 0);
        cylinder();
        glPopMatrix();
        
    }
    //cylinder();




    
    float rims[] = {5.67,5.047,5.047,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,rims);
    glTranslatef(0, 0.255, 0);
    //glRotatef(0	, 0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    
    for(float theta=0;theta<360;theta=theta+15)
    {
        glVertex3f(0,0,0);
        glVertex3f(0+(0.08*(cos(((theta+angle)*3.14)/180))),0+(0.08*(sin(((theta+angle)*3.14)/180))),0);
    }
    
    glEnd();
    
    
    glBegin(GL_QUADS);
    for(float theta=0;theta<360;theta=theta+15)
    {
        glVertex3f(-0.5,0,0);
        glVertex3f(-0.5+(0.08*(cos(((theta+angle)*3.14)/180))),0+(0.08*(sin(((theta+angle)*3.14)/180))),0);
    }
    glEnd();
    
    glBegin(GL_QUADS);
    for(float theta=0;theta<360;theta=theta+15)
    {
        glVertex3f(0,0,-0.4);
        glVertex3f(0+(0.08*(cos(((theta+angle)*3.14)/180))),0+(0.08*(sin(((theta+angle)*3.14)/180))),-0.4);
    }
    glEnd();
    glBegin(GL_QUADS);
    for(float theta=0;theta<360;theta=theta+15)
    {
        glVertex3f(-0.5,0,-0.4);
        glVertex3f(-0.5+(0.08*(cos(((theta+angle)*3.14)/180))),0+(0.08*(sin(((theta+angle)*3.14)/180))),-0.4);
    }
    glEnd();
    

    for(int i=-100;i<100;i+=100)
    {
        glPushMatrix();
        glTranslatef(i,0,0);
        glTranslatef(tran, 0, 0);
        house();
        glPopMatrix();
    }
    glPopMatrix();
    
    if(tran == 100)
    {
        angle = 0;
        
    }
    
    
    
}





void move()
{
    glPushMatrix();
    
    car();
    glPopMatrix();
    
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //here create a protective block so transformation inside does not have a compound effect
    //Rotate wheels
    //land();

    glShadeModel(GL_SMOOTH);
    move();

    
    
    glutSwapBuffers();
    
    glFlush();
}

void f(int a)
{
    //what's happening here?
    glutTimerFunc(25, f, 0);
    //a simple rotation angle increment routine
    angle += 3;
    tran += 0.03; //moving objects for animation
    if (angle > 360)//1.5)
    {
        angle -= 360;//= -0.5;
    }
    if (tran > 100)//1.5)
    {
        tran = 100;//tran = 0;//= -0.5;
    }

    glutPostRedisplay();
}

void night()
{
    glClearColor(0.1,0.1,0.1,0);
    GLfloat fogcolour[4]={0.0,0.0,0.0,1.0};
    
    glFogfv(GL_FOG_COLOR,fogcolour);
    glFogf(GL_FOG_DENSITY,0.5);
    glFogi(GL_FOG_MODE,GL_EXP);
    /* end */
    glHint(GL_FOG_HINT, GL_FASTEST);
    glEnable(GL_FOG);
    
    glutPostRedisplay();
}

void day()
{
    glClearColor(0.75,0.85,1,0);
    glDisable(GL_FOG);
    glutPostRedisplay();
}

void keyboard(unsigned char key,int x, int y)
{
    switch(key)
    {
        case 'n':
            night();
            break;
        case 'd':
            day();
            break;
        case 27: //esc button exits the program
            exit(1);
            break;
        case 'r':
            
            break;
        case 'z':
            vieww1 += 0.1;
            break;
        case 'x':
            vieww1 -= 0.1;
            break;

            
    }
    glutPostRedisplay();
}

static void SpecialKeyFunc( int Key, int x, int y )
{
    switch ( Key ) {
        case GLUT_KEY_RIGHT:
            view += 0.1;
            vieww += 0.1;
            glutPostRedisplay();
            break;
            
        case GLUT_KEY_LEFT:
            view -= 0.1;
            vieww -= 0.1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            view2 += 0.1;
            vieww2 += 0.1;
            glutPostRedisplay();
            break;
            
        case GLUT_KEY_DOWN:
            view2 -= 0.1;
            vieww2 -= 0.1;
            glutPostRedisplay();
            break;
            
    }
}



void init()
{
    //float ambientLight[4] = {0.2, 0.2, 0.2, 1.0};
    //float lightpos[] = {1.0,1.0,1.0,0.0};
    glClearColor(0.75,0.85,1,0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glEnable(GL_LIGHTING);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    //glLightfv(GL_LIGHT1, GL_POSITION, lightpos);
    float black[] = {0.0,0.0,0.0,1.0};
    float white[] = {1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT1,GL_AMBIENT,black);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT1,GL_SPECULAR,white);
    glEnable(GL_LIGHT1);
    
    glMatrixMode(GL_PROJECTION);
    //gluPerspective(45.0,1.0,0.1,500);
    glMatrixMode(GL_MODELVIEW);
    //gluLookAt(vieww, vieww2, vieww1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    //note here we initialize double buffer viewing
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    
    
    MainWindow = glutCreateWindow("Program 5");
    //glClearColor(0,0,0,0);
    //glEnable(GL_DEPTH_TEST);
    init();
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc( SpecialKeyFunc );
    glMatrixMode(GL_MODELVIEW);
    
    glutTimerFunc(25, f, 0);
    
    cube(3);
    car(0.2);
    //wheelers();
    glutMainLoop();
    
}
