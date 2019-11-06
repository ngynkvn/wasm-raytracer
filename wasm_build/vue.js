const Sphere = {
    name: 'Sphere',
    params: ['Center', 'Radius', 'Color']
}
const Light = {
    name: 'Light',
    params: ['Origin', 'Intensity', 'Type']
}
const Camera = {
    name: 'Camera',
    params: ['Position']
}
const Dimensions = {
    name: 'Dimensions',
    params: ['Width', 'Height']
}
const Viewport = {
    name: 'Viewport',
    params: ['WHZ']
}
const SceneObjects = [Sphere, Light, Camera, Dimensions, Viewport]
const NameToParamOrder = Object.assign({}, ...SceneObjects.map(({ name, params }) => ({ [name]: params })))
Vue.component('text-editor', {
    data: function () {
        return {
            scene: scene_text,
            message: null
        }
    },
    methods: {
        render: function () {
            this.message = `Took ${render(this.scene)} ms`;
        }
    },
    template: `
        <div>
            <textarea id="scene" rows=25 cols=30> {{scene}} </textarea> 
            <button @click="render(scene)">Go</button>
            <p v-if="message">{{message}}</p>
        </div>
    `,
    mounted: function () {
        this.render();
    }
});

function scene_encode(obj_list) {
    return obj_list.map(o => {
        const { name } = o;
        return `${name} { ${NameToParamOrder[name].map(p => o[p]).join('\n')} }`
    }).join('\n');
}

Vue.component('ui-editor', {
    data: function () {
        return {
            objects: SceneObjects,
            selected: Sphere,
            attributes: {},
            object_list: [...starting_objs],
            message: null,
        }
    },
    methods: {
        render: function () {
            this.message = `Took ${render(scene_encode(this.object_list))} ms`;
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
    },
    template: `
    <div>
        <select v-model="selected">
            <option v-for="obj in objects" v-bind:value="obj">{{obj.name}}</option>
        </select>
        <div v-for="(param, i) in selected.params">
            <label :for="param">{{param}}:</label> <input :id="param" v-model="attributes[param]"></input>
        </div>
        <button @click="add">Add</button>
        <ul>
            <li v-for="(o, index) in object_list">{{o}}<button @click="removeItem(index)">X</button></li>
        </ul>
        <button @click="render">Go</button>
        <p v-if="message">{{message}}</p>
    </div>
    `,
    mounted: function () {
        this.render();
    }
});
var app;
Module.onRuntimeInitialized = function () {
    app = new Vue({
        el: '#app',
        data: {
            editor: 'text-editor',
        }
    })
};