# Raytracer 🔴

Based off https://www.gabrielgambetta.com/computer-graphics-from-scratch/introduction.html

Play with at https://unhealthy-vacation.surge.sh

<img src=https://user-images.githubusercontent.com/20323081/68098609-9974f900-fe8b-11e9-9ee7-ed1291d64993.png alt="Sample render" width=300px/>

Requires LibPNG and png++ to run.

Used _Emscripten / WASM_ and _Vue.js_ for web rendering

Used _C++_ and _LibPNG / png++_ for image rendering

Raytracing is implemented C++ and compiled with the Emscripten toolchain to permit running on web.

## To run
```
mkdir -p build

cd build

cmake ../

make
```
Outputs a binary named raytracer.

Run with `./raytracer < test.scene`

## Web assembly
Have the Emscripten SDK tools available to use from your terminal and simply run the two commands below: 
```
make
make run
```
Should be viewable at [localhost:8080](localhost:8080)

### Technical details

This is kind of a hodgepodge of a lot of things that I was interested in playing with including but not limited to:

- Raytracing and computer graphics
- Javascript Canvas API's 
- VueJS
- Communication and messaging between different programming environments / processes.
- Parsing data into usable data structures.

## Todo
- 🚧 Add parameterization (both from command line and JS environment).
- ✔️ Make a DSL for specifying the scene to render. 
- 🤔 Encoding + Decoding schemes
- 🤔 Comparing different ways of wasm - native communications and performance benchmarking.
  - Compare speeds between native + wasm as rendering complexity increases (will need to enable flags for rendering techniques to use)
