#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

#include <memory>

class TileRenderer;
class TileManager;

class BaseObject
{
    friend TileRenderer;
    friend TileManager;
public:
    BaseObject();
    virtual ~BaseObject();

private:

    uint64_t numPrimitivs_;

    QOpenGLBuffer index_;

    QOpenGLBuffer vertex_;
    QOpenGLBuffer normal_;
    QOpenGLBuffer binormal_;
    QOpenGLBuffer tex_;
    QOpenGLBuffer color_;

    std::shared_ptr<QOpenGLTexture> texture_;
};

#endif // GEOMETRYENGINE_H
