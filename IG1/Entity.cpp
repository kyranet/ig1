#include "Entity.h"
#include "Pixmap32RGBA.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

const std::string BALDOSAC_ = "..\\Bmps\\baldosaC.bmp";

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

TrianguloRGB::TrianguloRGB(GLdouble r) {

	mesh = Mesh::generaTrianguloRGB(r);
}

TrianguloRGB::~TrianguloRGB()
{
	delete mesh;
	mesh = nullptr;
}

void TrianguloRGB::update() {
	alfa_++;
	beta_ += 0.1;
}

void TrianguloRGB::render(Camera const& cam)
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

/*--------------------------------------------------------*/
RectanguloTexCor::RectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) : Entity()
{
	
	mesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	texture_ = new Texture();

	texture_->load(BALDOSAC_);
	modelMat = rotate(modelMat, radians(90.0), dvec3(1, 0, 0));
}

RectanguloTexCor::~RectanguloTexCor()
{
	delete mesh;
	mesh = nullptr;
}

void RectanguloTexCor::update()
{
	
}


void RectanguloTexCor::render(Camera const& cam)
{
	if (mesh != nullptr)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_DOUBLE, 0, mesh->getTexCoords());
		texture_->bind();
		
		glPointSize(2);
		glColor3d(0.0, 0.0, 1.0);

		uploadMvM(cam.getViewMat());
		
		mesh->render();	

		texture_->unbind();
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

/*Proporcional:
textCoords(i, j)=(i/NC, j/NF)*/


//  _______         __               __ __         ______ _____  
// |    ___|.-----.|  |_.----.-----.|  |  |.---.-.|__    |     \ 
// |    ___||__ --||   _|   _|  -__||  |  ||  _  ||__    |  --  |
// |_______||_____||____|__| |_____||__|__||___._||______|_____/ 
// 

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h) {

	setModelMat(translate(mat4(getModelMat()), vec3(re / 2, (re + re / 2), re / 2)));
	mesh = Mesh::generaEstrella3D(re, np, h);
	
}

Estrella3D::~Estrella3D()
{
	delete mesh;
	mesh = nullptr;
}


void Estrella3D::update() {
	alfa_++;
}

void Estrella3D::render(Camera const& cam)
{
	if (mesh != nullptr)
	{
		setModelMat(rotate(modelMat, radians(2.0), dvec3(0, 1, 1)));
		glLineWidth(2);
		glColor3d(1.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_FILL);
		uploadMvM(cam.getViewMat());
		mesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
		glColor3d(1.0, 1.0, 0.0);	
		glLineWidth(2);
		uploadMvM(cam.getViewMat());
		mesh->render();
		
	}
}


//TEXTURE

void Texture::init() {
	glGenTextures(1, &id);// genera un identificador para una nueva textura
	glBindTexture(GL_TEXTURE_2D, id);// filters and wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::bind(GLint mode) {  // modo para la mezcla los colores 
	glBindTexture(GL_TEXTURE_2D, id);// activa  la textura
	// la función de mezcla de colores no queda guardada en el objeto
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode); // modos: GL_REPLACE, GL_MODULATE, GL_ADD ...
}

void Texture::load(const std::string & BMP_Name, GLubyte alpha) {
	if (id == 0) init();
	PixMap32RGBA pixMap;// var. local para cargar la imagen del archivo
	pixMap.load_bmp24BGR(BMP_Name);// carga y añade alpha=255
	// carga correcta? -> exception
	if (alpha != 255) pixMap.set_alpha(alpha);
	w = pixMap.width();
	h = pixMap.height();
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixMap.data());// transferir a GPU
}

/*Las formas más habituales de combinar estos colores son:
 GL_REPLACE. Utilizar exclusivamente la textura: C = T(s,t)
 GL_MODULATE. Modular ambos colores: C = C * T(s,t)
 GL_ADD. Sumar ambos colores: C = C + T(s,t)
 GL_DECAL (para texturas RGBA). C = (1-At).C + At.T(s,t)*/



