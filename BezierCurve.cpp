#include <GL/glut.h>
#include <cmath>

void bezier(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 1.01; t += 0.02) {
        float u = 1 - t;
        float x = u*u*u*x0 + 3*u*u*t*x1 + 3*u*t*t*x2 + t*t*t*x3;
        float y = u*u*u*y0 + 3*u*u*t*y1 + 3*u*t*t*y2 + t*t*t*y3;
        glVertex2f(x, y);
    }
    glEnd();
}

void fractal(int depth, float s) {
    if (depth == 0) return;

    for (int i = 0; i < 8; i++) {
        float a = i * 3.14159 / 4; // 45 degrees per petal
        float c = cos(a) * s, sn = sin(a) * s;

        // Rotate base control points (0,0), (50,150), (150,150), (200,0)
        bezier(0, 0,
               50*c - 150*sn,  50*sn + 150*c,
               150*c - 150*sn, 150*sn + 150*c,
               200*c,          200*sn);
    }
    fractal(depth - 1, s * 0.6); // Recursive smaller layer
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 1);
    fractal(4, 1.0); // 4 recursive layers
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bezier Fractal");
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(display);
    glutMainLoop();
}