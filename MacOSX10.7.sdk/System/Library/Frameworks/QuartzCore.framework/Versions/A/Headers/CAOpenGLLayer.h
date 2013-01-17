/* CoreAnimation - CAOpenGLLayer.h

   Copyright (c) 2006-2007 Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>
#import <CoreVideo/CVBase.h>
#import <OpenGL/OpenGL.h>

@interface CAOpenGLLayer : CALayer
{
@private
  struct CAOpenGLLayerPrivate *_glPriv;
}

/* When false the contents of the layer is only updated in response to
 * -setNeedsDisplay messages. When true the layer is asked to redraw
 * periodically with timestamps matching the display update frequency.
 * The default value is NO. */

@property(getter=isAsynchronous) BOOL asynchronous;

/* Called before attempting to render the frame for layer time 't'.
 * When non-null 'ts' describes the display timestamp associated with
 * layer time 't'. If the method returns false, the frame is skipped. The
 * default implementation always returns true. */

- (BOOL)canDrawInCGLContext:(CGLContextObj)ctx
    pixelFormat:(CGLPixelFormatObj)pf forLayerTime:(CFTimeInterval)t
    displayTime:(const CVTimeStamp *)ts;

/* Called when a new frame needs to be generated for layer time 't'.
 * 'ctx' is attached to the rendering destination. It's state is
 * otherwise undefined. When non-null 'ts'  describes the display
 * timestamp associated with layer time 't'. Subclasses should call
 * the superclass implementation of the method to flush the context
 * after rendering. */

- (void)drawInCGLContext:(CGLContextObj)ctx pixelFormat:(CGLPixelFormatObj)pf
    forLayerTime:(CFTimeInterval)t displayTime:(const CVTimeStamp *)ts;

/* This method will be called by the CAOpenGLLayer implementation when
 * a pixel format object is needed for the layer. Should return an
 * OpenGL pixel format suitable for rendering to the set of displays
 * defined by the display mask 'mask'. The default implementation
 * returns a 32bpp fixed point pixel format, with NoRecovery and
 * Accelerated flags set. */

- (CGLPixelFormatObj)copyCGLPixelFormatForDisplayMask:(uint32_t)mask;

/* Called when the OpenGL pixel format 'pf' that was previously
 * returned from -copyCGLPixelFormatForDisplayMask: is no longer
 * needed. */

- (void)releaseCGLPixelFormat:(CGLPixelFormatObj)pf;

/* Called by the CAOpenGLLayer implementation when a rendering context
 * is needed by the layer. Should return an OpenGL context with
 * renderers from pixel format 'pf'. The default implementation
 * allocates a new context with a null share context. */

- (CGLContextObj)copyCGLContextForPixelFormat:(CGLPixelFormatObj)pf;

/* Called when the OpenGL context 'ctx' that was previously returned
 * from -copyCGLContextForPixelFormat: is no longer needed. */

- (void)releaseCGLContext:(CGLContextObj)ctx;

@end
