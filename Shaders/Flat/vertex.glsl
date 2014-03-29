#version 420

layout (location = 1) in vec3 position; //inputs. Locations are just numbers that bridge gap between shader and c++ programs.
layout (location = 2) in vec3 colour; 

out vec3 v_colour;//we need to define an output value since there is no predefined one like for position.


void main() //shader program's entry point
{
	//v_colour = colour;
	v_colour = vec3(1.0f,0.0f,0.0f);
	
	//gl_Position is a special GLSL variable for the vertex shader program.
	//It is compulsory to assign this variable in the vertex shader!!!
	//gl_Position is a vec4, so we need to fill in missing ones.
	//vec4(position, depth, point=1.0 or vector=0.0)
	gl_Position =  vec4(position, 1.0f);
	
	
	
}

/* Vertex Shader.
	
	Must:
		-Accept a single vertex as input
		-Provide a single vertex as output
	
	i.e. Per Vertex Shader.

*/
