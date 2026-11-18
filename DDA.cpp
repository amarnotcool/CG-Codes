#include <GL/glut.h>
#include <cmath>

int x1, y1, clicks = 0, style = 1;

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1, dy = y2 - y1;
    int steps = std::max(abs(dx), abs(dy));
    float xInc = dx / (float)steps, yInc = dy / (float)steps;
    float x = x1, y = y1;

    glColor3f(0, 1, 1);
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        if (style == 1 || (style == 2 && i % 4 == 0) || (style == 3 && (i / 8) % 2 == 0))
            glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
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
    glutCreateWindow("DDA Line");
    gluOrtho2D(-400, 400, -300, 300);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutMainLoop();
}