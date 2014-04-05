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

class Mesh
{
	public:
		
		
		/*
		 * Constructor:
		 * 
		 * Reads in shader source files, compiles and links them to a program handle
		 */
		Mesh(const string& shaderName);
	
		/*
		 * Destructor:
		 *
		 * Cleans up memory
		 */
		~Mesh();
	
		/*
		 * Gets location of an attribute within the shader program.
		 */
		GLint findAttribute(const char* name);
	
		/*
		 * Set this mesh to be the one currently in use
		 */
		void bindMesh();
		
		/*
		 * Draw this mesh to buffer
		 */
		void draw();
	
		
		
	private:
		
		/*CONSTANTS*/
		
		/**faces on a mesh. */
		GLuint FACES;
		/** Number of triangles on a face */
		GLuint TRIANGLES_PER_FACE;
		/** Number of vertices in a triangle. */
		GLuint VERTICES_PER_TRIANGLE;
		/** Number of indices used for drawing the mesh. */
		GLuint INDICES;
		/** The size of the index array. */
		GLsizei INDEX_ARRAY_SIZE;

		/** Number of dimensions used. */
		GLuint DIMENSIONS;
		/** The amount of components in our colour vectors.(RGB). */
		GLuint COLOUR_COMPONENT_COUNT;
		/** The size of an individual vertex. */
		GLuint VERTEX_SIZE;
		/** The amount of vertices in a cube. */
		GLsizei VERTEX_COUNT;
		/** The size of the vertex array. */
		GLuint VERTEX_ARRAY_SIZE;
		
			
		/*VARIABLES*/
		
		/*
		 * Name of this Shader Program instance
		 */
		string name;
		
		bool indexedMesh;
		
		/*HANDLES*/
		
		/*
		 *Handle for the red triangle. 
		 */
		GLuint meshHandle;
		
		
};