#ifndef TILERENDERER_H
#define TILERENDERER_H

#include "tiledrawable.h"
#include "tilemanager.h"
#include "shadersmanager.h"

#include <QOpenGLShaderProgram>

#include <vector>
#include <memory>

class TileRenderer : protected QOpenGLFunctions
{
public:
    TileRenderer();

    void setTileManaget(std::shared_ptr<TileManager> tileManager);

    void drawGeometry( const QMatrix4x4 &projMtr, const QMatrix4x4 &viewMtr);

private:

    void drawTile(std::shared_ptr<Tile> tile, const QMatrix4x4 &projMtr, const QMatrix4x4 &viewMtr);

    void initShaderProgram();

    std::shared_ptr<TileManager> tileManager_;
    std::shared_ptr<ShadersManager> shadersManager_;
};

#endif // TILERENDERER_H
