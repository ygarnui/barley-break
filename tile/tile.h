#ifndef TILE_H
#define TILE_H

#include "tiledrawable.h"
#include "geometry.h"

class Tile
{
public:
    Tile(size_t id);

    std::shared_ptr<TileDrawable> getTileDrawable() const;
    std::shared_ptr<Geometry> getTileGeometry() const;

    uint64_t getId() const noexcept;

    uint64_t getPosX() const noexcept;
    void setPosX(uint64_t x) noexcept;
    uint64_t getPosY() const noexcept;
    void setPosY(uint64_t y) noexcept;

private:

    std::shared_ptr<TileDrawable> tileDrawable_;
    std::shared_ptr<Geometry> tileGeometry_;

    uint64_t id_;


    uint64_t posX_;
    uint64_t posY_;
    uint64_t value_;
};

#endif // TILE_H
