Graphics-Framework
==================

A graphics framework that can be used as the starting point for a larger scale graphics engine

Objectives
----------

1. Be able to switch between different shader pograms
2. Be able to create different shader programs with ease from different shader files
3. Ensure that shader files and the actual shader program are decoupled
4. Be able to draw/ create multiple meshes
5. Be able to create/add a new mesh with ease
6. Ensure that the shaders and the meshes are decoupled
7. Decoupling between actual demo program and the shaders
8. Decoupling between actual demo program and the meshes

The Demo Program
----------------

In order to test our framework, we will create a simple mesh, and perform different lighting models on it when a keyboard event is registered. These lighting models will each be created from separate shader files (thus creating a different shader instance for each). The mesh will be created from a decoupled mesh object.
