#version 330 core

in vec2 UV;

uniform sampler2D mainTexture;
uniform sampler2D lightMap;
uniform vec4 ambientColor;
uniform vec2 resolution;

out vec4 Frag_color;

void main()
{
	vec4 diffuseColor = texture(mainTexture, UV);
	vec2 lightCoord = (gl_FragCoord.xy / resolution.xy);
	vec4 light = texture(lightMap, lightCoord);
	
	vec3 ambient = (ambientColor.rgb * ambientColor.a) + light.rgb;
	vec3 final = diffuseColor.rgb * ambient;
	
	Frag_color = vec4(final, diffuseColor.a);
}
