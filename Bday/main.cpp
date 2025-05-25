#include <GL/glut.h>
#include <cmath>
#include <vector>

#define PI 3.14159265

float fish1X = 0.0f, fish1Dir = 0.01f;
float fish2X = 0.0f, fish2Dir = -0.01f;
float bubbleY1 = 0.05f, bubbleY2 = 0.05f;
float localBubbleY1 = 0.02f, localBubbleY2 = 0.02f;
float bubbleX1 = 0.0f, bubbleX2 = 0.0f;  // Track mouth X for animation
float flameFlicker = 0.0f;


//Utility function to draw filled circles (used for balloons, heads, eyes, etc.)
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta));
    }
    glEnd();
}


float balloonOffset = 0.0f;
bool balloonUp = true;

void drawFloatingBalloons() {
    float baseY = 0.9f + 0.05f * sinf(balloonOffset); // Smooth bobbing
    float balloonX[] = {-0.8f, -0.6f, -0.2f, 0.2f, 0.6f, 0.6f};

    for (int i = 0; i < 8; i++) {
        glColor3f(1.0f, 0.2f, 0.6f);  // Pink balloons
        drawCircle(balloonX[i], baseY, 0.15f, 30);//balloon sizes
        glColor3f(0.0f, 0.0f, 0.0f); //black string
        glBegin(GL_LINES);
            glVertex2f(balloonX[i], baseY - 0.09f); // top of string, just under balloon
            glVertex2f(balloonX[i], baseY - 1.30f); // end of string (long line)
        glEnd();
    }
}

void drawBanner() {
    // Banner Shape
    glColor3f(1.0f, 0.6f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, 0.95f);  // Top-left
        glVertex2f(0.7f, 0.95f);   // Top-right
        glVertex2f(0.6f, 0.85f);   // Bottom-right
        glVertex2f(-0.6f, 0.85f);  // Bottom-left
    glEnd();

    // Hanging Strings
    glColor3f(0.0f, 0.0f, 0.0f); // Black threads
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.7f, 1.0f); glVertex2f(-0.7f, 0.95f); // Left rope
        glVertex2f(0.7f, 1.0f);  glVertex2f(0.7f, 0.95f);  // Right rope
    glEnd();

    // Banner Text
    const char* message = "Happy Birthday!";
    glColor3f(0.1f, 0.0f, 0.4f); // Deep violet text
    glRasterPos2f(-0.23f, 0.88f); // Adjust to center text

    for (int i = 0; message[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]); //Loops over each character in the message.
    }//Renders it one character at a time using GLUT’s built-in bitmap font
}

//Generates randomized confetti using GL_POINTS
void drawConfetti() {
    glPointSize(3.0f); //Sets the size of each point to 3 pixels.
    glBegin(GL_POINTS); //Begins a set of points — each glVertex2f() will draw a separate dot.
    for (int i = 0; i < 100; i++) {
        float x = -1.0f + static_cast<float>(rand()) / RAND_MAX * 2.0f; //Generate a random X position between -1.0 and 1.0.
        float y = 0.7f + static_cast<float>(rand()) / RAND_MAX * 0.2f; //Generate a random Y between 0.7 and 0.9.
        glColor3f(
            static_cast<float>(rand()) / RAND_MAX,
            static_cast<float>(rand()) / RAND_MAX,
            static_cast<float>(rand()) / RAND_MAX
        ); //Assigns a random RGB color to the point by generating 3 random floats between 0.0 and 1.0.


        glVertex2f(x, y); //Specifies the position of the confetti point using the randomly generated coordinates.
    }
    glEnd();
}


//Draws a simple table (top + two legs).
void drawTable() {
    // Table top
    glColor3f(0.5f, 0.3f, 0.1f);  // Brown
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.15f);
        glVertex2f(0.4f, -0.15f);
        glVertex2f(0.4f, -0.18f);
        glVertex2f(-0.4f, -0.18f);
    glEnd();

    // Table legs
    glBegin(GL_POLYGON); // Left leg
        glVertex2f(-0.35f, -0.18f);
        glVertex2f(-0.33f, -0.18f);
        glVertex2f(-0.33f, -0.45f);
        glVertex2f(-0.35f, -0.45f);
    glEnd();

    glBegin(GL_POLYGON); // Right leg
        glVertex2f(0.33f, -0.18f);
        glVertex2f(0.35f, -0.18f);
        glVertex2f(0.35f, -0.45f);
        glVertex2f(0.33f, -0.45f);
    glEnd();
}

