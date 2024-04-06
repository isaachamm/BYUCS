let app = new Vue({
	el: "#app",
	data: {
		todos: [{
			text: "make an app",
			completed: false
		},
		{
			text: "declare victory",
			completed: false
		},
		{
			text: "proft",
			completed: false
		}],
		message: '',
		show: 'all',
	},
	computed: {
		activeTodos() {
			return this.todos.filter(item => {
				return !item.completed;
			})
		},
		filteredTodos() {
			if (this.show === 'active') {
				this.todos.filter(item => {
					return !item.completed;
				});
			}
			if (this.show === 'completed') {
				this.todos.filter(item => {
					return item.completed;
				});
			}
			return this.todos;
			
		}
	},
	methods: {
		addItem() {
			this.todos.push({text: this.message, completed: false});
			this.message = ''
		},
		deleteItem(item) {
			let index = this.todos.indexOf(item);
			if (index > -1)
				this.todos.splice(index, 1);
		},
		showAll() {
			this.show = 'all';
		},
		showActive() {
			this.show = 'active';
		},
		showCompleted() {
			this.show = 'completed';
		},
		deleteCompleted() {
			this.todos = this.todos.filter(item => {
				return !item.completed;
			})
		}
	}
});