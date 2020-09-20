#include "tilerenderer.h"

TileRenderer::TileRenderer()
{
    initializeOpenGLFunctions();

    initShaderProgram();
}

void TileRenderer::setTileManaget(std::shared_ptr<TileManager> tileManager)
{
    tileManager_ = tileManager;
}

void TileRenderer::drawGeometry(const QMatrix4x4 &projMtr, const QMatrix4x4 &viewMtr)
{
    glDisable(GL_CULL_FACE);

    if(!tileManager_)
    {
        return;
    }
    std::vector<std::shared_ptr<Tile> > &tiles = tileManager_->getTiles();
    for(auto tile : tiles)
    {
        if(tile->getId() == 0)
        {
            continue;
        }
        drawTile(tile, projMtr, viewMtr);
    }
}


void TileRenderer::drawTile(std::shared_ptr<Tile> tile, const QMatrix4x4 &projMtr, const QMatrix4x4 &viewMtr)
{
    auto program = shadersManager_->getProgram(0);
    if(!program->bind())
       return;

    auto tileDrawable = tile->getTileDrawable();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tileDrawable->texture_->textureId());
    glUniform1i(glGetUniformLocation(program->programId(), "fTexture"), 0);

    program->setUniformValue("ModelViewMatrix", viewMtr);
    program->setUniformValue("ModelViewProjMatrix", projMtr * viewMtr * tileDrawable->getTransform());

    program->setUniformValue("LightPos", QVector4D(0,0,-1,0));
    program->setUniformValue("LightColor", QVector4D(1,1,1,1));
    program->setUniformValue("DiffuseMaterial", QVector4D(1,1,1,1));
    program->setUniformValue("ShadingParameters1", QVector4D(0.3,0.3,0.4,1));


    if(!tileDrawable->index_.bind())
        return;

    quintptr offset = 0;

    if(!tileDrawable->vertex_.bind())
        return;
    int vertexLocation = program->attributeLocation("vPosition");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    if(!tileDrawable->normal_.bind())
        return;
    int normalLocation = program->attributeLocation("vNormal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    if(!tileDrawable->tex_.bind())
        return;
    int texLocation = program->attributeLocation("vTex");
    program->enableAttributeArray(texLocation);
    program->setAttributeBuffer(texLocation, GL_FLOAT, offset, 2, sizeof(QVector2D));

    glDrawElements(GL_TRIANGLES, tileDrawable->numPrimitivs_, GL_UNSIGNED_INT, 0);
}

void TileRenderer::initShaderProgram()
{
    shadersManager_ = std::make_shared<ShadersManager>();
}















