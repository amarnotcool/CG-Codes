#include <GL/glut.h>
#include <cmath>

// Base Class (Polymorphism via virtual functions)
class Object {
public:
    float x = 0, y = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
};

// Derived Class: Bouncing Ball (Inheritance)
class Ball : public Object {
public:
    float dx = 3, dy = 4;
    bool paused = false;

    void draw() override {
        glColor3f(1, 0.8, 0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 15)
            glVertex2f(x + 20 * cos(i * 3.14 / 180), y + 20 * sin(i * 3.14 / 180));
        glEnd();
    }

    void update() override {
        if (paused) return;
        x += dx; y += dy;
        if (x > 230 || x < -230) dx = -dx;
        if (y > 230 || y < -230) dy = -dy;
    }
};

Ball b;
Object* obj = &b; // Base class pointer for Runtime Polymorphism

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    obj->draw(); // Polymorphic call
    glutSwapBuffers();
}

void timer(int) {
    obj->update(); // Polymorphic call
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void key(unsigned char k, int, int) {
    if (k == 'w') { b.dx *= 1.2; b.dy *= 1.2; }
    if (k == 's') { b.dx *= 0.8; b.dy *= 0.8; }
    if (k == 'p') b.paused = !b.paused;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OOP Bouncing Ball");
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}