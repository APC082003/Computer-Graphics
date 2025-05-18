/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include<windows.h>
#ifdef __APPLE__
//#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

//float p=-2.3;
void DrawCircle(float cx, float cy, float rx,float ry, int num_segments)
{
glBegin(GL_TRIANGLE_FAN);
for(int ii = 0; ii < num_segments; ii++)
{
float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

float x = rx * cosf(theta);//calculate the x component
float y = ry * sinf(theta);//calculate the y component

glVertex2f(x + cx, y + cy);//output vertex

}
glEnd();
}
void init(void)
{
glClearColor (0.0, 0.0, 0.0, 0.0);
glOrtho(-600.0, 600.0, -500.0, 500.0, -1.0, 1.0);
}


void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f,0.22f,0.66f);//FOR TOP HORIZONTAL RECTANGLE (BLUE)
    glBegin(GL_QUADS);
        glVertex3d(-300.0,300.0,0.0);
        glVertex3d(200.0,300.0,0.0);
        glVertex3d(200.0,200.0,0.0);
        glVertex3f(-300.0,200.0,0.0);
    glEnd();

    glColor3f(0.81f,0.07f,0.15f);//FOR BOTTOM HORIZONTAL RECTANGLE (RED)
    glBegin(GL_QUADS);
        glVertex3d(-300.0,200.0,0.0);
        glVertex3d(200.0,200.0,0.0);
        glVertex3d(200.0,100.0,0.0);
        glVertex3f(-300.0,100.0,0.0);
    glEnd();


    glColor3f(1.0f,1.0f,1.0f);//WHITE TRIANGLE
    glBegin(GL_TRIANGLES);
    glVertex3d(-300.0,300.0,0.0);
    glVertex3d(-100.0,200.0,0.0);
    glVertex3f(-300.0,100.0,0.0);
     glEnd();


    //glPushMatrix();

glColor3f(0.99, 0.82, 0.09);//YELLOW CIRCLE (SUN)

DrawCircle(-230,200,40,30,100);
 //glPopMatrix();


    glEnd();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(400,200);
    glutCreateWindow("FLAG OF PHILIPPINES");
    init();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}
