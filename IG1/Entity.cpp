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

void Entity::update() {

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
		glColor3d(0.0, 0.0, 1.0);
		glLineWidth(1);
		mesh->render();
		
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

TrianguloAnimado::TrianguloAnimado(GLdouble r) {

	mesh = Mesh::generaTrianguloRGB(r);
}

TrianguloAnimado::~TrianguloAnimado()
{
	delete mesh;
	mesh = nullptr;
}

void TrianguloAnimado::update() {
	alfa_++;
	beta_ += 0.1;
}

void TrianguloAnimado::render(Camera const& cam)
{
	if (mesh != nullptr)
	{
		glPointSize(2);
		//dmat4 modelMatAux = modelMat;

		modelMat = translate(dmat4(1), dvec3(100 * sin(beta_), 100 * cos(beta_), 0.0));
		modelMat = rotate(modelMat, radians(alfa_), { 0.0, 0.0, 1.0 });

		uploadMvM(cam.getViewMat());
		mesh->render();
		glColor3d(0.0, 0.0, 1.0);
		//modelMat = moelMatAux;
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
	modelMat = rotate(modelMat, radians(90.0), dvec3(1, 0, 0));
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

EstrellaAnimada::EstrellaAnimada(GLdouble re, GLdouble np, GLdouble h) {

	mesh = Mesh::generaEstrella3D(re, np, h);
	modelMat = translate(modelMat, dvec3(-h, re * 2.5, -1 * h));
	

}

EstrellaAnimada::~EstrellaAnimada()
{
	delete mesh;
	mesh = nullptr;
}


void EstrellaAnimada::update() {
	alfa_++;
}

void EstrellaAnimada::render(Camera const& cam)
{

	if (mesh != nullptr)
	{

		//primero me recoge la traslación en escena
		//luego en render, la camara debe en el upload.. camara * modelmat, pero antes hay que hacer la traslacion
		dmat4 modMatAux = dmat4(1.0);

		glColor3d(0.3, 0.5, 1.0);
		glLineWidth(2);
		modelMat = rotate(modelMat, radians(alfa_), dvec3(0, 0, 1));
		
		uploadMvM(cam.getViewMat() * me);
		mesh->render();

		
		modelMat = rotate(modelMat, radians(180.0), dvec3(0, 0, 1));


		glColor3d(0.3, 0.5, 1.0);
		modelMat = rotate(modelMat, radians(alfa_), dvec3(0, 0, 1));
		glLineWidth(2);
		uploadMvM(cam.getViewMat() * me);
		mesh->render();
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
	modelMat = translate(modelMat, dvec3(-l/2, l/2, -l/2));
	
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
		glColor3d(1.0, 0.0, 0.0);	
		glLineWidth(2);
		uploadMvM(cam.getViewMat());
		mesh->render();
		
	}
}
