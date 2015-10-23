#include "BasicShader.h"

BasicShader::BasicShader(const std::string& fileName)
	: ShaderProgram(fileName) {}

void BasicShader::SetMVP(mat4 m, mat4 v, mat4 p)
{
	SetUniform4fv("model", m);
	SetUniform4fv("view", v);
	SetUniform4fv("projection", p);
}

void BasicShader::SetDirLight(DirLight dirLight)
{
	SetUniform3fv("dirLight.direction", dirLight.direction);

	SetUniform3fv("dirLight.ambient", dirLight.ambient);
	SetUniform3fv("dirLight.diffuse", dirLight.diffuse);
	SetUniform3fv("dirLight.specular", dirLight.specular);
}

void BasicShader::SetPointLight(PointLight pointLight)
{
	SetUniform3fv("pointLight.position", pointLight.position);

	SetUniform3fv("pointLight.ambient", pointLight.ambient);
	SetUniform3fv("pointLight.diffuse", pointLight.diffuse);
	SetUniform3fv("pointLight.specular", pointLight.specular);

	SetUniform1f("pointLight.constant", pointLight.constant);
	SetUniform1f("pointLight.linear", pointLight.linear);
	SetUniform1f("pointLight.quadratic", pointLight.quadratic);
}

void BasicShader::SetSpotLight(SpotLight spotLight)
{
	SetUniform3fv("spotLight.position", spotLight.position);
	SetUniform3fv("spotLight.direction", spotLight.direction);

	SetUniform3fv("spotLight.ambient", spotLight.ambient);
	SetUniform3fv("spotLight.diffuse", spotLight.diffuse);
	SetUniform3fv("spotLight.specular", spotLight.specular);

	SetUniform1f("spotLight.constant", spotLight.constant);
	SetUniform1f("spotLight.linear", spotLight.linear);
	SetUniform1f("spotLight.quadratic", spotLight.quadratic);

	SetUniform1f("spotLight.cutOff", spotLight.cutOff);
	SetUniform1f("spotLight.outerCutOff", spotLight.outerCutOff);
}