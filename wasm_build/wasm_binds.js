
const width = 600;
const height = 600;
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext('2d');

function drawCanvasWTrace() {
    console.log("Drawing by calling trace from raytracer.")
    const imgData = ctx.createImageData(width, height);
    let i = 0;
    for (var y = height / 2; y > -height / 2; y--) {
        for (var x = -width / 2; x < width / 2; x++) {
            const [r, g, b] = Module.trace(x, y);
            imgData.data[i++] = r;
            imgData.data[i++] = g;
            imgData.data[i++] = b;
            imgData.data[i++] = 255;
        }
    }
    ctx.putImageData(imgData, 0, 0);
}

function drawCanvasWVec() {
    console.log("Drawing by requesting a vector from raytracer.")
    const imgData = ctx.createImageData(width, height);
    const vec = Module.create_vec();
    const len = vec.size();
    for (let i = 0; i < len; i++) {
        imgData.data[i] = vec.get(i);
    }
    ctx.putImageData(imgData, 0, 0);
}

function drawCanvasWView() {
    console.log("Drawing by requesting a mem view to raytracer.")
    const imgData = ctx.createImageData(width, height);
    const vec = Module.create_view();
    for (let i = 0; i < vec.length; i++) {
        imgData.data[i] = vec[i];
    }
    ctx.putImageData(imgData, 0, 0);
}
function drawCanvasWViewStr(str) {
    console.log("Drawing by requesting a mem view to based on scene.")
    const imgData = ctx.createImageData(width, height);
    const vec = Module.create_view_from(str);
    for (let i = 0; i < vec.length; i++) {
        imgData.data[i] = vec[i];
    }
    ctx.putImageData(imgData, 0, 0);
}
const text = document.getElementById('scene');
const p = document.getElementById('message');

const render = () => {
    const start = Date.now();
    drawCanvasWViewStr(text.value);
    p.innerText = "Took " + (Date.now() - start) + " ms";
}

Module.onRuntimeInitialized = () => { render() };