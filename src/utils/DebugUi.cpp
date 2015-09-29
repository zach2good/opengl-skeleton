#include "DebugUi.h"

DebugUi::DebugUi(SDL_Window* window)
{
	m_Window = window;
	ImGui_ImplSdl_Init(m_Window);
}

DebugUi::~DebugUi()
{
	ImGui_ImplSdl_Shutdown();
}

void DebugUi::prepare()
{
	ImGui_ImplSdl_NewFrame(m_Window);
	static bool opened = false;

	ImGuiIO& io = ImGui::GetIO();

	io.IniFilename = NULL;

	ImGui::SetNextWindowPos(ImVec2(10, 10), 0);
	ImGui::Begin("Debug Window", &opened, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

	static ImVector<float> values;

	values.push_back(ImGui::GetIO().Framerate);

	if (values.size() > 100) {
		values.erase(values.begin());
	}

	float arr[100];
	std::copy(values.begin(), values.end(), arr);

	ImGui::Text("%.3f ms/frame | %.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	if (values.empty()) { values.resize(90); memset(values.Data, 0, values.Size*sizeof(float)); }
	static int values_offset = 0;
	ImGui::PlotLines("##Lines", values.Data, values.Size, values_offset, "", -1.0f, 100.0f, ImVec2(0, 80));

	ImGui::Text("GL_VERSION: %s \n", glGetString(GL_VERSION));
	ImGui::Text("GL_VENDOR: %s \n", glGetString(GL_VENDOR));
	ImGui::Text("GL_SHADING_LANGUAGE_VERSION: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	ImGui::Text("GLEW_VERSION: %s \n", glewGetString(GLEW_VERSION));

	ImGui::End();
}

void DebugUi::processEvents(SDL_Event e)
{
	ImGui_ImplSdl_ProcessEvent(&e);
}

void DebugUi::render()
{
	ImGui::Render();
}