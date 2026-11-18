#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

struct Point {
    float x, y;
    Point operator+(Point p) { return {x + p.x, y + p.y}; }
    Point operator*(float s) { return {x * s, y * s}; }
    Point operator^(float a) {
        a = a * 3.14159 / 180;
        return {x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)};
    }
};

float angle = 0, scale = 1, tx = 0, ty = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    Point p[3] = {{-50, -40}, {50, -40}, {0, 50}};

    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++) {
        Point q = (p[i] * scale) ^ angle;
        q = q + Point{tx, ty};
        glVertex2f(q.x, q.y);
    }
    glEnd();
    glFlush();
}

void key(unsigned char k, int, int) {
    if (k == 't') { tx += 20; ty += 20; }
    if (k == 'r') angle += 10;
    if (k == 's') scale += 0.1;
    if (k == '0') { angle = tx = ty = 0; scale = 1; }
    if (k == 27) exit(0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Transformation");
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMainLoop();
}