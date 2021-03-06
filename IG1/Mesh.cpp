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
/*	__  __    _    _     _        _    ____  
	|  \/  |  / \  | |   | |      / \  / ___| 
	| |\/| | / _ \ | |   | |     / _ \ \___ \ 
	| |  | |/ ___ \| |___| |___ / ___ \ ___) |
	|_|  |_/_/   \_\_____|_____/_/   \_\____/ */


	/*	 _   _   _   _
		/ \ / \ / \ / \
		(E | J | E | S)
		 \_ / \_ / \_ / 
	*/
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
//-------------------------------------------------------------------------

 /*	  _   _   _   _   _   _   _   _   _   _   _  
	 / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \ 
	( P | O | L | I | E | S | P | I | R | A | L )
	 \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ */
Mesh* Mesh::generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) {
	Mesh* m = new Mesh();
	m->primitive = GL_LINE_STRIP;
	m->numVertices = numVert;


	//dvec2 da por sentado que los ejes se van a crear en el eje 0. x/y; z en el 0
	//creacion del array din�mico.
	m->vertices = new dvec3[m->numVertices];
	//inicializamos las variables x e y accediendo a los atributos de los v�rtices, lado y �ngulo 
	GLdouble x = verIni.x, y = verIni.y, ang = angIni, lado = ladoIni;

	//seudoc�digo siguiente (x, y, ang, long) = (x+long*cos(ang), y+long*sin(ang))


	//se inicializan y con esos se van construyendo el dvec3 
	for (GLuint i = 0; i < m->numVertices; i++)
	{
		m->vertices[i] = dvec3(x, y, 0.0); //se asigna los valores al vector 
		x = x + lado * glm::cos(radians(ang)); //se incrementa el lado del v�rtice x e y
		y = y + lado * glm::sin(radians(ang));
		ang = ang + incrAng; //se incrementa el �ngulo
		lado = lado + incrLado; //se incrementa el lado
	}

	//devolvemos el vector con el numero de vertices inicializado seg�n argumentos 
	return m;
}
//-------------------------------------------------------------------------


/*
	  _   _   _   _   _   _  
	 / \ / \ / \ / \ / \ / \ 
	( D | R | A | G | O | N )
	 \_/ \_/ \_/ \_/ \_/ \_/ 
 */
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
//-------------------------------------------------------------------------

/*
  _   _   _   _   _   _   _   _   _
 / \ / \ / \ / \ / \ / \ / \ / \ / \
( T | R | I | A | N | G | U | L | O )
 \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/
*/
Mesh* Mesh::generaTriangulo(GLdouble r) {
	//genera los tres v�rtices del tri�ngulo equil�tero de radio r, cenrado en el plano=0; primitiva GL_TRIANGLES
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

//-------------------------------------------------------------------------

/*
  _   _   _   _   _   _   _   _   _   _
 / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
( R | E | C | T | A | N | G | U | L | O )
 \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/
*/
Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;
	m->vertices = new dvec3[m->numVertices];

	GLdouble hw = w / 2;
	GLdouble hh = h / 2;
	m->vertices[0] = { -hw, hh, 0 };
	m->vertices[1] = { -hw, -hh, 0};
	m->vertices[2] = { hw,hh , 0 };
	m->vertices[3] = { hw, -hh, 0};
	
	return m;
}

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
	Mesh* m = generaRectangulo(w, h);

	m->colors = new dvec4[m->numVertices];
	// X axis color: red  ( Alpha = 1 : fully opaque)
	m->colors[0] = dvec4(0.5, 0.5, 0.0, 1.0);
	// Y axis color: green
	m->colors[1] = dvec4(0.0, 0.5, 0.5, 1.0);
	// Z axis color: blue
	m->colors[2] = dvec4(0.5, 0.0, 0.5, 1.0);

	m->colors[3] = dvec4(0.5, 0.0, 0.0, 1.0);


	return m;
}

//-------------------------------------------------------------------------

/*
  _   _   _   _   _   _   _   _
 / \ / \ / \ / \ / \ / \ / \ / \
( E | S | T | R | E | L | L | A )
 \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/

*/

Mesh* Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	/*Mesh* m = new Mesh();
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

	return m;*/

	Mesh* e3D = new Mesh();
	e3D->primitive = GL_TRIANGLE_FAN;
	e3D->numVertices = (2 * np + 3) * 2;
	e3D->vertices = new dvec3[e3D->numVertices];
	double ri = re / 2;
	double angIni = 90;
	double incrAng = 360 / (2 * np);
	dvec2 centro(0, 0);
	dvec2 verT(0, 0);
	e3D->vertices[0] = dvec3(0.0, 0.0, 0.0);
	for (int ver = 1; ver < (e3D->numVertices) / 2; ver++)
	{
		if (ver % 2 != 0)ri = ri / 2;
		else ri = ri * 2;
		verT = dvec2(centro.x + ri * cos(radians(angIni)), centro.y + ri * sin(radians(angIni)));
		angIni += incrAng;
		e3D->vertices[ver] = dvec3(verT.x, verT.y, -h);
	}
	e3D->vertices[((e3D->numVertices) / 2) - 1] = dvec3(0.0, 0.0, 0.0);
	for (int ver = (e3D->numVertices) / 2; ver < e3D->numVertices; ver++)
	{
		if (ver % 2 != 0)ri = ri / 2;
		else ri = ri * 2;
		verT = dvec2(centro.x + ri * cos(radians(angIni)), centro.y + ri * sin(radians(angIni)));
		angIni += incrAng;
		e3D->vertices[ver] = dvec3(verT.x, verT.y, h);
	}

	return e3D;
}

//-------------------------------------------------------------------------

/*
  _   _   _   _
 / \ / \ / \ / \
( C | U | B | O )
 \_/ \_/ \_/ \_/
*/

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

//-------------------------------------------------------------------------

//TEXTURAS

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {

	Mesh* m = generaRectangulo(w, h);
	m->texCoords = new dvec2(m->numVertices);


	m->texCoords[0] = dvec2(0, rh);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(rw, rh);
	m->texCoords[3] = dvec2(rw, 0);

	return m;
}

/*que a�ade coordenadas de textura para cubrir el rect�ngulo con una
imagen que se repite rw veces a lo ancho y rh a lo alto. 
*/