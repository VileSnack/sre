# Overview

SRE stands for Streaming Render Engine, a rendering engine that is heavily inspired by the REYES rendering engine, with the following design goals:

* Support images of arbitrary resolution.
* Support arbitrarily large amounts of scene-level geometry.
* Support arbitrarily large numbers of rendering processes.
* Support transparency, depth of field, spatial anti-aliasing, motion blur, and focal blur.

Rendering takes place in several stages, each of which is accomplished by a separate executable, using piping to transfer data from one stage to the next.

# Scene generation

The scene generation stage will create the renderable primitives. The input to this process can come from an automated scene generation tool, or from a scene file created by a user employing GUI tools, or any other set of tools. The output of these tools will consist of Bezier patches, Particle fields, and shaders:

* Bezier patches define a two-dimensional surface. The definition of the patch can contain a temporal parameter for animation.
* Bezier volumes define a three-dimensional space in which particles are distributed.
* Shaders define the texture properties of the geometric primitives.

# Primitive rendering

The primitive renderer is responsible for taking input in the form of shaders, Bezier patches, and Bezier volumes, and from them generating render hits, which are a sample of texture data appearing at a specific place in the viewing frame.

# Render hit coallation

The render hit coallator receives a stream of render hits and composites them into images.

# Inter-process data

  # Bezier patches

  Bezier patches