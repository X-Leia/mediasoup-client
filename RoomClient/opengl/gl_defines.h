#pragma once

#ifdef WEBRTC_MAC
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#if TARGET_OS_IPHONE
#define RTC_PIXEL_FORMAT GL_LUMINANCE
#define SHADER_VERSION
#define VERTEX_SHADER_IN "attribute"
#define VERTEX_SHADER_OUT "varying"
#define FRAGMENT_SHADER_IN "varying"
#define FRAGMENT_SHADER_OUT
#define FRAGMENT_SHADER_COLOR "gl_FragColor"
#define FRAGMENT_SHADER_TEXTURE "texture2D"

@class EAGLContext;
typedef EAGLContext GlContextType;
#else
#define RTC_PIXEL_FORMAT GL_RED
#define SHADER_VERSION "#version 150\n"
#define VERTEX_SHADER_IN "in"
#define VERTEX_SHADER_OUT "out"
#define FRAGMENT_SHADER_IN "in"
#define FRAGMENT_SHADER_OUT "out vec4 fragColor;\n"
#define FRAGMENT_SHADER_COLOR "fragColor"
#define FRAGMENT_SHADER_TEXTURE "texture"
//@class EAGLContext;
//typedef EAGLContext GlContextType;
#endif