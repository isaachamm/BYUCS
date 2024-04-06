<template>
  <div id="app">
    <div id="menu">
      <div id="brand">
        <router-link to="/">
          <img src="/images/logo.png">
        </router-link>
      </div>
      <div id="side">
        <router-link to="/browse">
          <div class="menu-item browse">
            <img src="/images/globe.png">
            <p>Browse</p>
          </div>
        </router-link>
        <router-link to="/cart">
          <div class="menu-item">
            <img src="/images/love.png">
            <!-- Changed this so that it accesses length of the array instead of just "0" -->
            <p>{{ $root.$data.cart.length }} items</p>
          </div>
        </router-link>
      </div>
    </div>  
    <router-view />
    <div class="footer">
      You can see my source code: <a href="https://github.com/BYUCS260/grocery-store-isaachamm"> HERE!!!</a>
    </div>
  </div>
</template>


<style>
* {
  box-sizing: border-box;
}

body {
  margin: 50px 100px;

}

#menu {
  display: grid;
  grid-template-columns: 1fr 1fr 1fr;
  grid-column-gap: 5px;
  grid-template-areas: "none brand side";
  margin-bottom: 50px;
}

#menu a {
  color: #B84901;
}

#brand {
  grid-area: brand;
  display: flex;
  justify-content: center;
}

#brand img {
  height: 200px;
}

#side {
  grid-area: side;
  display: flex;
  justify-content: flex-end;
}

#side img {
  width: 50px;
}

.menu-item {
  display: flex;
  flex-direction: column;
}

.menu-item p {
  margin: 0px;
}

.browse {
  margin-right: 50px;
}

.footer {
  display: flex;
  width: 100%;
  height: 275px;
  justify-content: center;
  align-items: center;
  background-color: rgb(146, 77, 77);
  font-family: Impact, Haettenschweiler, 'Arial Narrow Bold', sans-serif;
  font-size: 3em;
}


@media only screen and (max-width: 460px) {
  .footer a {
    font-size: 1em;
  }
  .footer {
    font-size: 1em;
  }
}

@media only screen and (min-width: 461px) and (max-width: 1200px) {
.footer a {
    font-size: 2em;
  }
  .footer {
    font-size: 2em;
  }
}

@media only screen and (min-width: 1201px) {
.footer a {
    font-size: 5em;
  }
}
</style>
