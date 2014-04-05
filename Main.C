#include "Main.h"

using namespace std;


//Display Callback
//Called whenever the contents of the window need to be redrawn on the window. 
//e.g. when window was minimized and gets restored, or if window was behind other windows
void display ()
{
	//Clear the screen
	//Clears both the screen's colour and the depth of anything it is displaying
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Let openGL know that our input is triangles to be tesselated.
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	/* Draw whatever is specified by the currently bound mesh (VAO)
	 * 1. Type of primitive we want to draw
	 * 2. Amount of indices in our array
	 * 3. Type of variable stored in the array
	 * 4. Pointer to the actual index array (leave as null to get the bound GL_ELEMENT_ARRAY_BUFFER instead)
	 */
	glDrawElements(GL_PATCHES, INDEX_ARRAY_SIZE, GL_UNSIGNED_INT, 0);
	
	//Instruct OpenGL to send all our commands to the graphics card (if it hasn't done so already)
	glFlush();
	
	//Swap the buffers. i.e. we write to one while other displays to prevent "screen tearing" where half of the old pixels still remain.
	glutSwapBuffers();
	
	printFPS();
	
	last_frame = getTime();
}

void keyboard(unsigned char key, int x, int y)
{
	int size;
	
    switch (key)
   {
      case 'w':
         xRot += ANGLE_DELTA;
         break;
      
      case 's':
         xRot -= ANGLE_DELTA;
         break;
      
      case 'a':
         yRot += ANGLE_DELTA;
         break;
      
      case 'd':
         yRot -= ANGLE_DELTA;
         break;
      
       case 'q':
         zRot += ANGLE_DELTA;
         break;
       
      case 'e':
         zRot -= ANGLE_DELTA;
         break;
      
      case 'h':
	xMove += SCALE;
	break;
      
      case 'f':
	xMove -= SCALE;
	break;
      
      case 't':
	yMove += SCALE;
	break;
      
      case 'g':
	yMove -= SCALE;
	break;
      
      case 'r':
	zMove += SCALE;
	break;
      
      case 'y':
	zMove -= SCALE;
	break;
      
       case 'i':
	yScale += SCALE;
	break;
       
       case 'k':
	yScale -= SCALE;
	break;
       
       case 'j':
	xScale += SCALE;
	break;
       
       case 'l':
	xScale -= SCALE;
	break;
       
       case 'u':
	zScale += SCALE;
	break;
       
       case 'o':
	zScale -= SCALE;
	break;
       
       case 'z':
	xScale = yScale = zScale = 1.0f;
        xRot = yRot = zRot = 0.0f;
        xMove = yMove = zMove = 0.0f;
        FOVY = 60.0f; 
	break;
       
	case '=':
         FOVY += 1;
         break;
	
	case '-':
         FOVY -= 1;
         break;
	
	case 'c':
		tessLevel += 1.0f;

		size=sizeof shaders/sizeof(Shader*);
		
		for(int i = 0; i < size; i ++)
		{
			shaders[i]->updatefloatUniform(tesselationLevelLoc, tessLevel);
		}
	break;
	
	case 'x':
		tessLevel -= 1.0f;

		size=sizeof shaders/sizeof(Shader*);
		
		for(int i = 0; i < size; i ++)
		{
			shaders[i]->updatefloatUniform(tesselationLevelLoc, tessLevel);
		}
	break;
	
	case '1':
		shaders[0]->activate();
		shaderSwitch(0);
	break;
	
	case '2':
		shaders[1]->activate();
		shaderSwitch(1);
	break;
	
	case '3':
		shaders[2]->activate();
		shaderSwitch(2);
	break;
	
	case KEY_ESCAPE:
         printf("Bye!\n");
         exit(0);
         break;
	
      default:
         printf("Key '%c' pressed, mouse at (%d, %d).\n", key, x, y);
         break;
   }
	
	updateWorld();
	updateProjection(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutPostRedisplay();

}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
		{
			cout << "Left ";
			break;
		}
		case GLUT_MIDDLE_BUTTON:
		{
			cout << "Middle ";
			break;
		}
		case GLUT_RIGHT_BUTTON:
		{
			cout << "Right ";
			break;
		}
		
		default:
			cout << "unknown ";
			break;
	}
	
	cout << "mouse button ";
	
	switch (state)
	{
		case GLUT_UP:
			cout << "released ";
			break;
		
		case GLUT_DOWN:
			cout << "pressed ";
			break;
		
		default:
			cout << "did something we don't know...";
			break;

	}
	
	cout << "at [" << x << ", " << y << "] " << endl;
}

