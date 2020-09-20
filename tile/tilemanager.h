#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <map>

#include "tile.h"

class TileManager
{
public:
    TileManager();

    std::vector<std::shared_ptr<Tile>>& getTiles();
    std::shared_ptr<Tile> getTileById(size_t id);

private:
    void initTiles();
    void initTile(std::shared_ptr<Tile> tile);

    std::vector<std::shared_ptr<Tile>> tiles_;

    std::shared_ptr<QOpenGLTexture> texture_;
};

#endif // TILEMANAGER_H
