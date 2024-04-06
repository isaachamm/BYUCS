<template>
<div class="product-grid">
    <div class="product-grid-item" v-for="person in directory" :key="person.id">
      <div>
        <h1>{{person.first_name}} {{person.last_name}}</h1>
      </div>
      <div>
        <img :src="'/creative-lab-images/' + (person.id%10) + '.jpeg'"/>
      </div>
      <div>
        <p>Spirit Animal: {{person.animal}}</p>
        <h4>{{person.country}}</h4>
        <h2>{{person.university}}</h2>
        <button @click="addToContacts(person)">Add to Contacts</button>
      </div>
    </div>
</div>
</template>

<style>

img {
  width: 100%;
  height: 250px;
  width: 200px;
  object-fit: cover;
 }

button {
  padding: 10px;
  background-color: rgb(206, 255, 47);
  border: double solid 1.5px silver;
  margin-bottom: 10px;
}

.product-grid {
  justify-self: center;
  display: grid;
  grid-template-columns: 1fr;
}

.product-grid-item {
  border: solid 2px silver;
}

@media only screen and (min-width: 461px) and (max-width: 1200px) {
  .product-grid {
    grid-template-columns: 1fr 1fr;
  }
}

@media only screen and (min-width: 1201px) {
  .product-grid {
    grid-template-columns: 1fr 1fr 1fr;
  }
}

</style>

<script>
export default {
  name: 'DirectoryView',
  props: {
    directory: Array
  },
  methods: {
    addToContacts(person) {
        this.$root.$data.contacts.push(person);
        // if (this.$root.$data.contacts.length === 0) {
        //   this.$root.$data.contacts.push(person);
        // }
        // else {
        //   let counter = 0;
        //   for (let contact in this.$root.$data.contacts) {
        //     if (person.id === contact.id) {
        //       console.log("cannot add – has already been added!")
        //     }
        //     else if (counter === this.$root.$data.contacts.length) {
        //       this.$root.$data.contacts.push(person);
        //     }
        //     counter++;
        //   }
        // }
      }
  }
}
</script>