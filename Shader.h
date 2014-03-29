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
using std::endl;

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
		void loadShaderFile(unsigned& handle, const string& file, GLenum shaderType);
		
		/*
		 * Read in file.
		 */
		char* loadFile(const string& fileName);
		
		bool hasFile(const string& path);
		
	private:
		
	/*CONSTANTS*/
	
		const string VERTEX_SHADER = "vertex.glsl";
		const string FRAGMENT_SHADER = "fragment.glsl";
		const string GEOMETRY_SHADER = "geometry.glsl";
		const string TESSELATION_CONTROL_SHADER = "tesselationControlShader.glsl";
		const string TESSELATION_EVALUATION_SHADER = "tesselationEvaluationShader.glsl";
		
	
	/*VARIABLES*/
		
		/*
		 * Handle to this shader program
		 */
		GLuint programHandle;
	
		/*
		 * Handle to Vertex Shader
		 */
		GLuint vertexShaderHandle;
		
		/*
		 * Handle to Geometry Shader
		 */
		GLuint geometryShaderHandle;
		
		/*
		 * Handle to Fragment Shader
		 */
		GLuint fragmentShaderHandle;
		
		/*
		 * Handle to Tesselation Control Shader
		 */
		GLuint tesControlShaderHandle;
		
		/*
		 * Handle to Tesselation Evaluation Shader
		 */
		GLuint tesEvalShaderHandle;
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	
};