void drawGiftBox(float x, float y, float size) {
    // Box base
    glColor3f(1.0f, 0.2f, 0.2f);  // Red
    glBegin(GL_POLYGON);
        glVertex2f(x - size, y); // Bottom-left
        glVertex2f(x + size, y); // Bottom-right
        glVertex2f(x + size, y + size * 1.5f); // Top-right
        glVertex2f(x - size, y + size * 1.5f); // Top-left
    glEnd();

    // Ribbon vertical
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow
    glBegin(GL_POLYGON);
        glVertex2f(x - size * 0.1f, y);
        glVertex2f(x + size * 0.1f, y);
        glVertex2f(x + size * 0.1f, y + size * 1.5f);
        glVertex2f(x - size * 0.1f, y + size * 1.5f);
    glEnd();

    // Ribbon bow (simple)
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(x, y + size * 1.5f, size * 0.2f, 20);
    // Shadow
        glColor4f(0.0f, 0.0f, 0.0f, 0.2f);
        drawCircle(x, y, size * 0.7f, 30);  // Soft circle shadow
}

void drawCake() {
    glPushMatrix();
    glTranslatef(-0.05f, -0.10f, 0.0f);  // ✅ Fixed: 3 arguments Translates (moves) the coordinate system by (-0.05, -0.10, 0) in x, y, z directions.This shifts the cake slightly left and downward in the scene.

    glColor3f(1.0f, 0.6f, 0.4f);  //Draws a rectangular cake body with a soft orange color.
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f,-0.05f);
        glVertex2f(0.10f, -0.05f);
        glVertex2f(0.10f, 0.1f);
        glVertex2f(-0.05f, 0.1f);
    glEnd();

    // Candle
    glColor3f(0.0f, 0.0f, 1.0f); //Vertical blue line on top of cake representing the candle stick.


    glBegin(GL_LINES);
        glVertex2f(0.028f, 0.1f);
        glVertex2f(0.028f, 0.15f);
    glEnd();

// Flame
glColor3f(1.0f, 1.0f, 0.0f);
float flameOffset = 0.005f * sinf(flameFlicker);
drawCircle(0.028f, 0.17f + flameOffset, 0.01f + 0.002f * cosf(flameFlicker), 20); //Animate flame position using sine wave oscillation for flicker.Draw inner flame: yellow circle with dynamic size + position.
//Draw inner flame: yellow circle with dynamic size + position.

// Glow
glColor4f(1.0f, 1.0f, 0.0f, 0.2f);
drawCircle(0.028f, 0.17f + flameOffset, 0.03f + 0.01f * cosf(flameFlicker), 20); //Draw glowing aura using transparent yellow circle.
// Icing lines
glColor3f(1.0f, 1.0f, 1.0f);
glLineWidth(2.0f);
glBegin(GL_LINE_STRIP);
    for (float x = -0.05f; x <= 0.1f; x += 0.015f) {
        glVertex2f(x, 0.1f + 0.01f * sinf(40 * x));
    }
glEnd();
//Draws wavy icing line along the cake top.

//Uses sine wave to simulate decorative icing.



// Cherry
glColor3f(1.0f, 0.0f, 0.0f);
drawCircle(0.028f, 0.10f, 0.01f, 20);


    glPopMatrix();//Restore previous transformation state so cake position doesn't affect next objects.
}
//Red circle at base of the flame to represent a cherry.

void drawFish(float x, float y, bool facingRight, float& mouthX, float& mouthY) {
    float dir = facingRight ? 1.0f : -1.0f;//Set direction multiplier to flip geometry if needed.

    // Store mouth position
    mouthX = x + 0.03f * dir;//Calculate mouth position (near front center of fish).
    mouthY = y + 0.01f;

    // Body
    glColor3f(0.9f, 0.4f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float theta = i * PI / 180;
        float ex = 0.04f * cos(theta) * (i < 180 ? 1 : 0.7);
        float ey = 0.02f * sin(theta);
        glVertex2f(x + ex * dir, y + ey);
    }
    glEnd();
    //Draws an ellipse-like fish body.Uses cos/sin to trace shape. Rear half is squished to form tail taper.

    // Tail
    glColor3f(0.9f, 0.6f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.03f * dir, y);
    glVertex2f(x - 0.07f * dir, y + 0.03f);
    glVertex2f(x - 0.07f * dir, y - 0.03f);
    glEnd();
    //Triangle tail at the back of the fish, adjusted based on direction.

    // Eye
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(mouthX, mouthY, 0.005f, 10); //Draw black dot as fish eye, at the mouth position for simplicity.


}


