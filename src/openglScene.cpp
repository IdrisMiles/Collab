#include "openglScene.h"
#include <iostream>
#include <QMouseEvent>
#include <math.h>

OpenGLScene::OpenGLScene(QWidget *parent) : QOpenGLWidget(parent),
    m_xRot(0),
    m_yRot(0),
    m_zRot(0),
    m_xDis(0),
    m_yDis(0),
    m_zDis(200)
{
    QSurfaceFormat format;
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    setFormat(format);
    setFocus();
    setFocusPolicy(Qt::StrongFocus);
}


OpenGLScene::~OpenGLScene()
{
    cleanup();
}


QSize OpenGLScene::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize OpenGLScene::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void OpenGLScene::setXTranslation(int x)
{
    qNormalizeAngle(x);
    if (x != m_xDis) {
        m_xDis = x;
        emit xTranslationChanged(x);
        update();
    }
}

void OpenGLScene::setYTranslation(int y)
{
    qNormalizeAngle(y);
    if (y != m_yDis) {
        m_yDis = y;
        emit yTranslationChanged(y);
        update();
    }
}

void OpenGLScene::setZTranslation(int z)
{
//    qNormalizeAngle(z);
    if (z != m_zDis) {
        m_zDis= z;
        emit zTranslationChanged(z);
        update();
    }
}

void OpenGLScene::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void OpenGLScene::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void OpenGLScene::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void OpenGLScene::cleanup()
{
}


void OpenGLScene::initializeGL()
{
    //connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &OpenGLScene::cleanup);

    glewInit();

    glClearColor(0.4, 0.4, 0.4, 1);

    customInitGL();
}

void OpenGLScene::customInitGL()
{
    /*
    // setup shaders
    m_skinningShader = new QOpenGLShaderProgram;
    m_skinningShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "../shader/skinningVert.glsl");
    m_skinningShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "../shader/skinningFrag.glsl");
    m_skinningShader->bindAttributeLocation("vertex", 0);
    m_skinningShader->bindAttributeLocation("normal", 1);
    m_skinningShader->link();

    m_skinningShader->bind();
    m_projMatrixLoc = m_skinningShader->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_skinningShader->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_skinningShader->uniformLocation("normalMatrix");
    m_lightPosLoc = m_skinningShader->uniformLocation("lightPos");


    // initialise view and projection matrices
    m_viewMat = glm::mat4(1);
    m_viewMat = glm::lookAt(glm::vec3(0,0,0),glm::vec3(0,0,-1),glm::vec3(0,1,0));
    m_projMat = glm::perspective(45.0f, GLfloat(width()) / height(), 0.01f, 2000.0f);

    // Light position is fixed.
    m_lightPos = glm::vec3(0, 0, 70);
    glUniform3fv(m_lightPosLoc, 1, &m_lightPos[0]);


    //---------------------------------------------------------------------------------------
    // Demo triangle - replace this per project

    //---------------------------------------------------------------------------------------


    m_skinningShader->release();
    */
}

void OpenGLScene::paintGL()
{
    // clean gl window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // update model matrix
    m_modelMat = glm::mat4(1);
    m_modelMat = glm::translate(m_modelMat, glm::vec3(0.2f*m_xDis, -0.2f*m_yDis, -0.1f*m_zDis));// m_zDis));
    m_modelMat = glm::rotate(m_modelMat, glm::radians(m_xRot/16.0f), glm::vec3(1,0,0));
    m_modelMat = glm::rotate(m_modelMat, glm::radians(m_yRot/16.0f), glm::vec3(0,1,0));
    //m_modelMat = glm::translate(m_modelMat, glm::vec3(0.1f*m_xDis, -0.1f*m_yDis, 0));

    /*

    // Set shader params
    m_skinningShader->bind();

    glUniformMatrix4fv(m_projMatrixLoc, 1, false, &m_projMat[0][0]);
    glUniformMatrix4fv(m_mvMatrixLoc, 1, false, &(m_modelMat*m_viewMat)[0][0]);
    glm::mat3 normalMatrix =  glm::inverse(glm::mat3(m_modelMat));
    glUniformMatrix3fv(m_normalMatrixLoc, 1, true, &normalMatrix[0][0]);


    //---------------------------------------------------------------------------------------
    // Draw code - replace this with project specific draw stuff


    //---------------------------------------------------------------------------------------


    m_skinningShader->release();
    */
}

void OpenGLScene::resizeGL(int w, int h)
{
    m_projMat = glm::perspective(45.0f, GLfloat(w) / h, 0.01f, 5000.0f);
}



void OpenGLScene::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void OpenGLScene::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    }
    else if (event->buttons() & Qt::RightButton) {
        setZTranslation(m_zDis + 8 * dy);
    }
    else if (event->buttons() & Qt::MiddleButton) {
        setYTranslation(m_yDis + dy);
        setXTranslation(m_xDis + dx);
    }
    m_lastPos = event->pos();
}
