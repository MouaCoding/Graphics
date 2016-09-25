#include <stdlib.h>
#include <stdio.h>
#include <GLUT/GLUT.h>

void processMenu(int value);

int antialiasing = 0;
int gridSize = 3;
GLuint selectedPoint = ~0;
int winWidth, winHeight;
GLuint selectBuffer[64];
GLdouble modelMatrix[16], projMatrix[16];
GLint viewport[4];
int render = 0;
int camera = 0;
int added = 0;
int vert=0, hori = 0;



GLfloat grid2x2[2][2][3] =
{
    {
        {-2.0, -2.0, 0.0},
        {2.0, -2.0, 0.0}},
    {
        {-2.0, 2.0, 0.0},
        {2.0, 2.0, 0.0}}
};

GLfloat grid4x4[4][4][3] =
{
    {
        {-2.0, -2.0, -1.0},
        {-0.5, -2.0, 0.0},
        {0.5, -2.0, 0.0},
        {2.0, -2.0, -1.0}},
    {
        {-2.0, -0.5, 0.0},
        {-0.5, -0.5, 1.0},
        {0.5, -0.5, 1.0},
        {2.0, -0.5, 0.0}},
    {
        {-2.0, 0.5, 0.0},
        {-0.5, 0.5, 1.0},
        {0.5, 0.5, 1.0},
        {2.0, 0.5, 0.0}},
    {
        {-2.0, 2.0, -1.0},
        {-0.5, 2.0, 0.0},
        {0.5, 2.0, 0.0},
        {2.0, 2.0, -1.0}}
};
GLfloat *grid = &grid4x4[0][0][0];
int uSize = 4;
int vSize = 4;
int rend = gridSize;

void setupMesh(void)
{
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(gridSize, 0.0, 1.0, gridSize, 0.0, 1.0);
}

int nogrid = 0;
void evaluateGrid(void)
{
    glColor3f(1.0, 1.0, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, //order = 3
            uSize, 0, 1, uSize * 3, vSize, grid);
    if(render == 1)
    {
        
        glColor3f(0.0, 0.0, 1.0);
        glEvalMesh2(GL_FILL, 0, rend, 0, rend);
        if(nogrid != 1){
        glColor3f(1.0, 1.0, 1.0);
      glEvalMesh2(GL_LINE, 0, gridSize, 0, gridSize);
        }
        
    }
    else
       glEvalMesh2(GL_LINE, 0, gridSize, 0, gridSize);
}

void drawControlPoints(void)
{
    int i;
    
    glColor3f(1.0, 1.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (i = 0; i < uSize * vSize; i++) {
        glVertex3fv(&grid[i * 3]);
    }
    glEnd();
}

void selectControlPoints(void)
{
    int i;
    
    for (i = 0; i < uSize * vSize; i++) {
        glLoadName(i);
        glBegin(GL_POINTS);
        glVertex3fv(&grid[i * 3]);
        glEnd();
    }
}

int angle = 0,a;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (camera == 1)
    {
        if(vert == 1)
            glRotatef(angle, 1, 0, 0);//gluLookAt(vieww,vieww2,vieww1, 0, 0, 0, 0.0, 1.0, 0.0);
        if(hori == 1)
            glRotatef(angle, 0, 1, 0);//gluLookAt(vieww,vieww2,vieww1, 0, 0, 0, 0.0, 1.0, 0.0);
        a=angle;
    }
    evaluateGrid();
    drawControlPoints();
    glutSwapBuffers();
}

void
ortho(void)
{
    if (winWidth <= winHeight)
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat) winHeight / (GLfloat) winWidth,
                4.0 * (GLfloat) winHeight / (GLfloat) winWidth, -4.0, 4.0);
    else
        glOrtho(-4.0 * (GLfloat) winWidth / (GLfloat) winHeight,
                4.0 * (GLfloat) winWidth / (GLfloat) winHeight, -4.0, 4.0, -4.0, 4.0);
}

GLuint
pick(int x, int y)
{
    int hits;
    
    (void) glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(~0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(x, winHeight - y, 8.0, 8.0, viewport);
    ortho();
    glMatrixMode(GL_MODELVIEW);
    selectControlPoints();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    hits = glRenderMode(GL_RENDER);
    if (hits) {

        return selectBuffer[3];
    } else {
        return ~0;
    }
}

void
reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    winWidth = w;
    winHeight = h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    ortho();
    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
    viewport[0] = 0;
    viewport[1] = 0;
    viewport[2] = winWidth;
    viewport[3] = winHeight;
}

