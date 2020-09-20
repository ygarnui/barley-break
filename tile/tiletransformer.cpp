#include "tiletransformer.h"

TileTransformer::TileTransformer(uint64_t x, uint64_t y)
{
    row_ = x;
    column_ = y;
    tilePosition_.resize(x);
    for(auto& v : tilePosition_)
    {
        v.resize(y);
    }
}

void TileTransformer::setTileManaget(std::shared_ptr<TileManager> tileManager)
{
    std::vector<std::shared_ptr<Tile> > &tiles = tileManager->getTiles();
    if(tiles.size() != row_ * column_)
    {
        return;
    }

    tileManager_ = tileManager;

    for(size_t i = 0; i < row_; i++)
    {
        for(size_t j = 0; j < column_; j++)
        {
            tilePosition_[i][j] = tiles[i * column_ + j]->getId();
            tiles[i * column_ + j]->setPosX(i);
            tiles[i * column_ + j]->setPosY(j);
        }
    }

    for(size_t i = 0; i < row_; i++)
    {
        for(size_t j = 0; j < column_; j++)
        {
            auto tileDrawable = tiles[tilePosition_[i][j]]->getTileDrawable();
            tileDrawable->setTranslate(getTranslate(i, j));
        }
    }
}

void TileTransformer::clickOnTile(QVector3D vec, QMatrix4x4 mtr)
{
    float minLen = 100000;
    std::vector<std::shared_ptr<Tile> > &tiles = tileManager_->getTiles();
    std::shared_ptr<Tile> curTile;
    for(size_t i = 0; i < tiles.size(); i++)
    {
        auto& tile = tiles[i];
        if(tile->getId() == 0)
        {
            continue;
        }
        const auto& tileGeometry = tile->getTileGeometry();
        const auto& tileDrawable = tile->getTileDrawable();
#if 0
        QVector3D centr = tileDrawable->getTransform() * tileGeometry->centr;
#else
        QVector3D centr = mtr * tileDrawable->getTransform() * tileGeometry->centr;
#endif
        QVector3D len = centr - vec;
        float curLen = len.length();
        if(curLen < minLen)
        {
            minLen = curLen;
            curTile = tiles[i];
        }
    }
    clickOnTile(curTile->getId());
}

void TileTransformer::clickOnTile(uint64_t id)
{
    size_t resx;
    size_t resy;
    bool res = false;

    auto currentTile = tileManager_->getTileById(id);

    if(!currentTile)
    {
        return;
    }

    auto currentTileDrawable = currentTile->getTileDrawable();

    res = checkingNeighboringCells(currentTile->getPosX(), currentTile->getPosY(), resx, resy);

    if(!res)
    {
        return;
    }

    swapTile(currentTile->getPosX(), currentTile->getPosY(), resx, resy);

//    auto nullTile = tileManager_->getTileById(tilePosition_[resx][resy]);
//    if(!nullTile)
//    {
//        return;
//    }

//    auto nulltTileDrawable = nullTile->getTileDrawable();
//    nullTile->setPosX(currentTile->getPosX());
//    nullTile->setPosY(currentTile->getPosY());

//    currentTile->setPosX(resx);
//    currentTile->setPosY(resy);

//    QMatrix4x4& currentTransform = currentTileDrawable->getTransform();
//    currentTransform.setToIdentity();
//    currentTransform.translate(getTranslate(resx, resy));

//    QMatrix4x4& nullTransform = nulltTileDrawable->getTransform();
//    nullTransform.setToIdentity();
//    nullTransform.translate(getTranslate(nullTile->getPosX(), nullTile->getPosY()));
}

bool TileTransformer::checkingNeighboringCells(uint64_t x, uint64_t y, size_t &resx, size_t &resy)
{
    if(x+1 < row_)
    {
        if(tilePosition_[x+1][y] == 0)
        {
            resx = x + 1;
            resy = y;
            return true;
        }
    }

    if(y + 1 < column_)
    {
        if(tilePosition_[x][y+1] == 0)
        {
            resx = x;
            resy = y + 1;
            return true;
        }
    }

    if(x != 0)
    {
        if(tilePosition_[x-1][y] == 0)
        {
            resx = x - 1;
            resy = y;
            return true;
        }
    }

    if(y != 0)
    {
        if(tilePosition_[x][y-1] == 0)
        {
            resx = x;
            resy = y - 1;
            return true;
        }
    }
    return false;
}

void TileTransformer::swapTile(size_t x1, size_t y1, size_t x2, size_t y2)
{
    auto tile1 = tileManager_->getTileById(tilePosition_[x1][y1]);
    if(!tile1)
    {
        return;
    }

    auto tile2 = tileManager_->getTileById(tilePosition_[x2][y2]);
    if(!tile2)
    {
        return;
    }

    auto tileDrawable1 = tile1->getTileDrawable();
    auto tileDrawable2 = tile2->getTileDrawable();

    tile1->setPosX(x2);
    tile1->setPosY(y2);

    tile2->setPosX(x1);
    tile2->setPosY(y1);

    QMatrix4x4& transform1 = tileDrawable1->getTransform();
    transform1.setToIdentity();
    transform1.translate(getTranslate(x2, y2));

    QMatrix4x4& transform2 = tileDrawable2->getTransform();
    transform2.setToIdentity();
    transform2.translate(getTranslate(x1,y1));

    tilePosition_[x1][y1] = tile2->getId();
    tilePosition_[x2][y2] = tile1->getId();
}

QVector3D TileTransformer::getTranslate(size_t x, size_t y)
{
    float halfDeltaX = deltaX_ / 2.0;
    float halfDeltaY = deltaY_ / 2.0;
    float halfX = (row_ * deltaX_) / 2.0;
    float halfY = (column_ * deltaY_) / 2.0;
    return QVector3D(deltaX_ * x - halfX + halfDeltaX, deltaY_ * y - halfY + halfDeltaY, 0);
}