void reshape(int newWidth, int newHeight)
{
	//Fix our viewport
	glViewport (0, 0, newWidth, newHeight);
	
	//Ask GLUT for a redraw. Tells GLUT to call display function
	glutPostRedisplay();
}

void updateWorld()
{
	mat4 world;
	
	vec3 xAxis (1, 0, 0);
	world = rotate(world, xRot, xAxis);
	
	vec3 yAxis (0, 1, 0);
	world = rotate(world, yRot, yAxis);
	
	vec3 zAxis (0, 0, 1);
	world = rotate(world, zRot, zAxis);
	
	vec3 translation(xMove, yMove, zMove);
	world = translate (world, translation);
	
	vec3 scales(xScale, yScale, zScale);
	world = scale(world, scales);
	
	//glUniformMatrix4fv(worldLoc, 1, GL_FALSE, value_ptr(world));
	//phongShader->updateWorldUniform(world);
	
	int size;
	size=sizeof shaders/sizeof(Shader*);
	
	for(int i = 0; i < size; i ++)
	{
		shaders[i]->updateWorldUniform(world);
	}
}

void updateView()
{
	mat4 worldView = lookAt(cameraEye, cameraAt, cameraUp);
	
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(worldView));
	//phongShader->updateViewUniform(worldView);
	
	int size;
	size=sizeof shaders/sizeof(Shader*);
	
	for(int i = 0; i < size; i ++)
	{
		shaders[i]->updateViewUniform(worldView);
	}
	
}

void updateProjection(int width, int height)
{
	GLfloat aspect = (GLfloat)width / (GLfloat)height; //Aspect ratio, where width and height are the dimensions of the window
	
	mat4 projection = perspective(FOVY, aspect, NEAR, FAR);
	
	//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));
	//phongShader->updateProjectionUniform(projection);
	
	int size;
	size=sizeof shaders/sizeof(Shader*);
	
	for(int i = 0; i < size; i ++)
	{
		shaders[i]->updateProjectionUniform(projection);
	}
}

int getTime()
{
	//Return time in milliseconds since the program started (Elapsed Time)
	return glutGet(GLUT_ELAPSED_TIME);
}

void printFPS()
{
	
	int now = getTime();
		
	if (now - last_print > MILLISECONDS_PER_SECOND)
	{
		//Measure the actual time between to frames
		int deltaT = now - last_frame;
	
		//Convert deltaT to seconds 
		double seconds = (double)deltaT/MILLISECONDS_PER_SECOND; 
		double fps = 1.0 / seconds; //1.0 instead of 1 so that we get floating point division.
		
		cout << "FPS: "<<fps<<endl;
		last_print = now;
	}
}

void idle()
{
	int now = getTime();
	int deltaT = now - last_frame;
	
	if (deltaT >= TARGET_DELTA_T)
	{
		//Queue up a new frame. Ask GLUT for a redraw.
		glutPostRedisplay();
	}

}

void initGLEW()
{
	//initialise GLEW (GL Extension Wrangler - Managers/Wrangles shader programs)
	glewInit();
	
	if (!GLEW_VERSION_3_2)
	{
		fprintf(stderr, "This progarm requires OpenGL 3.2");
		exit(-1);
	}
}

void init ()
{
	glEnable(GL_VERTEX_ARRAY);//?
	//switch on Depth Testing to ensure that if something is behind something, it does not show
	glEnable(GL_DEPTH_TEST);
	//switch on Face Culling (Gets rid of faces looking away from us)
	glEnable(GL_CULL_FACE);
	
	//Switch openGL into wireframe drawing mode
	//glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_BACK, GL_LINE);
	
	//set the "clear colour" (background colour in any other API) to blue. (red, green, blue, alpha)
	glClearColor(0.0, 0.0, 1.0, 1.0);
	
	//compile and link shader programs
	//loadShaderPrograms();
	flatShader = new Shader("Flat");
	shaders[0] = flatShader;
	gouraudShader = new Shader("Gouraud");
	shaders[1] = gouraudShader;
	phongShader = new Shader("Phong");
	shaders[2] = phongShader;
	
	shaders[0]->activate();
	
	//activate the shader program to tell openGL that we are talking about this program when we use a function that has reference to the shaders.
	//glUseProgram(program);
	
	shaderSwitch(0);
	
	
	
	updateProjection(WINDOW_WIDTH, WINDOW_HEIGHT);
	updateView();
	updateWorld();
	
	loadGeometry();
	
	glBindVertexArray(cube);
	
	last_print = getTime();
	last_frame = getTime();
}

