#include<windows.h>        // Include the Windows API header for Windows-specific functions
#include <GL/glut.h>       // Include the GLUT library for OpenGL Utility Toolkit functions
#include <stdlib.h>        // Include the standard library for general functions
#include <GL/gl.h>         // Include the core OpenGL functions
#include <GL/glu.h>        // Include the OpenGL Utility Library functions
#include <cmath>          // Include this for sin and cos functions



// Initialization function to set up OpenGL state
void init()
{
    glClearColor(0.5f, 0.0f, 1.0f, 0.0f); // Set the clear color to black (RGBA: 0, 0, 0, 0)
    glOrtho(-100, 100, -100, 100, -100, 100); // Set up an orthographic projection matrix
}


// Display function to draw the checkerboard pattern
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the window with the current clear color

    int x1 = 50, x2 = 40, y1 = -10, y2 = 0; // Initial coordinates for the rectangles

    for (int i = 1; i <= 10; i++) // Outer loop to iterate over rows
    {
        for (int j = 1; j <= 10; j++) // Inner loop to iterate over columns
        {
            if (i % 2 == 0) // Check if the row number is even
            {
                if (j % 2 != 0) // Check if the column number is odd
                {
                    glColor3f(0, 0, 0); // Set the color to black
                    glRectf(x1, y1, x2, y2); // Draw the rectangle with the current coordinates
                }
                else // If the column number is even
                {
                    glColor3f(1, 1, 1); // Set the color to white
                    glRectf(x1, y1, x2, y2); // Draw the rectangle with the current coordinates
                }
            }
            else // If the row number is odd
            {
                if (j % 2 != 0) // Check if the column number is odd
                {
                    glColor3f(1, 1, 1); // Set the color to white
                    glRectf(x1, y1, x2, y2); // Draw the rectangle with the current coordinates
                }
                else // If the column number is even
                {
                    glColor3f(0, 0, 0); // Set the color to black
                    glRectf(x1, y1, x2, y2); // Draw the rectangle with the current coordinates
                }
            }

            x1 = x1 - 10; // Move the left x-coordinate to the right for the next rectangle
            x2 = x2 - 10; // Move the right x-coordinate to the right for the next rectangle
            glFlush(); // Force execution of OpenGL commands
        }

        x1 = 50; // Reset the x-coordinates for the next row
        x2 = 40; // Reset the x-coordinates for the next row
        y1 = y1 + 10; // Move the bottom y-coordinate up for the next row
        y2 = y2 + 10; // Move the top y-coordinate up for the next row
    }

}

// Main function where the program execution begins
int main(int argc, char *argv[])
{
    glutInit( & argc, argv );
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Initialize the display mode with single buffering and RGB color model
    glutInitWindowSize(700, 700); // Set the window size to 700x700 pixels
    glutInitWindowPosition(0, 0); // Set the initial window position at the top-left corner of the screen
    glutCreateWindow("Checkerboard/Chessboard"); // Create a window with the title "DEMO"
    init(); // Call the initialization function to set up OpenGL state
    glutDisplayFunc(myDisplay); // Register the display callback function
    glutMainLoop(); // Enter the GLUT event processing loop

    return 0; // Return 0 to indicate successful execution
}

