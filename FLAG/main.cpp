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



    glColor3f(0.6f,1.0f,0.2f);
    glBegin(GL_QUADS);
        glVertex3d(0.0,400.0,0.0);
        glVertex3d(500.0,400.0,0.0);
        glVertex3d(500.0,100.0,0.0);
        glVertex3f(0.0,100.0,0.0);
    glEnd();

    //glPushMatrix();

glColor3f(0.8, 0.0, 0.0);

DrawCircle(250,250,100,100,100);
 //glPopMatrix();

    glColor3f(0.7f,0.8f,0.8f);
    glBegin(GL_QUADS);
        glVertex3d(-20.0,400.0,0.0);
        glVertex3d(0.0,400.0,0.0);
        glVertex3d(0.0,-100.0,0.0);
        glVertex3f(-20.0,-100.0,0.0);
    glEnd();

        glColor3f(0.7f,0.8f,0.8f);
    glBegin(GL_QUADS);
        glVertex3d(-50.0,-100.0,0.0);
        glVertex3d(50.0,-100.0,0.0);
        glVertex3d(50.0,-150.0,0.0);
        glVertex3f(-50.0,-150.0,0.0);
    glEnd();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(400,200);
    glutCreateWindow("FLAG");
    init();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}
