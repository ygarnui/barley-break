#include "tilemanager.h"

TileManager::TileManager()
{
    QImage image(":/textures/num.png");
    texture_ = std::make_shared<QOpenGLTexture>(image, QOpenGLTexture::GenerateMipMaps);
    texture_->setBorderColor(1,1,1,1);
    initTiles();
}

std::vector<std::shared_ptr<Tile> > &TileManager::getTiles()
{
    return tiles_;
}

std::shared_ptr<Tile> TileManager::getTileById(size_t id)
{
    if(id < tiles_.size())
    {
        return tiles_[id];
    }
    return nullptr;
}

void TileManager::initTiles()
{
    for(size_t i = 0; i < 16; i++)
    {
        auto tile = std::make_shared<Tile>(i);
        initTile(tile);
        tiles_.push_back(tile);
    }
}

void TileManager::initTile(std::shared_ptr<Tile> tile)
{
    auto tileGeometry = tile->getTileGeometry();
    auto tileDrawable = tile->getTileDrawable();
    auto& index = tileGeometry->index_;
    index.resize(36);
    size_t n = 0;

    for(size_t i = 0; i < 24; i+=4)
    {
        index[n++] = i;
        index[n++] = i + 1;
        index[n++] = i + 2;

        index[n++] = i + 1;
        index[n++] = i + 2;
        index[n++] = i + 3;
    }

    tileDrawable->index_.bind();
    tileDrawable->index_.allocate(index.data(),index.size() * sizeof(GLint));


    auto& vertex = tileGeometry->vertex_;
    vertex.resize(24);

    float x = 1;
    float y = 1;
    float z = 0.3;

    vertex[0] = QVector3D(-x,-y,-z);
    vertex[1] = QVector3D(x,-y,-z);
    vertex[2] = QVector3D(-x,y,-z);
    vertex[3] = QVector3D(x,y,-z);

    vertex[4] = QVector3D(-x,-y,z);
    vertex[5] = QVector3D(-x,y,z);
    vertex[6] = QVector3D(x,-y,z);
    vertex[7] = QVector3D(x,y,z);

    vertex[8] = QVector3D(-x,-y,-z);
    vertex[9] = QVector3D(-x,-y,z);
    vertex[10] = QVector3D(x,-y,-z);
    vertex[11] = QVector3D(x,-y,z);

    vertex[12] = QVector3D(-x,y,-z);
    vertex[13] = QVector3D(-x,y,z);
    vertex[14] = QVector3D(x,y,-z);
    vertex[15] = QVector3D(x,y,z);

    vertex[16] = QVector3D(-x,-y,-z);
    vertex[17] = QVector3D(-x,-y,z);
    vertex[18] = QVector3D(-x,y,-z);
    vertex[19] = QVector3D(-x,y,z);

    vertex[20] = QVector3D(x,-y,-z);
    vertex[21] = QVector3D(x,-y,z);
    vertex[22] = QVector3D(x,y,-z);
    vertex[23] = QVector3D(x,y,z);

    tileDrawable->vertex_.bind();
    tileDrawable->vertex_.allocate(vertex.data(), vertex.size() * sizeof (QVector3D));


    auto& normal = tileGeometry->normal_;
    normal.resize(24);

    normal[0] = QVector3D(0,0,1);
    normal[1] = QVector3D(0,0,1);
    normal[2] = QVector3D(0,0,1);
    normal[3] = QVector3D(0,0,1);

    normal[4] = QVector3D(0,0,-1);
    normal[5] = QVector3D(0,0,-1);
    normal[6] = QVector3D(0,0,-1);
    normal[7] = QVector3D(0,0,-1);

    normal[8] = QVector3D(0,1,0);
    normal[9] = QVector3D(0,1,0);
    normal[10] = QVector3D(0,1,0);
    normal[11] = QVector3D(0,1,0);

    normal[12] = QVector3D(0,-1,0);
    normal[13] = QVector3D(0,-1,0);
    normal[14] = QVector3D(0,-1,0);
    normal[15] = QVector3D(0,-1,0);

    normal[16] = QVector3D(1,0,0);
    normal[17] = QVector3D(1,0,0);
    normal[18] = QVector3D(1,0,0);
    normal[19] = QVector3D(1,0,0);

    normal[20] = QVector3D(-1,0,0);
    normal[21] = QVector3D(-1,0,0);
    normal[22] = QVector3D(-1,0,0);
    normal[23] = QVector3D(-1,0,0);

    tileDrawable->normal_.bind();
    tileDrawable->normal_.allocate(normal.data(), normal.size() * sizeof (QVector3D));


    auto& tex = tileGeometry->tex_;
    tex.resize(24);

    float tx = 1.0 / 16.0;
    uint64_t pos = tile->getId();

    tex[0] = QVector2D(0,0);
    tex[1] = QVector2D(0,0);
    tex[2] = QVector2D(0,0);
    tex[3] = QVector2D(0,0);

    tex[4] = QVector2D(tx * pos,1);
    tex[5] = QVector2D(tx * pos,0);
    tex[6] = QVector2D(tx * (pos + 1),1);
    tex[7] = QVector2D(tx * (pos + 1),0);

    tex[8] = QVector2D(0,0);
    tex[9] = QVector2D(0,0);
    tex[10] = QVector2D(0,0);
    tex[11] = QVector2D(0,0);

    tex[12] = QVector2D(0,0);
    tex[13] = QVector2D(0,0);
    tex[14] = QVector2D(0,0);
    tex[15] = QVector2D(0,0);

    tex[16] = QVector2D(0,0);
    tex[17] = QVector2D(0,0);
    tex[18] = QVector2D(0,0);
    tex[19] = QVector2D(0,0);

    tex[20] = QVector2D(0,0);
    tex[21] = QVector2D(0,0);
    tex[22] = QVector2D(0,0);
    tex[23] = QVector2D(0,0);

    tileDrawable->tex_.bind();
    tileDrawable->tex_.allocate(tex.data(), tex.size() * sizeof (QVector2D));

    tileDrawable->texture_ = texture_;

    tileDrawable->numPrimitivs_ = index.size();
}



















