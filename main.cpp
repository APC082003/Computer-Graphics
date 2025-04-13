/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is a test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed. The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <windows.h> // This includes the Windows API header file, which contains declarations for all Windows functions, constants, and types.

#ifdef __APPLE__
#include <GLUT/glut.h> // If compiling on a Mac, this includes the GLUT header specific to Mac.
#else
#include <GL/glut.h> // If compiling on other platforms, this includes the standard GLUT header.
#endif

#include <stdlib.h> // Includes standard library functions, such as memory allocation, process control, and conversions.
#include <unistd.h> // Includes POSIX API functions, which provide access to the operating system API.
#include <math.h> // Includes mathematical functions, like sine, cosine, and square root.

static GLfloat spin = 0.0; // A global variable to store the current rotation angle of the shape.
static float tx = 0.0; // A global variable to store the translation amount along the x-axis.
static float ty = 0.0; // A global variable to store the translation amount along the y-axis.


//FOR CIRCLE
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


// Function to display the content on the screen
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen




          // === ROAD ===
    glColor3f(0.3, 0.3, 0.3); // Dark gray road
    glBegin(GL_POLYGON);
        glVertex2f(-110.0, -40.0);
        glVertex2f(100.0, -40.0);
        glVertex2f(100.0, -10.0);
        glVertex2f(-100.0, -10.0);
    glEnd();

    // === ROAD MARKINGS === (optional dashed white lines)
    glColor3f(1.0, 1.0, 1.0); // White
    for (float i = -90.0; i <= 90.0; i += 20.0)
    {
        glBegin(GL_POLYGON);
            glVertex2f(i, -26.0);
            glVertex2f(i + 10.0, -26.0);
            glVertex2f(i + 10.0, -24.0);
            glVertex2f(i, -24.0);
        glEnd();
    }

    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0); // Rotation
    glTranslatef(tx, ty, 0); // Movement




    // === CAR TRANSFORM ===
    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0);
    glTranslatef(tx, ty, 0);

    // === Car Body ===
    glColor3f(0.2, 0.6, 0.8); // Blue
    glRectf(-40.0, -15.0, 40.0, 15.0);

    // === Car Roof ===
    glColor3f(0.1, 0.3, 0.5); // Darker blue
    glBegin(GL_POLYGON);
        glVertex2f(-25.0, 15.0);
        glVertex2f(-15.0, 30.0);
        glVertex2f(15.0, 30.0);
        glVertex2f(25.0, 15.0);
    glEnd();

    // === Car Windows ===
    glColor3f(0.6, 0.9, 1.0); // Light blue
    glBegin(GL_POLYGON); // Left window
        glVertex2f(-22.0, 15.0);
        glVertex2f(-13.0, 28.0);
        glVertex2f(-2.0, 28.0);
        glVertex2f(-2.0, 15.0);
    glEnd();

    glBegin(GL_POLYGON); // Right window
        glVertex2f(2.0, 15.0);
        glVertex2f(2.0, 28.0);
        glVertex2f(13.0, 28.0);
        glVertex2f(22.0, 15.0);
    glEnd();

    // === Car Doors ===
    glColor3f(0.1, 0.4, 0.6); // Slightly different shade
    glBegin(GL_LINE_LOOP); // Left door
        glVertex2f(-35.0, -15.0);
        glVertex2f(-10.0, -15.0);
        glVertex2f(-10.0, 15.0);
        glVertex2f(-35.0, 15.0);
    glEnd();

    glBegin(GL_LINE_LOOP); // Right door
        glVertex2f(10.0, -15.0);
        glVertex2f(35.0, -15.0);
        glVertex2f(35.0, 15.0);
        glVertex2f(10.0, 15.0);
    glEnd();

    // === Wheels ===
    glColor3f(0.0, 0.0, 0.0); // Black

    glBegin(GL_POLYGON); // Left wheel
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * 3.1415926f * i / 100;
        float x = 10 * cosf(theta);
        float y = 10 * sinf(theta);
        glVertex2f(x - 25, y - 20);
    }
    glEnd();

    glBegin(GL_POLYGON); // Right wheel
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * 3.1415926f * i / 100;
        float x = 10 * cosf(theta);
        float y = 10 * sinf(theta);
        glVertex2f(x + 25, y - 20);
    }
    glEnd();

    glPopMatrix();
    glFlush();
}



