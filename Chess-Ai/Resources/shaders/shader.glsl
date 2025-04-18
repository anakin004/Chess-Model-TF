#shader vertex
#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 v_TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    v_TexCoord = aTexCoord;
}


#shader fragment
#version 460 core

in vec2 v_TexCoord;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
	FragColor = texture(tex, v_TexCoord);
}