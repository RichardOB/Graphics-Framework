#include "Cube.h"


Cube::Cube():
Mesh()
{
	setParameters();
	
	GLfloat* vertices = new GLfloat[VERTEX_ARRAY_SIZE];
	int i = 0;
	
	/**BOTTOM FACE**/
	
	//black
	vertices[i++] = -1.0f; //make all 0.0 -0.5 and all 1 0.5
	vertices[i++] = -1.0f;
	vertices[i++] = -1.0f;
	
	//blue
	vertices[i++] = -1.0f;
	vertices[i++] = -1.0f;
	vertices[i++] = 1.0f;
	
	//magenta
	vertices[i++] = 1.0f;
	vertices[i++] = -1.0f;
	vertices[i++] = 1.0f;
	
	//red
	vertices[i++] = 1.0f;
	vertices[i++] = -1.0f;
	vertices[i++] = -1.0f;
	
	/**TOP FACE **/
	
	//green
	vertices[i++] = -1.0f;
	vertices[i++] = 1.0f;
	vertices[i++] = -1.0f;
	
	//cyan
	vertices[i++] = -1.0f;
	vertices[i++] = 1.0f;
	vertices[i++] = 1.0f;
	
	//white 
	vertices[i++] = 1.0f;
	vertices[i++] = 1.0f;
	vertices[i++] = 1.0f;
	
	//yellow 
	vertices[i++] = 1.0f;
	vertices[i++] = 1.0f;
	vertices[i++] = -1.0f;
	
	GLuint* indices = new GLuint[INDEX_ARRAY_SIZE];
	i = 0;
	
	//Left Face
	indices[i++] = 0;
	indices[i++] = 5;
	indices[i++] = 4;
	indices[i++] = 0;
	indices[i++] = 1;
	indices[i++] = 5;
	
	//Right Face
	indices[i++] = 2;
	indices[i++] = 7;
	indices[i++] = 6;
	indices[i++] = 2;
	indices[i++] = 3;
	indices[i++] = 7;
	
	//Front Face
	indices[i++] = 1;
	indices[i++] = 6;
	indices[i++] = 5;
	indices[i++] = 1;
	indices[i++] = 2;
	indices[i++] = 6;
	
	//Back Face
	indices[i++] = 3;
	indices[i++] = 4;
	indices[i++] = 7;
	indices[i++] = 3;
	indices[i++] = 0;
	indices[i++] = 4;
	
	//Top Face
	indices[i++] = 5;
	indices[i++] = 7;
	indices[i++] = 4;
	indices[i++] = 5;
	indices[i++] = 6;
	indices[i++] = 7;
	
	//Bottom Face
	indices[i++] = 2;
	indices[i++] = 1;
	indices[i++] = 0;
	indices[i++] = 2;
	indices[i++] = 0;
	indices[i++] = 3;
	
	
	bindMesh();
	
	/*Now that our mesh is set as the current one, we can start to modify it. Think of the bind function
		as the process of putting something into a desk clamp - once we have the mesh firmly
			between its metal pincers, we are free to start cutting and measuring to our
								hearts' content.*/
								
	/*Before we can set up the vertex arrays that will be associated with this mesh, we're going to put
	* the vertex data into buffers. This is because we need an object (or a "class", depending on how you look at it)
	* to handle writing all this data to the GPU and keeping track of it in memory etc.*/
	
	//Create handle for buffer
	GLuint indexBuffer, vertexBuffer;
	
	//Create an openGL object called a Buffer Object
	glGenBuffers(1, &indexBuffer);
	//clamp the buffer object with the  target: GL_ELEMENT_ARRAY_BUFFER clamp. 
	//This clamp (or "target" as openGL calls them) is used to specify things for our mesh.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	
	/*load data into our buffer
	 * 1. Specify which "clamp" to load data into
	 * 2. How much data (in bytes) we are loading into buffer i.e. size of  index array * amount of bytes taken up by the data type it stores [which is integer values values in this case]
	 * 3. Provide the array from which we will load the actual data
	 * 4. Give openGL a hint as to what we are going to do with the buffer. Since we arent going to read from it, or modify it, we will go with GL_STATIC_DRAW
	 */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDEX_ARRAY_SIZE * (int)sizeof(GLuint), indices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
	/*Now we need to SPECIFY THE FORMAT of the data we just loaded into the buffer [VERY IMPORTANT]*/
	
	glBufferData(GL_ARRAY_BUFFER, VERTEX_ARRAY_SIZE * (int)sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	
	initAttributes();
	
	//We need to enable the position input so that openGL knows we intend to provide some input.
	glEnableVertexAttribArray((GLuint)positionLoc);
	/* Provide some input for the position attribute
	 * 1. The input we are providing
	 * 2. The amount of components for each vertex (each vertex has exactly three components in its position)
	 * 3. Data type of our input
	 * 4. Flag indicating whether the data provided is normalised
	 * 5. Stride (The length of a step from one vertex to another)in bytes
	 * 6. The offset (which is where the data we are passing in starts
	 */
	glVertexAttribPointer((GLuint)positionLoc, DIMENSIONS, GL_FLOAT, GL_FALSE, VERTEX_SIZE  * (int)sizeof(GLfloat), 0);
	
	glEnableVertexAttribArray((GLuint)colourLoc);
	/* Provide some input for the position attribute
	 * 1. The input we are providing
	 * 2. The amount of components for each vertex (each vertex has exactly three components in its colour)
	 * 3. Data type of our input
	 * 4. Flag indicating whether the data provided is normalised
	 * 5. Stride (The length of a step from one vertex to another)in bytes
	 * 6. The offset (which is where the data we are passing in starts
	 */
	glVertexAttribPointer((GLuint)colourLoc, COLOUR_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, VERTEX_SIZE * (int)sizeof(GLfloat), 0);
	
	delete [] vertices;
	
}

void Cube::initAttributes()
{
	positionLoc = findAttribute("position");
	colourLoc = findAttribute("colour");
}

void Cube::setParameters()
{
	/**faces on a cube. */
	FACES = 6;
	/** Number of triangles on a face */
	TRIANGLES_PER_FACE = 2;
	/** Number of vertices in a triangle. */
	VERTICES_PER_TRIANGLE = 3;
	/** Number of indices used for drawing a cube. */
	INDICES= FACES * TRIANGLES_PER_FACE * VERTICES_PER_TRIANGLE;
	/** The size of the index array. */
	INDEX_ARRAY_SIZE = INDICES;

	/** Number of dimensions used. */
	DIMENSIONS = 3;
	/** The amount of components in our colour vectors.(RGB). */
	COLOUR_COMPONENT_COUNT = 3;
	/** The size of an individual vertex. */
	VERTEX_SIZE = DIMENSIONS;

	/** The amount of vertices in a cube. */
	VERTEX_COUNT = 8;
	/** The size of the vertex array. */
	VERTEX_ARRAY_SIZE = VERTEX_COUNT * VERTEX_SIZE;
}