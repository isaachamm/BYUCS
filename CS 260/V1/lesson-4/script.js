let app = new Vue ({
	el: '#root',
	
	data: {
		message: 'I really like bread',
		tasks: [{
			description: "Create some loaves of bread",
			completed: true,
		},
		{
			description: "Create some fish",
			completed: true
		},
		{
			description: "Create more loaves of bread",
			completed: false
		},
		{
			description: "Create more fish",
			completed: false
		},
		{
			description: "Create more loaves of bread",
			completed: false
		},
		{
			description: "Tell Peter to clean up the mess",
			completed: false
		}
		]
	},
	computed: {
		screaming() {
			return this.message.toUpperCase();
		},
		incompleteTasks() {
			return this.tasks.filter(task => !task.completed);
		}
	}
})