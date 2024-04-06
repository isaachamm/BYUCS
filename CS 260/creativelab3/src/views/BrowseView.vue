<template>
<div>
  <h4><u>Common Countries</u></h4>
	<div class="pure-menu pure-menu-horizontal">
		<ul class="pure-menu-list">
			<li class="pure-menu-item"><a @click="select('United States')" href="#" class="pure-menu-link">United States 🇺🇸</a></li>
			<li class="pure-menu-item"><a @click="select('Canada')" href="#" class="pure-menu-link">Canada 🇨🇦</a></li>
			<li class="pure-menu-item"><a @click="select('Mexico')" href="#" class="pure-menu-link">Mexico 🇲🇽</a></li>
			<li class="pure-menu-item"><a @click="select('Brazil')" href="#" class="pure-menu-link">Brazil 🇧🇷</a></li>
			<li class="pure-menu-item"><a @click="select('China')" href="#" class="pure-menu-link">China 🇨🇳</a></li>
			<li class="pure-menu-item"><a @click="select('United Kingdom')" href="#" class="pure-menu-link">United Kingdom 🇬🇧</a></li>
			<li class="pure-menu-item"><a @click="select('Japan')" href="#" class="pure-menu-link">Japan 🇯🇵</a></li>
		</ul>
  </div>
    <DirectoryView :directory="directory" />
</div>
</template>

<script>
import DirectoryView from "../components/DirectoryView.vue"
export default {
  name: 'BrowseView',
  components: {
	DirectoryView
	},
  data() {
    return {
      country: '',
    }
  },
  computed: {
    directory() {
      return this.$root.$data.directory.filter(person => person.country === this.country);
    }
  },
  methods: {
    select(country) {
      this.country = country;
    }
  }
}
</script>