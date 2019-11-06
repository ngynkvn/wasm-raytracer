const Sphere = {
    name: 'Sphere',
    params: ['Center', 'Radius', 'Color']
}
const Light = {
    name: 'Light',
    params: ['Origin', 'Intensity', 'Type']
}

var app = new Vue({
    el: '#app',
    data: {
        scene: `; A sample scene to be parsed by my hand-written parser
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
}`,
        objects: [Sphere, Light],
        selected: Sphere,
        attributes: {},
        object_list: []
    },
    methods: {
        render: () => {
            render();
        },
        add: function () {
            const { name } = this.selected;
            if (this.selected.params.length === Object.keys(this.attributes).length) {
                this.object_list.push({ name, ...this.attributes });
            }
        },
        removeItem: function (index) {
            this.object_list.splice(index, 1);
        }
    }
})
