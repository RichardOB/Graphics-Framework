#include "Mesh.h"

Mesh::Mesh():
FACES(0),
TRIANGLES_PER_FACE(0),
VERTICES_PER_TRIANGLE(0),
INDICES(0),
INDEX_ARRAY_SIZE(0),
DIMENSIONS(0),
COLOUR_COMPONENT_COUNT(0),
VERTEX_SIZE(0),
VERTEX_COUNT(0),
VERTEX_ARRAY_SIZE(0),
name(""),
indexedMesh(true),
wireFrame(false),
meshHandle(0)
{
	glGenVertexArrays(1, &meshHandle);
	bindMesh();
	
}

Mesh::~Mesh()
{
	
}

GLint Mesh::findAttribute(const char* attribName)
{
	GLint current;
	glGetIntegerv(GL_CURRENT_PROGRAM, &current);
	
	GLint location = glGetAttribLocation((GLuint)current, attribName);
	
	if (location == 0)
	{
		fprintf(stderr, "Could not find attribute named '%s'.\n", attribName);
	}
	
	cout << attribName << " : " << location << endl;
	
	return location;
}

void Mesh::bindMesh()
{
	glBindVertexArray(meshHandle);
}

void Mesh::draw()
{
	bindMesh();
	
	//Let openGL know that our input is triangles to be tesselated.
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	
	if (indexedMesh)
	{
		/* Draw whatever is specified by the currently bound mesh (VAO)
		 * 1. Type of primitive we want to draw
		 * 2. Amount of indices in our array
		 * 3. Type of variable stored in the array
		 * 4. Pointer to the actual index array (leave as null to get the bound GL_ELEMENT_ARRAY_BUFFER instead)
		 */
		glDrawElements(GL_PATCHES, INDEX_ARRAY_SIZE, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT);
	}
}

void Mesh::toggleWireFrame()
{
	if (!wireFrame)
	{
		//Switch openGL into wireframe drawing mode
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
		
		wireFrame = true;
	}
	else if (wireFrame)
	{
		//Switch openGL into wireframe drawing mode
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		
		wireFrame = false;
	}
}

