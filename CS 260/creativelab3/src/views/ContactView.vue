<template>
	
<div class="wrapper">
	<h1>Your Contact List: Current Contacts</h1>
    <div>
    <p v-show="$root.$data.contacts.length ===0">Contact list is empty! Explore contacts to make connections!</p>
    </div>
    <div class="contact-table">
    <div class="contact-table-item" v-for="contact in $root.$data.contacts" :key="contact.id">
        <div class="text">
        <h1>{{contact.first_name}} {{contact.last_name}}</h1>
        </div>
        <div>
        <img :src="'/creative-lab-images/' + (contact.id%10) + '.jpeg'"/>
        </div>
        <div class="text">
        <h2>{{contact.university}}</h2>
        </div>
        <button class="auto" @click="removeFromContacts(contact)">Remove from contacts</button>
    </div>
  </div>
</div>
</template>

<style scoped>

button {
  color: whitesmoke;
  background-color: rgb(177, 0, 0);
}

h1 {
  width: 100%;
}

.wrapper {
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  align-content: center;
}

.contact-table {
  text-align: center;
  display: grid;
  grid-template: 1fr 1fr 1fr 1fr;
  align-content: center;
}

.contact-table-item {
  display: flex;
  justify-content: center;
  align-content: center;
  text-align: center;
  flex-wrap: wrap;
  border-bottom: solid 1px black;
  margin-top: 5px;
}

.text {
  display: flex;
  align-self: center;
  width: 250px;
  margin: 10px;
}

.auto {
  display: flex;
  align-self: center;
  align-content: center;
}

</style>

<script>
export default {
	name: "ContactView",
  props: {
		contacts: Array,
	},
	methods: {
		removeFromContacts(contact) {
			let index = this.$root.$data.contacts.indexOf(contact);
			if (index > -1)
			this.$root.$data.contacts.splice(index,1);
		}
	}

}
</script>