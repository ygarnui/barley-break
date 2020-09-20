#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <QVector3D>
#include <QVector2D>

class Geometry
{
public:
    Geometry();

    std::vector<uint32_t> index_;
    std::vector<QVector3D> vertex_;
    std::vector<QVector3D> normal_;
    std::vector<QVector3D> binormal_;
    std::vector<QVector2D> tex_;
    std::vector<uint32_t> color_;

    QVector3D centr;

};

#endif // GEOMETRY_H
