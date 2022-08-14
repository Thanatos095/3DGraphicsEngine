#VERTEX_SHADER
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec4 color;

uniform mat4 u_MVP;
uniform vec4 u_color;

void main()
{
	gl_Position = u_MVP * vec4(aPos, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	color = u_color;
}

#FRAGMENT_SHADER
#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec4 color;
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord) * color;
}