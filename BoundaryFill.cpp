#include <GL/glut.h>

void boundaryFill(int x, int y) {
    float c[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, c); // Read current pixel color

    // Stop if pixel is White boundary (1,1,1) OR already filled Cyan (0,1,1)
    if (!(c[0] == 1 && c[1] == 1 && c[2] == 1) && !(c[0] == 0 && c[1] == 1 && c[2] == 1)) {
        glColor3f(0, 1, 1); // Fill color: Cyan
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
        glFlush();

        boundaryFill(x + 1, y);
        boundaryFill(x - 1, y);
        boundaryFill(x, y + 1);
        boundaryFill(x, y - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1); // Single white boundary color
    glBegin(GL_LINE_LOOP);
        glVertex2i(200, 200);
        glVertex2i(400, 200);
        glVertex2i(300, 350);
    glEnd();
    glFlush();
}

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        boundaryFill(x, 600 - y); // Flip Y-axis
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Boundary Fill");
    gluOrtho2D(0, 800, 0, 600);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}