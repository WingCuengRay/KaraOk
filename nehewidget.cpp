#include "nehewidget.h"
#include "QtOpenGL/qgl.h"
#include <QtOpenGL/QGLWidget>
#include <GL/glu.h>
#include <stdio.h>



NeHeWidget::NeHeWidget(QWidget *parent,bool fs) :
    QGLWidget(parent)
{
    xRot = yRot = zRot = 0;
    xSpeed = ySpeed = 0;
    zoom = -6;
    fullscreen = fs;
    setWindowTitle("Ray's here");

    light = false;          //不能缺少初始化语句！！！

    //增加定时器，实现动画功能
    QTimer *timer;
    timer = new QTimer(this);
    timer->start(30);           //每10毫秒更新一次画面
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
}

NeHeWidget::~NeHeWidget()
{}


void NeHeWidget::initializeGL()
{
    LoadGLTextures();
    glEnable(GL_TEXTURE_2D);

     // 启用阴影平滑
    glShadeModel( GL_SMOOTH );
    // 黑色背景
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    // 设置深度缓存
    glClearDepth( 1.0 );
     // 启用深度测试
    glEnable( GL_DEPTH_TEST );
    // 所作深度测试的类型
    glDepthFunc( GL_LEQUAL );
    // 告诉系统对透视进行修正
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

}


void NeHeWidget::paintGL()
{
    //缺少了GL_DEPTH_BUFFER_BIT则不能正常显示
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, zoom);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);

//    glBindTexture(GL_TEXTURE_2D, texture[0]);
//    glBegin(GL_QUADS);
//    //注意4个顶点的顺序要按照逆时针的顺序。
//    //顶面
//    glTexCoord2f(0.0, 0.0);
//    glVertex3f(  1.0,   1.0,    -1.0);
//    glTexCoord2f(1.0, 0.0);
//    glVertex3f( -1.0,   1.0,    -1.0);
//    glTexCoord2f(1.0, 1.0);
//    glVertex3f( -1.0,   1.0,     1.0);
//    glTexCoord2f(0.0, 1.0);
//    glVertex3f(  1.0,   1.0,     1.0);
//    glEnd();

//    //底面
//    glBindTexture(GL_TEXTURE_2D, texture[1]);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0, 0.0);
//    glVertex3f(1.0, -1.0, 1.0);
//    glTexCoord2f(1.0, 0.0);
//    glVertex3f(-1.0, -1.0, 1.0);
//    glTexCoord2f(1.0, 1.0);
//    glVertex3f(-1.0, -1.0, -1.0);
//    glTexCoord2f(0.0, 1.0);
//    glVertex3f(1.0, -1.0, -1.0);
//    glEnd();


//    //前面
//    glBindTexture(GL_TEXTURE_2D, texture[2]);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0, 0.0);
//    glVertex3f(1.0, 1.0, 1.0);
//    glTexCoord2f(0.0,1.0);
//    glVertex3f(-1.0, 1.0, 1.0);
//    glTexCoord2f(1.0, 1.0);
//    glVertex3f(-1.0, -1.0, 1.0);
//    glTexCoord2f(1.0, 0.0);
//    glVertex3f(1.0, -1.0, 1.0);
//    glEnd();


//    //后面
//    glBindTexture(GL_TEXTURE_2D, texture[3]);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0, 0.0);
//    glVertex3f(1.0, 1.0, -1.0);

//    glTexCoord2f(1.0, 0.0);
//    glVertex3f(1.0, -1.0, -1.0);

//    glTexCoord2f(1.0, 1.0);
//    glVertex3f(-1.0, -1.0, -1.0);

//    glTexCoord2f(0.0, 1.0);
//    glVertex3f(-1.0, 1.0, -1.0);
//    glEnd();

//    //左面
//    glBindTexture(GL_TEXTURE_2D, texture[4]);
//    glBegin(GL_QUADS);

//    glTexCoord2f(0.0, 0.0);
//    glVertex3f(-1.0, 1.0, 1.0);

//    glTexCoord2f(1.0, 0.0);
//    glVertex3f(-1.0, 1.0, -1.0);

//    glTexCoord2f(1.0, 1.0);
//    glVertex3f(-1.0, -1.0, -1.0);

//    glTexCoord2f(0.0, 1.0);
//    glVertex3f(-1.0, -1.0, 1.0);
//    glEnd();

//    //右面
//    glBindTexture(GL_TEXTURE_2D, texture[5]);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0, 0.0);
//    glVertex3f(  1.0,  1.0, -1.0 );

//    glTexCoord2f(1.0, 0.0);
//    glVertex3f(  1.0,  1.0,  1.0 );

//    glTexCoord2f(1.0, 1.0);
//    glVertex3f(  1.0, -1.0,  1.0 );

//    glTexCoord2f(0.0, 1.0);
//    glVertex3f(  1.0, -1.0, -1.0 );
//    glEnd();

//    xRot += xSpeed;
//    yRot += ySpeed;
}


 // 重置OpenGL窗口大小
void NeHeWidget::resizeGL(int width, int height)
{
        // 防止窗口大小变为0
    if ( height == 0 )
    {
        height = 1;
    }
    // 重置当前的视口
    glViewport( 0, 0, (GLint)width, (GLint)height );
    // 选择投影矩阵
    glMatrixMode( GL_PROJECTION );
        // 重置投影矩阵
    glLoadIdentity();
    // 设置视口的大小
    gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
    // 选择模型观察矩阵
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}


void NeHeWidget::LoadGLTextures()
{
    QImage tex, buf;

    glGenTextures(6, texture);
    for(int i=0; i<6; i++)
    {
        char s[20] = {0};

        sprintf(s, "box-man%d.jpg",i+1);
        QString dir = "/home/ray/Pictures/Wallpaper/1080P/" + QString(s);
        if(!buf.load(dir))
//        if(!buf.load("/home/ray/Downloads/opengl_qt_nehe_06/light/light1/crate.bmp"))
        {
            qWarning("Could not read image file, using single-color instead.");
            QImage dummy(128, 128, QImage::Format_RGB32);
            dummy.fill( Qt::green );
            buf = dummy;
        }

        tex = QGLWidget::convertToGLFormat(buf);
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        //每绑定一个纹理都要设置该两项
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//        glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
//                     GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());

//      用gluBuild2DMipmaps() 缩小后的效果比glTexImage2D的好。
//      但是对性能的要求也高，否则会出现卡的现象
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tex.width(), tex.height(), GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
    }

    return;
}



void NeHeWidget::keyPressEvent(QKeyEvent *e)
{
    switch ( e->key() )
    {

    }
}
