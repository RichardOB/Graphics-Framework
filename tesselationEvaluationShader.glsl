#version 420

/*
 * All we are saying here is that we are tesselating triangles, and we want each subdivision to be equal.
 * i.e. If we are dividing things into two parts, make them equal parts.
 */
layout (triangles, equal_spacing) in;

/*
 * We rae going to be placing ou new vertices by normalizing them. This only works in model space!
 * In world space, our sphere might be centered around (3 0 3) (Normalizing in that position will lead to bad things)
 *
 * Basically, we keep everything in model space so that our normalization trick works, and then convert to world 
 * space once we are done (Things such as this are the reason we moved from the fixed function pipeline, where tricks
 * like this would not be possible).
 */
 
 
// World Matrix
uniform mat4 world;
// View Matrix
uniform mat4 view;
// Projection Matrix
uniform mat4 projection;

//pass colour along (Will be the same as the position since it is a colour cube/sphere)
out vec3 tes_colour;
out vec3 n;
out vec3 l;


void main()
{
	/*
	 * Our point is being computed in a bit of a weird way:
	 * 1. We take each element of gl_in and get its gl_Position member - These are just the input vertices of the triangle.
	 * 2. Then we multiply each of these with the corresponding coordinate of gl_TessCoord. This vector is the 
	 * 	barycentric coordinates that the tesselator has generated for us.
	 *
	 * After the tesselation control shader completed its work, the tesselator will do all the actual work. This is a fixed-function
	 * stage of the pipeline, so it has no special information about our scene or where we want things to go.
	 *
	 * So it just generates points on the triangle and describes how close the point is to each corner.
	 * So gl_TessCoord.x is how close it is to the first corner, gl_TessCoord.y how close it is to the second corner, and same for gl_TessCoord.z and the third corner.
	 * So the x, y and z after the gl_TessCoord have nothing to do with actual x, y or z coordinates, they are just handy ways to access the first, second and third 
	 * barycentric coordinates. 
	 * 
	 * Multiplying each corner by its barycentric coordinate and summing the results gives us the actual point in model space.
	 */
	vec3 p0 = gl_in[0].gl_Position.xyz * gl_TessCoord.x;
	vec3 p1 = gl_in[1].gl_Position.xyz * gl_TessCoord.y;
	vec3 p2 = gl_in[2].gl_Position.xyz * gl_TessCoord.z;
	
	vec3 position = normalize(p0 + p1 + p2);
	
	//we want our colour to be the same as its position
	tes_colour = position;
	 
	//calculate position in world coordinates so that we can use the vec3 coordinate as a normal vector in world space
	vec4 worldPos = world * vec4(position, 1.0f);
	n = worldPos.xyz;
	 
	//Position of light in world space
	vec4 light = vec4(1, 3, 1, 1);
	
	//find the direction vector to the light source (normalize it since we only need direction)
	l = normalize(light - worldPos).xyz;
	
	gl_Position = projection * view * world * vec4(position, 1.0f);
}