void shaderSwitch(int pos)
{
	//get a handle on the position and colour inputs in the shader
	positionLoc = findAttribute("position");
	colourLoc =  findAttribute("colour");
	
	//worldLoc = findUniform("world");
	worldLoc = shaders[pos]->findUniform("world");
	//viewLoc = findUniform("view");
	viewLoc = shaders[pos]->findUniform("view");
	//projectionLoc = findUniform("projection");
	projectionLoc = shaders[pos]->findUniform("projection");
	
	//tesselationLevelLoc = findUniform("level");
	
	tesselationLevelLoc = shaders[pos]->findUniform("level");
	
	int size=sizeof shaders/sizeof(Shader*);
		
		for(int i = 0; i < size; i ++)
		{
			shaders[i]->updatefloatUniform(tesselationLevelLoc, tessLevel);
		}
}

void loadGeometry()
{
	loadCube();
}

void loadCube()
{
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
	
	
	/*Create our Vertex Attribute Array Object (Mesh "Object")
	 * 1. Number of Meshes (VAOs) we want
	 * 2. Where to store their handle(s) (Array of GLuints or unsigned ints [or single])
	 */
	glGenVertexArrays(1, &cube);
	
	//Now set the mesh (VAO) we have just created to be the one currently in use
	glBindVertexArray(cube);
	
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(INDEX_ARRAY_SIZE * sizeof(GLuint)), indices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
	/*Now we need to SPECIFY THE FORMAT of the data we just loaded into the buffer [VERY IMPORTANT]*/
	
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(VERTEX_ARRAY_SIZE * sizeof(GLfloat)), vertices, GL_STATIC_DRAW);
	
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
	glVertexAttribPointer((GLuint)positionLoc, DIMENSIONS, GL_FLOAT, GL_FALSE, (GLsizei)(VERTEX_SIZE * sizeof(GLfloat)), 0);
	
	glEnableVertexAttribArray((GLuint)colourLoc);
	/* Provide some input for the position attribute
	 * 1. The input we are providing
	 * 2. The amount of components for each vertex (each vertex has exactly three components in its colour)
	 * 3. Data type of our input
	 * 4. Flag indicating whether the data provided is normalised
	 * 5. Stride (The length of a step from one vertex to another)in bytes
	 * 6. The offset (which is where the data we are passing in starts
	 */
	glVertexAttribPointer((GLuint)colourLoc, COLOUR_COMPONENT_COUNT, GL_FLOAT, GL_FALSE, (GLsizei)(VERTEX_SIZE * sizeof(GLfloat)), 0);
	
	delete [] vertices;
}

GLint findAttribute(const char* name)
{
	GLint current;
	glGetIntegerv(GL_CURRENT_PROGRAM, &current);
	
	GLint location = glGetAttribLocation((GLuint)current, name);
	
	if (location == 0)
	{
		fprintf(stderr, "Could not find attribute named '%s'.\n", name);
	}
	
	cout << name << " : " << location << endl;
	
	GLint test = phongShader->findAttribute(name);
	
	cout << name << " (from shader): " << test << endl;
	
	return location;
}

void cleanUp()
{
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	
	glDeleteProgram(program);
}

int main (int argc, char** argv)
{
	glutInit(&argc, argv); //Glut needs access to argc and argv since it implements some command line switches
	
	//Use two buffers to prevent screen tearing, 
	//use a depth buffer to work in 3D, 
	//and use a colour screen
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(640, 480); //Size of the window we would like
	glutCreateWindow("COS344_Practical_3");//Set title of the window
	
	glutDisplayFunc(display); //Register Display Event/ Callback
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	initGLEW();
	init();
	
	//Hand over to GLUT
	//Will cause GLUT to start calling our callback functions (like Display) and handle anything else it needs to.
	glutMainLoop();
	
	cleanUp();
	
	return 0;	
}
