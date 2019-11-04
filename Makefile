
wasm:
	mkdir -p wasm_build
	(cd wasm_build && emcc --std=c++1z --bind ../wasm.cpp ../raytracer.cpp -o test.js)