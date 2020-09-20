#include "tile.h"

Tile::Tile(size_t id)
{
    tileDrawable_ = std::make_shared<TileDrawable>();
    tileGeometry_ = std::make_shared<Geometry>();;
    id_ = id;
}

std::shared_ptr<TileDrawable> Tile::getTileDrawable() const
{
    return tileDrawable_;
}

std::shared_ptr<Geometry> Tile::getTileGeometry() const
{
    return tileGeometry_;
}

uint64_t Tile::getId() const noexcept
{
    return id_;
}

uint64_t Tile::getPosX() const noexcept
{
    return posX_;
}

void Tile::setPosX(uint64_t x) noexcept
{
    posX_ = x;
}

uint64_t Tile::getPosY() const noexcept
{
    return posY_;
}

void Tile::setPosY(uint64_t y) noexcept
{
    posY_ = y;
}
