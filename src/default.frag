#version 330 core
out vec4 FragColor;

in vec3 color;

in vec2 texCoord;


uniform sampler2D tex0;

void main()
{
	FragColor = vec4(texture(tex0, texCoord).rgb, 1);
}
