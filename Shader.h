#include "GL/glew.h"
#include "GL/glut.h" //GL Utility Library. Manages opening windows and runs the main loop
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-pedantic"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "libs/glm/gtc/type_ptr.hpp"
#pragma GCC diagnostic pop

using glm::mat4;
using glm::vec3;
using glm::rotate;
using glm::translate;
using glm::scale;
using glm::perspective;
using glm::lookAt;
using glm::value_ptr; //conversion of matrices to format that shaders expect

using std::string;
using std::cout;

class Shader
{
	public:
		
		
		/*
		 * Constructor:
		 * 
		 * Reads in shader source files, compiles and links them to a program handle
		 */
		Shader(const string& shaderName);
	
		/*
		 * Destructor:
		 *
		 * Cleans up memory
		 */
		~Shader();
	
		/*
		* Load Shader Program from source. Compile it, and output any errors
		* Loads handle of Shader into reference handle.
		*/
		void loadShaderFile(unsigned& handle, const char* file, GLenum shaderType);
		
		/*
		 * Read in file.
		 */
		char* loadFile(const char* fileName);
	
};