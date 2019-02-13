#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::uploadMvM(dmat4 const& modelViewMat) const
{ 
	dmat4 aMat = modelViewMat * modelMat;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mesh; mesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat()); 
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------

//clase poliespiral
Poliespiral::Poliespiral(GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert): Entity() {
	mesh = Mesh::generaPoliespiral(glm::dvec2(0, 0), 0, incrAng, ladoIni, incrLado, numVert);
}

Poliespiral::~Poliespiral() {
	delete mesh;
	mesh = nullptr;
}
void Poliespiral::render(Camera const& cam) {
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
		glColor3d(0.0, 0.0, 1.0);
	}
}
//-------------------------------------------------------------------------

//clase poliespiral
Dragon::Dragon(GLuint numVert) : Entity() {
	
	mesh = Mesh::generaDragon(numVert);

	modelMat = translate(modelMat, dvec3(-40.0, -170.0, 0.0));
	modelMat = scale(modelMat, dvec3(40.0, 40.0, 40.0));
}

Dragon::~Dragon() {
	delete mesh;
	mesh = nullptr;
}
void Dragon::render(Camera const& cam) {
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glPointSize(2);
		mesh->render();
		glColor3d(0.0, 0.0, 1.0);
	}
}

//-------------------------------------------------------------------------

//clase triangulo
TrianguloRGB::TrianguloRGB(GLdouble r) : Entity() {
	mesh = Mesh::generaTrianguloRGB(r);
}

TrianguloRGB::~TrianguloRGB() {
	delete mesh;
	mesh = nullptr;
}

void TrianguloRGB::render(Camera const& cam) {
	//glPolygonMode(GL_BACK, GL_LINE);
	//glPolygonMode(GL_BACK, GL_POINT);
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glPointSize(2);
		mesh->render();
		glColor3d(0.0, 0.0, 1.0);
	}
}

//-------------------------------------------------------------------------

//clase rectangulo
RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Entity() {
	mesh = Mesh::generaRectanguloRGB(w, h);
}

RectanguloRGB::~RectanguloRGB() {
	delete mesh;
	mesh = nullptr;
}

void RectanguloRGB::render(Camera const& cam) {
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glPointSize(2);
		mesh->render();
		glColor3d(0.0, 0.0, 1.0);
	}
}

//-------------------------------------------------------------------------

//clase rectangulo
Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h) : Entity() {
	mesh = Mesh::generaEstrella3D(re, np, h);
}

Estrella3D::~Estrella3D() {
	delete mesh;
	mesh = nullptr;
}

void Estrella3D::render(Camera const& cam) {
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
		glColor3d(0.0, 0.0, 1.0);
	}
}
