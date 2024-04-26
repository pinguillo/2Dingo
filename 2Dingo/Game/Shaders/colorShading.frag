#version 130

in vec2 fragPosition;
in vec4 fragColor;
in vec2 fragUV;

out vec4 color;

uniform sampler2D textureSampler;

void main()
{
	vec4 textureColor = texture(textureSampler, fragUV);
	color = fragColor * textureColor;
//	color = vec4(	fragColor.t * (cos(fragPosition.x * 4.0 + time) + 1.0) * 1.0,
//					fragColor.g * (cos(fragPosition.y * 8.0 + time) + 1.0) * 1.0,
//					fragColor.b * (cos(fragPosition.x * 2 + time) + 1.0) * 1.0,
//					fragColor.a) * textureColor;
}