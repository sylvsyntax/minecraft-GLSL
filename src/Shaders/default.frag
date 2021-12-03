#version 330 core
out vec4 FragColor;

in vec3 crntPos;

in vec3 Normal;

in vec3 color;

in vec2 texCoord;

uniform sampler2D diffuse0;

uniform vec4 lightColor;

uniform vec3 lightPos;

uniform vec3 camPos;

vec4 pointLight()
{

	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);

	float a = 3.0;
	float b = .7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);


	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	return texture(diffuse0, texCoord) * lightColor * (diffuse * inten + ambient + specular * inten);
}

vec4 direcLight()
{
	float ambient = 0.20f;

	vec3 normal = normalize(Normal);

	// must be opposite direction of where you want to face
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	return texture(diffuse0, texCoord) * lightColor * (diffuse + ambient + specular);

}

void main()
{
	FragColor = pointLight();
}
