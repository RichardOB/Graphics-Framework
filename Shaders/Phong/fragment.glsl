#version 420

in vec3 tes_colour;
in vec3 n;
in vec3 l;

out vec4 colour;



void main() //shader program's entry point
{
	//Position of static camera
	vec3 view = normalize(vec3(1,1,1));
	
	float ambientCoefficient = 0.1f;
	
	float diffuse = dot(l, n);
	
	vec3 r = 2 * dot(l, n) * n - l;
	float specular = pow(dot(r, view), 50);
	
	float intensity = ambientCoefficient;
	
	//we do not wan't to add negative values of diffuse or specular to intensity
	if (diffuse > 0)
	{
		intensity += diffuse;
	}
	
	if (specular > 0)
	{
		intensity += specular;
	}
	
	colour = vec4(tes_colour * intensity, 0.6f); //with alpha value added. For now it is left to completely opaque.
}

/* Fragment Shader.

	MUST: - Provide a single output (A final colour for a fragment

	CAN: - Receive multiple inputs. Everything that is output from previous shader is an input for the Fragment Shader Program

	NB: No LAYOUT section since the Fragment Shader has no interface to our program - it only has interface with shader programs before it.
*/
