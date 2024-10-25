#include "GeoDraw.h"
#include "math.h"
#include <stdio.h>

// Constants
#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 500
#define HOLE_X 700
#define HOLE_Y 400
#define HOLE_RADIUS 30
#define BALL_RADIUS 20
#define FRICTION 0.9

// STROKE COUNTER
int strokeCount = 0;

// Function prototypes
void drawField();
void updateBallPosition(float* x, float* y, float* velX, float* velY);
int isInHole(float x, float y);
void scoreBoard();


void drawField() {
    gd_resetCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    gd_setCanvasColor(GREEN);
    gd_setFillColor(BLACK);
    gd_circleFilled(HOLE_X, HOLE_Y, HOLE_RADIUS);
    gd_setFillColor(WHITE);
    gd_circleFilled(700, 400, BALL_RADIUS);
    gd_save("grass.html");
}

void updateBallPosition(float* x, float* y, float* velX, float* velY) {
    *x += *velX;
    *y += *velY;

    *velX *= FRICTION;
    *velY *= FRICTION;

    // Stop the ball if it slows down enough
    if (fabs(*velX) < 0.01 && fabs(*velY) < 0.01) {
        *velX = 0;
        *velY = 0;
    }
}

int isInHole(float x, float y) {
    float distance = sqrt(pow(x - HOLE_X, 2) + pow(y - HOLE_Y, 2));
    return distance <= HOLE_RADIUS;
}

void scoreBoard() {
    char strokeText[20];
    sprintf(strokeText, "STROKES: %d", strokeCount);
    gd_setTextAlignment(LEFT);
    gd_setPenColor(BLACK);
    gd_text(strokeText, 10, 490);
}

int main() {
    float ballX = 60, ballY = 100, velX = 10, velY = 10;

    drawField();

    while (1) {
        gd_clear();
        drawField();

        updateBallPosition(&ballX, &ballY, &velX, &velY);

        if (isInHole(ballX, ballY)) {
            printf("Hole in one! Strokes: %d\n", strokeCount);
            break;  // End game
        }

        if (velX == 0 && velY == 0) {
            strokeCount++;
            printf("Hit the ball again! Strokes so far: %d\n", strokeCount);
            velX = 10;  // Reset velocity for the next stroke
            velY = 10;
        }

        scoreBoard();
        gd_pause(30);
    }

    return 0;
}
