#include "GL/glew.h"
#include "GL/glut.h" //GL Utility Library. Manages opening windows and runs the main loop
#include <iostream>

#include "Mesh.h"

class Cube: public Mesh
{
	public:
		
		Cube();
	
	private:
		
		void setParameters();
	
		void initAttributes();
	
		/*HANDLES*/
	
		GLint positionLoc = 0;
	
		GLint colourLoc = 0;
};