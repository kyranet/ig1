#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;  vertices = nullptr;
  delete[] colors;    colors = nullptr;
}
//-------------------------------------------------------------------------

void Mesh::render()
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate, stride, pointer 
    }
	
    glDrawArrays(primitive, 0, numVertices);   // primitive graphic, first index and number of elements to be rendered

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* m = new Mesh();
  m->primitive = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  // X axis vertices
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  // Y axis vertices
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  // Z axis vertices
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  // X axis color: red  ( Alpha = 1 : fully opaque)
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}

Mesh* Mesh::generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) {
	Mesh* m = new Mesh();
	m->primitive = GL_LINE_STRIP;
	m->numVertices = numVert;


	//dvec2 da por sentado que los ejes se van a crear en el eje 0. x/y; z en el 0
	//creacion del array dinámico.
	m->vertices = new dvec3[m->numVertices];
	//inicializamos las variables x e y accediendo a los atributos de los vértices, lado y ángulo 
	GLdouble x = verIni.x, y = verIni.y, ang = angIni, lado = ladoIni;

	//seudocódigo siguiente (x, y, ang, long) = (x+long*cos(ang), y+long*sin(ang))


	//se inicializan y con esos se van construyendo el dvec3 
	for (GLuint i = 0; i < m->numVertices; i++)
	{
		m->vertices[i] = dvec3(x, y, 0.0); //se asigna los valores al vector 
		x = x + lado * glm::cos(radians(ang)); //se incrementa el lado del vértice x e y
		y = y + lado * glm::sin(radians(ang));
		ang = ang + incrAng; //se incrementa el ángulo
		lado = lado + incrLado; //se incrementa el lado
	}

	//devolvemos el vector con el numero de vertices inicializado según argumentos 
	return m;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaDragon(GLuint numVert) {
	Mesh* m = new Mesh();
	m->primitive = GL_POINTS;
	m->numVertices = numVert;
	m->vertices = new dvec3[m->numVertices];

	const GLdouble PR1 = 0.787473;

	double azar;
	dvec3 previous = dvec3(0.0, 0.0, 0.0);
	for (GLuint i = 0; i < m->numVertices; i++)
	{
		azar = rand() / double(RAND_MAX);
		previous = m->vertices[i] = azar < PR1
			? dvec3(
				0.824074 * previous.x + 0.281482 * previous.y - 0.882290,
				-0.212346 * previous.x + 0.864198 * previous.y - 0.110607,
				0)
			: dvec3(
				0.088272 * previous.x + 0.520988 * previous.y + 0.785360,
				-0.463889 * previous.x - 0.377778 * previous.y + 8.095795,
				0);
	}
	return m;
}

Mesh* Mesh::generaTriangulo(GLdouble r) {
	//genera los tres vértices del triángulo equilátero de radio r, cenrado en el plano=0; primitiva GL_TRIANGLES
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLES;

	GLuint numVert = 3;
	m->numVertices = numVert;
	m->vertices = new dvec3[m->numVertices];

	GLdouble angIni = radians(90.0);
	GLdouble incrAng = radians(360.0) / 3.0;
	GLdouble ang = angIni;
	for (GLuint i = 0; i < m->numVertices; i++)
	{
		m->vertices[i] = dvec3(
			0 + r * cos(ang),
			0 + r * sin(ang),
			0
		);
		ang += incrAng;
	}
	return m;

}

Mesh* Mesh::generaTrianguloRGB(GLdouble r) {
	Mesh* m = generaTriangulo(r);

	m->colors = new dvec4[m->numVertices];
	// X axis color: red  ( Alpha = 1 : fully opaque)
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	GLuint numVert = 4;



	return m;
}

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
	Mesh* m = generaRectangulo(w, h);
	return m;
}

Mesh* Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_FAN;
	m->numVertices = 2 * np + 2;
	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = { 0, 0, 0 };

	GLdouble hh = h / 2;
	GLdouble ri = re / 2;
	GLdouble x, z, he;
	GLdouble angle = 0;
	GLdouble angleIncr = 360 / (np * 2);
	for (GLuint i = 1; i < m->numVertices; i++)
	{
		if (i % 2 == 1)
		{
			x = re * cos(radians(angle + angleIncr * i));
			z = re * sin(radians(angle + angleIncr * i));
			he = h;
		}
		else
		{
			x = ri * cos(radians(angle + angleIncr * i));
			z = ri * sin(radians(angle + angleIncr * i));
			he = hh;
		}
		m->vertices[i] = { x, he, z };
	}

	return m;
}

Mesh* Mesh::generaContCubo(GLdouble l)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 10;

	GLdouble h = l / 2;
	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = { h, h, h };
	m->vertices[1] = { h, -h, h };
	m->vertices[2] = { -h, h, h };
	m->vertices[3] = { -h, -h, h };
	m->vertices[4] = { -h, h, -h };
	m->vertices[5] = { -h, -h, -h };
	m->vertices[6] = { h, h, -h };
	m->vertices[7] = { h, -h, -h };
	m->vertices[8] = m->vertices[0];
	m->vertices[9] = m->vertices[1];

	return m;
}
