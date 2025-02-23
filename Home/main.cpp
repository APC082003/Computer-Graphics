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

void init()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glOrtho(-10,10,-10,10,-10,10);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f,0.1f,0.1f);
    glBegin(GL_TRIANGLES);
    glVertex3d(3.0,3.0,0.0);
    //glVertex3d(2.0,-2.0,0.0);
    glVertex3d(7.0,0.0,0.0);
    glVertex3f(-1.0,0.0,0.0);
     glEnd();

    glColor3f(2.0f,.05f,1.0f);
    glBegin(GL_QUADS);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(6.0,0.0,0.0);
        glVertex3d(6.0,-5.0,0.0);
        glVertex3f(0.0,-5.0,0.0);
    glEnd();
        glColor3f(0.1f,0.0f,0.1f);
    glBegin(GL_QUADS);
        glVertex3d(2.0,-3.0,0.0);
        glVertex3d(4.0,-3.0,0.0);
        glVertex3d(4.0,-5.0,0.0);
        glVertex3f(2.0,-5.0,0.0);
    glEnd();


    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(400,200);
    glutCreateWindow("Home");
    init();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}


