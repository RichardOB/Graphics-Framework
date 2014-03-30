#include "Shader.h"

// Use member initialisation list to initialise the values in the object
Shader::Shader(const string& shaderName):
sName(""),
programHandle(0),
vertexShaderHandle(0), 
geometryShaderHandle(0),
fragmentShaderHandle(0),
tesControlShaderHandle(0),
tesEvalShaderHandle(0),
worldLoc(-1),
viewLoc(-1),
projectionLoc(-1),
worldMatrix(mat4(0.0f)),
viewMatrix(mat4(0.0f)),
projectionMatrix(mat4(0.0f))
{
	string pathToShader = "/Shaders/" + shaderName + "/";
	
	const string VERTEX = pathToShader + VERTEX_SHADER;
	const string TESSELATION_CONTROL = pathToShader + TESSELATION_CONTROL_SHADER;
	const string TESSELATION_EVAL = pathToShader + TESSELATION_EVALUATION_SHADER;
	const string GEOMETRY = pathToShader + GEOMETRY_SHADER;
	const string FRAGMENT = pathToShader + FRAGMENT_SHADER;
	
	//init each shader (Tesselation shaders and Geometry shader are optional)
	loadShaderFile(vertexShaderHandle, VERTEX, GL_VERTEX_SHADER);
	glAttachShader(programHandle, vertexShaderHandle);
	
	loadShaderFile(fragmentShaderHandle, FRAGMENT, GL_FRAGMENT_SHADER);
	glAttachShader(programHandle, fragmentShaderHandle);
	
	//Optional Shaders
	
	if (hasFile(TESSELATION_CONTROL))
	{
		loadShaderFile(tesControlShaderHandle, TESSELATION_CONTROL, GL_TESS_CONTROL_SHADER);
		glAttachShader(programHandle, tesControlShaderHandle);
	}
	else if (hasFile(TESSELATION_EVAL))
	{
		cout << "[WARNING] Tesselation Evaluation file found without Tesselation Control Shader file in Shader " + shaderName << endl;
	}
	
	if (hasFile(TESSELATION_EVAL))
	{
		loadShaderFile(tesControlShaderHandle, TESSELATION_EVAL, GL_TESS_EVALUATION_SHADER);
		glAttachShader(programHandle, tesEvalShaderHandle);
	}
	else if (hasFile(TESSELATION_CONTROL))
	{
		cout << "[WARNING] Tesselation Control file found without Tesselation Evaluation Shader file in Shader " + shaderName << endl;
	}
	
	if (hasFile(GEOMETRY))
	{
		loadShaderFile(geometryShaderHandle, GEOMETRY, GL_GEOMETRY_SHADER);
		glAttachShader(programHandle, geometryShaderHandle);
	}
	
	
	/*Time to "link" things together*/
	
	//Get a handle to a program object (a bigger program made of smaller shader programs)
	programHandle = glCreateProgram();
	
	//Run the linker
	glLinkProgram(programHandle);
	
	int status;
	
	//Get the compile status for the specified handle and store it in the status integer
	glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
	
	//if errors found, we need to print out the error messages
	if (status == GL_FALSE)
	{
		int len;
		
		//We need length of the info log in order to create a character array of that size.
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &len);
		
		char* log = new char[len];
		
		/* Get the actual log file
		 * 1. handle of shader
		 * 2. pass in the length of the buffer so that openGL does not write past the end of the buffer.
		 * 3. pass in a reference to a variable where openGL will record the "actual" amount of characters that was written in the buffer.
		 * 4. pass the "buffer" you wish openGL to write to.
		 */
		glGetProgramInfoLog(programHandle, len, &len, log);
		
		/*Now we print the error, free its memory and quit the application*/
		
		//Throw an exception.
		//fprintf(stderr, "Link error: %s.\n", log);
		cout << "[ERROR] Link Error in Shader " + shaderName + ": " + log << endl;

		//Finally, free the memory allocated.
		delete log;

		//Exit the program.
		exit(-1);
	}
	
	getUniformLocations();
	
}

Shader::~Shader()
{
	
}

