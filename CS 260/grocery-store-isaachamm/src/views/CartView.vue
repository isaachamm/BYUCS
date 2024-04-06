<template>
	
<div class="wrapper">
	<h1>Your Shopping Cart: Current items</h1>
    <div>
    <p v-show="$root.$data.productCart.length ===0">Cart is empty! Add an item to begin shopping!</p>
    </div>
    <div class="product-grid">
    <div class="product-grid-item" v-for="cartItem in $root.$data.productCart" :key="cartItem.id">
      <div class="info">
        <h1>{{cartItem.name}}</h1>
        <h1>{{cartItem.counter}}</h1>
      </div>
      <div class="price right">
        <h2>{{cartItem.price}}</h2>
        <button class="auto" @click="removeFromCart(cartItem)">Remove from Cart</button>
      </div>
    </div>
  </div>
</div>
</template>

<script>
export default {
	name: "CartView",
  props: {
		cart: Array,
	},
	methods: {
		removeFromCart(cartItem) {
			let index = this.$root.$data.cart.indexOf(cartItem);
			if (index > -1)
			this.$root.$data.cart.splice(index,1);
		}
	}

}
</script>

<style scoped>
.wrapper {
  display: flex;
  align-items: center;
  justify-content: center;
  flex-wrap: wrap;
}

h1 {
  width: 100%;
  justify-self: center;
  text-align: center;
}

.product-grid {
  margin-top: 20px;
  display: grid;
  flex-wrap: wrap;
  justify-content: space-around;
}

.product-grid-item {
  gap: 10px;
  display: flex;
  align-content: center;
  border: solid 3px black;
}

.product {
  margin: 10px;
  margin-top: 50px;
  width: 200px;
}

.product img {
  border: 2px solid #333;
  height: 250px;
  width: 200px;
  object-fit: cover;
}

.product .image {
  display: flex;
  justify-content: center;
  margin-bottom: 5px;
}

.info {
  background: rgb(245, 211, 91);
  padding: 10px 30px;
  height: 80px;
  width: 300px;
  align-content: center;
}

.info h1 {
  font-size: 16px;
}

.info h2 {
  font-size: 14px;
}

.info p {
  margin: 0px;
  font-size: 10px;
  text-align: center;
}


.price {
  display: flex;
  align-items: center;
}

.price h2{
  padding: 5px 10px;
}

button {
  height: 50px;
  background: pink;
  border: none;
}

.auto {
  margin-left: auto;
}

</style>
