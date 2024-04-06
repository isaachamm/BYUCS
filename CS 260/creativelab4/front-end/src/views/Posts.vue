<template>
<div class="home">
  <section class="image-gallery">
    <div class="image" v-for="post in posts" :key="post.id">
      <h2>{{post.title}}</h2>
      <p>{{post.name}}</p>
      <p>{{post.date}}</p>
      <p v-if="post.post">{{post.post}}</p>
      <img :src="post.path" />
    </div>
  </section>
</div>
</template>

<style scoped>
.image h2 {
  font-style: italic;
}

/* Masonry */
*,
*:before,
*:after {
  box-sizing: inherit;
}

img {
  width: 100%;
}

/* Masonry on small screens */
@media only screen and (min-width: 550px) {
  img {
    width: 400px;
  }
}
</style>

<script>
// @ is an alias to /src
import axios from 'axios';

export default {
  name: 'Posts',
  data() {
    return {
      posts: [],
    }
  },
  created() {
    this.getPosts();
  },
  methods: {
    async getPosts() {
      try {
        let response = await axios.get("/api/posts");
        this.posts = response.data;
        return true;
      } catch (error) {
        console.log(error);
      }
    },
  }
}
</script>
