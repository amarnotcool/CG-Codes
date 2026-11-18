#include <GL/glut.h>

void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r, p = 1 - r;

    glColor3f(0, 1, 1);
    glBegin(GL_POINTS);
    while (x <= y) {
        // Plot all 8 symmetric octants
        glVertex2i(xc + x, yc + y); glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y); glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x); glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x); glVertex2i(xc - y, yc - x);

        x++;
        if (p < 0) p += 2 * x + 1;
        else { y--; p += 2 * (x - y) + 1; }
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle(0, 0, 150); // Center (0,0), Radius 150
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Midpoint Circle");
    gluOrtho2D(-400, 400, -300, 300);
    glutDisplayFunc(display);
    glutMainLoop();
}