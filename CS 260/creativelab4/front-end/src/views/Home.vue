<template>
<div>
  <div class="text">
    <h1>Welcome to the Firepit!</h1>
    <h2>You might be wondering: </h2> 
    <h2>What is a group blog?</h2>
    <h2>How does it work?</h2>
    <h2>Do I really want to be <i>that</i> person that's always blogging about their life?</h2>
    <p>Follow the simple tutorial below to learn more!</p>
    <hr/>
  </div>
  <div class="tutorial">
    <p>1) First, add your name</p>
    <p>2) Then, come up with a title for your blog post</p>
      <p>——Example titles include: <i>How to get married in 60 days! (For BYU students),
            How to live on a budget of $1 / day: My experience,</i> and 
            <i>Why you should drive Uber: A guide to the ultimate side hustle</i>
    <p>3) Next, make sure you have a picture ready to upload!</p>
      <p><i>Something minimalistic to appeal to the audience's attention...</i></p>
        <img src="../../public/images/DS-WP-2.png" />
      <p><i>Or something more active to keep them entertained!</i></p>
        <img src="../../public/images/DS-WP-7.jpg" />
    <p>4) Don't forget to mark the time and date of the post...</p>
    <p>5) Finally, write to your heart's content on any topic that comes to mind!</p>
  </div>
</div>
</template>

<style scoped>

.text {
  text-align: center;
}



/* Masonry */
*,
*:before,
*:after {
  box-sizing: inherit;
}

.image-gallery {
  column-gap: 1.5em;
}

.image {
  margin: 0 0 1.5em;
  display: inline-block;
  width: 100%;
}

img {
  width: 100%;
}

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
  name: 'Home',
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
