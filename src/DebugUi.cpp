#include "DebugUi.h"

DebugUi::DebugUi(SDL_Window* window)
{
	m_Window = window;
	ImGui_ImplSdlOgl3_Init(m_Window);

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL; // Disables ini file output

	floats = std::vector<FloatDebug>();
	bools = std::vector<BoolDebug>();
}

DebugUi::~DebugUi()
{
	ImGui_ImplSdlOgl3_Shutdown();
}

void DebugUi::cleanUp()
{
	ImGui_ImplSdlOgl3_Shutdown();
}

void DebugUi::prepare()
{
	ImGui_ImplSdlOgl3_NewFrame(m_Window);

	static bool opened = false;

	ImGui::SetNextWindowPos(ImVec2(10, 10), 0);
	ImGui::SetNextWindowSize(ImVec2(250, 300), 0);
	ImGui::Begin("Debug Window", &opened, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

	static ImVector<float> values;

	values.push_back(ImGui::GetIO().Framerate);

	if (values.size() > 100) {
		values.erase(values.begin());
	}

	float arr[100];
	std::copy(values.begin(), values.end(), arr);
	if (ImGui::CollapsingHeader("Frame Info"))
	{
		ImGui::Text("%.3f ms/frame | %.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		if (values.empty()) { values.resize(90); memset(values.Data, 0, values.Size*sizeof(float)); }
		static int values_offset = 0;
		ImGui::PlotLines("##Lines", values.Data, values.Size, values_offset, "", -1.0f, 100.0f, ImVec2(0, 80));
	}

	if (ImGui::CollapsingHeader("OpenGL Information"))
	{
		ImGui::Text("GL_VERSION: %s \n", glGetString(GL_VERSION));
		ImGui::Text("GL_VENDOR: %s \n", glGetString(GL_VENDOR));
		ImGui::Text("GL_SHADING_LANGUAGE_VERSION: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	if (ImGui::CollapsingHeader("Floats"))
	{
		for (int i = 0; i < floats.size(); i++) {
			FloatDebug fd = floats.at(i);
			ImGui::Text(fd.title);
			ImGui::PushItemWidth(-1.0f);
			ImGui::SliderFloat(fd.title, fd.value, fd.min, fd.max);
			ImGui::PopItemWidth();
		}
	}

	if (ImGui::CollapsingHeader("Bools"))
	{
		for (int i = 0; i < bools.size(); i++) {
			ImGui::Checkbox(bools.at(i).title, bools.at(i).value);
		}
	}

	ImGui::End();

}

void DebugUi::processEvents(SDL_Event e)
{
	ImGui_ImplSdlOgl3_ProcessEvent(&e);
}

void DebugUi::render()
{
	ImGui::Render();
}

void DebugUi::addFloat(const char* title, float* var)
{
	floats.push_back(FloatDebug(title, var, 0.0f, 10.0f));
}

void DebugUi::addFloat(const char* title, float* var, float min, float max)
{
	floats.push_back(FloatDebug(title, var, min, max));
}

void DebugUi::addBool(const char* title, bool* var)
{
	bools.push_back(BoolDebug(title, var));
}