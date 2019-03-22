//#pragma once
#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Viewport.h"
//-------------------------------------------------------------------------

class Camera {
public:
	Camera(Viewport* avp) : vp(avp), viewMat(1.0), projMat(1.0),
							xRight(avp->getW() / 2.0), xLeft(-xRight), 
							yTop(avp->getH() / 2.0), yBot(-yTop) { };
	~Camera() {};
	Viewport* getVP() { return vp; }

	// view matrix (the inverse of modeling matrix)
	glm::dmat4 const& getViewMat() const { return viewMat; };
	void uploadVM() const; // transfers viewMat to the GPU

	void set2D();  // eye(0,0,500), look(0,0,0), up(0, 1, 0)
	void set3D();  // eye(500,500,500), look(0,10,0), up(0, 1, 0)

    void setAxes(); // da valor a los tres ejes del sistema de la cámara
    void setVM();
    
	// void pitch(GLdouble a); // rotates a degrees on the X axis
	// void yaw(GLdouble a);   // rotates a degrees on the Y axis
	// void roll(GLdouble a);  // rotates a degrees on the Z axis

    void moveLR(GLdouble cs); // Left / Right
    void moveFB(GLdouble cs); // Forward / Backward
    void moveUD(GLdouble cs); // Up / Down 

    void changePrj(); // Change between Orthogonal to Perspective

    void orbit(GLdouble incAng, GLdouble incY); // modifies the position of the camera

	// projection matrix
	glm::dmat4 const& getProjMat() const { return projMat; };
	void uploadPM() const;  // transfers projMat to the GPU

	// set scene visible area size and transfers projMat to the GPU
	void uploadSize(GLdouble aw, GLdouble ah); 

	// update scale factor and transfers projMat to GPU
	void uploadScale(GLdouble s); 
	
protected:
	
	glm::dmat4 viewMat;    // view matrix = inverse of modeling matrix
	glm::dmat4 projMat;     // projection matrix
    glm::dvec3 eye, look, up; // para generar la matriz de vista con lookAt
    glm::dvec3 right, upward, front; // para los ejes right=u, upward=v, front=-
    GLdouble angle = 1000.0;
	
	GLdouble xRight, xLeft, yTop, yBot;    // size of scene visible area
	GLdouble nearVal = 1, farVal = 10000;  // view volume
	GLdouble factScale = 1;
    GLdouble radius = 1000.0;

    bool orto = true;
	
	Viewport* vp;
};

//-------------------------------------------------------------------------

#endif //_H_Camera_H_