void Shader::loadShaderFile(unsigned& handle, const string& file, GLenum shaderType)
{
	/*
	 * shaderType Enum: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
	 */
	
	//Create an object. Get an integer handle on the object (instead of a pointer)
	handle = glCreateShader(shaderType);
	
	//load the file
	char* source = loadFile(file);
	
	/*
	 * Attach shader file to actual shader object.
	 * 1. We send in the handle of the shader program object whose source we want to set.
	 * 2. We state how many indexes the array (which represents the lines in your program) we're passing in has. i.e. an array of arrays of char or char**. 
	 *     We read in the program as one long line and therefore pass in a 1 as the argument.
	 * 3. We send the actual pointer, which must be a const char** (requiring a cast). 
	 * 4. We send in the length of the string. Since ours is NULL_terminated, we can just pass through NULL here.
	 *
	 * NB: 3. gets rid of some "qualifiers" (it makes the char* a constant. We therefore need to drop -Wcast-qual from the makefile.
	 */
	glShaderSource(handle, 1, (const GLchar**)&source, NULL);
	
	//Compile the source code associated with the given handle
	glCompileShader(handle);
	
	//After the shader source has been set inside OpenGL, we can free the memory we allocated. 
	free(source);
	
	/* Now we need to check if the program compiled properly. In order to check for errors
	    we will need to query some information about our object. */
	    
	int status;
	
	//Get the compile status for the specified handle and store it in the status integer
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	
	//if errors found, we need to print out the error messages
	if (status == GL_FALSE)
	{
		int len;
		
		//We need length of the info log in order to create a character array of that size.
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &len);
		
		char* log = new char[len];
		
		/* Get the actual log file
		 * 1. handle of shader
		 * 2. pass in the length of the buffer so that openGL does not write past the end of the buffer.
		 * 3. pass in a reference to a variable where openGL will record the "actual" amount of characters that was written in the buffer.
		 * 4. pass the "buffer" you wish openGL to write to.
		 */
		glGetShaderInfoLog(handle, len, &len, log);
		
		/*Now we print the error, free its memory and quit the application*/
		
		//Throw an exception.
		//fprintf(stderr, "Compilation Error in %s: %s.\n", file,log);
		cout << "[ERROR] Compilation Error in " + file + ": " + log << endl;

		//Finally, free the memory allocated.
		delete log;

		//Exit the program.
		exit(-1);
	}
}

char* Shader::loadFile(const string& fileName)
{
	FILE* file = fopen(fileName.c_str(), "r");//open file for reading
	
	if (file == NULL)
	{
		//fprintf(stderr, "could not open file '%s'.\n", fileName);
		cout << "[ERROR] Could not open file: " + fileName << endl;
	}
	
	//since we don;t know file size, we start with really small array and grow it.
	unsigned int bufferSize = 1;
	char* buffer = (char*) malloc (bufferSize);//malloc() used instead of 'new' because it is guaranteed to work with realloc()
	
	//BASIC IDEA: We read a char, then check if we have space for it. If we don't, we will DOUBLE THE SIZE of the buffer.
	//We therefore need to keep track of where we are in the buffer o perform this check.
	unsigned int index = 0;
	
	//A loop that checks if we are at the end of the file.
	while (true)
	{
		//get next char
		char c = (char) fgetc(file);
		
		//check for errors
		if (ferror(file) != 0)
		{
			//fprintf(stderr, "could not open file '%s'.\n", fileName);
			cout << "[ERROR] Could not open file: " + fileName << endl;
		}
		
		if (index == bufferSize - 1)
		{
			bufferSize *= 2;
			
			//realloc() takes in a void* (so we need to cast our buffer pointer) and the new size for the buffer.
			buffer = (char*) realloc((void*) buffer, bufferSize);//buffer is resized and realloc() is used to avoid copying the old contents over character by character.
		}
		
		//Check if end of file
		if (feof (file))
		{
			break;
		}
		
		//Otherwise, add char to buffer
		buffer[index] = c;
		index ++;
	}
	
	buffer[index] = '\0';
	fclose(file);
	return buffer;
}

bool Shader::hasFile(const string& path)
{
	FILE* file = fopen(path.c_str(), "r");//open file for reading
	
	if (file == NULL)
	{
		return false;
	}
	else
	{
		fclose(file);
	}
	
	return true;
}

GLint Shader::findAttribute(const char* name)
{
	GLint location = glGetAttribLocation(programHandle, name);
	
	if (location == 0)
	{
		//fprintf(stderr, "Could not find attribute named '%s'.\n", name);
		cout << "[WARNING] In Shader " + sName + ": Could not find attribute named '" + name + "'"<<endl;
	}
	
	return location;
}

GLint Shader::findUniform(const char* name)
{
	GLint location = glGetUniformLocation(programHandle, name);
	
	if (location == -1)
	{
		//fprintf(stderr, "Could not find uniform named '%s'.\n", name);
		cout << "[WARNING] In Shader " + sName + ": Could not find uniform named '" + name + "'"<<endl;
	}
	
	return location;
}

void Shader::getUniformLocations()
{
	worldLoc = findUniform("world");
	viewLoc = findUniform("view");
	projectionLoc = findUniform("projection");
}

void Shader::updateMatrixUniform(GLint uniformLocation, mat4 matrix)
{
	GLint current;
	
	glGetIntegerv(GL_CURRENT_PROGRAM, &current);
	
	if (programHandle == (GLuint)current)
	{
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value_ptr(matrix));
	}
}

void Shader::updateWorldUniform(mat4 world)
{
	worldMatrix = world;
	
	updateMatrixUniform(worldLoc, worldMatrix);
}

void Shader::updateViewUniform(mat4 view)
{
	viewMatrix = view;
	
	updateMatrixUniform(viewLoc, viewMatrix);
}

void Shader::updateProjectionUniform(mat4 projection)
{
	projectionMatrix = projection;
	
	updateMatrixUniform(projectionLoc, projectionMatrix);
}