void drawAquarium() {
    glPushMatrix();
    glTranslatef(0.2f, -0.10f, 0.0f);
    glScalef(0.6f, 0.5f, 1.0f);  //Translate and scale the aquarium for correct placement and proportion.



    // Glass
    glColor4f(0.4f, 0.7f, 1.0f, 0.3f); //Transparent light-blue circle to simulate aquarium glass.
    drawCircle(0.0f, 0.09f, 0.2f, 100);

    // Border
    glColor3f(0.2f, 0.4f, 0.7f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * PI * float(i) / 100;
        glVertex2f(0.2f * cos(theta), 0.09f + 0.2f * sin(theta)); //Blue circular outline around aquarium for clarity.
    }
    glEnd();

    // Fish bounds
    float safeX = 0.135f;
    float x1 = std::min(std::max(fish1X, -safeX), safeX);
    float x2 = std::min(std::max(fish2X, -safeX), safeX);
//Clamp fish X-coordinates to prevent them from swimming through glass.
    float mouthX1, mouthY1, mouthX2, mouthY2;


    // Slightly raise fish Y positions
    drawFish(x1, 0.02f, fish1Dir > 0, mouthX1, mouthY1);
    drawFish(x2, 0.08f, fish2Dir > 0, mouthX2, mouthY2);

    // Track current mouth X/Y (for bubbles to start from)
    bubbleX1 = mouthX1;
    bubbleX2 = mouthX2;

    // Draw animated bubbles
    // Store mouthX as before
    bubbleX1 = mouthX1;
    bubbleX2 = mouthX2;

// Draw bubbles (convert local → world manually)
    float globalY1 = localBubbleY1 * 0.5f - 0.10f;  // scale + translate Y
    float globalY2 = localBubbleY2 * 0.5f - 0.10f;
    float globalX1 = bubbleX1 * 0.6f + 0.2f;        // scale + translate X
    float globalX2 = bubbleX2 * 0.6f + 0.2f;

    glPopMatrix();  // ← UNDO transform first before drawing in world space

    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
    drawCircle(globalX1, globalY1, 0.015f, 20);
    drawCircle(globalX2, globalY2, 0.015f, 20);


    glPopMatrix();
}



void drawGrass() {
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -0.35f);
        glVertex2f(1.0f, -0.35f); //Draws a rectangle stretching from the bottom of the screen up to -0.35 (used as ground layer).
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void drawGirl() {
    // Head
    glColor3f(1.0f, 0.85f, 0.75f);
    drawCircle(0.0f, 0.5f, 0.12f, 100);

// Hair with side ponytails
glColor3f(0.4f, 0.2f, 0.1f); // Brown color

// Main hair (sides and back only)
glBegin(GL_POLYGON);
for(int i = 0; i <= 80; ++i) {
    float theta = PI/5 + PI/3 * float(i)/40; // 60°-120° range
    glVertex2f(0.12f * cos(theta), 0.5f + 0.12f * sin(theta));
}
glEnd();
//Draw a semicircle-like back hair covering part of the head.

// Left ponytail
glBegin(GL_TRIANGLE_FAN);
for(int i = 0; i <= 30; ++i) {
    float theta = PI * float(i)/20;
    glVertex2f(-0.15f + 0.03f*cos(theta), 0.48f + 0.05f*sin(theta));
}
glEnd();
//Left ponytail using a semi-ellipse.

// Right ponytail
glBegin(GL_TRIANGLE_FAN);
for(int i = 0; i <= 30; ++i) {
    float theta = PI * float(i)/20;
    glVertex2f(0.15f + 0.03f*cos(theta), 0.48f + 0.05f*sin(theta));
}
glEnd();
//Right ponytail with mirrored shape.

// Eyes (positioned lower)
glColor3f(1.0f, 1.0f, 1.0f);
drawCircle(-0.04f, 0.50f, 0.02f, 50);  // Lowered Y position from 0.53 to 0.50
drawCircle(0.04f, 0.50f, 0.02f, 50);

// Pupils
glColor3f(0.0f, 0.0f, 0.0f);
drawCircle(-0.04f, 0.50f, 0.008f, 50);
drawCircle(0.04f, 0.50f, 0.008f, 50);

// Eyebrows
glColor3f(0.2f, 0.1f, 0.05f);
glLineWidth(2.0f);
glBegin(GL_LINES);
    glVertex2f(-0.06f, 0.54f); glVertex2f(-0.02f, 0.54f);  // Lowered Y position
    glVertex2f(0.02f, 0.54f); glVertex2f(0.06f, 0.54f);
glEnd();

// Nose
glColor3f(0.9f, 0.7f, 0.6f);
glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.015f, 0.48f);
    glVertex2f(0.015f, 0.48f);
