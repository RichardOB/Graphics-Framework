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
		
		/*
		 * Verify whether shader exists
		 */
		bool hasFile(const string& path);
		
		/*
		 * Send Matrices to Shader Program
		 */
		void loadMatrixUniforms();
		
		/*
		 * Activate this shader program
		 */
		void activate();
		
		/*
		 *Returns location of an attribute within this shader program.
		 */
		GLint findAttribute(const char* name);
		
		/*
		 * Returns location of a Uniform within this shader program.
		 */
		GLint findUniform(const char*);
		
		void getUniformLocations();
		
		void updateMatrixUniform(GLint uniformLocation, mat4 matrix);
		
		void updatefloatUniform(GLint uniformLocation, float value);
		
		void updateWorldUniform(mat4 world);
		
		void updateViewUniform(mat4 view);
		
		void updateProjectionUniform(mat4 projection);
		
		
	private:
		
	/*CONSTANTS*/
	
		const string VERTEX_SHADER = "vertex.glsl";
		const string FRAGMENT_SHADER = "fragment.glsl";
		const string GEOMETRY_SHADER = "geometry.glsl";
		const string TESSELATION_CONTROL_SHADER = "tesselationControlShader.glsl";
		const string TESSELATION_EVALUATION_SHADER = "tesselationEvaluationShader.glsl";
	
	/*VARIABLES*/
		
		/*
		 * Name of this Shader Program instance
		 */
		string sName;
	
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
		
		/*
		 *Handle for the world matrix uniform. 
		 */
		GLint worldLoc;

		/*
		 *Handle for the view matrix uniform. 
		 */
		GLint viewLoc;

		/*
		 *Handle for the projection matrix uniform. 
		 */
		GLint projectionLoc;
		
		/*
		 * Shader's World, View and Projection Matrices. Used to update and keep track of the coresponding uniforms
		 */
		mat4 worldMatrix;
		mat4 viewMatrix;
		mat4 projectionMatrix;
	
};