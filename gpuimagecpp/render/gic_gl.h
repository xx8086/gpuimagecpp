//
//  gic_gl.h
//  GPUImageCPP
//
//  Created by liu on 2018/9/10.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef gic_gl_h
#define gic_gl_h

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
//#define glGenVertexArrays glGenVertexArraysOES
//#define glBindVertexArray glBindVertexArrayOES
//#define glGenVertexArrays glGenVertexArraysOES
//#define glGenVertexArrays glGenVertexArraysOES
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

#endif /* gic_gl_h */
