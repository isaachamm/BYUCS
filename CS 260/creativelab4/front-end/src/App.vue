<template>
<div id="app">
  <div class="header">
    <router-link to="/">
      <img class="icon" src="../public/images/firepit.png" />
    </router-link>
    <div class="title">
      <h1>The Firepit: A group blog. Share your thoughts with us!</h1>  
      <router-link to="/">Home</router-link> |
      <router-link to="/posts">The Firepit</router-link> |
      <router-link to="/add">Add a post!</router-link>
    </div>
  </div>
  <div class="content">
    <router-view />
  </div>
  <div class="footer">
    <!-- Add git repository here -->
    <a href="https://github.com/isaachamm/cs260-creativelab4">Github repo</a>
  </div>
</div>
</template>

<style>
html {
  box-sizing: border-box;
}

body {
  font-family: 'Montserrat', sans-serif;
  font-size: 16px;
  background: #fff;
  padding: 0px;
  margin: 0px;
}

/* Header */
.header {
  display: flex;
  padding: 10px 100px 0px 100px;
  background-color: #fbb982;
  color: #1C454F;
}

.icon {
  width: 40px;
  margin-top: 20px;
  margin-right: 20px;
}

.title {
  margin-top: 5px;
  margin-bottom: 5px;
}

.title h1 {
  font-size: 30px;
}

.content {
  padding: 20px 100px;
  min-height: 500px;
}

/* Footer */
.footer {
  height: 50px;
  padding: 20px 100px 0px 100px;
  background: #e3e3e3;
  font-size: 12px;
}

.footer a {
  color: #000;
}

h1 {
  font-size: 20px;
}

h2 {
  font-size: 14px;
}
</style>
