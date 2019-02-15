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

//  _______ __               ______ _______ ______ 
// |    ___|__|.-----.-----.|   __ \     __|   __ \
// |    ___|  ||  -__|__ --||      <    |  |   __ <
// |_______|  ||_____|_____||___|__|_______|______/
//        |___|                                    

EjesRGB::EjesRGB(GLdouble l)
	: Entity() 
{
  mesh = Mesh::createRGBAxes(l);
}

EjesRGB::~EjesRGB() 
{ 
	delete mesh;
	mesh = nullptr; 
}

void EjesRGB::render(Camera const& cam)
{
	if (mesh != nullptr)
	{
		uploadMvM(cam.getViewMat()); 
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}

//  ______         __ __                     __              __ 
// |   __ \.-----.|  |__|.-----.-----.-----.|__|.----.---.-.|  |
// |    __/|  _  ||  |  ||  -__|__ --|  _  ||  ||   _|  _  ||  |
// |___|   |_____||__|__||_____|_____|   __||__||__| |___._||__|
//                                   |__|                       

Poliespiral::Poliespiral(GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert)
	: Entity()
{
	mesh = Mesh::generaPoliespiral(glm::dvec2(0, 0), 0, incrAng, ladoIni, incrLado, numVert);
}

Poliespiral::~Poliespiral()
{
	delete mesh;
	mesh = nullptr;
}

void Poliespiral::render(Camera const& cam)
{
	if (mesh != nullptr)
	{
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
		glColor3d(0.0, 0.0, 1.0);
	}
}

//  _____                               
// |     \.----.---.-.-----.-----.-----.
// |  --  |   _|  _  |  _  |  _  |     |
// |_____/|__| |___._|___  |_____|__|__|
//                   |_____|            

Dragon::Dragon(GLuint numVert)
	: Entity()
{
	mesh = Mesh::generaDragon(numVert);

	modelMat = translate(modelMat, dvec3(-40.0, -170.0, 0.0));
	modelMat = scale(modelMat, dvec3(40.0, 40.0, 40.0));
}

Dragon::~Dragon()
{
	delete mesh;
	mesh = nullptr;
}

void Dragon::render(Camera const& cam)
{
	if (mesh != nullptr)
	{
		uploadMvM(cam.getViewMat());
		glPointSize(2);
		mesh->render();
		glColor3d(0.0, 0.0, 1.0);
	}
}

//  _______        __                           __        
// |_     _|.----.|__|.---.-.-----.-----.--.--.|  |.-----.
//   |   |  |   _||  ||  _  |     |  _  |  |  ||  ||  _  |
//   |___|  |__|  |__||___._|__|__|___  |_____||__||_____|
//                                |_____|                 

TrianguloRGB::TrianguloRGB(GLdouble r)
	: Entity()
{
	mesh = Mesh::generaTrianguloRGB(r);
}

TrianguloRGB::~TrianguloRGB()
{
	delete mesh;
	mesh = nullptr;
}

void TrianguloRGB::render(Camera const& cam)
{
	//glPolygonMode(GL_BACK, GL_LINE);
	//glPolygonMode(GL_BACK, GL_POINT);
	if (mesh != nullptr)
	{
		uploadMvM(cam.getViewMat());
		glPointSize(2);
		mesh->render();
		glColor3d(0.0, 0.0, 1.0);
	}
}

//  ______              __                            __        
// |   __ \.-----.----.|  |_.---.-.-----.-----.--.--.|  |.-----.
// |      <|  -__|  __||   _|  _  |     |  _  |  |  ||  ||  _  |
// |___|__||_____|____||____|___._|__|__|___  |_____||__||_____|
//                                      |_____|                 

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h)
	: Entity()
{
	mesh = Mesh::generaRectanguloRGB(w, h);
}

RectanguloRGB::~RectanguloRGB()
{
	delete mesh;
	mesh = nullptr;
}

void RectanguloRGB::render(Camera const& cam)
{
	if (mesh != nullptr)
	{
		uploadMvM(cam.getViewMat());
		glPointSize(2);
		mesh->render();
		glColor3d(0.0, 0.0, 1.0);
	}
}

//  _______         __               __ __         ______ _____  
// |    ___|.-----.|  |_.----.-----.|  |  |.---.-.|__    |     \ 
// |    ___||__ --||   _|   _|  -__||  |  ||  _  ||__    |  --  |
// |_______||_____||____|__| |_____||__|__||___._||______|_____/ 
// 

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h)
	: Entity()
{
	mesh = Mesh::generaEstrella3D(re, np, h);
}

Estrella3D::~Estrella3D()
{
	delete mesh;
	mesh = nullptr;
}

void Estrella3D::render(Camera const& cam)
{
	if (mesh != nullptr)
	{
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
		glColor3d(0.0, 0.0, 1.0);
	}
}

//  ______         __        
// |      |.---.-.|__|.---.-.
// |   ---||  _  ||  ||  _  |
// |______||___._||  ||___._|
//               |___|       

Caja::Caja(GLdouble l)
	: Entity()
{
	mesh = Mesh::generaContCubo(l);
}

Caja::~Caja()
{
	delete mesh;
	mesh = nullptr;
}

void Caja::render(Camera const& cam)
{
	if (mesh != nullptr)
	{
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
		glColor3d(0.0, 0.0, 1.0);
	}
}
