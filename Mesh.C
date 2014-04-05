#include "Mesh.h"

Mesh::Mesh(const string& meshName):
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
meshHandle(0)
{
	name = meshName;
	glGenVertexArrays(1, &meshHandle);
	bindMesh();
	
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
	
	if (indexedMesh)
	{
		glDrawElements(GL_PATCHES, INDEX_ARRAY_SIZE, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT);
	}
}