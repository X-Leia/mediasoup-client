#include "mainwindow.h"
#include <QMetaType>
#include <QApplication>
#include "mediasoupclient.hpp"
#include "logger/spd_logger.h"
#include "service/engine.h"
#include "service/i_room_client_observer.h"
#include "api/media_stream_interface.h"
#include "rtc_base/thread.h"
#include "rtc_base/win32_window.h"
#include "rtc_base/win32_socket_init.h"
#include "rtc_base/win32_socket_server.h"
#include "rtc_base/physical_socket_server.h"
#include <QOpenGLFunctions>

static void registerMetaTypes()
{
    //qRegisterMetaType<vi::RoomState>("vi::RoomState");
    //qRegisterMetaType<rtc::scoped_refptr<webrtc::MediaStreamTrackInterface>>("rtc::scoped_refptr<webrtc::MediaStreamTrackInterface>");
    //qRegisterMetaType<webrtc::VideoFrame*>("const webrtc::VideoFrame*");
}

int main(int argc, char *argv[])
{
    registerMetaTypes();

    rtc::WinsockInitializer winsockInit;
    rtc::Win32SocketServer ss;
    rtc::Win32Thread mainThread(&ss);
    rtc::ThreadManager::Instance()->SetCurrentThread(&mainThread);

    vi::Logger::init();
    getEngine()->init();
    mediasoupclient::Initialize();

    DLOG("mediasoupclient version: {}", mediasoupclient::Version().c_str());

    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    auto w = std::make_shared<MainWindow>();
    w->init();
    w->show();
    int ret =  a.exec();

    mediasoupclient::Cleanup();
    getEngine()->destroy();
    vi::Logger::destroy();

    return ret;
}
