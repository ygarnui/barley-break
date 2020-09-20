#ifndef TILETRANSFORMER_H
#define TILETRANSFORMER_H

#include "tiledrawable.h"
#include "tilemanager.h"

#include <vector>
#include <memory>

class TileTransformer
{
public:
    TileTransformer(uint64_t x, uint64_t y);

    void setTileManaget(std::shared_ptr<TileManager> tileManager);

    void clickOnTile(QVector3D vec, QMatrix4x4 mtr);
    void clickOnTile(uint64_t id);

private:

    bool checkingNeighboringCells(uint64_t x, uint64_t y, size_t &resx, size_t &resy);
    void swapTile(size_t x1, size_t y1, size_t x2, size_t y2);
    QVector3D getTranslate(size_t x, size_t y);

    uint64_t row_;
    uint64_t column_;

    std::vector<std::vector<uint64_t>> tilePosition_;

    float deltaX_ = 2.7;
    float deltaY_ = 2.7;

    std::shared_ptr<TileManager> tileManager_;
};

#endif // TILETRANSFORMER_H
