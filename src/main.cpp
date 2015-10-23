#include "common.h"

#undef main
int main(int argc, char *argv[])
{
	auto window = Window("OpenGL Skeleton", 1280, 720);

	auto camera = Camera();
	camera.Position = vec3(0, 0, 5);

	auto basicShader = BasicShader("../res/shaders/basicShader");
	auto lampShader = ShaderProgram("../res/shaders/lampShader");

	auto objectMesh = Mesh("../res/models/cube.obj");
	auto texture = Texture("../res/textures/box.jpg");

	texture.Bind(texture.GetTextureID());

	auto shininess = 32.0f;

	auto objectTrans = Transformation();

	auto cubeMesh = Mesh("../res/models/cube.obj");
	auto sphereMesh = Mesh("../res/models/sphere.obj");
	auto flashlightMesh = Mesh("../res/models/flashlight.obj");
	auto quadMesh = Mesh("../res/models/quad.obj");

	auto quadTrans = Transformation();
	quadTrans.SetPosition(vec3(-10.0f, -1.8f, 10.0f));
	quadTrans.SetRotation(vec3(-90, 0, 0));
	quadTrans.SetScale(vec3(10.f));

	auto dirLightTrans = Transformation();
	dirLightTrans.SetPosition(vec3(0, 2.0f, 0));
	dirLightTrans.SetScale(vec3(0.2f));

	auto pointLightTrans = Transformation();
	pointLightTrans.SetPosition(vec3(1, 1, 1));
	pointLightTrans.SetScale(vec3(0.1f));

	auto pointLight2Trans = Transformation();
	pointLight2Trans.SetPosition(vec3(2, 1, 1));
	pointLight2Trans.SetScale(vec3(0.1f));

	auto spotLightTrans = Transformation();
	spotLightTrans.SetPosition(vec3(0.0f, 0.0f, 2.0f));
	spotLightTrans.SetRotation(vec3(90.0f, 0.0f, 0.0f));
	spotLightTrans.SetScale(vec3(0.1f));

	auto dirLight = DirLight(vec3(-0.2f, -1.0f, -0.3f), WHITE);
	auto pointLight = PointLight(vec3(0.0f), RED);
	auto pointLight2 = PointLight(vec3(1.0f), BLUE);
	auto spotLight = SpotLight(spotLightTrans.GetPosition(), camera.Front, GREEN);

	auto showWireFrame = false;

	// Setup DebugUi
	auto debugUi = DebugUi(window.getWindow());
	auto speedMultiplier = 1.0f;
	debugUi.addFloat("Speed Multiplier", &speedMultiplier, 0.0f, 5.0f);
	debugUi.addFloat("Shininess", &shininess, 0.0f, 128.0f);
	debugUi.addVec3("Camera", &camera.Position);
	debugUi.addVec3("Spotlight pos", &spotLight.position);
	debugUi.addBool("Show Wireframe", &showWireFrame);
	debugUi.addColor("DirLight Color", &dirLight.color);
	debugUi.addColor("PointLight 1 Color", &pointLight.color);
	debugUi.addColor("PointLight 2 Color", &pointLight2.color);
	debugUi.addColor("SpotLight Color", &spotLight.color);

	auto startTime = Timer::GetTime();

	while (!window.isCloseRequested()) {

		// Determine deltaTime
		auto deltaTime = Timer::GetTime() - startTime;
		startTime = Timer::GetTime();

		if (deltaTime > 0.100f) // Stop the time related functions going nuts if the delta is too huge
		{
			deltaTime = 0.016f;
		}

		window.update();

		glPolygonMode(GL_FRONT_AND_BACK, (showWireFrame) ? GL_LINE : GL_FILL);

		//Update
		auto time = (SDL_GetTicks() / 500.0f) * speedMultiplier;
		auto time_sin = sinf(time);
		auto time_cos = cosf(time);

		objectTrans.SetRotation(vec3(0, time_sin * 10, 0));

		dirLight.update();

		pointLightTrans.SetPosition(vec3(time_sin * 2, 0, time_cos * 2));
		pointLight.position = pointLightTrans.GetPosition();
		pointLight.update();

		pointLight2Trans.SetPosition(vec3(time_cos * 2, 0.5f, time_sin * 2));
		pointLight2.position = pointLight2Trans.GetPosition();
		pointLight2.update();

		spotLight.update();
		spotLightTrans.SetPosition(spotLight.position);

		// Clear
		window.clear();

		auto projection = glm::perspective(camera.Zoom, float(window.getWidth()) / float(window.getHeight()), 0.1f, 1000.0f);

		// Draw Quad
		lampShader.Bind();
		lampShader.SetUniform4fv("model", quadTrans.GetTransformationMatrix());
		lampShader.SetUniform4fv("view", camera.GetViewMatrix());
		
		lampShader.SetUniform4fv("projection", projection);
		lampShader.SetUniform3fv("viewPos", camera.Position);
		lampShader.SetUniform3fv("color", FIREBRICK);
		quadMesh.render();
		lampShader.Unbind();

		// 3D Render
		basicShader.Bind();

		// Model, View and World Matrices
		basicShader.SetMVP(
			objectTrans.GetTransformationMatrix(),
			camera.GetViewMatrix(),
			projection
			);
		basicShader.SetUniform3fv("viewPos", camera.Position);

		basicShader.SetUniform1i("texture", texture.GetTextureID());
		basicShader.SetUniform1f("shininess", shininess);

		basicShader.SetDirLight(dirLight);

		basicShader.SetUniform3fv("pointLights[0].position", pointLight.position);
		basicShader.SetUniform3fv("pointLights[0].ambient", pointLight.ambient);
		basicShader.SetUniform3fv("pointLights[0].diffuse", pointLight.diffuse);
		basicShader.SetUniform3fv("pointLights[0].specular", pointLight.specular);
		basicShader.SetUniform1f("pointLights[0].constant", pointLight.constant);
		basicShader.SetUniform1f("pointLights[0].linear", pointLight.linear);
		basicShader.SetUniform1f("pointLights[0].quadratic", pointLight.quadratic);

		basicShader.SetUniform3fv("pointLights[1].position", pointLight2.position);
		basicShader.SetUniform3fv("pointLights[1].ambient", pointLight2.ambient);
		basicShader.SetUniform3fv("pointLights[1].diffuse", pointLight2.diffuse);
		basicShader.SetUniform3fv("pointLights[1].specular", pointLight2.specular);
		basicShader.SetUniform1f("pointLights[1].constant", pointLight2.constant);
		basicShader.SetUniform1f("pointLights[1].linear", pointLight2.linear);
		basicShader.SetUniform1f("pointLights[1].quadratic", pointLight2.quadratic);

		basicShader.SetSpotLight(spotLight);

		objectMesh.render();

		basicShader.Unbind();

		// Draw Dir Light
		lampShader.Bind();
		lampShader.SetUniform4fv("model", dirLightTrans.GetTransformationMatrix());
		lampShader.SetUniform4fv("view", camera.GetViewMatrix());
		lampShader.SetUniform4fv("projection", projection);
		lampShader.SetUniform3fv("viewPos", camera.Position);
		lampShader.SetUniform3fv("color", dirLight.color);
		cubeMesh.render();
		lampShader.Unbind();

		// Draw Point Light 1
		lampShader.Bind();
		lampShader.SetUniform4fv("model", pointLightTrans.GetTransformationMatrix());
		lampShader.SetUniform4fv("view", camera.GetViewMatrix());
		lampShader.SetUniform4fv("projection", projection);
		lampShader.SetUniform3fv("viewPos", camera.Position);
		lampShader.SetUniform3fv("color", pointLight.color);
		sphereMesh.render();
		lampShader.Unbind();

		// Draw Point Light	2
		lampShader.Bind();
		lampShader.SetUniform4fv("model", pointLight2Trans.GetTransformationMatrix());
		lampShader.SetUniform4fv("view", camera.GetViewMatrix());
		lampShader.SetUniform4fv("projection", projection);
		lampShader.SetUniform3fv("viewPos", camera.Position);
		lampShader.SetUniform3fv("color", pointLight2.color);
		sphereMesh.render();
		lampShader.Unbind();

		// Draw Spot Light
		lampShader.Bind();
		lampShader.SetUniform4fv("model", spotLightTrans.GetTransformationMatrix());
		lampShader.SetUniform4fv("view", camera.GetViewMatrix());
		lampShader.SetUniform4fv("projection", projection);
		lampShader.SetUniform3fv("viewPos", camera.Position);
		lampShader.SetUniform3fv("color", spotLight.color);
		flashlightMesh.render();
		lampShader.Unbind();

		// Render 2D
		debugUi.prepare();
		debugUi.render();

		// Swap
		window.swap();
	}

	debugUi.cleanUp();
	window.cleanUp();

	return 0;
}