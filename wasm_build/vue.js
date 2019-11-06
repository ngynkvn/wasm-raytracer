const Sphere = {
    name: 'Sphere',
    params: ['Center', 'Radius', 'Color']
}
const Light = {
    name: 'Light',
    params: ['Origin', 'Intensity', 'Type']
}

Vue.component('text-editor', {
    data: function () {
        return {
            scene: scene_text
        }
    },
    methods: {
        render: () => {
            render();
        }
    },
    template: `
        <div>
            <textarea id="scene" rows=25 cols=30> {{scene}} </textarea> 
            <button @click="render">Go</button>
        </div>
    `
});
Vue.component('ui-editor', {
    data: function () {
        return {
            objects: [Sphere, Light],
            selected: Sphere,
            attributes: {},
            object_list: [],
        }
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
    },
    template: `
    <div>
        <select v-model="selected">
            <option v-for="obj in objects" v-bind:value="obj">{{obj.name}}</option>
        </select>
        <div v-for="param in selected.params">
            <label :for="param">{{param}}:</label> <input :id="param" v-model="attributes[param]"></input>
        </div>
        <button @click="add">Add</button>
        <ul>
            <li v-for="(o, index) in object_list">{{o}}<button @click="removeItem(index)">X</button></li>
        </ul>
    </div>
    `
});
var app = new Vue({
    el: '#app',
    data: {
        editor: 'text-editor',
    }
})
