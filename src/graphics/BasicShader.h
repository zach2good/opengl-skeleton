#pragma once

#include "ShaderProgram.h"
#include "glm\glm.hpp"
#include "DirLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class BasicShader : public ShaderProgram
{
public:
	BasicShader(const std::string& fileName);
	
	void SetMVP(mat4 m, mat4 v, mat4 p);

	void SetDirLight(DirLight dirLight);

	void SetPointLight(PointLight pointLight);

	void SetSpotLight(SpotLight spotLight);
};
