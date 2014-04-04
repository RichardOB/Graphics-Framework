#version 420

layout (vertices = 3) out; //states that each polygon we deal with has three vertices. Anything more would mean we're dealing with Bezier, B-spline, or cubic Hermite parametric surfaces

uniform float level;

void main()
{
	/*NB: The TCS (Tesselation Control Shader) is conceptually executed per-primitive, but it actually
	 * runs a seperate instance (or invocation) for each vertex of that primitive.
	 * This is where the gl_InvocationID comes in - it simply tells us which vertex we're being executed
	 * (invoked) on.
	 */
	
	//Pass the positions of our vertices through
	// We are just simply copying the input position to the output position for each vertex in the primitive
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	
	/* This is the part that is interesting.
	 * Here, we set three outer tesselation levels, and one inner level. 
	 * - The outer levels control the subdivision of the triangle's edges:
	 *	A value of 1.0f says "leave it alone", a value of 2.0f means "divide this edge in two" 
	 * - The inner level controlss the subdivision of the triangle's inside. 
	 *	The value here basically says how many internal vertices to generate:
	 *	- Once we get to three internal vertices we get a tiny triangle in the center of our original triangle.
	 * 
	 */
	gl_TessLevelOuter[0] = level;
	gl_TessLevelOuter[1] = level;
	gl_TessLevelOuter[2] = level;
	gl_TessLevelInner[0] = level;
	
}
