#include "tiledrawable.h"

TileDrawable::TileDrawable()
{

}

QMatrix4x4 &TileDrawable::getTransform()
{
    return transform_;
}

void TileDrawable::setTranslate(const QVector3D &vec)
{
    transform_.setToIdentity();
    transform_.translate(vec);
}


