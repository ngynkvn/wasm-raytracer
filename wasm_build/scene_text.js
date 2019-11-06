//Yeah I know.. It was just annoying to look at in the actual ui-logic.
const scene_text = `; A sample scene to be parsed by my hand-written parser
Camera {
    0 0 0
}
Dimensions {
    600 600
}
Viewport {
    1 1 1
}
Sphere {
    0 -1 3   ; Coords <x y z>
    1        ; Radius
    255 0 0  ; Color <R G B>
}

Sphere {
    2 0 4
    1
    0 255 0
}

Sphere {
    -2 0 4
    1
    0 0 255
}

Sphere {
    0 -5001 0
    5000
    0 255 255
}

Light {
    0 0 0
    .2
    AMBIENT
}

Light {
    2 1 0
    .6
    POINT
}

Light {
    1 4 4
    .2
    DIRECTIONAL
}`

const starting_objs = [
    {name: "Camera", Position: "0 0 0"},
    {name: "Dimensions", Width: "600", Height:"600"},
    {name: "Viewport", WHZ: "1 1 1"},
    {name: "Sphere", Center: "0 -1 3", Radius: "1", Color: "255 0 0"},
    {name: "Sphere", Center: "2 -0 4", Radius: "1", Color: "0 255 0"},
    {name: "Sphere", Center: "-2 0 4", Radius: "1", Color: "0 0 255"},
    {name: "Sphere", Center: "0 -5001 0", Radius: "5000", Color: "0 255 255"},
    {name: "Light", Origin: "0 0 0", Intensity: ".2", Type: "AMBIENT"},
    {name: "Light", Origin: "2 1 0", Intensity: ".6", Type: "POINT"},
    {name: "Light", Origin: "1 4 4", Intensity: ".2", Type: "DIRECTIONAL"},
]