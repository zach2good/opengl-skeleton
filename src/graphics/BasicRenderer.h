#include <SDL.h>
#include <GL\glew.h>
#include <graphics\models\RawModel.h>
#include <graphics\models\TexturedModel.h>

class BasicRenderer {

public:

	void Prepare();
	void RenderArrays(RawModel model);
	void RenderElements(RawModel model);

	void Render(TexturedModel texturedModel);
};