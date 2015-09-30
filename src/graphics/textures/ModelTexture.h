#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include <GL\glew.h>

class ModelTexture
{
public:
	ModelTexture(GLuint id) : m_textureID(id) {};

	inline GLuint GetTextureID() { return m_textureID; }

	//inline float GetShineDamper() { return m_shineDamper; }
	//inline void SetShineDamper(float s) { m_shineDamper = s; }
	//inline float GetShine() { return m_shine; }
	//inline void SetShine(float s) { m_shine = s; }
	//inline bool GetHasTransparency() { return m_hasTransparency; }
	//inline bool GetUseUpNormal() { return m_useUpNormal; }

private:
	GLuint m_textureID;

	//bool m_hasTransparency;
	//bool m_useUpNormal;
	//float m_shineDamper;
	//float m_shine;
};

#endif // MODELTEXTURE_H