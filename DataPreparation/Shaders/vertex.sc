$input a_position, a_texcoord0
$output v_texcoord0

#include <bgfx_shader.in>

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(a_position, 1.0);
    v_texcoord0 = a_texcoord0;
}
