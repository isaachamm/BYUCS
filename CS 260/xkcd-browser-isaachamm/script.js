Vue.component('star-rating', VueStarRating.default);

let app = new Vue ({
	el: "#app",
	
	data: {
		number: '',
		max: '',
		current: {
			title: '',
			img: '',
			alt: ''
		},
		loading: true,
		addedName: '',
		addedComment: '',
		comments: {},
		ratings: {},
	},
	computed: {
		month() {
			var month = new Array;
			if (this.current.month === undefined)
				return'';
			month[0] = "January";
			month[1] = "February";
			month[2] = "March";
			month[3] = "April";
			month[4] = "May";
			month[5] = "June";
			month[6] = "July";
			month[7] = "August";
			month[8] = "September";
			month[9] = "October";
			month[10] = "November";
			month[11] = "December";
			return month[this.current.month - 1];
		},
		average() {
			if (!(this.ratings[this.number]))
				return '';
			let avg = 0;
			avg = this.ratings[this.number].sum/this.ratings[this.number].total;
			return avg;
		},
	},
	watch: {
		number(value, oldValue) {
			if (oldValue === '') {
			this.max = value;
			}
			else {
				this.xkcd();
			}
		},
	},
	created() {
		this.xkcd();
	},
	methods: {
		async xkcd() {
			try {
				this.loading = true;
				let url = 'https://xkcd.now.sh/?comic=';
				if (this.number === '') {
					url += 'latest';
				}
				else {
					url += this.number;
				}
				const response = await axios.get(url);	//response BECOMES the json
				this.current = response.data;
				this.loading = false;
				this.number = response.data.num;
			} catch (error) {
				this.number = this.max;
			}
		},
		firstComic() {
			this.number = 1;
		},
		previousComic() {
			this.number = this.number - 1;
			if (this.number < 1) {
				this.number = 1;
			}
		},
		nextComic() {
			this.number = this.number + 1;
			if (this.number > this.max) {
				this.number = this.max;
			}
		},
		lastComic() {
			this.number = this.max;
		},
		getRandom(min, max) {
			min = Math.ceil(min);
			max = Math.floor(max);
			return Math.floor(Math.random() * (max - min + 1)) + min;
		},
		randomComic() {
			this.number = this.getRandom(1, this.max);
		},
		setRating(rating) {
			if (!(this.number in this.ratings))
				Vue.set(this.ratings, this.number, {
					sum : 0,
					total: 0,
				});
			this.ratings[this.number].sum += rating;
			this.ratings[this.number].total += 1;

		},
		addComment() {
			if (!(this.number in this.comments))
				Vue.set(app.comments, this.number, new Array);
			this.comments[this.number].push({
				author: this.addedName,
				text: this.addedComment,
				date: moment().format("MM-D-YYYY")
			});
			this.addedName = '';
			this.addedComment = '';
		},

		
		// xkcd() {
		// 	let url = 'https://xkcd.now.sh/?comic=';
		// 	if (this.number === '') {
		// 	url += 'latest';
		// 	}
		// 	else {
		// 		url += this.number;
		// 	}
		// 	axios.get(url)
		// 		.then(response => {
		// 			this.current = response.data;
		// 			return true;
		// 		})
		// 		.catch(error => {
		// 			console.log(error)
		// 		});
		// }
	}
});