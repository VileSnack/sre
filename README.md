# Overview

## Objective

SRE stands for Streaming Render Engine, a rendering engine that is heavily inspired by the REYES rendering engine, with the following design goals:

* Support images of arbitrary resolution.
* Support arbitrarily large amounts of scene-level geometry.
* Support arbitrarily large numbers of rendering processes.
* Support transparency, depth of field, spatial anti-aliasing, motion blur, and focal blur.



Rendering takes place in several stages, each of which is accomplished by a separate executable, using piping to transfer data from one stage to the next.

# Scene generation

Scene generation begins with 3D authoring tools of some kind, whether it be a 3D modelling application or a scripting language. The output from the scene generation stage consists of primitives to be rendered and shaders to define the qualities of each primitive at every point.

# Primitive rendering

The primitive renderer is responsible for taking input in the form of shaders and primitives, and from these generating *render hits*.

# Render hit coallation

The render hit coallator receives a stream of render hits and composites them into images.

# Project road map

The project is currently focused on developing the render hit coallator, which is the final rendering stage.

# Inter-process data

* Render hits. This is a rendered sample of framebuffer data. It contains the horizontal and vertical coordinates of the pixel within the frame, the sub-pixel within the pixel (to support all three forms of anti-aliasing), the depth (to properly support occlusion), and channel data (to specify the desired color and other output data).

* A render hit stream consists of:
  * An integer for the horizontal coordinate of the pixel;
  * An integer for the vertical coordinate of the pixel;
  * An integer for the sub-pixel within the pixel;
  * A float value for the depth of the data;
  * One or more channel data, separated by a comma;
  * A semicolon to terminate the render hit.

* A channel datum consists of:
  * A string for the name of the channel;
  * A float value for the channel;
  * An optional alpha value (default is 1.0);
  * An optional spread value (default is 0.0);
  * A comma, if this is not the final channel datum in the render hit.

# More detail

When the primitive renderer reads a shader from its input stream, it sets this shader as the current shader for all subsequent patches.

Bezier patches are read from the input stream, and are defined by a three-dimensional array of coefficients. The patch is initially assigned a five-dimensional bounding volume from <0,0,0,-1,-1> to <1,1,1,1,1>, where the first element is the time within the frame, the second and third elements are the spatial parameters of the patch, and the final two parameters are used for depth of field. The corners of this bounding volume are projected against the framebuffer, and recursively subdivided and re-projected, until each child patch is either entirely outside of the viewing frame or spans over two pixels or less in both directions. These final sub-patches are tested against the sub-pixels within their projected area. If a test passes, the current shader is called for the patch location and the results of the shader are output as a render hit. 

The render coallator accepts a stream of render hits and appends each hit to a raster line file based on the vertical coordinate of the render hit's pixel. This allows scene geometry to be rendered in any order without regard to its location in the framebuffer, and also supports an amount of scene geometry limited only by the amount of available storage space.

When the end of the stream of render hits is reached, the coallator then takes each raster file and separates each render hit by pixel and sub-pixel.

Each sub-pixel's render hits are sorted by depth, and then the color data of each render hit is applied in furthest-to-nearest order, to support transparency. When each sub-pixel's channel data is calculated, the channels are averaged together to produce the channel data for the pixel, which is written to the output file.