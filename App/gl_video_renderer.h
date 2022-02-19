/**
 * This file is part of janus_client project.
 * Author:    Jackie Ou
 * Created:   2020-10-01
 **/

#pragma once


#include <GL/glew.h>
#include <memory>
#include "api/video/video_sink_interface.h"
#include "api/video/video_frame.h"
#include <mutex>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "service/gl_renderer.h"

class GLVideoShader;
class I420TextureCache;
class QTimer;

class GLVideoRenderer 
	: public QOpenGLWidget
    , public QOpenGLFunctions
    , public vi::GlRenderer
	, public std::enable_shared_from_this<GLVideoRenderer>
{
	Q_OBJECT

public:
	GLVideoRenderer(QWidget *parent);

	~GLVideoRenderer();

	void init();

protected:
	void initializeGL() override;

	void resizeGL(int w, int h) override;

	void paintGL() override;

    void OnFrame(const webrtc::VideoFrame& frame) override;

signals:
    void frameArrived(const webrtc::VideoFrame& frame);

private slots:

    void onFrameArrived(const webrtc::VideoFrame& frame);

	void cleanup();

private:
	std::shared_ptr<GLVideoShader> _videoShader;

	std::shared_ptr<I420TextureCache> _i420TextureCache;

	std::shared_ptr<webrtc::VideoFrame> _cacheFrame;

    bool _inited = false;
};