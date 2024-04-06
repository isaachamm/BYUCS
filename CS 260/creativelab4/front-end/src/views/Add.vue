<template>
<div class="admin">
    <h1>You can add a Firepit post here!</h1>
    <div class="heading">
      <div class="circle">1</div>
      <h2>Add your name</h2>
    </div>
    <div class="add">
      <div class="form">
        <input v-model="name" placeholder="Your Name">
        <p></p>
		</div>
	</div>
	<div class="heading">
      <div class="circle">2</div>
      <h2>Add a Date / Time</h2>
    </div>
    <div class="add">
      <div class="form">
        <input v-model="date" placeholder="mm/dd/yy @ 12:00am">
        <p></p>
	</div>
	</div>
	<div class="heading">
      <div class="circle">3</div>
      <h2>Add a Title</h2>
    </div>
    <div class="add">
      <div class="form">
        <input v-model="title" placeholder="Title">
        <p></p>
	</div>
	</div>
	<div class="heading">
      <div class="circle">4</div>
      <h2>Add a picture</h2>
	</div>
	<div class="add">
		<div class="form">
			<input type="file" name="photo" @change="fileChanged">
    </div>
	</div>
	<br>
	<div class="heading">
      <div class="circle">5</div>
      <h2>Add some words, thoughts, a story, a poem, etc!</h2>
	</div>
        <textarea class="textInput" v-model="post" placeholder="Add Post Text Here"></textarea>
        <p></p>
        <button @click="upload">Upload Post</button>
      <div class="upload" v-if="addPost">
		<h2>{{addPost.title}}</h2>
		<p>By {{addPost.name}}</p>
		<p>Posted on {{addPost.date}}</p>
        <p>{{addPost.post}}</p>
        <img :src="addPost.path" />
      </div>
    <!-- </div> -->
  <div class="heading">
      <div class="circle">6</div>
      <h2>Edit/Delete an Post</h2>
    </div>
    <div class="edit">
      <div class="form">
        <input v-model="findTitle" placeholder="Search by Title">
        <div class="suggestions" v-if="suggestions.length > 0">
          <div class="suggestion" v-for="s in suggestions" :key="s.id" @click="selectPost(s)">{{s.title}}
          </div>
        </div>
      </div>
      <div class="upload" v-if="findPost">
        <input v-model="findPost.title">
        <p></p>
        <textarea v-model="findPost.post"></textarea>
        <p></p>
        <img :src="findPost.path" />
      </div>
      <div class="actions" v-if="findPost">
        <button @click="deletePost(findPost)">Delete</button>
        <button @click="editPost(findPost)">Edit</button>
      </div>
    </div>
</div>
</template>

<style scoped>
.image h2 {
  font-style: italic;
  font-size: 1em;
}

.heading {
  display: flex;
  margin-bottom: 20px;
  margin-top: 20px;
}

.heading h2 {
  margin-top: 8px;
  margin-left: 10px;
}

.add,
.edit {
  display: flex;
}

.circle {
  border-radius: 50%;
  width: 18px;
  height: 18px;
  padding: 8px;
  background: #333;
  color: #fff;
  text-align: center
}

/* Form */
input,
textarea,
select,
button {
  font-family: 'Montserrat', sans-serif;
  font-size: 1em;
}

.textInput {
  width: 100%;
  height: 100px;
}

.form {
  margin-right: 50px;
}


/* Uploaded images */
.upload h2 {
  margin: 0px;
}

.upload img {
  max-width: 300px;
}

/* Suggestions */
.suggestions {
  width: 200px;
  border: 1px solid #ccc;
}

.suggestion {
  min-height: 20px;
}

.suggestion:hover {
  background-color: #5BDEFF;
  color: #fff;
}

</style>

<script>
import axios from 'axios';
export default {
  name: 'Add',
  data() {
    return {
      title: "",
      post: "",
      name: "",
      date: "",
      file: null,
      addPost: null,
      posts: [],
      findTitle: "",
      findPost: null,
    }
  },
  computed: {
    suggestions() {
      let posts = this.posts.filter(post => post.title.toLowerCase().startsWith(this.findTitle.toLowerCase()));
      return posts.sort((a, b) => a.title > b.title);
    }
  },
  created() {
    this.getPosts();
  },
  methods: {
    fileChanged(event) {
      this.file = event.target.files[0]
    },
    async upload() {
      try {
        const formData = new FormData();
        formData.append('photo', this.file, this.file.name)
        let r1 = await axios.post('/api/photos', formData);
        let r2 = await axios.post('/api/posts', {
          title: this.title,
          path: r1.data.path,
          post: this.post,
          name: this.name,
          date: this.date,
        });
        this.addPost = r2.data;
      } catch (error) {
        console.log(error);
      }
    },
    async getPosts() {
      try {
        let response = await axios.get("/api/posts");
        this.posts = response.data;
        return true;
      } catch (error) {
        console.log(error);
      }
    },
    selectPost(post) {
      this.findTitle = "";
      this.findPost = post;
    },
    async deletePost(post) {
      try {
        await axios.delete("/api/posts/" + post._id);
        this.findPost = null;
        this.getPosts();
        return true;
      } catch (error) {
        console.log(error);
      }
    },
    async editPost(post) {
      try {
        await axios.put("/api/posts/" + post._id, {
          title: this.findPost.title,
          post: this.findPost.post,
          date: this.findPost.date,
          name: this.findPost.name,
        });
        this.findPost = null;
        this.getPosts();
        return true;
      } catch (error) {
        console.log(error);
      }
    },
  },
}
</script>