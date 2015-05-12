#version 330 core


struct DirectionalLight
{
	vec3 Color;
	vec3 Direction;
	float Intensity;
};


uniform DirectionalLight SunLight;
uniform sampler2D Texture;
uniform mat4 CameraMatrix;
in vec2 uv;
in vec3 normal;
out vec3 color;


vec3 ambientLight = vec3(0.05, 0.05, 0.05);

void main()
{
	vec3 eyeDirection = normalize((inverse(CameraMatrix) * vec4(0.0, 0.0, 1.0, 1.0)).xyz);
	float cosTheta = clamp(dot(normal, SunLight.Direction), 0, 1);
	float cosAlpha = clamp(dot(eyeDirection, reflect(SunLight.Direction, normal)), 0, 1);
	vec3 materialColor = texture(Texture, uv).rgb;


	vec3 Ambient = materialColor * ambientLight;
	vec3 Diffuse = materialColor * SunLight.Color * SunLight.Intensity * cosTheta;
	vec3 Specular = materialColor * SunLight.Color * SunLight.Intensity * pow(cosAlpha, 5);
	

	color = Ambient + Diffuse;// + Specular;
}