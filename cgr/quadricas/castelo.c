// Alexandre Maros
// pridexs.com
// CGR - Computacao Grafica
// Quadricas
//
// Castelo
// gcc castelo.c -o castelo -lglut -lGLU -lGL
//
// Keys:
// Controle do portao: q & a
// Controle Camera: x,y,z e r.

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

GLfloat dx, y, z;

GLfloat gatePos;

void init(void) 
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 40.0 };
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0 }; 

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    z=20.0;
    y=15;
    dx=35;
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef (-1.8, 0.0, 0.0);
    glRotatef(dx, 1.0, 0.0, 0.0);
    glRotatef(y , 0.0, 1.0, 0.0);
    glRotatef(z, 0.0, 0.0, 1.0);
    
    GLUquadricObj *q1;
    
    // torre centro
    glPushMatrix();
        q1 = gluNewQuadric();      
        glRotatef(-157.0, 5.0 , 5.0 , 5.0);
        glTranslatef(0.0, 0.0, 0.0);    
        gluCylinder(q1,0.5f,0.5f,1.0f,32,32);
    glPopMatrix(); 
    glPushMatrix();
        glRotatef(-157.0, 5.0 , 5.0 , 5.0);
        glTranslatef(0.0, 0.0, 1.0);
        glutSolidCone (0.7, 1.0, 20, 16);
    glPopMatrix();

    // torre direita
    glPushMatrix();        
        glRotatef(-157.0, 5.0 , 5.0 , 5.0);
        glTranslatef(0.0, 4.0, 0.0);    
        gluCylinder(q1,0.5f,0.5f,1.0f,32,32);
    glPopMatrix(); 
    glPushMatrix();
        glRotatef(-157.0, 5.0 , 5.0 , 5.0);
        glTranslatef(0.0, 4.0, 1.0);
        glutSolidCone (0.7, 1.0, 20, 16);
    glPopMatrix(); 

    //torre fundo esquerda
    glPushMatrix();        
        glRotatef(-157.0, 5.0 , 5.0 , 5.0);
        glTranslatef(-4.0, 0.0, 0.0);    
        gluCylinder(q1,0.5f,0.5f,1.0f,32,32);
        glPopMatrix(); 
    glPushMatrix();
        glRotatef(-157.0, 5.0 , 5.0 , 5.0);
        glTranslatef(-4.0, 0.0, 1.0);
        glutSolidCone (0.7, 1.0, 20, 16);
    glPopMatrix();

    // parede fundo direita
    glPushMatrix();        
        glRotatef(-157.0, 5.0 , 5.0 , 5.0);
        glTranslatef(-4.0, 4.0, 0.0);    
        gluCylinder(q1,0.5f,0.5f,1.0f,32,32);
    glPopMatrix(); 
    glPushMatrix();
        glRotatef(-157.0, 5.0 , 5.0 , 5.0);
        glTranslatef(-4.0, 4.0, 1.0);
        glutSolidCone (0.7, 1.0, 20, 16);
    glPopMatrix();

    // parede portao
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(0.0, 0.8, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(0.0, 1.2, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(0.0, 2.8, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(0.0, 3.2, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();

    // torre
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(0.0, 2.0, 1.2);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0 , 5.0 , 5.0);
        glTranslatef(0.0, 2.0, 1.6);
        glutSolidCone (0.7, 1.0, 20, 16);
    glPopMatrix(); 

    // parede esquerda
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-3.2, 0.0, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-2.4, 0.0, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-1.6, 0.0, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-0.8, 0.0, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();

   // parede lado direito
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-3.2, 4.0, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-2.4, 4.0, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-1.6, 4.0, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-0.8, 4.0, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();

    // parede fundo
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-4.0, 0.8, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-4.0, 1.6, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-4.0, 2.4, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(-4.0, 3.2, 0.4);
        glutSolidCube(0.8);
    glPopMatrix();
    
    // portao
    glPushMatrix();
        glRotatef(-157.0, 5.0, 5.0, 5.0);
        glTranslatef(0.0,+2.0f,gatePos);
        glutSolidCube(0.8);
    glPopMatrix();
    
    glutSwapBuffers();
   
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho (-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 5.0*(GLfloat)h/(GLfloat)w, -20.0, 20.0);
    else
        glOrtho (-5.0*(GLfloat)w/(GLfloat)h, 5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
 }

void keyboard(unsigned char key, int x, int z)
{
    switch (key) {
        case 'x':
            dx += 10.f;
            if (dx > 360.f)
                dx = 0.;
            glutPostRedisplay();
            break;
      case 'y':
          y += 10.;
              if (y > 360.f) 
                  y = 0.f;
          glutPostRedisplay();
          break;
      case 'z':
          z += 10.;
          if (z > 360.f)
              z = 0.;
          glutPostRedisplay();
          break;
      case 'r':
          z=20.0;
          y=15;
          dx=35;
          glutPostRedisplay();
          break;
      case 'q':
          gatePos += 0.1;
          if (gatePos > 1.2)
              gatePos = 1.2;
          glutPostRedisplay();
          break;
      case 'a':
          gatePos -= 0.1;
          if (gatePos < 0.4)
              gatePos = 0.4;
          glutPostRedisplay();
          break;
      case 27:
          exit(0);
          break;
    }
}

int main(int argc, char** argv)
{
    gatePos = 0.4f;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
