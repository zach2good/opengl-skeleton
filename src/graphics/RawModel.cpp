#include "RawModel.h"

RawModel::RawModel(GLuint _vaoID, int _vertexCount)
:vaoID(_vaoID), vertexCount(_vertexCount)
{

}

RawModel::~RawModel()
{

}

GLuint RawModel::getVaoID()
{
	return vaoID;
}

int RawModel::getVertexCount()
{
	return vertexCount;
}