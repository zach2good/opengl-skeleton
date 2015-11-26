#include "Scene3.h"

void Scene3::init()
{
	m_Window->setGLDepthTest(false);
	m_Window->setGLMultisample(false);
	m_Window->setGLCullFace(false);
	m_Window->setGLBlend(false);

	FW::WatchID watchID = fileWatcher.addWatch("../res/shaders/", new UpdateListener(), true);
}

void Scene3::destroy()
{

}

void Scene3::update()
{
	fileWatcher.update();
}

void Scene3::render()
{

}
