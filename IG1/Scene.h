//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
//#include "Mesh.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene() { };
	~Scene();
    void init(bool bidimensional = true); 
    void render(Camera const& cam);
	void update();
	  
protected:

	  std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

