<template>
  <div>
    <h3>Search by country!</h3>
      <form class="pure-form">
        <i class="fas fa-search"></i><input v-model="searchText" />
      </form>
    <DirectoryView :directory="directory" />
  </div>
</template>

<style> 

form {
  margin: 10px;
  justify-content: center;
}

input {
  justify-content: center;
}

</style>

<script>

import DirectoryView from "../components/DirectoryView.vue"

export default {
  name: 'HomeView',
  components: {
    DirectoryView,
  },
  data() {
    return {
      searchText: '',
    }
  },
  computed: {
    directory() {
      return this.$root.$data.directory.filter(person => 
        person.country.toLowerCase().search(this.searchText.toLowerCase()) >= 0);
    }

  }
}
</script>
