#include "BasicRenderer.h"

void BasicRenderer::Prepare()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void BasicRenderer::RenderArrays(RawModel model)
{
	glBindVertexArray(model.GetVaoID());
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, model.GetVertexCount());
	glDisableVertexAttribArray(0);
}

void BasicRenderer::RenderElements(RawModel model)
{
	glBindVertexArray(model.GetVaoID());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
}

void BasicRenderer::Render(TexturedModel texturedModel)
{

}