#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "tile/tilerenderer.h"
#include "tile/tiletransformer.h"
#include "shadersmanager.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QMouseEvent>

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    bool bindSelectBuffer();
protected:
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:

    std::shared_ptr<TileRenderer> tileRenderer_;
    std::shared_ptr<TileManager> tileManager_;
    std::shared_ptr<ShadersManager> shadersManager_;
    std::shared_ptr<TileTransformer> tileTransformer_;

    QMatrix4x4 projection_;
    QMatrix4x4 rotate_;
    QMatrix4x4 view_;

    bool mouseRelease;
    QVector2D mousePressPosition_;
    QVector3D rotationAxis_;

    QQuaternion rotation;

    GLuint FBOForSelect;
    GLuint RBOColorForSelect;
    GLuint RBODepthForSelect;

    GLuint colorTexture;
    GLuint depthTexture;

    uint32_t width_;
    uint32_t height_;

    bool ReadPixels(GLfloat& depth);

};

#endif // MAINWIDGET_H
