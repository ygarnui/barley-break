#include "shadersmanager.h"

ShadersManager::ShadersManager()
{
    addShaderProgram(":/shaders/vertexPositionNormal.vert", ":/shaders/fragment.frag");
}

std::shared_ptr<QOpenGLShaderProgram> ShadersManager::getProgram(size_t id)
{
    if(id < programs_.size())
    {
        return programs_[id];
    }

    return nullptr;
}

bool ShadersManager::addShaderProgram(QString vertex, QString Fragment)
{
    auto program = std::make_shared<QOpenGLShaderProgram>();
    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertex))
        return false;

    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, Fragment))
        return false;

    if (!program->link())
        return false;

    if (!program->bind())
        return false;

    programs_.push_back(program);
    return true;
}
