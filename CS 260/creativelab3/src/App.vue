<template>
  <div id="app">
    <nav>
      <router-link to="/">Home</router-link> |
      <router-link to="/browse">Browse by Country</router-link> |
      <router-link to="contacts">Contact List</router-link>
    </nav>
    <router-view/>
    <div class="footer">
      <h3>You can see my source code: <a href="https://github.com/isaachamm/cs260-creativelab3">here</a></h3>
    </div>
  </div>
</template>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

nav {
  padding: 30px;
}

nav a {
  font-weight: bold;
  color: #2c3e50;
}

nav a.router-link-exact-active {
  color: #42b983;
}

.footer{
  display: flex;
  align-content: center;
  justify-content: center;
  background-color: rgb(206, 255, 47);
  height: 150px;
}

</style>
