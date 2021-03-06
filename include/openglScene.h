#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H


#include <GL/glew.h>

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>



class OpenGLScene : public QOpenGLWidget
{

    Q_OBJECT

public:
    OpenGLScene(QWidget *parent = 0);
    virtual ~OpenGLScene();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

//    enum RenderType { SKINNED = 0, RIG = 1, NUMRENDERTYPES };


public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setXTranslation(int x);
    void setYTranslation(int y);
    void setZTranslation(int z);
    void cleanup();
    virtual void UpdateAnimation() = 0;

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void xTranslationChanged(int x);
    void yTranslationChanged(int y);
    void zTranslationChanged(int z);

protected:
    void initializeGL() override;
    virtual void customInitGL();
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


    int m_xRot;
    int m_yRot;
    int m_zRot;
    int m_xDis;
    int m_yDis;
    int m_zDis;
    QPoint m_lastPos;
    glm::vec3 m_lightPos;

    glm::mat4 m_projMat;
    glm::mat4 m_viewMat;
    glm::mat4 m_modelMat;




};

#endif // OPENGLSCENE_H