void
mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            selectedPoint = pick(x, y);

        } else {
            selectedPoint = -1;
        }
    }
}

void
motion(int x, int y)
{
    GLdouble objx, objy, objz;
    
    if (selectedPoint != ~0) {
        gluUnProject(x, winHeight - y, 0.95,
                     modelMatrix, projMatrix, viewport,
                     &objx, &objy, &objz);
        grid[selectedPoint * 3 + 0] = objx;
        grid[selectedPoint * 3 + 1] = objy;
        glutPostRedisplay();
    }

}

static void
keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);

    }
    
}

static void SpecialKeyFunc( int Key, int x, int y )
{
    switch ( Key ) {
        case GLUT_KEY_RIGHT:
            if(camera != 1)
            rend++;
            hori = 1;
            vert=0;
            angle++;
            glutPostRedisplay();
            break;
            
        case GLUT_KEY_LEFT:
            if(camera != 1)
            rend--;
            hori = 1;
            vert=0;
            angle--;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            if(camera !=1)
            gridSize++;
            setupMesh();
            vert = 1;
            hori = 0;
            angle++;
            //angle++;
            glutPostRedisplay();
            break;
            
        case GLUT_KEY_DOWN:
            if(camera !=1)
            gridSize--;
            setupMesh();
            vert = 1;
            hori = 0;
            angle--;
            //angle--;
            glutPostRedisplay();
            break;
            
    }
}


enum {
    M_2ND_ORDER_GRID, M_4TH_ORDER_GRID, M_INCREASE_GRID, M_DECREASE_GRID, M_TOGGLE_ANTIALIASING, M_QUIT
};


void
menu(int value)
{
    switch (value) {
        case M_2ND_ORDER_GRID:
            grid = &grid2x2[0][0][0];
            uSize = 2;
            vSize = 2;
            setupMesh();
            break;
        case M_4TH_ORDER_GRID:
            grid = &grid4x4[0][0][0];
            uSize = 4;
            vSize = 4;
            setupMesh();
            break;
        case M_INCREASE_GRID:
            gridSize += 2;
            setupMesh();
            break;
        case M_DECREASE_GRID:
            gridSize -= 2;
            if (gridSize < 2) {
                gridSize = 2;
            }
            setupMesh();
            break;
        case M_TOGGLE_ANTIALIASING:
            if (antialiasing) {
                antialiasing = 0;
                glDisable(GL_BLEND);
                glDisable(GL_LINE_SMOOTH);
                glDisable(GL_POINT_SMOOTH);
            } else {
                antialiasing = 1;
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_BLEND);
                glEnable(GL_LINE_SMOOTH);
                glEnable(GL_POINT_SMOOTH);
            }
            break;
        case M_QUIT:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void createMenu()
{
    glutCreateMenu(processMenu);
    glutAddMenuEntry("Add Row/Column", 3);
    glutAddMenuEntry("Delete Row/Column", 4);
    glutAddMenuEntry("Extend Row/Column", 9);
    glutAddMenuEntry("Edit Point", 5);
    glutAddMenuEntry("Rendering Resolution", 1);
    glutAddMenuEntry("No Mesh", 9);
    glutAddMenuEntry("Unrender/Unfill", 2);
    glutAddMenuEntry("Camera View", 6);
    glutAddMenuEntry("Camera Off", 7);
    glutAddMenuEntry("Camera Reset", 8);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMenu(int value)
{
    if(value == 1)
    {
        render =1;
        nogrid =0;
    }
    if(value == 9)
    {
        nogrid =1;
    }
    if(value == 2)
    {
        render =0;
        nogrid =0;
    }
    if(value == 3)//add
    {
        gridSize++;
        setupMesh();
    }
    if(value == 4)//add
    {
    gridSize--;
    setupMesh();
    }
    
    if(value == 6)//camera on
    {
        
        camera =1;
        glPushMatrix();
    }
    if(value == 7)//camera off
    {
        camera = 0;

        //break;
    }
    if(value == 8)//camera reset
    {
        camera =0;
        //angle = 0;
        glPopMatrix();
        //glRotatef(-a, 1, 0, 0);
    }
    if(value == 9)
    {
        gridSize++;
    }
}

int
main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Project 4");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc( SpecialKeyFunc );
    glutMotionFunc(motion);
    glutCreateMenu(menu);

    createMenu();
    glSelectBuffer(sizeof(selectBuffer), selectBuffer);
    setupMesh();
    glutMainLoop();
    return 0;
}
