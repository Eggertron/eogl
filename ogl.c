/*  Author: Edgar Han
    Date: 2017-03-08
    
    This is a wrapper to make programming OpenGL
    easier
*/

#include <GL/glut.h>
#include "ogl.h"

/*  Some defaults for init */
int init() { 
    /* Red diffuse light. */
    GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
    /* Infinite light location */
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */
}
void size(int w, int h) { 
    glutInitWindowSize(w, h);
}

void background(float r, float g, float b, float a) { 
    glClearColor(r, g, b, a); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
int translate(float x, float y, float z) { 
    glTranslatef(x, y, z);
    return 0;
}

int rotate(float d, float x, float y, float z) { 
    glRotatef(d, x, y, z);
}

void rotateX(float d) { 
    glRotatef(d, 1.0, 0.0, 0.0);
}

void rotateY(float d) { 
    glRotatef(d, 0.0, 1.0, 0.0);
}

void rotateZ(float d) { 
    glRotatef(d, 0.0, 0.0, 1.0);
}

void displayFunc(void) { 
    draw();
    glutSwapBuffers();
}

void idleFunc(void) { 
    glutPostRedisplay();
}

int box() { 
    GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
    {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
    GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
    {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
    {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
    GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */
    /* Setup cube vertex data. */
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;


    int i;

    for (i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

/*  The main function will be created here
    and the setup() and draw() functions will need
    to be implemented in the code */
int main(int argc, char **argv) { 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("testing window");
    init();
    setup();    // this needs to be implemented
    glutDisplayFunc(displayFunc);
    glutIdleFunc(idleFunc);     // draw needs to be implemented
    glutMainLoop();
    return 0;
}