glEnd();

// Smiling mouth (changed from sad)
glColor3f(0.8f, 0.3f, 0.3f);
glBegin(GL_LINE_STRIP);
for(int i = 0; i <= 10; i++) {
    float angle = PI * 3.0f + PI * 1.0f * i/10;  // Changed angle range for smile
    glVertex2f(0.03f * cos(angle), 0.45f + 0.03f * sin(angle));
}
glEnd();//A curved arc below the nose representing a smile.

    // Blush
    glColor4f(1.0f, 0.6f, 0.6f, 0.4f);
    drawCircle(-0.07f, 0.48f, 0.015f, 50);
    drawCircle(0.07f, 0.48f, 0.015f, 50);

    // Body (dress)
    glColor3f(0.9f, 0.2f, 0.4f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.15f, 0.38f);
        glVertex2f(0.15f, 0.38f);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(-0.2f, 0.0f);
    glEnd();

    // Arms
    glColor3f(1.0f, 0.85f, 0.75f);
    glLineWidth(10.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.16f, 0.35f); glVertex2f(-0.25f, 0.10f);
        glVertex2f(0.16f, 0.35f);  glVertex2f(0.25f, 0.10f);
    glEnd();
    // Hands
    glColor3f(1.0f, 0.85f, 0.75f);
    drawCircle(-0.25f, 0.10f, 0.03f, 50);
    drawCircle(0.25f, 0.10f, 0.03f, 50);

    // Legs (adding rectangles as legs)
    glColor3f(1.0f, 0.85f, 0.75f); // Same color as the arms
// Left leg
glBegin(GL_POLYGON);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(-0.05f, 0.0f);
    glVertex2f(-0.05f, -0.35f);
    glVertex2f(-0.1f, -0.35f);
glEnd();

// Right leg
glBegin(GL_POLYGON);
    glVertex2f(0.05f, 0.0f);
    glVertex2f(0.1f, 0.0f);
    glVertex2f(0.1f, -0.35f);
    glVertex2f(0.05f, -0.35f);
glEnd();


    // Shoes (adding small ellipses for shoes)
    glColor3f(0.2f, 0.2f, 0.2f); // Dark color for shoes
    drawCircle(-0.07f, -0.35f, 0.05f, 20);  // Left shoe
    drawCircle(0.07f, -0.35f, 0.05f, 20);   // Right shoe


}


void drawParent(bool isMale, float xOffset)
//xOffset controls horizontal placement (e.g. left or right of center).
{
    float scale = 1.25f;  // Make parent taller than the girl

    // Head
    glColor3f(1.0f, 0.85f, 0.75f);
    drawCircle(xOffset, scale * 0.5f, 0.12f, 100);

    // Hair

// Long hair for mother (drawn *behind* face)
if (!isMale) {
    glColor3f(0.4f, 0.2f, 0.1f); // Brown hair
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 100; i++) {
        float theta = PI * i / 100.0f;
        float x = xOffset + 0.16f * cos(theta);  // wider than head
        float y = scale * 0.4f + 0.25f * sin(theta);  // slightly lower
        glVertex2f(x, y);
    }
    // Close polygon down behind neck
    glVertex2f(xOffset + 0.1f, scale * 0.0f);  // Right base
    glVertex2f(xOffset - 0.1f, scale * 0.0f);  // Left base
    glEnd();
}
// draw the face/head after the hair
glColor3f(1.0f, 0.85f, 0.75f);
drawCircle(xOffset, scale * 0.5f, 0.12f, 100);

