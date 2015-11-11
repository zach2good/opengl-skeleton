attribute vec4 a_vertex; // vertex position
attribute vec3 a_normal; // vertex normal
attribute vec2 a_texcoord; // texture coordinates

varying float v_diffuse;
varying vec2 v_texcoord;

void main()
{
	gl_Position = a_vertex;
}

