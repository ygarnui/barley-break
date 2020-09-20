#include "geometryintersection.h"

GeometryIntersection::GeometryIntersection()
{

}

void GeometryIntersection::getRay(QMatrix4x4 mtr, int x, int y, QVector3D &orig, QVector3D &dir)
{
    Q_UNUSED(mtr);
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(orig);
    Q_UNUSED(dir);
    //TO DO
    /*
    Vector3D v;
    const Matrix4x4& matProj = GetProjectionMatrix();
    v.x = ((2.0f * x) / width - 1.0f) / matProj[0];
    v.y = -((2.0f * y) / height - 1.0f) / matProj[5];
    v.z = 1.0f;
    // Get the inverse view matrix
    const Matrix4x4& matView = bUseScaledMatrix ? pCamera_->getMatrixView() : pCamera_->GetViewMatrixWithoutScale();
    Matrix4x4 mWorldView = matView;
    //if (RenderType >= Render::OGLRender)
    //{
    //v.z = -1.0f;
    //}
    mWorldView.Invert();
    // Transform the screen space pick ray into 3D space
    dir.x = v.x * mWorldView[0] + v.y * mWorldView[4] + v.z * mWorldView[8];
    dir.y = v.x * mWorldView[1] + v.y * mWorldView[5] + v.z * mWorldView[9];
    dir.z = v.x * mWorldView[2] + v.y * mWorldView[6] + v.z * mWorldView[10];
    if (dir.x || dir.y || dir.z)
    {
        dir.Normalize();
    }
    org = mWorldView.GetPosition();
    */
}

bool GeometryIntersection::intersecTile(const QVector3D &orig, const QVector3D &dir, const QMatrix4x4 &mtr, std::shared_ptr<Geometry> geom)
{
    QVector4D resOrig = mtr * QVector4D(orig.x(), orig.y(), orig.z(), 1.0);
    QVector3D newOrig(resOrig.x(),resOrig.y(), resOrig.z());
    QVector3D res;
    for(size_t i = 0; i < geom->index_.size(); i+=3)
    {
        auto& vec =  geom->vertex_;
        if(IntersectLineWithTriangleBC(newOrig, dir, vec[i], vec[i + 1], vec[i + 2], res))
        {
            return true;
        }
    }
    return false;
}

bool GeometryIntersection::IntersectLineWithTriangleBC(const QVector3D &orig, const QVector3D &dir, const QVector3D &v0, const QVector3D &v1, const QVector3D &v2, QVector3D &point)
{
    QVector3D e1 = v1 - v0;
    QVector3D e2 = v2 - v0;
    // Вычисление вектора нормали к плоскости
    QVector3D pvec = QVector3D::crossProduct(dir, e2);

    double det = QVector3D::dotProduct(e1, pvec);

    // линия параллельна плоскости
    if (abs(det) < std::numeric_limits<double>::epsilon())
    {
        return false;
    }

    QVector3D tvec;
    if (det > 0.0f)
    {
        tvec = orig - v0;
    }
    else
    {
        tvec = v0 - orig;
        det = -det;
    }

    double inv_det = 1 / det;
    double u = QVector3D::dotProduct(tvec, pvec) * inv_det;
    if (u < 0 || u > 1)
    {
        return false;
    }

    QVector3D qvec = QVector3D::crossProduct(tvec, e1);
    double v = QVector3D::dotProduct(dir, qvec) * inv_det;
    if (v < 0 || u + v > 1)
    {
        return false;
    }
    double dist = QVector3D::dotProduct(e2, qvec) * inv_det;

    point = orig + dir * dist;

    return true;
}
