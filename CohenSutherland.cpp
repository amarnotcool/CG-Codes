#include <GL/glut.h>
#include <vector>

struct Pt { float x, y; };
float xmin = -150, ymin = -150, xmax = 150, ymax = 150;
std::vector<Pt> poly = {{-220, 0}, {0, 220}, {220, 0}, {0, -220}};
bool clipped = false;

// Cohen-Sutherland 4-bit Outcode (1=Left, 2=Right, 4=Bottom, 8=Top)
int outcode(Pt p) {
    int c = 0;
    if (p.x < xmin) c |= 1; else if (p.x > xmax) c |= 2;
    if (p.y < ymin) c |= 4; else if (p.y > ymax) c |= 8;
    return c;
}

Pt intersect(Pt a, Pt b, int edge) {
    float m = (b.x != a.x) ? (b.y - a.y) / (b.x - a.x) : 0;
    if (edge == 1) return {xmin, a.y + m * (xmin - a.x)};
    if (edge == 2) return {xmax, a.y + m * (xmax - a.x)};
    if (edge == 4) return {(b.x != a.x) ? a.x + (ymin - a.y) / m : a.x, ymin};
    return {(b.x != a.x) ? a.x + (ymax - a.y) / m : a.x, ymax};
}

std::vector<Pt> clipEdge(std::vector<Pt> in, int edge) {
    std::vector<Pt> out;
    for (int i = 0; i < in.size(); i++) {
        Pt curr = in[i], prev = in[(i + in.size() - 1) % in.size()];
        bool in1 = !(outcode(prev) & edge), in2 = !(outcode(curr) & edge);
        if (in2) {
            if (!in1) out.push_back(intersect(prev, curr, edge));
            out.push_back(curr);
        } else if (in1) out.push_back(intersect(prev, curr, edge));
    }
    return out;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1); // White Clipping Window
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin); glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax); glVertex2f(xmin, ymax);
    glEnd();

    std::vector<Pt> p = poly;
    if (clipped) {
        for (int edge : {1, 2, 4, 8}) p = clipEdge(p, edge); // Clip all 4 edges
        glColor3f(0, 1, 0); // Green when clipped
    } else glColor3f(1, 0, 0); // Red when unclipped

    glBegin(GL_POLYGON);
    for (auto v : p) glVertex2f(v.x, v.y);
    glEnd();
    glFlush();
}

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { clipped = !clipped; display(); }
}

void key(unsigned char k, int x, int y) {
    if (k == 'c') { clipped = true; display(); }
    if (k == 'r') { clipped = false; display(); }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Polygon Clipping");
    gluOrtho2D(-400, 400, -300, 300);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutMainLoop();
}