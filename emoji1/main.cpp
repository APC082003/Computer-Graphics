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

#ifdef __APPLE__
#include <GLUT/glut.h>
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
//For eyebrows
void DrawHalfCircle(float cx, float cy, float rx, float ry, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Center point
    for (int ii = 0; ii <= num_segments / 2; ii++) // Only draw half-circle
    {
        float theta = 3.1415926f * float(ii) / float(num_segments / 2);
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

//For spectacles
void DrawCircleOutline(float cx, float cy, float rx, float ry, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


void init(void)
{
glClearColor (0.0, 0.0, 0.0, 0.0);
glOrtho(-500.0, 500.0, -300.0, 300.0, -1.0, 1.0);
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
//glPushMatrix();
//Face
glColor3f(1.0, 1.0, 0.9);
DrawCircle(0,0,300,200,100);
 //glPopMatrix();
//Mouth
 glColor3f(1.0, 0.0, 0.0);
DrawCircle(0,-100,100,50,50);
//EYES
 glColor3f(0.0, 0.0, 0.0);
DrawCircle(100,50,50,30,50);
DrawCircle(-100,50,50,30,50);

    //  dots inside eyes
    glColor3f(1.0, 1.0, 1.0);
    DrawCircle(115, 65, 15, 10, 30); // Right eye dot
    DrawCircle(-85, 65, 15, 10, 30); // Left eye dot
//Eyebrows
    glColor3f(0.0, 0.0, 0.0);
    DrawHalfCircle(100, 120, 60, 20, 50);
    DrawHalfCircle(-100, 120, 60, 20, 50);

     // Spectacles (black frames)
    glColor3f(0.0, 0.0, 0.0);
    DrawCircleOutline(100, 50, 70, 50, 100);  // Right frame
    DrawCircleOutline(-100, 50, 70, 50, 100); // Left frame

    // Spectacle bridge (connecting the two frames)
    glBegin(GL_LINES);
    glVertex2f(-30, 50);
    glVertex2f(30, 50);
    glEnd();


//Tongue
    glColor3f(1.0, 0.4, 0.4);
    DrawCircle(0, -120, 50, 25, 50);


glFlush();
}

int main(int argc, char *argv[])

{
     glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (600, 600);
glutInitWindowPosition (100, 100);
glutCreateWindow ("WOW EMOJI");
init();
    glutDisplayFunc(display);
glutMainLoop();
return 0;
}

