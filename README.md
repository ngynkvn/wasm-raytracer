# Raytracer

Based off https://www.gabrielgambetta.com/computer-graphics-from-scratch/introduction.html

![Sample render](https://user-images.githubusercontent.com/20323081/68098609-9974f900-fe8b-11e9-9ee7-ed1291d64993.png)

Requires LibPNG and png++ to run.

## To run
```
mkdir -p build

cd build

cmake ../

make
```
Outputs a binary named raytracer.

## Web assembly
Have the Emscripten SDK tools available to use from your terminal and simply run the two commands below: 
```
make
make run
```
Should be viewable at [localhost:8080](localhost:8080)

## Todo
- Add parameterization (both from command line and JS environment).
- Make a DSL for specifying the scene to render. 
