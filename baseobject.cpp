#include "baseobject.h"

#include <QVector2D>
#include <QVector3D>

BaseObject::BaseObject()
    : index_(QOpenGLBuffer::IndexBuffer)
{
    index_.create();
    vertex_.create();
    normal_.create();
    binormal_.create();
    tex_.create();
    color_.create();
}

BaseObject::~BaseObject()
{
    index_.destroy();
    vertex_.destroy();
    normal_.destroy();
    binormal_.destroy();
    tex_.destroy();
    color_.destroy();
}

