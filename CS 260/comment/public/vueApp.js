const app = new Vue({
	el: '#app',
	data: {
		newComment: "",
	  comments: [
		{ title: 'Comment 1', upvotes: 5 },
		{ title: 'Comment 2', upvotes: 6 },
		{ title: 'Comment 3', upvotes: 1 },
		{ title: 'Comment 4', upvotes: 4 },
		{ title: 'Comment 5', upvotes: 3 },
	  ],
	},
	created: function() {
		this.getAll();
	},
	computed: {
		sortedComments() {
			return this.comments.sort((a, b) => {
				return b.upvotes - a.upvotes;
			})
		}
	},
	methods: {
		addComment() {
			const comment = { title: this.newComment, upvotes: 0 };
			fetch('/comments', {
			  method: 'POST',
			  headers: { 'Content-Type': 'application/json' },
			  body: JSON.stringify(comment),
			})
			  .then((r) => r.json())
			  .then((response) => {
				this.comments.push(response);
			  });
		},
		incrementUpvotes(item) {
			fetch(`/comments/${item._id}/upvote`, {
			  method: 'PUT',
			})
			  .then((r) => r.json())
			  .then((response) => {
				item.upvotes = response.upvotes;
			  });
		},
		getAll() {
			const url = '/comments';
			fetch(url)
			  .then((r) => r.json())
			  .then((response) => {
				this.comments = response;
			  });
		},

	},
  });