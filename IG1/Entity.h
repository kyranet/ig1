//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"

#include <string>
//-------------------------------------------------------------------------

/*
  _____ _                _____ ______ ____           _____ ______
 / ____| |        /\    / ____|  ____|  _ \   /\    / ____|  ____|
| |    | |       /  \  | (___ | |__  | |_) | /  \  | (___ | |__
| |    | |      / /\ \  \___ \|  __| |  _ < / /\ \  \___ \|  __|
| |____| |____ / ____ \ ____) | |____| |_) / ____ \ ____) | |____
 \_____|______/_/    \_\_____/|______|____/_/    \_\_____/|______|
*/
class Entity 
{
public:
	Entity() : modelMat(1.0) { }; 
	virtual ~Entity() { };

	virtual void render(Camera const& cam) = 0;

	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };

	void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }

	virtual void update();
  
protected:

	Mesh* mesh = nullptr;   // surface mesh
	glm::dmat4 modelMat;    // modeling matrix

	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
	EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(Camera const& cam); 
};

//-------------------------------------------------------------------------

class Poliespiral : public Entity {

public:
	Poliespiral(GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral();
	virtual void render(Camera const& cam);
};

//-------------------------------------------------------------------------

class Dragon : public Entity {

public:
	Dragon(GLuint numVert);
	~Dragon();
	virtual void render(Camera const& cam);
};

//-------------------------------------------------------------------------

class RectanguloRGB : public Entity {

public:
	RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(Camera const& cam);
};

//-------------------------------------------------------------------------

class Caja : public Entity {

public:
	Caja(GLdouble l);
	~Caja();
	virtual void render(Camera const& cam);
};


class TrianguloRGB : public Entity {

protected:
	GLdouble alfa_;
	GLdouble beta_ = 0.25;


public:
	TrianguloRGB(GLdouble r);
	~TrianguloRGB();
	
	virtual void render(Camera const& cam);
	virtual void update();

};

//-------------------------------------------------------------------------

class Estrella3D: public Entity {

public:
	Estrella3D(GLdouble re, GLdouble np, GLdouble h);
	~Estrella3D();
	virtual void render(Camera const& cam);
	virtual void update();
	
	//Matriz cuadrada
	glm::dmat4 me = glm::dmat4 (1.0);

private:
	//variable para la transformación en ejecución según evento
	GLdouble alfa_;
	 
};

// utiliza la clase PixMap32RGBA para el método load
class Texture
{
public:
	Texture(GLint wrap = GL_REPEAT) : w(0), h(0), id(0) {};
	~Texture() { if (id != 0) glDeleteTextures(1, &id); };
	void load(const std::string & BMP_Name, GLubyte alpha = 255);// cargar y transferir a GPU
	void bind(GLint mode = GL_REPLACE);// para mezcla de colores
	void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
protected:
	GLuint w, h;// dimensiones de la imagen
	GLuint id;// identificador interno (GPU) de la textura
	void init();
};



//RECTANGULO TEXCOR
class RectanguloTexCor : public Entity {

public:
	RectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~RectanguloTexCor();

	virtual void render(Camera const& cam);
	virtual void update();

protected:
	Texture* texture_ = nullptr;
};

#endif //_H_Entities_H_



/*Texture Wrapping: qué se hace cuando las coordenadas de textura
caen fuera del rango [0, 1].
GL_REPEAT: la textura se repite (tiling). Se ignora la parte entera
de las coordenadas de textura.
GL_CLAMP: coordenadas de textura superiores a 1 se ajustan a 1,
y las coordenadas inferiores a 0 se ajustan a 0.*/