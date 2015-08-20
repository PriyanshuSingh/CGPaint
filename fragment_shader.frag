#version 410 core

uniform vec3 fColor;
out vec4 frag_colour;

void main(void)
{
    frag_colour = vec4(fColor, 1.0f);
}

