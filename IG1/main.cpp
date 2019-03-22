//#include <Windows.h>
//#include <gl/GL.h>    // OpenGL
//#include <gl/GLU.h>   // OpenGL Utility Library
//#include <GL/glut.h>  // OpenGL Utility Toolkit

#include <GL/freeglut.h>  // Free OpenGL Utility Toolkit for creating windows, initializing OpenGL contexts, and handling input events
#include <glm.hpp>  // OpenGL Mathematics. A C++ mathematics library for graphics programming

#include "Camera.h"
#include "Scene.h"
#include "Viewport.h"

#include <iostream>

using namespace std;

//---------- Global variables
//-------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);

// Camera position, view volume and projection
Camera camera(&viewPort);

// Graphics objects of the scene
Scene scene;

// The mouse coordinates
glm::dvec2 mCoord;

// The pressed button
int mBot;

//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void mouseWheel(int whellNumber, int direction, int x, int y);

//-------------------------------------------------------------------------

int main(int argc, char *argv[]) {
  cout << "Starting console..." << '\n';

  // Initialization
  glutInit(&argc, argv);

  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
  glutInitContextFlags(GLUT_DEBUG);  // GLUT_FORWARD_COMPATIBLE

  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

  glutInitWindowSize(800, 600);  // window size
  // glutInitWindowPosition (140, 140);

  glutInitDisplayMode(
      GLUT_RGBA | GLUT_DOUBLE |
      GLUT_DEPTH /*| GLUT_STENCIL*/);  // RGBA colors, double buffer, depth
                                       // buffer and stencil buffer

  int win = glutCreateWindow("IG1");  // window's identifier

  // Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutSpecialFunc(specialKey);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutMouseWheelFunc(mouseWheel);

  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';

  // after creating the context
  camera.set2D();
  scene.init();

  glutMainLoop();

  // cin.ignore(INT_MAX, '\n');  cin.get();
  glutDestroyWindow(win);  // Destroy the context

  return 0;
}
//-------------------------------------------------------------------------

void display()  // double buffering
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  scene.render(camera);

  glutSwapBuffers();
}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight) {
  // Resize Viewport
  viewPort.uploadSize(newWidth, newHeight);

  // Resize Scene Visible Area
  camera.uploadSize(viewPort.getW(), viewPort.getH());  // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y) {
  bool need_redisplay = true;

  switch (key) {
    case 27:                // Escape key
      glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop
      break;
    case '+':
      camera.uploadScale(+0.01);  // zoom in  (increases the scale)
      break;
    case '-':
      camera.uploadScale(-0.01);  // zoom out (decreases the scale)
      break;
    case 'l':
      camera.set3D();
      break;
    case 'o':
      camera.set2D();
      break;
    case 'u':
      scene.update();
      break;
    case 'p':
      camera.changePrj();
      break;
    case '3':
      scene.~Scene();
      scene.init(false);
      break;
    default:
      need_redisplay = false;
      break;
  }  // switch

  if (need_redisplay) glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y) {
  bool need_redisplay = true;

  switch (key) {
    case GLUT_KEY_RIGHT:
      camera.moveLR(1.0);
      //  camera.pitch(1);   // rotate 1 on the X axis
      break;
    case GLUT_KEY_LEFT:
      camera.moveLR(-1.0);
      //  camera.yaw(1);     // rotate 1 on the Y axis
      break;
    case GLUT_KEY_UP:
      camera.moveUD(1.0);
      //  camera.roll(1);    // rotate 1 on the Z axis
      break;
    case GLUT_KEY_DOWN:
      camera.moveUD(-1.0);
      //  camera.roll(-1);   // rotate -1 on the Z axis
      break;
    default:
      need_redisplay = false;
      break;
  }  // switch

  if (need_redisplay) glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
  // state indica si el botón se ha presionado o soltado:
  // GLUT_UP / _DOWN;
  // button es el botón que se ha presionado o soltado:
  // GLUT_LEFT / _RIGHT_BUTTON;
  mBot = button;              // Guardamos el botón del mouse en una var. global
                              // (x, y) es la posición del ratón en la ventana,
                              // siendo (0,0) la esquina (left, top)
  mCoord = glm::dvec2(x, y);  // Guardamos las coordenadas del mouse
}

void motion(int x, int y) {
  glm::dvec2 mp = mCoord;     // guardar la anterior posición en var. temp.
  mCoord = glm::dvec2(x, y);  // Guardamos la posición actual
  mp = mp - mCoord;           // desplazamiento realizado
  if (mBot == GLUT_LEFT_BUTTON) {
    camera.orbit(mp.x * 0.05, -mp.y);  // sensitivity = 0.05
  } else if (mBot == GLUT_RIGHT_BUTTON) {
    if (mp.x != 0) camera.moveLR(mp.x);
    if (mp.y != 0) camera.moveUD(-mp.y);
  }
  glutPostRedisplay();
}

void mouseWheel(int whellNumber, int direction, int x, int y) {
  int m = glutGetModifiers();

  // direction es la dirección de la rueda (+1 / -1)
  if (m == 0) {
    camera.moveFB(direction == 1 ? -500 : 500);
  } else if (m == GLUT_ACTIVE_CTRL) {
    camera.uploadScale(direction == 1 ? 0.01 : -0.01);
  }

  glutPostRedisplay();
}

//-------------------------------------------------------------------------