// Father's hair
    if (isMale)
        glColor3f(0.5f, 0.0f, 0.0f); // Black
    else
        glColor3f(0.4f, 0.2f, 0.1f); // Brown

    // Hair cap
    glBegin(GL_POLYGON);
    for (int i = 1; i <= 140; i++) {
        float theta = PI * float(i) / 175;
        glVertex2f(xOffset + 0.12f * cos(theta), scale * 0.5f + 0.12f * sin(theta));
    }
    glEnd();

    // Eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(xOffset - 0.04f, scale * 0.50f, 0.02f, 50);
    drawCircle(xOffset + 0.04f, scale * 0.50f, 0.02f, 50);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(xOffset - 0.04f, scale * 0.50f, 0.008f, 50);
    drawCircle(xOffset + 0.04f, scale * 0.50f, 0.008f, 50);

    // 👓 Spectacles for father
    if (isMale) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);  // Left frame
        for (int i = 0; i <= 40; i++) {
            float theta = 2 * PI * i / 40;
            glVertex2f(xOffset - 0.04f + 0.025f * cos(theta), scale * 0.50f + 0.025f * sin(theta));
        }
        glEnd();
        glBegin(GL_LINE_LOOP);  // Right frame
        for (int i = 0; i <= 40; i++) {
            float theta = 2 * PI * i / 40;
            glVertex2f(xOffset + 0.04f + 0.025f * cos(theta), scale * 0.50f + 0.025f * sin(theta));
        }
        glEnd();

        glBegin(GL_LINES);  // Bridge
        glVertex2f(xOffset - 0.02f, scale * 0.50f);
        glVertex2f(xOffset + 0.02f, scale * 0.50f);
        glEnd();
    }

    // Eyebrows
    glColor3f(0.2f, 0.1f, 0.05f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(xOffset - 0.06f, scale * 0.54f); glVertex2f(xOffset - 0.02f, scale * 0.54f);
        glVertex2f(xOffset + 0.02f, scale * 0.54f); glVertex2f(xOffset + 0.06f, scale * 0.54f);
    glEnd();

    // Nose
    glColor3f(0.9f, 0.7f, 0.6f);
    glBegin(GL_TRIANGLES);
        glVertex2f(xOffset, scale * 0.50f);
        glVertex2f(xOffset - 0.015f, scale * 0.48f);
        glVertex2f(xOffset + 0.015f, scale * 0.48f);
    glEnd();

    // Mouth (smile)
    glColor3f(0.8f, 0.3f, 0.3f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 10; i++) {
        float angle = PI * 3.0f + PI * 1.0f * i / 10;
        glVertex2f(xOffset + 0.03f * cos(angle), scale * 0.45f + 0.03f * sin(angle));
    }
    glEnd();

    // Blush
    glColor4f(1.0f, 0.6f, 0.6f, 0.4f);
    drawCircle(xOffset - 0.07f, scale * 0.48f, 0.015f, 50);
    drawCircle(xOffset + 0.07f, scale * 0.48f, 0.015f, 50);

    // Body
if (isMale) {
    // Father's body: rectangle torso + rectangle bottom (pants-like)
    glColor3f(0.2f, 0.3f, 0.9f); // Blue

    // Torso
    glBegin(GL_POLYGON);
        glVertex2f(xOffset - 0.15f, scale * 0.40f);
        glVertex2f(xOffset + 0.15f, scale * 0.40f);
        glVertex2f(xOffset + 0.15f, scale * 0.10f);
        glVertex2f(xOffset - 0.15f, scale * 0.10f);
    glEnd();

    // Lower rectangle (pants-style)
    glBegin(GL_POLYGON);
        glVertex2f(xOffset - 0.13f, scale * 0.10f);
        glVertex2f(xOffset  +0.0f, scale * 0.10f);
        glVertex2f(xOffset  +0.0f, scale * -0.25f);
        glVertex2f(xOffset - 0.13f, scale * -0.25f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(xOffset  +0.01f, scale * 0.10f);
        glVertex2f(xOffset  +0.13f, scale * 0.10f);
        glVertex2f(xOffset  +0.13f, scale * -0.25f);
        glVertex2f(xOffset  +0.01, scale * -0.25f);
    glEnd();
} else {
    // Mother's body: rectangle torso + triangle dress extension
    glColor3f(0.8f, 0.4f, 0.7f); // Pinkish

    // Torso
    glBegin(GL_POLYGON);
        glVertex2f(xOffset - 0.15f, scale * 0.40f);
        glVertex2f(xOffset + 0.15f, scale * 0.40f);
        glVertex2f(xOffset + 0.15f, scale * 0.10f);
        glVertex2f(xOffset - 0.15f, scale * 0.10f);
    glEnd();

    // Triangle (dress bottom)
    glBegin(GL_TRIANGLES);
        glVertex2f(xOffset - 0.35f, scale * -0.25f);  // left
        glVertex2f(xOffset + 0.35f, scale * -0.25f);  // right
        glVertex2f(xOffset, scale * 0.30f);           // bottom center
    glEnd();
}


    // Arms
    glColor3f(1.0f, 0.85f, 0.75f);
    glLineWidth(10.0f);
    glBegin(GL_LINES);
        glVertex2f(xOffset - 0.15f, scale * 0.35f); glVertex2f(xOffset - 0.25f, scale * 0.10f);
        glVertex2f(xOffset + 0.15f, scale * 0.35f); glVertex2f(xOffset + 0.25f, scale * 0.10f);
    glEnd();

    drawCircle(xOffset - 0.25f, scale * 0.10f, 0.035f, 40);
    drawCircle(xOffset + 0.25f, scale * 0.10f, 0.035f, 40);

    // Legs
    glColor3f(1.0f, 0.85f, 0.75f);
    glBegin(GL_POLYGON);
        glVertex2f(xOffset - 0.1f, scale * -0.25f);
        glVertex2f(xOffset - 0.05f, scale * -0.25f);
        glVertex2f(xOffset - 0.05f, scale * -0.35f);
        glVertex2f(xOffset - 0.1f, scale * -0.35f);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(xOffset + 0.05f, scale *-0.25f);
        glVertex2f(xOffset + 0.1f, scale * -0.25f);
        glVertex2f(xOffset + 0.1f, scale * -0.35f);
        glVertex2f(xOffset + 0.05f, scale * -0.35f);
    glEnd();

    // Shoes
    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircle(xOffset - 0.07f, scale * -0.35f, 0.05f, 20);
    drawCircle(xOffset + 0.07f, scale * -0.35f, 0.05f, 20);
}

void animate(int value) {
    fish1X += fish1Dir;
    fish2X += fish2Dir;

    float maxX = 0.135f;  // Clamp to aquarium edge minus tail

    // Flip direction on hitting edge
    if (fish1X > maxX || fish1X < -maxX) fish1Dir *= -1;
    if (fish2X > maxX || fish2X < -maxX) fish2Dir *= -1;

    // Bubble Y movement
    bubbleY1 += 0.005f;
    bubbleY2 += 0.006f;
    if (bubbleY1 > 0.15f) bubbleY1 = -0.25f; //Raise bubbles vertically.Reset to start below aquarium once they float off screen.
    if (bubbleY2 > 0.15f) bubbleY2 = -0.3f;

    balloonOffset += 0.05f;
    flameFlicker += 0.2f; //Increment offsets controlling balloon bobbing and candle flicker.

    glutPostRedisplay();
    glutTimerFunc(30, animate, 0);//Register next timer callback in ~30ms for smooth animation.

}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGrass();
    drawFloatingBalloons();   // Balloons in the back
    drawBanner();
    drawConfetti();  // 🎉
    drawParent(true, -0.6f);  // Father to the left
    drawParent(false, 0.6f);  // Mother to the right


    drawGirl();  // Girl in center
  // ⬇️ DRAW THESE LAST TO APPEAR IN FRONT
    drawTable();
    drawGiftBox(-0.3f, -0.15f, 0.05f);  // Left gift (floor)
    drawGiftBox(-0.2f, -0.15f, 0.06f);   // Center gift (floor)

    drawCake();
    drawAquarium();  // Now appears beside the cake on the table
  // Bubble Y movement from current mouth positions upward
    localBubbleY1 += 0.01f;
    localBubbleY2 += 0.012f;

    if (localBubbleY1 > 0.4f) localBubbleY1 = 0.02f;
    if (localBubbleY2 > 0.4f) localBubbleY2 = 0.02f;



    glFlush();
}

void init() {
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Birthday");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(30, animate, 0);
    glutMainLoop();
    return 0;
}
