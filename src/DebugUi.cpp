#include "DebugUi.h"
#include <string.h>

DebugUi::DebugUi(SDL_Window* window)
{
	m_Window = window;
	ImGui_ImplSdlOgl3_Init(m_Window);

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL; // Disables ini file output

	floats = std::vector<FloatDebug>();
	bools = std::vector<BoolDebug>();
	colors = std::vector<ColorDebug>();
	vecs = std::vector<Vec3Debug>();
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

	for (int i = 0; i < vecs.size(); i++) {

		if (ImGui::CollapsingHeader(vecs.at(i).title))
		{
			
			Vec3Debug v = vecs.at(i);

			// TODO: Ugly and slow, fix me
			std::string x = std::string(v.title) + std::string("x");;
			std::string y = std::string(v.title) + std::string("y");;
			std::string z = std::string(v.title) + std::string("z");;
			
			ImGui::PushItemWidth(-1.0f);
			ImGui::SliderFloat(x.c_str(), &v.val->x, -10.0f, 10.0f);
			ImGui::PopItemWidth();

			ImGui::PushItemWidth(-1.0f);
			ImGui::SliderFloat(y.c_str(), &v.val->y, -10.0f, 10.0f);
			ImGui::PopItemWidth();

			ImGui::PushItemWidth(-1.0f);
			ImGui::SliderFloat(z.c_str(), &v.val->z, -10.0f, 10.0f);
			ImGui::PopItemWidth();
		}
	}


	for (int i = 0; i < colors.size(); i++) {
		if (ImGui::CollapsingHeader(colors.at(i).title))
		{
			// TODO: This is ugly and hard to understand, fix this
			// ...but it works...
			ColorDebug col = colors.at(i);
			ImColor icol = ImColor(col.col->r, col.col->g, col.col->b, 0.0f);

			ColorPicker(colors.at(i).title, &icol);

			col.col->r = icol.Value.x;
			col.col->g = icol.Value.y;
			col.col->b = icol.Value.z;
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

void DebugUi::addColor(const char* title, vec3* val)
{
	colors.push_back(ColorDebug(title, val));
}

void DebugUi::addVec3(const char* title, vec3* val)
{
	vecs.push_back(Vec3Debug(title, val));
}

/*
*	From nem0
*   https://github.com/ocornut/imgui/issues/346
*
*/
bool DebugUi::ColorPicker(const char* label, ImColor* color)
{
	static const float HUE_PICKER_WIDTH = 20.0f;
	static const float CROSSHAIR_SIZE = 10.0f;
	static const ImVec2 SV_PICKER_SIZE = ImVec2(180, 180);

	bool value_changed = false;

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	ImVec2 picker_pos = ImGui::GetCursorScreenPos();

	ImColor colors[] = {
		ImColor(255, 0, 0),
		ImColor(255, 255, 0),
		ImColor(0, 255, 0),
		ImColor(0, 255, 255),
		ImColor(0, 0, 255),
		ImColor(255, 0, 255),
		ImColor(255, 0, 0) };

	for (int i = 0; i < 6; ++i)
	{
		draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 10, picker_pos.y + i * (SV_PICKER_SIZE.y / 6)),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 10 + HUE_PICKER_WIDTH,
				picker_pos.y + (i + 1) * (SV_PICKER_SIZE.y / 6)),
			colors[i],
			colors[i],
			colors[i + 1],
			colors[i + 1]);
	}

	float hue, saturation, value;

	ImGui::ColorConvertRGBtoHSV(
		color->Value.x, color->Value.y, color->Value.z, hue, saturation, value);

	auto hue_color = ImColor::HSV(hue, 1, 1);

	draw_list->AddLine(
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 8, picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 12 + HUE_PICKER_WIDTH,
			picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImColor(255, 255, 255));

	draw_list->AddRectFilledMultiColor(
		picker_pos,
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
		ImColor(0, 0, 0),
		hue_color,
		ImColor(255, 255, 255),
		ImColor(255, 255, 255));

	float x = saturation * value;

	ImVec2 p(picker_pos.x + x * SV_PICKER_SIZE.x, picker_pos.y + value * SV_PICKER_SIZE.y);

	draw_list->AddLine(ImVec2(p.x - CROSSHAIR_SIZE, p.y), ImVec2(p.x - 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x + CROSSHAIR_SIZE, p.y), ImVec2(p.x + 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y + CROSSHAIR_SIZE), ImVec2(p.x, p.y + 2), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y - CROSSHAIR_SIZE), ImVec2(p.x, p.y - 2), ImColor(255, 255, 255));

	ImGui::InvisibleButton("saturation_value_selector", SV_PICKER_SIZE);

	if (ImGui::IsItemHovered())
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(
			ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		if (ImGui::GetIO().MouseDown[0])
		{
			mouse_pos_in_canvas.x = ImMin(mouse_pos_in_canvas.x, mouse_pos_in_canvas.y);

			value = mouse_pos_in_canvas.y / SV_PICKER_SIZE.y;

			saturation = value == 0 ? 0 : (mouse_pos_in_canvas.x / SV_PICKER_SIZE.x) / value;

			value_changed = true;
		}
	}

	ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SV_PICKER_SIZE.x + 10, picker_pos.y));

	ImGui::InvisibleButton("hue_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

	if (ImGui::IsItemHovered())
	{
		if (ImGui::GetIO().MouseDown[0])
		{
			hue = ((ImGui::GetIO().MousePos.y - picker_pos.y) / SV_PICKER_SIZE.y);
			value_changed = true;
		}
	}

	*color = ImColor::HSV(hue, saturation, value);

	return value_changed | ImGui::ColorEdit3(label, &color->Value.x);
}