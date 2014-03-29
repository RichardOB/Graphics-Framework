#version 420

in vec3 col;

out vec4 colour;



void main() //shader program's entry point
{
	colour = vec4(col, 1.0f); //with alpha value added. For now it is left to completely opaque.
}

/* Fragment Shader.

	MUST: - Provide a single output (A final colour for a fragment

	CAN: - Receive multiple inputs. Everything that is output from previous shader is an input for the Fragment Shader Program

	NB: No LAYOUT section since the Fragment Shader has no interface to our program - it only has interface with shader programs before it.
*/
