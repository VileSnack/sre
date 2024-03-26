# Overview

## History

I started this project some years ago, after a couple decades of using the Persistence of Vision Ray Tracer (www.povray.org), which is a freeware 3d rendering application running on scripting files, and coming across a paper at graphics.pixar.com which described the REYES paradigm. I took some of the ideas from the REYES papers, some more ideas from POV-Ray, and came up with a rendering strategy of my own.

## Goals

The POV-Ray renderer is an excellent tool for a hobbyist who has lots of time but very little money, but it has some limitations:

* Rendering requires all of the scene geometry to be loaded into memory at once. This is a limitation of ray-tracing in general.
* Implementation of depth-of-field has opportunities for performance improvement.
* Rendering of small/distant objects is prone to ray misses, causing unwanted artifacts during animations.

REYES rendering overcomes some of these limitations, but it also has limitations of its own:

* Supporting full transparency requires a degree of rendered imagery to be retained in memory until rendering is complete.
* Some scene geometry has to be retained in memory when it is not being rendered.

My hope is to address all of the above weaknesses, and accomplish the following as well:

* Support images of arbitrary resolution. (To be ready when 16K monitors are all the rage.)
* Support arbitrarily large amounts of scene-level geometry. We should be able to render a forest and all of its leaves.
* Support arbitrarily large numbers of independent rendering processes. This allows large rendering jobs to be split up among separate processes.
* Support transparency, depth of field, spatial anti-aliasing, motion blur, and focal blur. These are necessary for most animation work.

## Modular rendering process.

Rendering will proceed in distinct stages:

* Scene generation. This is the stage where the author creates the scene, using whatever authoring tools are available.
* Primitive rendering. The renderer will take the data generated in the previous step and from it generate image fragments.
* Image fragment coallation. The coallator will take the fragments generated in the previous step and from it generate an image file.

# Project road map

The project is currently focused on developing the image fragment coallator, which is the final rendering stage.

This is going to be a separate executable so that it can be used for other rendering techniques. The primitive rendering stage described above need not be the only way to generate image fragments; a CAD program, or a ray-casting renderer, can generate image fragments. Also, making it a separate executable will enable it to be tested before the prior stages are developed.

# Image Fragment Coallation

The idea behind image fragment coallation is to free the previous rendering stages from a forced ordering of rendering. Ray tracers work on a pixel-by-pixel basis, usually starting with the top-most raster line, rendering the pixels on that line from left to right, and then working downward from there. The REYES method also imposes a spatial re-ordering of scene geometry (each primitive is assigned to one or more "buckets", with each bucket then being rendered in order).

Both of these approaches require each primitive to occupy memory while some other primitive is being rendered, and although the REYES scheme at least allows primitives in completed buckets to be released, primitives in unrendered buckets still occupy memory.

By allowing scene geometry to be rendered in any order, each piece of scene geometry needs to be in memory only while it is being rendered. This allows for more complicated primitives to be rendered.

Also, because the individual fragments can be generated in any order, rendering of a single scene can be divided up among multiple independent processors, with their results merged at the final stage. This allows for more efficient management of rendering operations.

Another advantage of this approach is that a pass-through utility can be used to monitor the progress of a scene file; by reading each image fragment, applying it to the image in a display monitor, and then piping that same fragment to the coallation stage, render management personnel can observe the progress of rendering in real time.

The trade-off for this is that the image fragments must be stored before they can be coallated into the final image. However, this data can be stored in files, and not in computer memory.

Another trade-off is that scene data will have to be built into the shader so that shadows and reflections can be accurately calculated, and will have to be coded to account for the motions of all scene obects (light sources and shadow-casting geometry).

## Image fragments

The image fragment is a piece of data which identifies a point that forms part of the rendered image of a primitive, with the following structure:

* The horizontal coordinate of the pixel;
* The vertical coordinate of the pixel;
* The sub-pixel (zero-indexed) within the pixel;
* The depth;
* An array of channel data.

Each channel datum is a record of data that describes the value of an image element:

* The name of the channel;
* The value;
* The alpha value (defaults to 1.0);
* The spread value (defaults to 0.0).

The alpha value determines how much of the deeper scenery is visible.

The spread value is used to distribute the effect of the value and alpha over a depth range, to better support fog and smoke effects.

(Note that the alpha value is optional only if the spread value is left out as well.)

In the stream expected by the image fragment coallator:

* Image fragments are delimited by semicolons. The final image fragment can end with an end-of-file.
* Channel data entries are delimited by commas; the final channel datum in an image fragment can share that fragment's semicolon/EOF terminator. Also, the alpha and spread values default to 1 and 0 respectively.

If an object with a surface color (.875,.5,.25,.9), giving a slightly transparent caramel color, covers sub-pixel #13 of the pixel at (123,45), at a distance of 3.4534 units from the camera viewpoint, the image fragment stream would look like this:

123 45 12 3.4534 R .875 .9, G .500 .9, B .25 .9;

Note that the channel data does not have to be color and transparency data; the channel can also specify highlighting, surface normals, the coordinates of a mapped texture, or any other set of values.
