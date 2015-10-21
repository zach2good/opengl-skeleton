#include "common.h"

class BasicShader : public ShaderProgram
{
public:
	BasicShader(const std::string& fileName)
		: ShaderProgram(fileName) {}

	void SetMVP(mat4 m, mat4 v, mat4 p)
	{
		SetUniform4fv("model", m);
		SetUniform4fv("view", v);
		SetUniform4fv("projection", p);
	}

	void SetDirLight(DirLight dirLight)
	{
		SetUniform3fv("dirLight.direction", dirLight.direction);

		SetUniform3fv("dirLight.ambient", dirLight.ambient);
		SetUniform3fv("dirLight.diffuse", dirLight.diffuse);
		SetUniform3fv("dirLight.specular", dirLight.specular);
	}

	void SetPointLight(PointLight pointLight)
	{
		SetUniform3fv("pointLight.position", pointLight.position);

		SetUniform3fv("pointLight.ambient", pointLight.ambient);
		SetUniform3fv("pointLight.diffuse", pointLight.diffuse);
		SetUniform3fv("pointLight.specular", pointLight.specular);

		SetUniform1f("pointLight.constant", pointLight.constant);
		SetUniform1f("pointLight.linear", pointLight.linear);
		SetUniform1f("pointLight.quadratic", pointLight.quadratic);
	}

	void SetSpotLight(SpotLight spotLight)
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
};

