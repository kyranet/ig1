#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
     
  // lights
  // textures  
  // meshes

  TrianguloAnimado* triangulo_ = new TrianguloAnimado(30);
  Dragon* dragon_ = new Dragon(3000);

  // Graphics objects (entities) of the scene
  grObjects.push_back(new EjesRGB(200.0)); 
  //solo acepta double por eso .0
  grObjects.push_back(new Poliespiral(160, 1, 1, 50));

  //grObjects.push_back(new Dragon(3000));
  //grObjects.push_back(new TrianguloRGB(100));

  //OBJETOS QUE SE TRANSLADARAN
  grObjects.push_back(triangulo_);
  grObjects.push_back(dragon_);


  auto dragon_mat_ = dragon_->getModelMat();
  dragon_mat_ = translate(dragon_mat_, { 0.2, 4, 0 });
  dragon_mat_ = scale(dragon_mat_, { 0.1,0.1, 0.1 });
  dragon_->setModelMat(dragon_mat_);

  //grObjects.push_back(new RectanguloRGB(200, 100));
  //grObjects.push_back(new Estrella3D(30, 5, 20));
  //grObjects.push_back(new Caja(40));
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources   
  
  for (Entity* el: grObjects)
  {
	  delete el;  el = nullptr;
  }
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

