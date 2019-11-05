
wasm:
	mkdir -p wasm_build
	(cd wasm_build && emcc --std=c++1z --bind ../wasm.cpp ../raytracer.cpp ../scene_parser.cpp -s TOTAL_MEMORY=67108864 -o test.js)

run:
	(cd wasm_build && emrun --no_browser --port 8080 test.html)
