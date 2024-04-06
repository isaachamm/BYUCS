import Vue from 'vue'
import App from './App.vue'
import router from './router'
import mock from '../mock-data'

let data = {
  directory: mock,
  contacts: [],
}

// Vue.config.productionTip = false

new Vue({
  router,
  data,
  render: h => h(App)
}).$mount('#app')
