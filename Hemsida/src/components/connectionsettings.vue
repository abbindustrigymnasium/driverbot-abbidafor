<template>
    <v-dialog v-model="dialog" persistent  max-width="290" height="290">
          <v-card>
            <v-card-title class="headline">Anslutning till Server</v-card-title>

            <v-card-text style="height: 300px;">
              <v-text-field v-model="name" label="Name" filled></v-text-field>

              <v-text-field v-model="password" label="MQTT Password" filled></v-text-field>

              <v-text-field v-model="port" label="Port" filled></v-text-field>
              <v-text-field v-model="adress" label="Adress" filled></v-text-field>
            </v-card-text>

            <v-card-actions>
              <v-spacer></v-spacer>

              <v-btn color="green darken-1" text @click="save()">Spara</v-btn>
            </v-card-actions>
          </v-card>
    </v-dialog>
</template>

<script>
export default {
    name: "connectionsettings",
   
      // de egenskaper som finns för komponenten
  data() {
    return {
        dialog: false,
        name: "",
        password: "",
        port: "",
        adress: ""
    };
  },

// när man skapar upp komponenten så körs created funktionen
  created() {
    let User = this.$store.getters.GetUser;
    this.name = User.name;
    this.password = User.password;
    this.port = User.port;
    this.adress = User.adress;
    this.dialog = this.$store.getters.dialog;
  },

computed: {  
},

// ändra annslutnings konfiguration
  methods: {
    save() {
      let User = {
        name: this.name,
        password: this.password,
        port: this.port,
        adress: this.adress
      };

    // om man ändrar anslutningsuppgifter till maqiatto sparas det
      this.$store.dispatch("Save", User);

    // uppdaterar state om dialoen ska visas
      this.dialog = false;
      this.$store.dispatch("Dialog", this.dialog);      
    }
  }
}
</script>