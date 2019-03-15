#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------
void Scene::init(bool bidimensional)
{ 
	// OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

	grObjects.push_back(new EjesRGB(200.0));

	//escena 2D
	if (bidimensional)
	{
		/*******************_Animacion 2D_**********************/
		//objetos que se trasladaran una vez creada la escena
		TrianguloRGB* triangulo_ = new TrianguloRGB(30);
		Dragon* dragon_ = new Dragon(3000);
		/*******************_            _**********************/

		// Graphics objects (entities) of the scene
		grObjects.push_back(new Poliespiral(160, 1, 1, 50));
		grObjects.push_back(triangulo_);
		grObjects.push_back(dragon_);

		//se recoge la matriz identidad para efectuar la transformación
		auto dragon_mat_ = dragon_->getModelMat();
		dragon_mat_ = translate(dragon_mat_, { 0.2, 4, 0 });	//traslación
		dragon_mat_ = scale(dragon_mat_, { 0.1,0.1, 0.1 });		//escala
		dragon_->setModelMat(dragon_mat_);						//se aplican los cambios
	}
	//si se produce el evento por input: Escena 3D
	else
	{
		RectanguloTexCor* rectanguloTexCor_ = new RectanguloTexCor(400, 200, 4, 2);
		Caja* caja_ = new Caja(40);

		/*******************_ANIMACION 3D_**********************/
		Estrella3D* estrellaAnm_ = new Estrella3D(30, 6, 20);

		// Graphics objects (entities) of the scene
		grObjects.push_back(rectanguloTexCor_);
		grObjects.push_back(caja_);
		grObjects.push_back(estrellaAnm_);
	}
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources   
  
  for (Entity* el: grObjects)
  {
	  delete el;  el = nullptr;
  }
  grObjects.clear();
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam)
{
	for (Entity* el: grObjects)
	{
		el->render(cam);
	}
}

void Scene::update() {
	for (auto el : grObjects)
	{
		el->update();
	}
}
//-------------------------------------------------------------------------
