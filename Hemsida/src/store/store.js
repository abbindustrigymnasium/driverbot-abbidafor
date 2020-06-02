// sparar variabler som skickas mellan komponenterna

// importerar vue och vuex biblioteken
// vuex är det bibliotek som hjälper till att dela variabler mellan komponenterna
import Vue from 'vue'
import Vuex from 'vuex'
Vue.use(Vuex)

// root state object.
// each Vuex instance is just a single state tree.
// default inställningar mot maqiuatto anges här
const state = {
  loadingStatus: "not loading",
  // logger:"",
  logger: [],
  connect: false,
  loglimit: 10,
  dialog: false,
  user: {
    name: "ida.forsman@abbindustrigymnasium.se",
    password: "passworddriverbot",
    port: 8883,
    adress: "maqiatto.com"
  }
}

// mutations are operations that actually mutates the state.
// each mutation handler gets the entire state tree as the
// first argument, followed by additional payload arguments.
// mutations must be synchronous and can be recorded by plugins
// for debugging purposes.
// ändra från applikationen så använder man dessa metoder
const mutations = {
  Loading_Status(state, Status) {
    state.loadingStatus = Status;
  },
  clear_Logger(state) {
    // state.logger = "";
    state.logger = [];
  },
  Connect_(state, status) {
    state.connect = status;
  },
  Set_User(state, data) {
    state.user = data;
  },
  add_To_Logger(state, text) {
    if (state.loglimit <= state.logger.length) {
      state.logger.shift();
    }
    state.logger.push(text);
    // state.logger += text;
  },
  Save_: (state, user) => {

    state.user = user;
  },

  Dialog_: (state, dialog) => {
    state.dialog = dialog;
  }
}

// actions are functions that cause side effects and can involve
// asynchronous operations.
// funktioner som ändrar state
const actions = {
  LoadingStatus: ({
    commit
  }, Status) => {

    commit('Loading_Status', Status);
  },
  addToLogger: ({
    commit
  }, text) => {

    commit('add_To_Logger', text);
  },
  clearLogger: ({
    commit
  }) => {

    commit('clear_Logger');
  },
  Connect: ({
    commit
  }, status) => {

    commit('Connect_', status);
  },
  SetUser: ({
    commit
  }, data) => {

    commit('Set_User', data);
  },

  Dialog: ({
    commit
  }, dialog) => {

    commit('Dialog_', dialog);
  },

  Save: ({
    commit
  }, user) => {

    commit('Save_', user);
  },
}

// getters are functions
// getters läser ut state
const getters = {
  logger: state => state.logger,
  connected: state => state.connect,
  GetUser: state => state.user,
  dialog: state => state.dialog
}

// A Vuex instance is created by combining the state, mutations, actions,
// and getters.
// initierar state hantering i applikationen med de olika läs och uppdateringsfuntionerna
export default new Vuex.Store({
  state,
  getters,
  actions,
  mutations
})