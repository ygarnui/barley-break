#ifndef SHADERSMANAGER_H
#define SHADERSMANAGER_H

#include <QOpenGLShaderProgram>

#include <memory>
#include <vector>

class ShadersManager
{
public:
    ShadersManager();

    std::shared_ptr<QOpenGLShaderProgram> getProgram(size_t id);
private:
    bool addShaderProgram(QString vertex, QString Fragment);

    std::vector<std::shared_ptr<QOpenGLShaderProgram>> programs_;
};

#endif // SHADERSMANAGER_H
