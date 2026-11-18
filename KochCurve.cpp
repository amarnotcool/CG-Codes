#include <GL/glut.h>
#include <cmath>

void koch(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        return;
    }

    float dx = (x2 - x1) / 3, dy = (y2 - y1) / 3;
    float xA = x1 + dx, yA = y1 + dy;
    float xB = x1 + 2 * dx, yB = y1 + 2 * dy;

    // 60-degree peak point (cos 60° = 0.5, sin 60° = 0.866)
    float xC = xA + (dx * 0.5 - dy * 0.866);
    float yC = yA + (dx * 0.866 + dy * 0.5);

    koch(x1, y1, xA, yA, depth - 1);
    koch(xA, yA, xC, yC, depth - 1);
    koch(xC, yC, xB, yB, depth - 1);
    koch(xB, yB, x2, y2, depth - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4, 0.8, 1.0);
    glBegin(GL_LINES);
        koch(-150, -90, 150, -90, 4); // Bottom side
        koch(150, -90, 0, 170, 4);    // Right side
        koch(0, 170, -150, -90, 4);   // Left side
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Koch Snowflake");
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(display);
    glutMainLoop();
}