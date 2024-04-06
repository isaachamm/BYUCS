let app = new Vue ({
	el: "#root",
	data: {
		title: 'Brought to you by Javascript',
		className: 'red',
		isLoading: 'false'
	},
	methods: {
		toggleLoading() {
			this.isLoading = !this.isLoading;
		}
	}
});