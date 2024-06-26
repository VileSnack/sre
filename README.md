# Overview

## History

I started this project some years ago, after a couple decades of using the Persistence of Vision Ray Tracer (www.povray.org), which is a freeware 3d rendering application running on scripting files, and coming across a paper at graphics.pixar.com which described the REYES method. I took some of the ideas from the REYES papers, some more ideas from POV-Ray, and came up with a rendering strategy of my own.

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
* Support arbitrarily large numbers of independent rendering processes. This allows large rendering jobs to be split up among separate processes. Among other things, this allows old hardware to remain useful.
* Support transparency, depth of field, spatial anti-aliasing, motion blur, and focal blur. These are necessary for most animation work.

## Modular rendering

Rendering will be handled by separate executables, which will either pipe output to the following stage, or write output to file, from which the following stage will read:

* Scene generation. This is the stage where the author creates the scene, using whatever authoring tools are available.
* Primitive rendering. The renderer will take the data generated in the previous step and from it generate image fragments.
* Image fragment collation. The collator will take the image fragments generated in the previous step and group them for more efficient processing by the image file generator.
* Image file generation. The generator will take each group of fragments (perhaps from different sources) and combine them into the final image.

# Project road map

The image fragment collator is essentially done.

The image file generator is the next stage. Currently it is in the note-taking phase.

# Image Fragment Collation

One limitation of both ray-tracing and REYES rendering is that they both have a requirement to keep some rendered imagery and some scene geometry in memory, including imagery and geometry which is not involved in the rendering that is ongoing. This increases the memory requirements for the processor. This partly due to the strategy of rendering an image starting from one part of the image and progressing to the other.

The solution used by the SRE is to save rendered imagery to file as it is generated, so that there is no need to retain it in memory. This frees the renderer from the need to render scene geometry in any particular order, which in turn frees the renderer from needing to retain scene geometry in memory when it is not being rendered.

This is accomplished by including the fragment's location in the final raster image with the fragment, and saving each image fragment to file. Once all rendering has been accomplished, the files containing the fragment data can be processed to generate the final image.

This strategem also allows multiple processors to render scene geometry for the same image, without interfering with each other.

Another advantage of this approach is that a pass-through utility can be used to monitor the progress of a render; by reading each image fragment, applying it to the image in a display monitor, and then piping that same fragment to the collation stage, render management personnel can observe the progress of rendering in real time.

The trade-off for this is that the image fragments must be stored before they can be collated into the final image. However, this data can be stored in files, and not in computer memory; hard drive space is the very cheapest resource in IT.

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
* The alpha value (defaults to `1.0`);
* The spread value (defaults to `0.0`).

The alpha value determines how much of the deeper scenery is visible.

The spread value is used to distribute the effect of the value and alpha over a depth range, to better support fog and smoke effects.

(Note that the alpha value is optional only if the spread value is left out as well.)

In the stream expected by the image fragment collator:

* Image fragments are delimited by semicolons. The final image fragment can end with an end-of-file.
* Channel data entries are delimited by commas; the final channel datum in an image fragment can share that fragment's semicolon/EOF terminator. Also, the alpha and spread values default to 1 and 0 respectively.

If an object with a surface color (.875,.5,.25,.9), giving a slightly transparent caramel color, covers sub-pixel #13 of the pixel at (123,45), at a distance of 3.4534 units from the camera viewpoint, the image fragment stream would look like this:

`123 45 12 3.4534 R .875 .9, G .500 .9, B .25 .9;`

Note that the channel data does not have to represent color and transparency data; the channel can also specify highlighting, surface normals, the coordinates of a mapped texture, or any other set of values. This can be used to allow many lighting and environmental effects to be applied at a later stage of processing.

## ifc

The project `ifc` in this repository contains the source for the image fragment collator, written in C.

Its operation is very simple: It receives a stream of image fragments via `stdin` and writes each fragment to a file selected based on the vertical coordinate of the fragment's pixel. Existing files are **not** overwritten, but instead are extended with new data.

The output files by default are written to the working directory of the `ifc` process. This can be changed by supplying the name of another directory as the first command-line argument when executing the utility. The directory will be created if it does not already exist.

## ifg

The project `ifg` in this repository contains the source for the image file generator, written in C.

The image file generator is the final stage of rendering. It will take a set of files containing image fragment data and from them generate a final image file.

The current concept supports the following command-line options:

* `-f` Output file name. The output file type will be derived from the file extension. Will probably support PNG and EXR.

* `-i` (short for *input directory*): Input directory to include. Can be repeated. This is to support rendering from multiple processors.

* `-l` The x-coordinate of the left-most pixels to be processed. These pixels will be the left edge of the image file. Pixels with lower values will be ignored. Defaults to `0`.

* `-t` The y-coordinate of the top row of pixels to be processed. These pixels will be the top edge of the image file. Pixels with lower values will be ignored. Defaults to `0`.

* `-r` The x-coordinate of right-most pixels to be processed. These pixels will be the right edge of the image file. Pixels with higher values will be ignored.

* `-b` The y-coordinate of the bottom row of pixels to be processed. These pixels will be the bottom edge of the image file. Pixels with higher values will be ignored.

* `-w` The same as `-l 0 -r N-1` where `N` is the supplied value.

* `-h` The same as `-t 0 -b N-1` where `N` is the supplied value.

* `-a` (short for *anti-aliasing*) The sampling level per pixel.