// Function to increment the spin angle to the left
void spinDisplay_left(void)
{
    spin = spin + 1; // Increases the rotation angle by 1 degree.
    glutPostRedisplay(); // Marks the current window as needing to be redisplayed.
}

// Function to decrement the spin angle to the right
void spinDisplay_right(void)
{
    spin = spin - 1; // Decreases the rotation angle by 1 degree.
    glutPostRedisplay(); // Marks the current window as needing to be redisplayed.
}

// Function to continuous display
void conDisplay_down(void)
{
    ty = ty - 0.001; // Increases the rotation angle by 1 degree.
    glutPostRedisplay(); // Marks the current window as needing to be redisplayed.
}
void conDisplay_up(void)
{
    ty = ty + 0.001; // Increases the rotation angle by 1 degree.
    glutPostRedisplay(); // Marks the current window as needing to be redisplayed.
}

void conDisplay_left(void)
{
    tx = tx - 0.001; // Increases the rotation angle by 1 degree.
    glutPostRedisplay(); // Marks the current window as needing to be redisplayed.
}
void conDisplay_right(void)
{
    tx = tx + 0.001; // Increases the rotation angle by 1 degree.
    glutPostRedisplay(); // Marks the current window as needing to be redisplayed.
}


// Function to initialize the OpenGL environment
void init(void)
{
    glClearColor(1.0, 0.0, 0.0, 0.0); // Sets the clear color to red (RGB: 1.0, 0.0, 0.0, Alpha: 0.0).
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0); // Sets up a 2D orthographic viewing region with the given boundaries.
}

// Function to handle keyboard input
void my_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'l': // If 'l' key is pressed
            spinDisplay_left(); // Call the function to spin left.
            break;
        case 'r': // If 'r' key is pressed
            spinDisplay_right(); // Call the function to spin right.
            break;
        case 's': // If 's' key is pressed
            glutIdleFunc(NULL); // Stop any ongoing animation.
            break;
        default:
            break;
    }
}

// Function to handle special key input (arrow keys)
void spe_key(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP: // If up arrow key is pressed
           glutIdleFunc(conDisplay_up);
            break;
        case GLUT_KEY_DOWN: // If down arrow key is pressed
           glutIdleFunc(conDisplay_down);
            break;
        case GLUT_KEY_RIGHT: // If right arrow key is pressed
            glutIdleFunc(conDisplay_right);
            break;
        case GLUT_KEY_LEFT: // If left arrow key is pressed
            glutIdleFunc(conDisplay_left);
            break;
        default:
            break;
    }
}

// Function to handle mouse input
void my_mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(spinDisplay_left); // Start spinning left when the left mouse button is pressed.
            break;
        case GLUT_MIDDLE_BUTTON:
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(spinDisplay_right); // Start spinning right when the middle or right mouse button is pressed.
            break;
        default:
            break;
    }
}

// Main function to set up the GLUT environment and enter the event processing loop
int main(int argc, char *argv[])
{
    glutInit( & argc, argv );
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Initialize the display mode with single buffering and RGB color model.
    glutInitWindowSize(500, 500); // Set the window size to 500x500 pixels.
    glutInitWindowPosition(100, 100); // Set the initial window position.
    glutCreateWindow("Car by Abrity"); // Create a window with the title "mist".
    init(); // Call the initialization function.

    glutDisplayFunc(display); // Register the display callback function.
    glutKeyboardFunc(my_keyboard); // Register the keyboard callback function.
    glutSpecialFunc(spe_key); // Register the special key callback function.
    glutMouseFunc(my_mouse); // Register the mouse callback function.
    glutMainLoop(); // Enter the GLUT event processing loop.
    return 0; // Exit the program.
}
