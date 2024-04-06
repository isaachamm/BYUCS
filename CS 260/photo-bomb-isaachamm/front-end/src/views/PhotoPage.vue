<template>
	<div class="home">
		<img :src="photo[0].path" />
		<p>Title: {{ photo[0].title }}</p>
		<p>Posted by {{ photo[0].username }}</p>
		<p>Created on {{ formatDate(photo[0].created) }}</p>
		<p>Description: {{ photo[0].description }}</p>
		<div class="comment" v-for="word in photoComments" :key="word.id">
			<p>Comment: {{ word.comment }} </p>
			<p>User: {{ word.username }} </p>
			<p class="photoDate">Commented on: {{formatDate(photo.created)}}</p>
		</div>
		<div v-if="user" class="add">
			<div class="form">
				<textarea v-model="newComment" placeholder="Place New Comment here"></textarea>
				<br/>
				<button @click="upload">Upload Comment</button>
			</div>
		</div>
	</div>
</template>

<style scoped>
img {
	margin-top: 125px;
	width: 400px;
}

textarea {
	width: 500px;
	height: 100px;
}

button {
	margin: 10px;
}

.home {
	text-align: center;
}

.comment {
	border: solid black 1px;
	margin: 10px;
	text-align: left;
}
</style>

<script>
import axios from 'axios';
import moment from 'moment';

export default {
	name: 'PhotoPage',
	data() {
		return {
			photo: '',
			error: '',
			newComment: '',
			photoComments: [],
		}
	},
	async created() {
		this.getOnePhoto();
		this.getComments();
		try {
		let response = await axios.get('/api/users');
		this.$root.$data.user = response.data.user;
		} catch (error) {
		this.$root.$data.user = null;
		}
	},
	computed: {
		user() {
			return this.$root.$data.user;
		}

	},
	methods: {
		formatDate(date) {
			return moment(date).format('d MMMM YYYY @ hh:mm');
		},
		async getOnePhoto() {
			try {
				let response = await axios.get('/api/photos/single/' + this.$route.params.id);
				this.photo = response.data;
			} catch (error) {
				this.error = error.response.data.message;
			}
		},
		async getComments() {
			try {
				let response = await axios.get('/api/photos/comment/' + this.$route.params.id);
				this.photoComments = response.data;
			} catch (error) {
				this.error = error.response.data.message;
			}
		},
		async upload() {
			if (!this.newComment)
				return;
			try {
				await axios.post('/api/photos/comment/' + this.$route.params.id, {
					comment: this.newComment,
				});
			this.getComments();
			} catch (error) {
				console.log(error);
			}
		},
	},
}
</script>
