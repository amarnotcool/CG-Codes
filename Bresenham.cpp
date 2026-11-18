#include <GL/glut.h>
#include <cmath>

int x1, y1, clicks = 0, style = 1;

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1, sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy, step = 0;

    glColor3f(1, 1, 0);
    glBegin(GL_POINTS);
    while (true) {
        if (style == 1 || (style == 2 && step % 4 == 0) || (style == 3 && (step / 8) % 2 == 0))
            glVertex2i(x1, y1);

        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx)  { err += dx; y1 += sy; }
        step++;
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES); // 4 Quadrants
        glVertex2i(-400, 0); glVertex2i(400, 0);
        glVertex2i(0, -300); glVertex2i(0, 300);
    glEnd();
    glFlush();
}

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int mx = x - 400, my = 300 - y;
        if (clicks == 0) { x1 = mx; y1 = my; clicks = 1; }
        else { drawLine(x1, y1, mx, my); clicks = 0; }
    }
}

void key(unsigned char k, int x, int y) {
    if (k == '1') style = 1;
    else if (k == '2') style = 2;
    else if (k == '3') style = 3;
    else if (k == 'c') display();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bresenham Line");
    gluOrtho2D(-400, 400, -300, 300);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutMainLoop();
}