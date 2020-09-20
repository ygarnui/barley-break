#ifndef TILEDRAWABLE_H
#define TILEDRAWABLE_H

#include "baseobject.h"

#include <memory>

#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class TileDrawable : public BaseObject
{
public:
    TileDrawable();


    QMatrix4x4& getTransform();
    void setTranslate(const QVector3D &vec);

private:

    QMatrix4x4 transform_;
};

#endif // TILEDRAWABLE_H
