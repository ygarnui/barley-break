
#include "mainwidget.h"

#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

MainWidget::~MainWidget()
{
    makeCurrent();
    doneCurrent();
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::RightButton)
    {
        QVector2D diff = QVector2D(e->localPos()) - mousePressPosition_;

        QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

        rotationAxis_ = (rotationAxis_ + n).normalized();

        rotation = QQuaternion::fromAxisAndAngle(rotationAxis_, 1) * rotation;

        view_.setToIdentity();
        view_.translate(0,0,-25);
        view_.rotate(rotation);

        mousePressPosition_ = QVector2D(e->localPos());

        update();
    }
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton || e->buttons() == Qt::RightButton)
    {
        mouseRelease = false;
        mousePressPosition_ = QVector2D(e->localPos());
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mousePressPosition_ = QVector2D(e->localPos());
        mouseRelease = true;
        update();
    }
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_MULTISAMPLE);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);

    shadersManager_ = std::make_shared<ShadersManager>();

    tileRenderer_ = std::make_shared<TileRenderer>();
    tileManager_ = std::make_shared<TileManager>();
    tileTransformer_ = std::make_shared<TileTransformer>(4,4);

    tileRenderer_->setTileManaget(tileManager_);
    tileTransformer_->setTileManaget(tileManager_);

    view_.translate(0,0,-25);
}

void MainWidget::resizeGL(int w, int h)
{
    width_ = w;
    height_ = h;

    qreal aspect = qreal(w) / qreal(h ? h : 1);

    const qreal zNear = 3.0, zFar = 50.0, fov = 45.0;

    projection_.setToIdentity();

    projection_.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    tileRenderer_->drawGeometry(projection_, view_);

    GLfloat depth = 0;
    if(mouseRelease)
    {
        mouseRelease = false;
        ReadPixels(depth);
        float x = mousePressPosition_.x() * 2.0f / width_ - 1.0f;
        float y = (height_ - mousePressPosition_.y()) * 2.0f / height_ - 1.0f;
        QVector3D vec(x, y, depth);

        if(depth != 1.0f)
        {
            QMatrix4x4 resMtr = projection_ * view_;
#if 0
            QVector3D res = resMtr.inverted() * vec;
            tileTransformer_->clickOnTile(res, resMtr);
            qDebug()<<res;
#else
            tileTransformer_->clickOnTile(vec, resMtr);
#endif
            update();
        }
    }
}

bool MainWidget::ReadPixels(GLfloat& depth)
{
    glReadPixels(mousePressPosition_.x(), height_ - mousePressPosition_.y(), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    qDebug()<<"depth: "<<depth;

    return true;
}














