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

	if (bidimensional)
	{
		/*******************_Animacion 2D_**********************/
		TrianguloAnimado* triangulo_ = new TrianguloAnimado(30);
		Dragon* dragon_ = new Dragon(3000);
		/*******************_            _**********************/

		// Graphics objects (entities) of the scene
		grObjects.push_back(new EjesRGB(200.0));
		grObjects.push_back(new Poliespiral(160, 1, 1, 50));


		//OBJETOS QUE SE TRANSLADARAN
		grObjects.push_back(triangulo_);
		grObjects.push_back(dragon_);

		auto dragon_mat_ = dragon_->getModelMat();
		dragon_mat_ = translate(dragon_mat_, { 0.2, 4, 0 });
		dragon_mat_ = scale(dragon_mat_, { 0.1,0.1, 0.1 });
		dragon_->setModelMat(dragon_mat_);
	}
	else
	{
		RectanguloRGB* rectanguloRGB_ = new RectanguloRGB(400, 200);
		//Estrella3D* estrella3D_ = new Estrella3D(30, 5, 20);
		Caja* caja_ = new Caja(40);

		/*******************_ANIMACION 3D_**********************/
		EstrellaAnimada* estrellaAnm_ = new EstrellaAnimada(30, 5, 20);

    estrellaAnm_->me = translate(estrellaAnm_->me, dvec3(-30, 5 * 2.5, -1 * 20));
		grObjects.push_back(rectanguloRGB_);
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