int main(int argc, char *argv[])
{
	Window window = Window("OpenGL Skeleton", 1280, 720);

	Input input = Input();

	Camera camera = Camera();
	camera.Position = vec3(0, 0, 5);

	BasicShader debugShader = BasicShader("../res/shaders/debugShader"); 
	BasicShader basicShader = BasicShader("../res/shaders/basicShader");
	ShaderProgram lampShader = ShaderProgram("../res/shaders/lampShader");
	ShaderProgram depthShader = ShaderProgram("../res/shaders/depthShader");

	Mesh objectMesh = Mesh("../res/models/head/head.obj");

	Texture diffuseMap = Texture("../res/models/head/Diffuse.png");
	Texture specularMap = Texture("../res/models/head/Specular.png");
	Texture normalMap = Texture("../res/models/head/Normal.png");

	diffuseMap.Bind(diffuseMap.GetTextureID());
	specularMap.Bind(specularMap.GetTextureID());
	normalMap.Bind(normalMap.GetTextureID());

	Transformation objectTrans = Transformation();
	objectTrans.SetScale(vec3(5.8f));

	Mesh dirLightMesh = Mesh("../res/models/cube.obj");
	Mesh pointLightMesh = Mesh("../res/models/sphere.obj");
	Mesh flashlightMesh = Mesh("../res/models/flashlight.obj");

	Transformation dirLightTrans = Transformation();
	dirLightTrans.SetPosition(vec3(0, 2.0f, 0));
	dirLightTrans.SetScale(vec3(0.2f));

	Transformation pointLightTrans = Transformation();
	pointLightTrans.SetPosition(vec3(1, 1, 1));
	pointLightTrans.SetScale(vec3(0.1f));

	Transformation spotLightTrans = Transformation();
	spotLightTrans.SetPosition(vec3(0.0f, 0.0f, 2.0f));
	spotLightTrans.SetRotation(vec3(90.0f, 0.0f, 0.0f));
	spotLightTrans.SetScale(vec3(0.1f));

	DirLight dirLight = DirLight(vec3(-0.2f, -1.0f, -0.3f), WHITE);
	PointLight pointLight = PointLight(vec3(0.0f), RED);
	SpotLight spotLight = SpotLight(spotLightTrans.GetPosition(), camera.Front, GREEN);

	int centerX = window.getWidth() / 2;
	int centerY = window.getHeight() / 2;

	bool useNormalMapping = true;

	bool showWireFrame = false;
	bool showNormalMap = false;
	bool showSpecularMap = false;

	DebugUi debugUi = DebugUi(window.getWindow());

	float speedMultiplier = 1.0f;

	debugUi.addFloat("Speed Multiplier", &speedMultiplier, 0.0f, 5.0f);

	debugUi.addVec3("Camera", &camera.Position);

	debugUi.addBool("Normal Mapping", &useNormalMapping);
	debugUi.addBool("Show Wireframe", &showWireFrame);
	debugUi.addBool("Show Normal Map", &showNormalMap);
	debugUi.addBool("Show Specular Map", &showSpecularMap);

	debugUi.addColor("DirLight Color", &dirLight.color);
	debugUi.addColor("PointLight Color", &pointLight.color);
	debugUi.addColor("SpotLight Color", &spotLight.color);

	while (!window.isCloseRequested()) {

		// Determine deltaTime
		float deltaTime = 1000.0f / SDL_GetTicks();

		input.pollInput();
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
			window.requestClose();
		}
		if (input.isKeyHeld(SDL_SCANCODE_A))
		{
			camera.ProcessKeyboard(LEFT, deltaTime);
		}
		if (input.isKeyHeld(SDL_SCANCODE_D))
		{
			camera.ProcessKeyboard(RIGHT, deltaTime);
		}
		if (input.isKeyHeld(SDL_SCANCODE_W))
		{
			camera.ProcessKeyboard(FORWARD, deltaTime);
		}
		if (input.isKeyHeld(SDL_SCANCODE_S))
		{
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		}
		if (input.isKeyHeld(SDL_SCANCODE_Q))
		{
			camera.ProcessKeyboard(UP, deltaTime);
		}
		if (input.isKeyHeld(SDL_SCANCODE_E))
		{
			camera.ProcessKeyboard(DOWN, deltaTime);
		}

		glPolygonMode(GL_FRONT_AND_BACK, (showWireFrame) ? GL_LINE : GL_FILL);

		//Update
		float time = (SDL_GetTicks() / 500.0f) * speedMultiplier;
		float time_sin = sinf(time);
		float time_cos = cosf(time);

		objectTrans.SetRotation(vec3(0, time_sin * 10, 0));

		pointLightTrans.SetPosition(vec3(time_sin * 2, 0, time_cos * 2));
		pointLight.position = pointLightTrans.GetPosition();
		pointLight.update();

		spotLightTrans.SetPosition(vec3(-time_sin, -0.7f, 2));
		spotLight.position = spotLightTrans.GetPosition();
		spotLight.update();

		// Clear
		window.clear();

		// 3D Render
		basicShader.Bind();

		// Model, View and World Matrices
		basicShader.SetMVP(
			objectTrans.GetTransformationMatrix(),
			camera.GetViewMatrix(),
			glm::perspective(camera.Zoom, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f)
		);

		basicShader.SetUniform3fv("viewPos", camera.Position);

		// Material
		// Passing in Textures in a struct crashes the program?
		basicShader.SetUniform1i("diffuseMap", diffuseMap.GetTextureID());
		basicShader.SetUniform1i("specularMap", specularMap.GetTextureID());
		basicShader.SetUniform1i("normalMap", normalMap.GetTextureID());
		basicShader.SetUniform1f("shininess", 32.0f);

		basicShader.SetDirLight(dirLight);
		basicShader.SetPointLight(pointLight);
		basicShader.SetSpotLight(spotLight);

		basicShader.SetUniform1i("useNormalMapping", useNormalMapping);
		basicShader.SetUniform1i("showNormalMap", showNormalMap);
		basicShader.SetUniform1i("showSpecularMap", showSpecularMap);

		objectMesh.render();

		basicShader.Unbind();

		// Draw Dir Light
		lampShader.Bind();
		lampShader.SetUniform4fv("model", dirLightTrans.GetTransformationMatrix());
		lampShader.SetUniform4fv("view", camera.GetViewMatrix());
		lampShader.SetUniform4fv("projection", glm::perspective(camera.Zoom, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f));
		lampShader.SetUniform3fv("viewPos", camera.Position);
		lampShader.SetUniform3fv("color", dirLight.color);
		dirLightMesh.render();
		lampShader.Unbind();

		// Draw Point Light
		lampShader.Bind();
		lampShader.SetUniform4fv("model", pointLightTrans.GetTransformationMatrix());
		lampShader.SetUniform4fv("view", camera.GetViewMatrix());
		lampShader.SetUniform4fv("projection", glm::perspective(camera.Zoom, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f));
		lampShader.SetUniform3fv("viewPos", camera.Position);
		lampShader.SetUniform3fv("color", pointLight.color);
		pointLightMesh.render();
		lampShader.Unbind();

		// Draw Spot Light
		lampShader.Bind();
		lampShader.SetUniform4fv("model", spotLightTrans.GetTransformationMatrix());
		lampShader.SetUniform4fv("view", camera.GetViewMatrix());
		lampShader.SetUniform4fv("projection", glm::perspective(camera.Zoom, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f));
		lampShader.SetUniform3fv("viewPos", camera.Position);
		lampShader.SetUniform3fv("color", spotLight.color);
		flashlightMesh.render();
		lampShader.Unbind();

		// 2D Render
#ifdef _DEBUG 
		// Render 2D
		if (showWireFrame) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
		debugUi.prepare();
		debugUi.render();
		if (showWireFrame) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINES); }
#endif // _DEBUG 

		// Swap
		window.swap();
	}

	debugUi.cleanUp();
	window.cleanUp();

	return 0;
}