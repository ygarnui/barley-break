#ifndef GEOMETRYINTERSECTION_H
#define GEOMETRYINTERSECTION_H

#include "geometry.h"

#include <memory>

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

class GeometryIntersection
{
public:
    GeometryIntersection();

    void getRay(QMatrix4x4 mtr, int x, int y, QVector3D& orig, QVector3D& dir);
    bool intersecTile(const QVector3D& orig, const QVector3D& dir, const QMatrix4x4& mtr, std::shared_ptr<Geometry> geom);
    bool intersecTile(const QVector3D& orig, const QVector3D& dir, std::shared_ptr<Geometry> geom);
private:

    static bool IntersectLineWithTriangleBC(const QVector3D& orig, const QVector3D& dir, const QVector3D& v0, const QVector3D& v1, const QVector3D& v2, QVector3D& point);

    uint32_t height_ = 0;
    uint32_t width_ = 0;

};

#endif // GEOMETRYINTERSECTION_H
