#include <GL/glut.h>

void floodFill(int x, int y) {
    float c[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, c); // Read current pixel color

    // If pixel is black (background: R=0, G=0, B=0), fill it
    if (c[0] == 0 && c[1] == 0 && c[2] == 0) {
        glColor3f(0, 1, 0); // Fill color: Green
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
        glFlush();

        floodFill(x + 1, y);
        floodFill(x - 1, y);
        floodFill(x, y + 1);
        floodFill(x, y - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES); // Multi-colored edges (shows why Flood Fill is used over Boundary Fill)
        glColor3f(1, 0, 0); glVertex2i(200, 200); glVertex2i(350, 200);
        glColor3f(0, 0, 1); glVertex2i(350, 200); glVertex2i(350, 350);
        glColor3f(1, 1, 0); glVertex2i(350, 350); glVertex2i(200, 350);
        glColor3f(1, 0, 1); glVertex2i(200, 350); glVertex2i(200, 200);
    glEnd();
    glFlush();
}

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        floodFill(x, 600 - y); // Flip Y-axis to match OpenGL coordinates
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Flood Fill");
    gluOrtho2D(0, 800, 0, 600);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}